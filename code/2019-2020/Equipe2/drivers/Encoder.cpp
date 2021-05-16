/*
 * encoder.c
 *
 *  Created on: Jan 23, 2020
 *      Author: thomas
 */


#include "Encoder.h"

int state=0;
/**
  * @brief 	Encoder object constructor
  * @param 	none
  * @retval none
  */
Encoder::Encoder(void){
    prev_ccr1=0;
    prev_ccr2=0;
    delta1=0;
    delta2=0;
    OVF_cnt1=0;
    OVF_cnt2=0;
}

/**
  * @brief 	Initialisation of both encoder and interruptions 
  * @param 	none
  * @retval none
  */
void Encoder::init(void){
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; //Enable the clock of PORTA, PORTB, PORTD
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable the clock of TPM2 
	
	TPM2_SC = ENCODER_MASK_TPM2_PRESCALER;		// prescaler for TPM2 
	TPM2_SC |= TPM_SC_CMOD(1);					// enable TPM2 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM2_MOD = ENCODER_MOD;						// value of auto-reload
	
	TPM2_C0SC = 0;
	TPM2_C1SC = 0;
	TPM2_C0SC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM2 channel_0 for ENC_SIG_A1 (p555)
	TPM2_C1SC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM1 channel_1 for ENC_SIG_A2 (p555)
	TPM2_SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM2
	
	
	PORTB_PCR2 |= PORT_PCR_MUX(3);				// ENC_SIG_A1 PTB2 TPM2_CH0
	PORTB_PCR3 |= PORT_PCR_MUX(3);				// ENC_SIG_A2 PTB3 TPM2_CH1
	
	//Configures the individual port pins for input or output
	GPIOB_PDDR |= (1<<2);
	GPIOB_PDDR |= (1<<3); 
	
	
	// enable interrupts 19 (TPM = FTM2)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 19);			// clear pending interrupt 19
	NVIC_ISER |= (1 << 19);			// enable interrupt 19
	
}

/**
  * @brief 	Get left wheel speed 
  * @param 	none
  * @retval int : Left wheel speed
  */
int Encoder::getLeftSpeed(void){
	if(delta1>0)return ENCODER_CAL_SPEED/delta1;
	return -1;
}

/**
  * @brief 	Get right wheel speed 
  * @param 	none
  * @retval int : right wheel speed
  */
int Encoder::getRightSpeed(void){
	if(delta2>0)return ENCODER_CAL_SPEED/delta2;
	return -1;
}

/**
  * @brief 	Encoder interrupt handler 
  * @param 	none
  * @retval none
  */
void Encoder::interruptHandler(void){
	
	if ((TPM2_SC & TPM_SC_TOF_MASK)) {//Clear the bit flag of the overflow interrupt FTM2
		TPM2_SC |= TPM_SC_TOF_MASK;
		OVF_cnt1++;
		OVF_cnt2++;
		if(OVF_cnt1>MAX_OVF)delta1=-1;
		if(OVF_cnt2>MAX_OVF)delta2=-1;
	}
	if ((TPM2_C0SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture1 FTM2
		TPM2_C0SC |= TPM_CnSC_CHF_MASK ;
		int ccr1=TPM2_C0V;
		
		delta1 = ccr1 - prev_ccr1 + OVF_cnt1*ENCODER_MOD;
		prev_ccr1 = ccr1;
		OVF_cnt1=0;
		
	}
	if ((TPM2_C1SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture2 FTM2
		TPM2_C1SC |= TPM_CnSC_CHF_MASK ;
		int ccr2=TPM2_C1V;
		delta2 = ccr2 - prev_ccr2 + OVF_cnt2*ENCODER_MOD;
		prev_ccr2 = ccr2;
		OVF_cnt2=0;
	}
	
}

