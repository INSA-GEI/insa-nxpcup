/*
 * servo.c
 *
 *  Created on: Dec 8, 2019
 *      Author: thomas
 */

#include <drivers_perso/Debug.h>
#include "servo.h"
#include "fsl_tpm.h"

void servo_init(void){
	tpm_config_t tpmInfo;
	tpm_chnl_pwm_signal_param_t tpmParam[1];

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 			//Enable the clock of PORTA
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK; 			//Enable the clock of TPM0 (Timer/PWM Module)
	PORTA->PCR[12] |= PORT_PCR_MUX(3);				// Servo PTA12 TPM1_CH0

	//TPM1->SC = SERVO_MASK_TPM1_PRESCALER;		// prescaler for TPM1 (Servo) will be 8 => 48/8 = 6MHz
	//TPM1->SC |= TPM_SC_CMOD(1);					// enable TPM1 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM_GetDefaultConfig(&tpmInfo);
	tpmInfo.prescale=kTPM_Prescale_Divide_8;
	TPM_Init(TPM1, &tpmInfo);

	//TPM1->MOD = SERVO_TPM1_ARR;					// value of auto-reload (called here modulo) TPM1 (Servo), period = 10 ms (100 Hz)
	//TPM1->C0SC = SERVO_SET_CHANNEL_0;			// Configuration of TPM1 channel_0 for the Servo (p555)
	//TPM1->C0V = SERVO_CENTER_POS;				// TPM1 channel_0 value matches to 1.5 ms (middle)
	//TPM1->SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM1 (10 ms rate)
	tpmParam[0].chnlNumber = (tpm_chnl_t)kTPM_Chnl_0;
	tpmParam[0].level = kTPM_LowTrue;
	tpmParam[0].dutyCyclePercent = 50U;
	TPM_SetupPwm(TPM1, tpmParam, 1U, kTPM_EdgeAlignedPwm, 100U, 48000000U);
	TPM_StartTimer(TPM1, kTPM_SystemClock);

	// enable interrupts 18 (TPM = FTM1)  in NVIC, no interrupt levels
	// INFO: Basculement vers les fonctions CMSIS
	NVIC_ClearPendingIRQ(TPM1_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);
	//NVIC_ICPR |= (1 << 18);						// clear pending interrupt 18
	//NVIC_ISER |= (1 << 18);						// enable interrupt 18

}

void servo_setPos(int angle){
	int pos=SERVO_CENTER_POS;
	if(angle>0){
		pos+=angle*(SERVO_HARD_RIGHT-SERVO_CENTER_POS)/SERVO_MAX_RIGHT_ANGLE;
	}else{
		pos+=angle*(SERVO_HARD_LEFT-SERVO_CENTER_POS)/SERVO_MAX_LEFT_ANGLE;
	}

	//TPM1->C0V=pos;
	TPM_UpdatePwmDutycycle(TPM1,(tpm_chnl_t)kTPM_Chnl_0, kTPM_EdgeAlignedPwm, (uint8_t)(pos));
}

void init_servo_cam(){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//PTD0 ALT1 => GPIO
	PORTD->PCR[0] = 0;
	PORTD->PCR[0] |= PORT_PCR_MUX(1);		// Servo PTD
	GPIOD->PDDR |= DEBUG_PWM_SERVO_CAM; 				//Conf en ouput

	/*
	uart_write("Servo_cam_ok\n\r",14);
	uart_writeNb(GPIOD_PDOR);
	uart_write("\n\r",2);
	uart_write("portD0 :",8);
	uart_writeNb(PORTD_PCR0);
	uart_write("\n\r",2);
	 */

}


