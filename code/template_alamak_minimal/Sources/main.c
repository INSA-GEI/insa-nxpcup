/*
 * FRDM-KL25 Freedom Board NXP Cup Minimal Program
 * (c) THD Technische Hochschule Deggendorf
 * (c) DIT Deggendorf Institute of Technology
 * Version 2.1, 09.01.2018
 * Change: ported to NXP Cup and Alamank Car
 */

#include "derivative.h" /* include peripheral declarations */

// Define threshold for Camera Black Line recognition
#define THRESHOLD				100			// Difference between black and white

// Defines for Direction PD Servo Control Loop
#define KP						50			// Proportional coefficient
#define KDP						25			// Differential coefficient

// Defines for LineScan Camera
#define TAOS_DELAY				asm ("nop")				// minimal delay time
#define	TAOS_SI_HIGH			GPIOB_PDOR |= (1<<8)	// SI on PTB8
#define	TAOS_SI_LOW				GPIOB_PDOR &= ~(1<<8)	// SI on PTB8
#define	TAOS_CLK_HIGH			GPIOB_PDOR |= (1<<9)	// CLK on PTB9
#define	TAOS_CLK_LOW			GPIOB_PDOR &= ~(1<<9)	// CLK on PTB9

// Function declaration
void ImageCapture(void);
int abs (int);

// Variable declaration
int i;										// counter for loops
int temp_reg;								// temporary register
int ImageData [128];						// array to store the LineScan image
int ImageDataDifference [128];				// array to store the PineScan pixel difference
int BlackLineRight;							// position of the black line on the right side
int BlackLineLeft;							// position of the black line on the left side
int RoadMiddle = 0;							// calculated middle of the road
int diff = 0;								// actual difference from line middle position
int diff_old = 0;							// previous difference from line middle position
int servo_position = 0;						// actual position of the servo relative to middle
int CompareData;							// set data for comparison to find max

