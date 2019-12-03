/*
 * Debug.c
 *
 *  Created on: Nov 30, 2019
 *      Author: User
 */


#include "Debug.h"

void debug_init(){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	
	//Initialize the Red LED (PTB18)
	PORTB_PCR18 = PORT_PCR_MUX(1);
	GPIOB_PSOR |= DEBUG_RED_Pin;
	GPIOB_PDDR |= DEBUG_RED_Pin;
	//Initialize the Green LED (PTB19)
	PORTB_PCR19 = PORT_PCR_MUX(1);
	GPIOB_PSOR |= DEBUG_GREEN_Pin;
	GPIOB_PDDR |= DEBUG_GREEN_Pin;
	//Initialize the Blue LED (PTD1)
	PORTD_PCR1 = PORT_PCR_MUX(1);
	GPIOD_PSOR = DEBUG_BLUE_Pin;
	GPIOD_PDDR |= DEBUG_BLUE_Pin;
	
	//Initialize Debugging UART pins (PTA1 : RX and PTA2 : TX)
	PORTA_PCR1 = PORT_PCR_MUX(2);
	GPIOA_PDDR |= (1<<1);	//output
	PORTA_PCR2 = PORT_PCR_MUX(2);
	
	//PTD1 (SW_USER_2) & PTD3 (SW_USER_1)
	PORTD_PCR1 = PORT_PCR_MUX(1);
	PORTD_PCR3 = PORT_PCR_MUX(1);
	GPIOD_PDDR &=~ (1<<1)|(1<<3);
	
	//PTE2-5 : Rotary switch (2:LSB, 5:MSB);
	PORTE_PCR2 = PORT_PCR_MUX(1);
	PORTE_PCR3 = PORT_PCR_MUX(1);
	PORTE_PCR4 = PORT_PCR_MUX(1);
	PORTE_PCR5 = PORT_PCR_MUX(1);
	GPIOE_PDDR &=~ ((1<<2)|(1<<3)|(1<<4)|(1<<5));
}
unsigned char debug_getRotarySW(){
	return (GPIOE_PDIR & 0x003C)>>2;
	//return GPIOE_PDIR;
}
