/*
 * Motor.c
 *
 *  Created on: Dec 7, 2019
 *      Author: User
 */

#include "Motor.h"

void motor_init(void){
	tpm_config_t tpmInfo;
	tpm_chnl_pwm_signal_param_t tpmParam[2];

	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK | SIM_SCGC6_TPM2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK;

	PORTA->PCR[4]   = 0;
	PORTA->PCR[4]  |= PORT_PCR_MUX(3);	// PTA4 Motor Right In 1 (speed) PTA4 TPM0_CH1
	PORTA->PCR[5]  |= PORT_PCR_MUX(1);	// PTA5 Motor Right In 2 (direction)
	PORTC->PCR[8]  |= PORT_PCR_MUX(1);	// PTC8 Motor Left  In 1 (direction)
	PORTC->PCR[9]  |= PORT_PCR_MUX(3);	// PTC9 Motor Left  In 2 (speed) PTC9 TPM0_CH5

	PORTC->PCR[7]  |= PORT_PCR_MUX(1);	// Motor Right Enable
	PORTC->PCR[0]  |= PORT_PCR_MUX(1);	// Motor Left  Enable

	FGPIOA->PDDR |= (1<<4);
	FGPIOA->PDDR |= (1<<5);
	FGPIOC->PDDR |= (1<<8);
	FGPIOC->PDDR |= (1<<9);
	FGPIOC->PDDR |= (1<<0);
	FGPIOC->PDDR |= (1<<7);

	//should be right by clock_init
	//SIM_SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	//SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

//	TPM0->SC |= 3; 					// prescaler (divise par 8)
//	TPM0->MOD = 599; 				// frequency modulo
//	TPM0->SC |= TPM_SC_CMOD(1); 		// enable timer
	TPM_GetDefaultConfig(&tpmInfo);
	tpmInfo.prescale=kTPM_Prescale_Divide_8;
	TPM_Init(TPM0, &tpmInfo);

	// TODO A revoir
//	TPM0->C1SC = 0x28;				// CH1 (right  motor)
	tpmParam[0].chnlNumber = (tpm_chnl_t)kTPM_Chnl_1;
	tpmParam[0].level = kTPM_LowTrue;
	tpmParam[0].dutyCyclePercent = 0U;

//	TPM0->C5SC = 0x28;				// CH5 (left motor)
	tpmParam[0].chnlNumber = (tpm_chnl_t)kTPM_Chnl_5;
	tpmParam[0].level = kTPM_LowTrue;
	tpmParam[0].dutyCyclePercent = 0U;

	TPM_SetupPwm(TPM0, tpmParam, 2U, kTPM_EdgeAlignedPwm, 600U, 48000000U);
	TPM_StartTimer(TPM0, kTPM_SystemClock);

	MOTOR_LEFT_ENABLE;
	MOTOR_RIGHT_ENABLE;

	MOTOR_LEFT_FORWARD;
	MOTOR_RIGHT_FORWARD;

	MOTOR_LEFT_FSPEED(0);
	MOTOR_RIGHT_FSPEED(0);
	
	//IT 10 kHz
	TPM0->SC |= TPM_SC_TOIE_MASK;			//enable IT
	// INFO: Basculement vers les fonctions CMSIS
	NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);
//	NVIC_ICPR |= (1 << 17);					// clear pending interrupt TPM0
//	NVIC_ISER |= (1 << 17);					// enable interrupt TPM0

}
