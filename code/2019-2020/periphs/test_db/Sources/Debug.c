/*
 * Debug.c
 *
 *  Created on: Nov 30, 2019
 *      Author: User
 */


#include "Debug.h"

// bit order : A-G+DP, map for digits 0-9,A-F and '-' for out of range nb
//											0			1			2			3			4			5			6			7			8			9			A			B			C			D			E			F			-
const unsigned int debugDisplayNbMap[17]={0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110, 0b11101110, 0b00111110, 0b10011100, 0b01111010, 0b10011110, 0b10001110 ,0b00000010};

void debug_init(){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTA_MASK;

	//Initialize the Red LED (PTB18)
	PORTB_PCR18 = PORT_PCR_MUX(1);
	GPIOB_PSOR = DEBUG_RED_Pin;
	GPIOB_PDDR |= DEBUG_RED_Pin;
	//Initialize the Green LED (PTB19)
	PORTB_PCR19 = PORT_PCR_MUX(1);
	GPIOB_PSOR = DEBUG_GREEN_Pin;
	GPIOB_PDDR |= DEBUG_GREEN_Pin;
	//Initialize the Blue LED (PTD1) //WARNING : BLUE LED attached to same pin as SW_USER2
	PORTD_PCR1 = PORT_PCR_MUX(1);
	GPIOD_PSOR = DEBUG_BLUE_Pin;
	GPIOD_PDDR |= DEBUG_BLUE_Pin;


	//PTD1 (SW_USER_2) & PTD3 (SW_USER_1)//WARNING : BLUE LED attached to same pin as SW_USER2
	PORTD_PCR1 = PORT_PCR_MUX(1);
	PORTD_PCR3 = PORT_PCR_MUX(1);
	GPIOD_PDDR &=~ (1<<1);
	GPIOD_PDDR &=~ (1<<3);

	//PTE2-5 : Rotary switch (2:LSB, 5:MSB);
	PORTE_PCR2 = PORT_PCR_MUX(1);
	PORTE_PCR3 = PORT_PCR_MUX(1);
	PORTE_PCR4 = PORT_PCR_MUX(1);
	PORTE_PCR5 = PORT_PCR_MUX(1);
	GPIOE_PDDR &=~ (1<<2);
	GPIOE_PDDR &=~ (1<<3);
	GPIOE_PDDR &=~ (1<<4);
	GPIOE_PDDR &=~ (1<<5);

	//Display init
	PORTC_PCR5 = PORT_PCR_MUX(1);
	GPIOC_PDDR |= DISP_CLK_PIN;
	PORTC_PCR6 = PORT_PCR_MUX(1);
	GPIOC_PDDR |= DISP_SIN_PIN;
	PORTC_PCR10 = PORT_PCR_MUX(1);
	GPIOC_PDDR |= DISP_LATCH_PIN;
	DISP_CLK_OFF;
	DISP_SIN_OFF;
	DISP_LATCH_ON;

	//UART init
	uart_init(BAUDRATE);
	ADC_init();
	BatteryVoltage();
	lptmr_conf();
}
unsigned char debug_getRotarySW(){
	//return (GPIOE_PDIR & 0x003C)>>2;
	return GPIOE_PDIR;
}
unsigned char debug_getUserSW1(void){
	return !(GPIOD_PDIR & (1<<3));
}
unsigned char debug_getUserSW2(void){
	return !(GPIOD_PDIR & (1<<1));
}

void debug_displaySendRaw(uint8_t data){
	DISP_LATCH_OFF;
	for (int i=0; i<8;i++){
		if(data & (1<<i)){
			DISP_SIN_ON;
		}else {
			DISP_SIN_OFF;
		}			
		DISP_CLK_ON;
		DISP_CLK_OFF;
	}
	DISP_LATCH_ON;
}
void debug_displaySendNb(int8_t nb){
	if(nb<0){
		nb=-nb;
		debug_displaySendRaw(debugDisplayNbMap[nb>16 ? 16 : nb]|0b00000001);
	}else{
		debug_displaySendRaw(debugDisplayNbMap[nb>16 ? 16 : nb]);
	}
}

#define BUFLEN 256

static uint8_t _tx_buffer[sizeof(RingBuffer) + BUFLEN] __attribute__ ((aligned(4)));
static uint8_t _rx_buffer[sizeof(RingBuffer) + BUFLEN] __attribute__ ((aligned(4)));

static RingBuffer *const tx_buffer = (RingBuffer *) &_tx_buffer;
static RingBuffer *const rx_buffer = (RingBuffer *) &_rx_buffer;

void UART0_IRQHandler(){
	int status = UART0_S1;

	if ((status & UART_S1_TDRE_MASK) && !buf_isempty(tx_buffer)) {
		UART0_D = buf_get_byte(tx_buffer);
		if(buf_isempty(tx_buffer))
			UART0_C2 &= ~UART_C2_TIE_MASK;
	}

	if ((status & UART_S1_RDRF_MASK) && !buf_isfull(rx_buffer)) {
		buf_put_byte(rx_buffer, UART0_D);
		if(buf_isfull(rx_buffer))
			UART0_C2 &= ~UART_C2_RIE_MASK;
	}
}

