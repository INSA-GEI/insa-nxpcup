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
    OVF_cnt1=0;
    OVF_cnt2=0;
}
void Encoder::init(void){
	SIM->SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; //Enable the clock of PORTA, PORTB, PORTD
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable the clock of TPM2
	
	TPM2->SC = ENCODER_MASK_TPM2_PRESCALER;		// prescaler for TPM2
	TPM2->SC |= TPM_SC_CMOD(1);					// enable TPM2 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM2->MOD = ENCODER_MOD;						// value of auto-reload
	
	TPM2->CONTROLS[0].CnSC = 0;
	TPM2->CONTROLS[1].CnSC = 0;
	TPM2->CONTROLS[0].CnSC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM2 channel_0 for ENC_SIG_A1 (p555)
	TPM2->CONTROLS[1].CnSC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM1 channel_1 for ENC_SIG_A2 (p555)
	TPM2->SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM2
	
	
	PORTB->PCR[2] |= PORT_PCR_MUX(3);				// ENC_SIG_A1 PTB2 TPM2_CH0
	PORTB->PCR[3] |= PORT_PCR_MUX(3);				// ENC_SIG_A2 PTB3 TPM2_CH1
	
	//Configures the individual port pins for input or output
	GPIOB->PDDR |= (1<<2);
	GPIOB->PDDR |= (1<<3);
	
	
	// enable interrupts 19 (TPM = FTM2)  in NVIC, no interrupt levels
	NVIC->ICPR[0] |= (1 << 19);			// clear pending interrupt 19
	NVIC->ISER[0] |= (1 << 19);			// enable interrupt 19
	
}

int Encoder::getLeftSpeed(void){
	if(delta1>0)return ENCODER_CAL_SPEED/delta1;
	return -1;
}

int Encoder::getRightSpeed(void){
	if(delta2>0)return ENCODER_CAL_SPEED/delta2;
	return -1;
}


void Encoder::interruptHandler(void){
	
	if ((TPM2->SC & TPM_SC_TOF_MASK)) {//Clear the bit flag of the overflow interrupt FTM2
		TPM2->SC |= TPM_SC_TOF_MASK;
		OVF_cnt1++;
		OVF_cnt2++;
		if(OVF_cnt1>MAX_OVF)delta1=-1;
		if(OVF_cnt2>MAX_OVF)delta2=-1;
	}
	if ((TPM2->CONTROLS[0].CnSC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture1 FTM2
		TPM2->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK ;
		int ccr1=TPM2->CONTROLS[0].CnV;
		
		delta1 = ccr1 - prev_ccr1 + OVF_cnt1*ENCODER_MOD;
		prev_ccr1 = ccr1;
		OVF_cnt1=0;
		
	}
	if ((TPM2->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture2 FTM2
		TPM2->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK ;
		int ccr2=TPM2->CONTROLS[1].CnV;
		delta2 = ccr2 - prev_ccr2 + OVF_cnt2*ENCODER_MOD;
		prev_ccr2 = ccr2;
		OVF_cnt2=0;
	}
	
}

