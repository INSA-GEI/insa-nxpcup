/*
 * encoder.c
 *
 *  Created on: Jan 23, 2020
 *      Author: thomas
 */


#include "Encoder.h"

int state=0;

void encoder_config(void){
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; //Enable the clock of PORTA, PORTB, PORTD
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable the clock of TPM2 
	
	TPM2_SC = ENCODER_MASK_TPM2_PRESCALER;		// prescaler for TPM2 
	TPM2_SC |= TPM_SC_CMOD(1);					// enable TPM1 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM2_MOD = ENCODER_ARR;						// value of auto-reload (called here modulo)
	
	TPM2_C0SC = SET_CHANNEL;					// Configuration of TPM2 channel_0 for ENC_SIG_A1 (p555)
	TPM2_C1SC = SET_CHANNEL;					// Configuration of TPM1 channel_1 for ENC_SIG_A2 (p555)
	TPM2_SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM2
	
	//TPM2_C0V = ;								// To complete...
	
	//Not sure for the value in PORT_PCR_MUX()...
<<<<<<< HEAD
	//PORTA_PCR13 |= PORT_PCR_MUX(1);				// ENC_INDEX_1 PTA13 
	//PORTD_PCR4 |= PORT_PCR_MUX(1);				// ENC_INDEX_2 PTD4 
=======
>>>>>>> 69da52f1fb5650bf0b12ea4fdbac7fda48b4a6b0
	PORTB_PCR2 |= PORT_PCR_MUX(3);				// ENC_SIG_A1 PT TPM2_CH0
	PORTB_PCR3 |= PORT_PCR_MUX(3);				// ENC_SIG_A2 PTA12 TPM2_CH1
	
	//Configures the individual port pins for input or output
<<<<<<< HEAD
	//GPIOA_PDDR |= (1<<13);
	//GPIOD_PDDR |= (1<<4);
=======
>>>>>>> 69da52f1fb5650bf0b12ea4fdbac7fda48b4a6b0
	GPIOB_PDDR |= (1<<2);
	GPIOB_PDDR |= (1<<3); 
	
	
	// enable interrupts 18 (TPM = FTM1)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 19);			// clear pending interrupt 19
	NVIC_ISER |= (1 << 19);			// enable interrupt 19
	
}


void FTM2_IRQHandler() {
<<<<<<< HEAD
	//Clear the bit of the interrupt FTM2
	TPM2_SC |= TPM_SC_TOF_MASK;
=======
	
	int prev_ccr1 = 0;
	int prev_ccr2 = 0;
	int delta = 0;
	
	
	
	//Clear the bit flag of the overflow interrupt FTM2
	if (!(TPM2_SC & TPM_SC_TOF_MASK)) {
			TPM2_SC |= TPM_SC_TOF_MASK;
			prev_ccr1 = prev_ccr1 - ENCODER_ARR;
			prev_ccr2 = prev_ccr2 - ENCODER_ARR;
			state=1-state;
			if(state){
				DEBUG_RED_OFF;
			}else{
				DEBUG_RED_ON;
			}
	}
	
	//Clear the bit flag of the capture1 FTM2
	if (!(TPM2_C0SC & TPM_CnSC_CHF_MASK)) {
		TPM2_C0SC |= TPM_CnSC_CHF_MASK ;
		delta = TPM2_C0V - prev_ccr1;
		prev_ccr1 = TPM2_C0V;
	}
	
	//Clear the bit flag of the capture2 FTM2
	if (!(TPM2_C1SC & TPM_CnSC_CHF_MASK)) {
			TPM2_C1SC |= TPM_CnSC_CHF_MASK ;
			delta = TPM2_C1V - prev_ccr2;
			prev_ccr2 = TPM2_C1V;
	}
	
	
>>>>>>> 69da52f1fb5650bf0b12ea4fdbac7fda48b4a6b0
}

