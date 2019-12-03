/*
 * Debug.c
 *
 *  Created on: Nov 30, 2019
 *      Author: User
 */


#include "Debug.h"

// bit order : A-G+DP, map for digits 0-9,A-F and '-' for out of range nb
//											0			1			2			3			4			5			6			7			8			9			A			B			C			D			E			F			-
const unsigned int debugDisplayNbMap[17]={0b10000001, 0b11110011, 0b01001001, 0b01100001, 0b00110011, 0b00100101, 0b00000101, 0b11110001, 0b00000001, 0b00100001, 0b00010001, 0b11000001, 0b01100011, 0b10000101, 0b01100001, 0b01110001 ,0b01111111};

void debug_init(){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTA_MASK;
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

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

	//Initialize Debugging UART pins (PTA1 : RX and PTA2 : TX)
	PORTA_PCR1 = PORT_PCR_MUX(2);
	GPIOA_PDDR |= (1<<1);	//output
	PORTA_PCR2 = PORT_PCR_MUX(2);
	GPIOA_PDDR &=~ (1<<2);

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

void debug_displaySendRaw(unsigned int data){
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
void debug_displaySendNb(unsigned int nb){
	debug_displaySendRaw(debugDisplayNbMap[nb>16 ? 16 : nb]);
}