// Main program
int main(void){
	
	// configure clock to 48 MHz from a 8 MHz crystal
	MCG_C2 = (MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK); 	// configure the oscillator settings
	MCG_C1 = (MCG_C1_CLKS(2) | MCG_C1_FRDIV(3));		// divider for 8 MHz clock	
	for (i = 0 ; i < 24000 ; i++)						// wait for OSCINIT to set
	// now in FBE mode
	MCG_C6 |= MCG_C6_CME0_MASK;		// enable the clock monitor
	MCG_C5 |= MCG_C5_PRDIV0(1); 	// set PLL ref divider to divide by 2
	temp_reg = MCG_C6; 				// store present C6 value (as CME0 bit was previously set)
	temp_reg &= ~MCG_C6_VDIV0_MASK; // clear VDIV settings
	temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); 	// write new VDIV and enable PLL
	MCG_C6 = temp_reg; 				// update MCG_C6		
	for (i = 0 ; i < 4000 ; i++) 	// wait for PLLST status bit to set
	// now in PBE mode
	SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV4(1));	// core clock, bus clock div by 2	
	MCG_C1 &= ~MCG_C1_CLKS_MASK;	// switch CLKS mux to select the PLL as MCGCLKOUT	
	for (i = 0 ; i < 2000 ; i++)	// Wait for clock status bits to update
	// now in PEE mode, core and system clock 48 MHz, bus and flash clock 24 MHz

	// turn on all port clocks
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
	// turn on all UART clocks - not needed in this project
	SIM_SCGC4 = SIM_SCGC4_UART0_MASK | SIM_SCGC4_UART1_MASK | SIM_SCGC4_UART2_MASK;
	
	// turn on all TPM clocks
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK | SIM_SCGC6_TPM2_MASK;

	// turn on ADC0 clock
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// set ADC inputs to ADC inputs
	PORTC_PCR2  |= PORT_PCR_MUX(0);		// Camera 1 PTC2 ADC0_SE11
	
	// set GPIOs to GPIO function
	PORTC_PCR0  |= PORT_PCR_MUX(1);	// PTC0 Push Button S2
	PORTB_PCR18 |= PORT_PCR_MUX(1);	// PTB18 LED red
	PORTB_PCR19 |= PORT_PCR_MUX(1);	// PTB19 LED green
	PORTD_PCR1  |= PORT_PCR_MUX(1);	// PTD1  LED blue
	PORTB_PCR8  |= PORT_PCR_MUX(1);	// PTB8 Camera SI
	PORTB_PCR9  |= PORT_PCR_MUX(1);	// PTB9 Camera Clock
	PORTA_PCR4  = 0;				// Set PTA4 Pin Control Register to Zero
	PORTA_PCR4  |= PORT_PCR_MUX(3);	// PTA4 Motor 1 In 1 (speed) PTA4 TPM0_CH1
	PORTA_PCR5  |= PORT_PCR_MUX(1);	// PTA5 Motor 1 In 2 (direction)
	PORTC_PCR8  |= PORT_PCR_MUX(1);	// PTC8 Motor 2 In 1 (direction)
	PORTC_PCR9  |= PORT_PCR_MUX(3);	// PTC9 Motor 2 In 2 (speed) PTC8 TPM0_CH5
	
	// set GPIO outputs to outputs
	GPIOB_PDDR |= (1<<18);			// PTB18 LED red
	GPIOB_PDDR |= (1<<19);			// PTB19 LED green
	GPIOD_PDDR |= (1<<1);			// PTD1  LED blue
	GPIOB_PDDR |= (1<<8);			// PTB8 Camera SI
	GPIOB_PDDR |= (1<<9);			// PTB9 Camera Clock
	GPIOA_PDDR |= (1<<4);			// PTA4 Motor 1 In 1
	GPIOA_PDDR |= (1<<5);			// PTA5 Motor 1 In 2 (direction)
	GPIOC_PDDR |= (1<<8);			// PTC9 Motor 2 In 1 (direction)
	GPIOC_PDDR |= (1<<9);			// PTC9 Motor 2 In 2 
	
	// all LEDs off
	GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off
	GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
	GPIOD_PDOR |= GPIO_PDOR_PDO(1<<1);    // blue LED off	
	
	// GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<18);  // red LED on
	// GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<19);  // green LED on
	// GPIOD_PDOR &= ~GPIO_PDOR_PDO(1<<1);   // blue LED on	
			
	// set GPIO input to input
	GPIOC_PDDR &= ~ (1<<0);			// PTC0 Push Button S2

	// set PWM outputs
	PORTA_PCR12 |= PORT_PCR_MUX(3);	// Servo Motor 1 Out  PTA12 TPM1_CH0
	
	// configure TPM clock source to be 48 MHz
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);		// MCGFLLCLK clock or MCGPLLCLK/2
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;	// use MCGPLLCLK/2 clock when running from 8 MHz and PLL
		
	// set TPM prescaler before enabling the timer
	TPM0_SC |= 3;					// prescaler for TPM0 (Motor) is 8
	TPM1_SC |= 3;					// prescaler for TPM1 (Servo) is 8
	
	// TPM modulo register, set frequency
	TPM0_MOD = 600;					// modulo TPM0 (Motor), periode = 0.10 ms (10000 Hz)
	TPM1_MOD = 60000;				// modulo TPM0 (Servo), periode = 10 ms (100 Hz)
	
	// set TPM clock mode to enable timer
	TPM0_SC |= TPM_SC_CMOD(1);		// enable TPM0 (Motor)
	TPM1_SC |= TPM_SC_CMOD(1);		// enable TPM1 (Servo)
	
	// configure TPM channel outputs high-true pulses
	TPM0_C1SC = 0x28;				// TPM0 channel1 Motor 1 In 1 speed left
	TPM0_C5SC = 0x28;				// TPM0 channel5 Motor 2 In 2 speed right
	TPM1_C0SC = 0x28;				// TPM1 channel0 Servo 1
	
	// TPM channel value registers, sets duty cycle
	TPM1_C0V = 9000;				// TPM1 channel0 Servo 1 ca. 1.5 ms (middle)
	
    // initial configuration of motors
	TPM0_C1V = 100;					// TPM0 channel1 left Motor 1 In 1 slow forward
	TPM0_C5V = 100;					// TPM0 channel5 right Motor 2 In 2 slow forward
	GPIOA_PDOR &= ~(1<<5);			// Set PTA5 left Motor 1 In 2 forward
	GPIOC_PDOR &= ~(1<<8);			// Set PTC8 right Motor 2 In 1 forward
	
    // configure interrupts in TPM0
	TPM1_SC |= TPM_SC_TOIE_MASK;	// enable overflow interrupt in TPM1 (10 ms rate)
	
	// ADC0 clock configuration
	ADC0_CFG1 |= 0x01;				// clock is bus clock divided by 2 = 12 MHz
	
	// ADC0 resolution    
	ADC0_CFG1 |= 0x08;				// resolution 10 bit, max. value is 1023

	// ADC0 conversion mode
	ADC0_SC3 = 0x00;				// single conversion mode
	    
    // enable interrupts 18 (TPM = FTM1)  in NVIC, no interrupt levels
    NVIC_ICPR |= (1 << 18);			// clear pending interrupt 18
    NVIC_ISER |= (1 << 18);			// enable interrupt 18
    
    // enable interrupts globally
    asm (" CPSIE i ");				// enable interrupts on core level
    
    // Main loop
	for(;;) {						// endless loop

		// do nothing
		
	}								// end of endless loop	
	return 0;
}