int uart_write(const char *p, int len){
	for(int i=0; i<len; i++) {
		while(buf_isfull(tx_buffer));
		buf_put_byte(tx_buffer, *p++);
		UART0_C2 |= UART_C2_TIE_MASK;
	}
	return len;
}
void uart_writeNb(int n){
	int d=1;
	if(n<0){
		n=-n;
		while(buf_isfull(tx_buffer));
		buf_put_byte(tx_buffer,'-');
	}
	while((10*d)<=n)d*=10;
	while(d>0){
		while(buf_isfull(tx_buffer));
		buf_put_byte(tx_buffer,((n/d)%10)+0x30);
		d/=10;
	}
}
int uart_write_err(const char *p, int len){
	int i;
	__disable_irq();
	for(i=0; i<len; i++) {
		while((UART0_S1 & UART_S1_TDRE_MASK) == 0);
		UART0_D = *p++;
	}
	__enable_irq();
	return len;
}

int uart_read(char *p, int len){
	int i = 0;
	while((i<len) && !buf_isempty(rx_buffer)){
		*p++ = buf_get_byte(rx_buffer);
		UART0_C2 |= UART_C2_RIE_MASK;
		i++;
	}
	return i;
}

void uart_init(int baudrate){

#ifdef UARTXBEE
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE_PCR20 = PORT_PCR_MUX(4);
	PORTE_PCR21 = PORT_PCR_MUX(4);
#else
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);
#endif
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);


	UART0_C2 = 0;
	UART0_C1 = 0;
	UART0_C3 = 0;
	UART0_S2 = 0;     

#define OVER_SAMPLE 16
	uint16_t divisor = (CORE_CLOCK / OVER_SAMPLE) / baudrate;
	UART0_C4 = UARTLP_C4_OSR(OVER_SAMPLE - 1);
	UART0_BDH = (divisor >> 8) & UARTLP_BDH_SBR_MASK;
	UART0_BDL = (divisor & UARTLP_BDL_SBR_MASK);

	// Initialize transmit and receive circular buffers
	buf_reset(tx_buffer, BUFLEN);
	buf_reset(rx_buffer, BUFLEN);

	// Enable the transmitter, receiver, and receive interrupts
	UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK;
	enable_irq(INT_UART0);
}

void buf_reset(RingBuffer *buf, int size){
	buf->head = buf->tail = 0;
	buf->size = size;
}

int buf_len(const RingBuffer *buf){
	int len = buf->tail - buf->head;
	if (len < 0)len += buf->size;
	return len;
}

int buf_isfull(const RingBuffer *buf){
	return buf_len(buf) == (buf->size-1);
}

int buf_isempty(const RingBuffer *buf){
	return buf->head == buf->tail;
}

int advance(uint16_t i, uint16_t size){
	if (++i >= size)i=0;
	return i;
}

uint8_t buf_get_byte(RingBuffer *buf){
	const uint8_t item = buf->data[buf->head];
	buf->head = advance(buf->head, buf->size);
	return item;
}

void buf_put_byte(RingBuffer *buf, uint8_t val){
	buf->data[buf->tail] = val;
	buf->tail = advance(buf->tail, buf->size);
}

/*********** LPTMR ***********/
void lptmr_conf(void){
	
	SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
	PORTA_PCR19 = PORT_PCR_MUX(6);//LPTMR0_ALT2 
	
	// enable interrupts 19 (TPM = FTM2)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 28);			// clear pending interrupt 28
	NVIC_ISER |= (1 << 28);			// enable interrupt 28
		
	// Control Status Register
	LPTMR0_CSR |=  LPTMR_CSR_TEN_MASK; 		 //Enable timer counter 
	LPTMR0_CSR &= ~LPTMR_CSR_TMS_MASK ;						//Timer mode counter is selected
	
	// Prescaler Register
	LPTMR0_PSR = LPTMR_PSR_PRESCALE(PSC_POWER);
	LPTMR0_PSR &= ~LPTMR_PSR_PBYP_MASK;		//Presclaer enable	(to check...)			
	LPTMR0_PSR |= LPTMR_PSR_PCS(2);			// Prescaler clock select
	
	// ARR
	LPTMR0_CMR = ARR_LPTMR;					// ARR at the max
	
	LPTMR0_CSR |= LPTMR_CSR_TIE_MASK ;		// Enable Interruption (to do at the end of the initialization)
	
	
}

void LPTMR0_IRQHandler(void){
	BatteryVoltage();
	//Clear flag interrupt
	LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;
	
	
}


/************** ADC0 *****************/

void ADC_init(void){
	// turn on ADC0 clock
		SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
		// ADC0 clock configuration : 													WARNING : maybe not compatible with 48MHz system clock ! to check
			ADC0_CFG1 |= 0x01;				// clock is bus clock divided by 2 = 24 MHz
			
			// ADC0 resolution    
			ADC0_CFG1 |= 0x08;				// resolution 10 bit, max. value is 1023

			// ADC0 conversion mode
			ADC0_SC3 = 0x00;				// single conversion mode
}

void BatteryVoltage(void) {

	uint16_t BattMeasurement;
	
	ADC0_CFG2 |= 0x10;							// select B side of the MUX
	//ADC0_SC1A |= ADC_SC1_AIEN_MASK;				//Interruption enabled
	ADC0_SC1A  =  3;							// set ADC0 channel 11
	while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
	BattMeasurement = (int)((ADC_SCALING*ADC0_RA)/ADC_RESOLUTION);	
		
	uart_write("La batterie est de ", 20);
	uart_writeNb(BattMeasurement);
	uart_write("mV.\r\n", 5);
	
	ADC0_SC1A  =  11;	//For the camera
	
}


