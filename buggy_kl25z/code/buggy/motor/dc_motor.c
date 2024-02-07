/*
 * dc_motor.c
 *
 *  Created on: 3 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */


#include "dc_motor.h"

//configuration for TPM of PWM for motors
const tpm_config_t TPM_PWM_MOTOR_config = {
	.prescale = kTPM_Prescale_Divide_8,
	.useGlobalTimeBase = false,
	.triggerSelect = kTPM_Trigger_Select_0,
	.enableDoze = false,
	.enableDebugMode = false,
	.enableReloadOnTrigger = false,
	.enableStopOnOverflow = false,
	.enableStartOnTrigger = false,
};

//channels of tpm configuration array to setup PWM for motors
const tpm_chnl_pwm_signal_param_t TPM_PWM_MOTOR_pwmSignalParams[] = {
{
	.chnlNumber = kTPM_Chnl_1,
	.level = kTPM_HighTrue,
	.dutyCyclePercent = 0U,
},
{
	.chnlNumber = kTPM_Chnl_5,
	.level = kTPM_HighTrue,
	.dutyCyclePercent = 0U,
}
};


void MOTOR_init(void){

	CLOCK_EnableClock(kCLOCK_Tpm0);  // enable clock for tpm0 PWM signal
	CLOCK_EnableClock(kCLOCK_PortA); // enable clock for PORTA (Motor right : speed and direction)
	CLOCK_EnableClock(kCLOCK_PortC); // enable clock for PORTC (Motor left : speed and direction; Enable : Motor right and left)


	CLOCK_SetTpmClock(CLOCK_SOURCE_MCGFLLCLK);			// set clock source 1 (MCGFLLCLK clock) for timer PWM

	TPM_Init(TPM_PWM_MOTOR, &TPM_PWM_MOTOR_config);		//configure tpm for PWM signal
	TPM_SetupPwm(TPM_PWM_MOTOR,TPM_PWM_MOTOR_pwmSignalParams,2,kTPM_EdgeAlignedPwm,PWM_MOTOR_FRECENCY,CLOCK_SOURCE_FRECENCY); //configure tpm signal type as PWM signal for motors
	TPM_StartTimer(TPM_PWM_MOTOR,kTPM_SystemClock);		//start tpm of PWM signal for motors

	PORT_SetPinMux(PORT_MOTOR_RIGHT,PIN_SPEED_MOTOR_RIGHT,kPORT_MuxAlt3);       // PTA4 Motor Right In 1 (PWM for speed)
	PORT_SetPinMux(PORT_MOTOR_RIGHT,PIN_DIRECTION_MOTOR_RIGHT,kPORT_MuxAsGpio); // PTA5 Motor Right In 2 (GPIO for direction)
	PORT_SetPinMux(PORT_MOTOR_LEFT,PIN_DIRECTION_MOTOR_LEFT,kPORT_MuxAsGpio);  // PTA8 Motor Left In 1 (GPIO for direction)
	PORT_SetPinMux(PORT_MOTOR_LEFT,PIN_SPEED_MOTOR_LEFT,kPORT_MuxAlt3);        // PTA9 Motor Left In 2 (PWM for speed)

	PORT_SetPinMux(PORT_MOTOR_ENABLE,PIN_ENABLE_MOTOR_RIGHT,kPORT_MuxAsGpio);    // Motor Right Enable
	PORT_SetPinMux(PORT_MOTOR_ENABLE,PIN_ENABLE_MOTOR_LEFT,kPORT_MuxAsGpio);     // Motor Left Enable

	gpio_pin_config_t config_ouput_gpio = {kGPIO_DigitalOutput,0}; // output logic, 0 at default

	//set GPIOs as output logic for Motors
	GPIO_PinInit(GPIO_MOTOR_RIGHT,PIN_SPEED_MOTOR_RIGHT,&config_ouput_gpio);
	GPIO_PinInit(GPIO_MOTOR_RIGHT,PIN_DIRECTION_MOTOR_RIGHT,&config_ouput_gpio);
	GPIO_PinInit(GPIO_MOTOR_LEFT,PIN_DIRECTION_MOTOR_LEFT,&config_ouput_gpio);
	GPIO_PinInit(GPIO_MOTOR_LEFT,PIN_SPEED_MOTOR_LEFT,&config_ouput_gpio);
	GPIO_PinInit(GPIO_MOTOR_ENABLE,PIN_ENABLE_MOTOR_LEFT,&config_ouput_gpio);
	GPIO_PinInit(GPIO_MOTOR_ENABLE,PIN_ENABLE_MOTOR_RIGHT,&config_ouput_gpio);


	//set initial speed's motors as 0
	MOTOR_Left_Speed_Forward(0);
	MOTOR_Right_Speed_Forward(0);

	//set forward direction for motors
	MOTOR_Left_Direction_Forward();
	MOTOR_Right_Direction_Forward();
	//enable the motors
	MOTOR_Left_Enable();
	MOTOR_Right_Enable();



}

void MOTOR_Left_Enable(void)
{
	GPIO_SetPinsOutput(GPIO_MOTOR_ENABLE, 1<<PIN_ENABLE_MOTOR_LEFT);
}

void MOTOR_Right_Enable(void){
	GPIO_SetPinsOutput(GPIO_MOTOR_ENABLE, 1<<PIN_ENABLE_MOTOR_RIGHT);
}

void MOTOR_Left_Disable(void){
	GPIO_ClearPinsOutput(GPIO_MOTOR_ENABLE, 1<<PIN_ENABLE_MOTOR_LEFT);
}

void MOTOR_Right_Disable(void){
	GPIO_ClearPinsOutput(GPIO_MOTOR_ENABLE, 1<<PIN_ENABLE_MOTOR_RIGHT);
}


void MOTOR_Left_Direction_Forward(void){
	GPIO_SetPinsOutput(GPIO_MOTOR_LEFT, 1<<PIN_DIRECTION_MOTOR_LEFT);
}


void MOTOR_Right_Direction_Forward(void){
	GPIO_SetPinsOutput(GPIO_MOTOR_RIGHT, 1<<PIN_DIRECTION_MOTOR_RIGHT);
}


void MOTOR_Left_Direction_Backward(void){
	GPIO_ClearPinsOutput(GPIO_MOTOR_LEFT, 1<<PIN_DIRECTION_MOTOR_LEFT);
}


void MOTOR_Right_Direction_Backward(void){
	GPIO_ClearPinsOutput(GPIO_MOTOR_RIGHT, 1<<PIN_DIRECTION_MOTOR_RIGHT);
}

void MOTOR_Left_Speed_Forward(uint8_t speed){
	TPM_UpdatePwmDutycycle(TPM_PWM_MOTOR, CHANNEL_PWM_MOTOR_LEFT, kTPM_EdgeAlignedPwm, 100 - speed);
}

void MOTOR_Right_Speed_Forward(uint8_t speed){
	TPM_UpdatePwmDutycycle(TPM_PWM_MOTOR, CHANNEL_PWM_MOTOR_RIGHT, kTPM_EdgeAlignedPwm, 100 - speed);
}

void MOTOR_Left_Speed_Backward(uint8_t speed){
	TPM_UpdatePwmDutycycle(TPM_PWM_MOTOR, CHANNEL_PWM_MOTOR_LEFT, kTPM_EdgeAlignedPwm, speed);
}

void MOTOR_Right_Speed_Backward(uint8_t speed){
	TPM_UpdatePwmDutycycle(TPM_PWM_MOTOR, CHANNEL_PWM_MOTOR_RIGHT, kTPM_EdgeAlignedPwm, speed);
}

