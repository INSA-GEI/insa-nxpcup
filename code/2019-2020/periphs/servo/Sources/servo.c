/*
 * servo.c
 *
 *  Created on: Dec 8, 2019
 *      Author: thomas
 */

#include "servo.h"


int servo_position = 0;		// actual position of the servo relative to middle
int servo_base = 7800;		// initial servo position (center)


void servo_init(void){
	
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK; //Enable the clock of PORTA
	
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; //Enable the clock of TPM0 (Timer/PWM Module)
	TPM1_SC |= TPM_SC_CMOD(1);		// enable TPM1 clock (LPTPM counter increments on every LPTPM counter clock p553)
			
	PORTA_PCR12 |= PORT_PCR_MUX(3);	// Servo PTA12 TPM1_CH0
	
	TPM1_SC |= MASK_TPM1_PRESCALER;		// prescaler for TPM1 (Servo) will be 8 => 48/8 = 6MHz
	
	TPM1_MOD = TPM1_ARR;				// value of auto-reload (called here modulo) TPM1 (Servo), period = 10 ms (100 Hz)
	
	TPM1_C0SC = SET_CHANNEL_0;				// Configuration of TPM1 channel_0 for the Servo (p555)
	
}

