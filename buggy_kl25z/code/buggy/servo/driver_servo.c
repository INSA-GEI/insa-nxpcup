/*
 * driver_servo.c
 *
 *  Created on: 30 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#include "driver_servo.h"

//premier servo LED casse
#define SERVO_CENTER_POS 		3000		// initial servo position (center)
#define SERVO_HARD_LEFT 		4000
#define SERVO_HARD_RIGHT 		2000        // initial 1800


const tpm_config_t TPM_config = {
		.prescale = kTPM_Prescale_Divide_8,
		.triggerSelect = kTPM_Trigger_Select_0,
        .enableDoze = false,
        .enableDebugMode = false,
		.enableReloadOnTrigger = false,
		.enableStopOnOverflow = false,
		.enableStartOnTrigger = false
};

const tpm_chnl_pwm_signal_param_t TPM_pwmSignalParams[] = {
  {
    .chnlNumber = kTPM_Chnl_0,
    .level = kTPM_HighTrue,
    .dutyCyclePercent = 0U,
  }
};

gpio_pin_config_t config_output_gpio = {kGPIO_DigitalOutput,0};


void servo_init(void) {

    CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_Tpm1);

	CLOCK_SetTpmClock(CLOCK_SOURCE_MCGFLLCLK);			// set clock source 1 (MCGFLLCLK clock) for timer PWM

	TPM_Init(SERVO_TPM_PWM, &TPM_config);
	TPM_SetupPwm(SERVO_TPM_PWM, TPM_pwmSignalParams, sizeof(TPM_pwmSignalParams) / sizeof(tpm_chnl_pwm_signal_param_t), kTPM_EdgeAlignedPwm, SERVO_FREQUENCY,SERVO_TPM_CLOCK_SOURCE);
	TPM_StartTimer(SERVO_TPM_PWM, kTPM_SystemClock);
	PORT_SetPinMux(SERVO_PWM_PORT, SERVO_PWN_PIN, kPORT_MuxAlt3);
	GPIO_PinInit(SERVO_PWM_GPIO, SERVO_PWN_PIN,&config_output_gpio);

	//TPM_UpdatePwmDutycycle(SERVO_TPM_PWM, SERVO_CHANNEL_PWM, kTPM_EdgeAlignedPwm, SERVO_CENTER_POS);

	SERVO_TPM_PWM->CONTROLS[SERVO_CHANNEL_PWM].CnV = SERVO_CENTER_POS;

	TPM_EnableInterrupts(SERVO_TPM_PWM,kTPM_TimeOverflowInterruptEnable);

	//Clear pending interrupts 18 (TPM = FTM1) in NVIC
	DisableIRQ(TPM1_IRQn);
	//Enable interrupts 18 (TPM = FTM1) in NVIC
	EnableIRQ(TPM1_IRQn);

}


void servo_setPos(int angle)
{
	int pos = SERVO_CENTER_POS;

	if(angle>0){
		pos+=angle*(SERVO_HARD_RIGHT-SERVO_CENTER_POS)/SERVO_MAX_RIGHT_ANGLE;
	}else{
		pos+=angle*(SERVO_HARD_LEFT-SERVO_CENTER_POS)/SERVO_MAX_LEFT_ANGLE;
	}
  	SERVO_TPM_PWM->CONTROLS[SERVO_CHANNEL_PWM].CnV = pos;
}
