/*
 * Debug.h
 *
 *  Created on: Nov 30, 2019
 *      Author: User
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <MKL25Z4.h>

#define CORE_CLOCK 48000000UL

#ifndef BAUDRATE
	#define BAUDRATE 115200
#endif

#define UARTXBEE //uncomment this line to enable uart on xbee module. By default uart is on opensda debugger

#define DEBUG_RED_Pin		(1 << 18)
#define DEBUG_GREEN_Pin		(1 << 19)
#define DEBUG_BLUE_Pin		(1 << 1)
#define DEBUG_CAM_LED_Pin   (1 << 12)

#define DEBUG_RED_OFF		(GPIOB_PSOR = DEBUG_RED_Pin)
#define DEBUG_RED_ON		(GPIOB_PCOR = DEBUG_RED_Pin)
#define DEBUG_GREEN_OFF		(GPIOB_PSOR = DEBUG_GREEN_Pin)
#define DEBUG_GREEN_ON		(GPIOB_PCOR = DEBUG_GREEN_Pin)
#define DEBUG_BLUE_OFF		(GPIOD_PSOR = DEBUG_BLUE_Pin)
#define DEBUG_BLUE_ON		(GPIOD_PCOR = DEBUG_BLUE_Pin)
#define DEBUG_CAM_LED_ON    (GPIOC_PSOR = DEBUG_CAM_LED_Pin)
#define DEBUG_CAM_LED_OFF   (GPIOC_PCOR = DEBUG_CAM_LED_Pin)

#define DISP_CLK_PIN		(1<<5)
#define DISP_SIN_PIN 		(1<<6)
#define DISP_LATCH_PIN 		(1<<10)

#define DISP_CLK_OFF		(GPIOC_PCOR = DISP_CLK_PIN)
#define DISP_CLK_ON			(GPIOC_PSOR = DISP_CLK_PIN)
#define DISP_SIN_OFF		(GPIOC_PCOR = DISP_SIN_PIN)
#define DISP_SIN_ON			(GPIOC_PSOR = DISP_SIN_PIN)
#define DISP_LATCH_OFF		(GPIOC_PCOR = DISP_LATCH_PIN)
#define DISP_LATCH_ON		(GPIOC_PSOR = DISP_LATCH_PIN)

#define LPTMR_ARR 65535

/**
  * @brief  Initialisation of all pins related to debug (LEDs, Cam, rotary switch, display, UART)
  * @param  None
  * @retval None
  */
void debug_init();

/**
  * @brief  Initialisation of all clocks related to debug (LEDs, Cam, rotary switch, display, UART)
  * @param  None
  * @retval None
  */
void clock_init();

//input stuff

/**
  * @brief  Get rotary switch value
  * @param  None
  * @retval unsigned char = rotary switch value
  */
unsigned char debug_getRotarySW(void);

/**
  * @brief  Get switch 1 value
  * @param  None
  * @retval unsigned char = switch 1 value
  */
unsigned char debug_getUserSW1(void);

/**
  * @brief  Get switch 2 value
  * @param  None
  * @retval unsigned char = switch 2 value
  */
unsigned char debug_getUserSW2(void);

//7segment dsplay stuff
/**
  * @brief  Send raw data to display
  * @param  uint8_t data = raw data to send
  * @retval none
  */
void debug_displaySendRaw(uint8_t data);

/**
  * @brief  Send number data to display
  * @param  int8_t nb = number data to send
  * @retval none
  */
void debug_displaySendNb(int8_t nb);


static inline void enable_irq(int n) {
    NVIC_ICPR |= 1 << (n - 16);
    NVIC_ISER |= 1 << (n - 16);			
}
static inline void __enable_irq(void)	{ asm volatile ("cpsie i"); }
static inline void __disable_irq(void)  { asm volatile ("cpsid i"); }

//uart stuff
typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint16_t size;
    volatile uint8_t data[];
} RingBuffer;



/**
  * @brief  Interrupt handler of UART0
  * @param  none
  * @retval none
  */
void UART0_IRQHandler() __attribute__((interrupt("IRQ")));

/**
  * @brief  Send string using UART 
  * @param  const char *p = string to write 
  * 		int len = string's length 
  * @retval none
  */
int uart_write(const char *p, int len);

/**
  * @brief  Send int using UART 
  * @param  int n = int to send 
  * @retval none
  */
void uart_writeNb(int n);

/**
  * @brief  Send string error using UART disabling interrupt
  * @param  const char *p = string to write 
  * 		int len = string's length 
  * @retval none
  */
int uart_write_err(const char *p, int len);

/**
  * @brief Receive string using UART
  * @param  const char *p = string received
  * 		int len = string's length 
  * @retval int = lenght of string received
  */
int uart_read(char *p, int len);

/**
  * @brief UART initialisation
  * @param  int baudrate = baudrate of UART 
  * @retval none
  */
void uart_init(int baudrate);

/**
  * @brief 	Reset buffers
  * @param  RingBuffer *buf = buffer's pointer to reset 
  * 		int size = size of the buffer 
  * @retval none
  */
void buf_reset(RingBuffer *buf, int size);

/**
  * @brief 	Get buffer's lenght
  * @param  const RingBuffer *buf = buffer's pointer 
  * @retval int = lenght of the buffer  
  */
int buf_len(const RingBuffer *buf);


/**
  * @brief 	Check if the buffer is full
  * @param  const RingBuffer *buf = buffer's pointer 
  * @retval int = buffer full -> 1 / buffer not full -> 0
  */
int buf_isfull(const RingBuffer *buf);

/**
  * @brief 	Check if the buffer is empty 
  * @param  const RingBuffer *buf = buffer's pointer 
  * @retval int = buffer empty -> 1 / buffer not empty -> 0
  */

int buf_isempty(const RingBuffer *buf);
uint8_t buf_get_byte(RingBuffer *buf);
void buf_put_byte(RingBuffer *buf, uint8_t val);


/************* Low Power Timer (LPTMR) **************/

#define f_timer 1 // 0.4Hz to 11.5kHz max setting
#define PSC_LPTMR 2048
#define PSC_POWER 11
#define ARR_LPTMR (int)(CORE_CLOCK/(f_timer*(PSC_LPTMR+1)))
#define LPTMR_ARR 65535
void lptmr_conf(void);

/************* ADC0 **************/
#define ADC_SCALING (3.3*(2.2+4.7)*1000.0/2.2)
#define ADC_RESOLUTION 1023		//10 bits 
#define BATT_SEUIL VBATT * ADC_RESOLUTION *0.5	//50% of battery


void BatteryVoltage(void);
void ADC_init(void);


#endif /* DEBUG_H_ */
