/*
 * driver_encoder.c
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#include "driver_encoder.h"
//Number of rising fronts per mm = 360/(Pi*Diameter) (fronts/mm)
const float FRONT_PAR_MM = NUMBER_RISING_FRONT_PER_ROUND / (PI * WHEEL_DIAMETER);

//Timer frequency (before ARR) = FCPU/ENCODER_PRECALER (/s)
const float ENCODER_FREQ_TIM = (float)CPU_FREQUENCY / (float)ENCODERS_TPM_PRESCALER;

//Constant to calculate the car speed = (Timer frequency before ARR)/(Number of rising fronts per mm) (mm/s/front)
const float ENCODER_CAL_SPEED = ENCODER_FREQ_TIM / FRONT_PAR_MM;


gpio_pin_config_t config_input_gpio = {kGPIO_DigitalInput};		// input logic configuration

//configuration for tpm of PWM for motors
const tpm_config_t ENCODERS_TPM_config = {
	.prescale = kTPM_Prescale_Divide_128,
	.useGlobalTimeBase = false,
	.triggerSelect = kTPM_Trigger_Select_0,
	.enableDoze = false,
	.enableDebugMode = false,
	.enableReloadOnTrigger = false,
	.enableStopOnOverflow = false,
	.enableStartOnTrigger = false,
};

//Variables to stock and calculate Capture Compare Value
int prev_ccr_left;
int prev_ccr_right;
int delta_left;
int delta_right;

//Variables to stock the Number of Overflows
int OVF_cnt_left;
int OVF_cnt_right;


void encoders_IRQHandler(void){

	if (TPM_GetStatusFlags(ENCODERS_TPM) & kTPM_TimeOverflowFlag) {
		TPM_ClearStatusFlags(ENCODERS_TPM,kTPM_TimeOverflowFlag); //Clear the bit flag of the overflow interrupt FTM2
		OVF_cnt_left++;
		OVF_cnt_right++;
		if(OVF_cnt_left > ENCODERS_MAX_OVF) delta_left = -1;
		if(OVF_cnt_right > ENCODERS_MAX_OVF) delta_right = -1;
	}
	if (TPM_GetStatusFlags(ENCODERS_TPM) & kTPM_Chnl0Flag) {
		TPM_ClearStatusFlags(ENCODERS_TPM,kTPM_Chnl0Flag); //Clear the bit flag of the capture1 FTM2
		int ccr_left = ENCODERS_TPM->CONTROLS[ENCODERS_TPM_CHANNEL_LEFT].CnV;
		delta_left = ccr_left - prev_ccr_left + OVF_cnt_left * ENCODERS_TPM_AUTORELOAD;
		prev_ccr_left = ccr_left;
		OVF_cnt_left=0;

	}
	if (TPM_GetStatusFlags(ENCODERS_TPM) & kTPM_Chnl1Flag) {
		TPM_ClearStatusFlags(ENCODERS_TPM,kTPM_Chnl1Flag); //Clear the bit flag of the capture2 FTM2
		int ccr_right = ENCODERS_TPM->CONTROLS[ENCODERS_TPM_CHANNEL_RIGHT].CnV;
		delta_right = ccr_right - prev_ccr_right + OVF_cnt_right * ENCODERS_TPM_AUTORELOAD;
		prev_ccr_right = ccr_right;
		OVF_cnt_right=0;
	}

}

void encoders_init(void){
    prev_ccr_right=0;
    prev_ccr_left=0;
    delta_right=0;
    delta_left=0;
    OVF_cnt_right=0;
    OVF_cnt_left=0;

	CLOCK_EnableClock(kCLOCK_Tpm2);  // enable clock for TPM2
	CLOCK_EnableClock(kCLOCK_PortA); // enable clock for PORTA
	CLOCK_EnableClock(kCLOCK_PortB); // enable clock for PORTC
	CLOCK_EnableClock(kCLOCK_PortD); // enable clock for PORTD

	TPM_Init(ENCODERS_TPM, &ENCODERS_TPM_config);								//configure ENCODERS_TPM
	TPM_SetupInputCapture(ENCODERS_TPM, kTPM_Chnl_0, kTPM_RisingEdge);			//setup input capture to TPM2 CH0 = ENC_SIG_A1 left
	TPM_SetupInputCapture(ENCODERS_TPM, kTPM_Chnl_1, kTPM_RisingEdge);			//setup input capture to TPM2 CH1 = ENC_SIG_A2 right
	TPM_SetTimerPeriod(ENCODERS_TPM,ENCODERS_TPM_AUTORELOAD);					//set value of auto-reload of ENCODERS_TPM

	//Enable interrupts for TPM2 CH1, TPM2 CH2, TimeOverflow
	TPM_EnableInterrupts(ENCODERS_TPM,kTPM_Chnl0InterruptEnable | kTPM_Chnl1InterruptEnable | kTPM_TimeOverflowInterruptEnable);

	TPM_StartTimer(ENCODERS_TPM,kTPM_SystemClock);		//start clock tpm2 of the encoders

	PORT_SetPinMux(ENCODER_PORT,ENCODER_PIN_SA_LEFT,kPORT_MuxAlt3);				// ENC_SIG_A1 left PTB2 TPM2_CH0
	PORT_SetPinMux(ENCODER_PORT,ENCODER_PIN_SA_RIGHT,kPORT_MuxAlt3);			// ENC_SIG_A2 right PTB3 TPM2_CH1

	GPIO_PinInit(ENCODER_GPIO,ENCODER_PIN_SA_LEFT,&config_input_gpio);
	GPIO_PinInit(ENCODER_GPIO,ENCODER_PIN_SA_RIGHT,&config_input_gpio);

	//Clear pending interrupts 19 (TPM = FTM2) in NVIC
	DisableIRQ(TPM2_IRQn);
	//Enable interrupts 19 (TPM = FTM2) in NVIC
	EnableIRQ(TPM2_IRQn);

}

float encoder_getLeftSpeed(void){
	if(delta_left>0)
	{
		//calculate the speed's left motor
		return ENCODER_CAL_SPEED/(float)delta_left;
	}
	return -1;
}

float encoder_getRightSpeed(void){
	if(delta_right>0)
	{
		//calculate the speed's right motor
		return ENCODER_CAL_SPEED/(float)delta_right;
	}
	return -1;
}