void FTM1_IRQHandler()				// TPM1 ISR
{
	TPM1_SC |= 0x80;							// clear TPM0 ISR flag
	
	GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<18);  // red LED on
	
	// Capture Line Scan Image
	ImageCapture();								// capture LineScan image
	
	// Find black line on the right side
	for(i=64;i<127;i++)							// calculate difference between the pixels
	{
		ImageDataDifference[i] = abs (ImageData[i] - ImageData[i+1]);
	}
	CompareData = THRESHOLD;					// threshold
	BlackLineRight = 126;
	for(i=64;i<127;i++)
	{
	   	if (ImageDataDifference[i] > CompareData)
	   	{
	   		CompareData = ImageDataDifference[i];
	   		BlackLineRight = i;
	   	}
	}
	
	// Find black line on the left side
	for(i=64;i>0;i--)							// calculate difference between the pixels
	{
		ImageDataDifference[i] = abs (ImageData[i] - ImageData[i-1]);
	}
	CompareData = THRESHOLD;					// threshold
	BlackLineLeft = 1;
	for(i=64;i>2;i--)							// only down to pixel 3, not 1
	{
	   	if (ImageDataDifference[i] > CompareData)
	   	{
	   		CompareData = ImageDataDifference[i];
	   		BlackLineLeft = i;
	   	}
	}
	
	// Find middle of the road, 64 for strait road
	RoadMiddle = (BlackLineLeft + BlackLineRight)/2;
	
	// if a line is only on the the left side
	if (BlackLineRight > 124)
	{
		RoadMiddle = BlackLineLeft + 50;
	}
	// if a line is only on the the right side
	if (BlackLineLeft < 3)
	{
		RoadMiddle = BlackLineRight - 50;
	}
	// if no line on left and right side
	if ((BlackLineRight > 124) && (BlackLineLeft < 3))
	{
		RoadMiddle = 64;
	}
	
	// Store old value
	diff_old = diff;							// store old difference
	
	// Find difference from real middle
	diff = RoadMiddle - 64;						// calculate actual difference
	
	// plausibility check
	if (abs (diff - diff_old) > 50)
			{
		diff = diff_old;
			}

	// Direction Control Loop: PD Controller
	servo_position = KP*diff + KDP*(diff-diff_old);

	// Set channel 0 PWM_Servo position
	TPM1_C0V  = 9000 - servo_position; 		// set channel 0 PWM_Servo
		
	// Set Motor Speed
	TPM0_C1V = 100;					// TPM0 channel1 left Motor 1 In 1 slow forward
	TPM0_C5V = 100;					// TPM0 channel5 right Motor 2 In 2 slow forward
	
	// red LED off
	GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off

}
	
// Capture LineScan Image
void ImageCapture(void)
	{
    unsigned char i;
    ADC0_CFG2 |= 0x10;							// select B side of the MUX
    TAOS_SI_HIGH;
    TAOS_DELAY;
    TAOS_CLK_HIGH;
    TAOS_DELAY;
    TAOS_SI_LOW;
    TAOS_DELAY;
    // inputs data from camera (first pixel)
	ADC0_SC1A  =  11;							// set ADC0 channel 11
	while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
	ImageData[0] = ADC0_RA;						// return value
	TAOS_CLK_LOW;

    for(i=1;i<128;i++)
    {
        TAOS_DELAY;
        TAOS_DELAY;
        TAOS_CLK_HIGH;
        TAOS_DELAY;
        TAOS_DELAY;
        // inputs data from camera (one pixel each time through loop)
    	ADC0_SC1A  =  11;							// set ADC0 channel 11
    	while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
    	ImageData[i] = ADC0_RA;						// return value
        TAOS_CLK_LOW;
    }
    
    TAOS_DELAY;
    TAOS_DELAY;
    TAOS_CLK_HIGH;
    TAOS_DELAY;
    TAOS_DELAY;
    TAOS_CLK_LOW;
}
