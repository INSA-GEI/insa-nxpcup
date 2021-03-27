/*
 * servo.c
 *
 *  Created on: Dec 8, 2019
 *      Author: thomas
 */

#include "servo.h"
#include "debug.h"


void servo_init(void){

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; 			//Enable the clock of PORTA
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; 			//Enable the clock of TPM0 (Timer/PWM Module)
	TPM1_SC = SERVO_MASK_TPM1_PRESCALER;		// prescaler for TPM1 (Servo) will be 8 => 48/8 = 6MHz
	TPM1_SC |= TPM_SC_CMOD(1);					// enable TPM1 clock (LPTPM counter increments on every LPTPM counter clock p553)
	PORTA_PCR12 |= PORT_PCR_MUX(3);				// Servo PTA12 TPM1_CH0
	TPM1_MOD = SERVO_TPM1_ARR;					// value of auto-reload (called here modulo) TPM1 (Servo), period = 10 ms (100 Hz)
	TPM1_C0SC = SERVO_SET_CHANNEL_0;			// Configuration of TPM1 channel_0 for the Servo (p555)
	TPM1_C0V = SERVO_CENTER_POS;				// TPM1 channel_0 value matches to 1.5 ms (middle)
	TPM1_SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM1 (10 ms rate)
	// enable interrupts 18 (TPM = FTM1)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 18);						// clear pending interrupt 18
	NVIC_ISER |= (1 << 18);						// enable interrupt 18

}

void servo_setPos(int angle){
	int pos=SERVO_CENTER_POS;
	if(angle>0){
		pos+=angle*(SERVO_HARD_RIGHT-SERVO_CENTER_POS)/SERVO_MAX_RIGHT_ANGLE;
	}else{
		pos+=angle*(SERVO_HARD_LEFT-SERVO_CENTER_POS)/SERVO_MAX_LEFT_ANGLE;
	}
	TPM1_C0V=pos;
}

void init_servo_cam(){
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	//Carac PWM initialisées dans motor.c
	
	//PTD5 ALT4
	PORTC_PCR5 |= PORT_PCR_MUX(4);	// Servo PTD5 TMP0_CH0
	TPM0_C0SC = SERVO_SET_CHANNEL_0;
	TPM0_C0V = 7000;
	
	uart_write("Servo_cam_ok\n\r",14);
		
}


