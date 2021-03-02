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
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; //Enable the clock of PORTA, PORTB, PORTD
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable the clock of TPM2 
	
	TPM2_SC = ENCODER_MASK_TPM2_PRESCALER;		// prescaler for TPM2 
	TPM2_SC |= TPM_SC_CMOD(1);					// enable TPM2 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM2_MOD = ENCODER_MOD;						// value of auto-reload
	
	TPM2_C0SC = 0;
	TPM2_C1SC = 0;
	TPM2_C0SC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM2 channel_0 for ENC_SIG_A1 (p555)
	TPM2_C1SC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM2 channel_1 for ENC_SIG_A2 (p555)
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

void Encoder::init_SENS(void){
	//for(int i=0;i<ONE_SECOND;i++){asm ("nop");};
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	//On regarde les 2nd canaux
	//ENC_SIG_B1 PTA 1
	//ENC_SIG_B2 PTA 2
	//On les configure en mode GPIO alt 1 cf FRDM-KL25Z pinouts
	PORTA_PCR1 |= PORT_PCR_MUX(1);
	PORTA_PCR2 |= PORT_PCR_MUX(1);
	//On peut maintenant lire leur valeur dans GPIOx_PDIR (par défaut les pins sont à 0 = input)
}

int Encoder::getLeftSpeed(void){
	if(delta1!=0)return ENCODER_CAL_SPEED/delta1;
	return 0;
}

int Encoder::getRightSpeed(void){
	if(delta2!=0)return ENCODER_CAL_SPEED/delta2;
	return 0;
}


void Encoder::interruptHandler(void){

	if ((TPM2_SC & TPM_SC_TOF_MASK)) {//Clear the bit flag of the overflow interrupt FTM2
		TPM2_SC |= TPM_SC_TOF_MASK;
		OVF_cnt1++;
		OVF_cnt2++;
		if(OVF_cnt1>MAX_OVF || OVF_cnt1<MAX_OVF)delta1=0; //la voiture n'avance pas ou très lentement
		if(OVF_cnt2>MAX_OVF || OVF_cnt2<MAX_OVF)delta2=0; //la voiture n'avance pas ou très lentement
	}
	if ((TPM2_C0SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture1 FTM2
		TPM2_C0SC |= TPM_CnSC_CHF_MASK ;
		int ccr1=TPM2_C0V;
		
		delta1 = ccr1 - prev_ccr1 + OVF_cnt1*ENCODER_MOD;
		//On regarde le sens
		if (!((GPIOA_PDIR>>1) & 0x1)){
			delta1=-delta1; //ok
		}
		//MAJ car le TMP continue de compter cf p(564)
		prev_ccr1 = ccr1;
		OVF_cnt1=0;
		
	}
	if ((TPM2_C1SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture2 FTM2
		TPM2_C1SC |= TPM_CnSC_CHF_MASK ;
		int ccr2=TPM2_C1V;
		delta2 = ccr2 - prev_ccr2 + OVF_cnt2*ENCODER_MOD;
		//On regarde le sens
		if (((GPIOA_PDIR>>2) & 0x1)){
			delta2=-delta2; //ok	
		}
		//MAJ car le TMP continue de compter cf p(564)
		prev_ccr2 = ccr2;
		OVF_cnt2=0;
	}
	
}

