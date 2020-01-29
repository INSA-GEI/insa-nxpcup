/*
 * encoder.c
 *
 *  Created on: Jan 23, 2020
 *      Author: thomas
 */


#include "Encoder.h"

int state=0;

Encoder::Encoder(void){
    prev_ccr1=0;
    prev_ccr2=0;
    delta1=0;
    delta2=0;
}
void Encoder::init(void){
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; //Enable the clock of PORTA, PORTB, PORTD
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable the clock of TPM2 
	
	TPM2_SC = ENCODER_MASK_TPM2_PRESCALER;		// prescaler for TPM2 
	TPM2_SC |= TPM_SC_CMOD(1);					// enable TPM1 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM2_MOD = ENCODER_MOD;						// value of auto-reload
	
	TPM2_C0SC = 0x04;					// Configuration of TPM2 channel_0 for ENC_SIG_A1 (p555)
	TPM2_C1SC = 0x04;					// Configuration of TPM1 channel_1 for ENC_SIG_A2 (p555)
	TPM2_SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM2
	
	//TPM2_C0V = ;								// To complete...
	
	PORTB_PCR2 |= PORT_PCR_MUX(3);				// ENC_SIG_A1 PT TPM2_CH0
	PORTB_PCR3 |= PORT_PCR_MUX(3);				// ENC_SIG_A2 PTA12 TPM2_CH1
	
	//Configures the individual port pins for input or output
	GPIOB_PDDR |= (1<<2);
	GPIOB_PDDR |= (1<<3); 
	
	
	// enable interrupts 18 (TPM = FTM1)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 19);			// clear pending interrupt 19
	NVIC_ISER |= (1 << 19);			// enable interrupt 19
	
}

int Encoder::getLeftSpeed(void){
    return ENCODER_CAL_SPEED/delta1;
}
int Encoder::getRightSpeed(void){
    return ENCODER_CAL_SPEED/delta2;
}


void Encoder::interruptHandler(void){
	if (!(TPM2_SC & TPM_SC_TOF_MASK)) {//Clear the bit flag of the overflow interrupt FTM2
		TPM2_SC |= TPM_SC_TOF_MASK;
		prev_ccr1 = prev_ccr1 - ENCODER_MOD;
		prev_ccr2 = prev_ccr2 - ENCODER_MOD;
		state=1-state;
		if(state){
			DEBUG_RED_OFF;
		}else{
			DEBUG_RED_ON;
		}
	}else if (!(TPM2_C0SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture1 FTM2
		TPM2_C0SC |= TPM_CnSC_CHF_MASK ;
		delta1 = TPM2_C0V - prev_ccr1;
		prev_ccr1 = TPM2_C0V;
	}else if (!(TPM2_C1SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture2 FTM2
		TPM2_C1SC |= TPM_CnSC_CHF_MASK ;
		delta2 = TPM2_C1V - prev_ccr2;
		prev_ccr2 = TPM2_C1V;
	}
}

