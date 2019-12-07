/*
 * Motor.c
 *
 *  Created on: Dec 7, 2019
 *      Author: User
 */

#include "Motor.h"


void motor_init(void){

	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK | SIM_SCGC6_TPM2_MASK;
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK;

	//should be right by clock_init
	//SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	//SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

	TPM0_SC |= 3; 					// prescaler
	TPM0_MOD = 600; 				// frequency modulo
	TPM0_SC |= TPM_SC_CMOD(1); 		// enable timer
	TPM0_C1SC = 0x28;				// CH1 (left motor)
	TPM0_C5SC = 0x28;				// CH2 (right motor)

	PORTA_PCR4  |= PORT_PCR_MUX(3);	// PTA4 Motor 1 In 1 (speed) PTA4 TPM0_CH1
	PORTA_PCR5  |= PORT_PCR_MUX(1);	// PTA5 Motor 1 In 2 (direction)
	PORTC_PCR8  |= PORT_PCR_MUX(1);	// PTC8 Motor 2 In 1 (direction)
	PORTC_PCR9  |= PORT_PCR_MUX(3);	// PTC9 Motor 2 In 2 (speed) PTC9 TPM0_CH5

	GPIOA_PDDR |= (1<<4);
	GPIOA_PDDR |= (1<<5);
	GPIOC_PDDR |= (1<<8);
	GPIOC_PDDR |= (1<<9); 

	MOTOR_LEFT_FORWARD;
	MOTOR_RIGHT_FORWARD;

	MOTOR_LEFT_SPEED(150);
	MOTOR_RIGHT_SPEED(150);

}
