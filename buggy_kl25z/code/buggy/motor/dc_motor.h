/*
 * dc_motor.h
 *
 *  Created on: 3 janv. 2024
 *      Author: TANG Huong Cam (tanghuongcam)
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include "MKL25Z4.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_tpm.h"

/**
 * Board's configurations for DC motor used in this drivers
 * 	- PTA4 : Motor Right In 1 (PWM for speed)
 * 	- PTA5 : Motor Right In 2 (GPIO for direction)
 * 	- PTA9 : Motor Left In 2 (PWM for speed)
 * 	- PTA8 : Motor Left In 1 (GPIO for direction)
 * 	- TPM0 : PWM for both motors
 * 		+ Channel 1 : PWM for motor Right
 * 		+ Channel 5 : PWM for motor Left
 */

/*Motors' Constants*/
#define PIN_ENABLE_MOTOR_RIGHT		7
#define PIN_ENABLE_MOTOR_LEFT 		0
#define PIN_DIRECTION_MOTOR_RIGHT 	5
#define PIN_SPEED_MOTOR_RIGHT 		4
#define PIN_DIRECTION_MOTOR_LEFT 	8
#define PIN_SPEED_MOTOR_LEFT 		9
#define CHANNEL_PWM_MOTOR_RIGHT 	1
#define CHANNEL_PWM_MOTOR_LEFT 		5

#define PORT_MOTOR_RIGHT 			PORTA
#define PORT_MOTOR_LEFT 			PORTC
#define GPIO_MOTOR_RIGHT 			GPIOA
#define GPIO_MOTOR_LEFT 			GPIOC
#define PORT_MOTOR_ENABLE 			PORTC
#define GPIO_MOTOR_ENABLE			GPIOC

#define TPM_PWM_MOTOR				TPM0
#define CLOCK_SOURCE_MCGFLLCLK 		1
#define PWM_MOTOR_FRECENCY 			10000U
#define CLOCK_SOURCE_FRECENCY 		48000000UL

/**
 * @brief Enable DC motor
 */
#define __MOTOR_LEFT_ENABLE		(GPIO_SetPinsOutput(GPIO_MOTOR_ENABLE,GPIO_PSOR_PTSO(PIN_ENABLE_MOTOR_LEFT)))
#define __MOTOR_RIGHT_ENABLE	(GPIO_SetPinsOutput(GPIO_MOTOR_ENABLE,GPIO_PSOR_PTSO(PIN_ENABLE_MOTOR_RIGHT)))


/**
 * @brief Disable DC motor
 */
#define __MOTOR_LEFT_DISABLE	(GPIO_ClearPinsOutput(GPIO_MOTOR_ENABLE,GPIO_PCOR_PTCO(PIN_ENABLE_MOTOR_LEFT)))
#define __MOTOR_RIGHT_DISABLE	(GPIO_ClearPinsOutput(GPIO_MOTOR_ENABLE,GPIO_PCOR_PTCO(PIN_ENABLE_MOTOR_RIGHT)))

/**
 * @brief Set direction for DC motor to FORWARD
 */
#define __MOTOR_LEFT_DIRECTION_FORWARD		(GPIO_SetPinsOutput(GPIO_MOTOR_LEFT,GPIO_PSOR_PTSO(PIN_DIRECTION_MOTOR_LEFT)))
#define __MOTOR_RIGHT_DIRECTION_FORWARD 	(GPIO_SetPinsOutput(GPIO_MOTOR_RIGHT,GPIO_PSOR_PTSO(PIN_DIRECTION_MOTOR_RIGHT)))


/**
 * @brief Set direction for DC motor to BACKWARD
 */
#define __MOTOR_LEFT_DIRECTION_BACKWARD		(GPIO_ClearPinsOutput(GPIO_MOTOR_LEFT,GPIO_PCOR_PTCO(PIN_DIRECTION_MOTOR_LEFT)))
#define __MOTOR_RIGHT_DIRECTION_BACKWARD 	(GPIO_ClearPinsOutput(GPIO_MOTOR_RIGHT,GPIO_PCOR_PTCO(PIN_DIRECTION_MOTOR_RIGHT)))

/**
 * @brief Set the speed for DC motor
 * @param speed Speed to set, must be from 0 to 100
 */
#define __MOTOR_LEFT_SPEED(speed)  (TPM_UpdatePwmDutycycle(TPM_PWM_MOTOR, CHANNEL_PWM_MOTOR_LEFT, kTPM_EdgeAlignedPwm,s))
#define __MOTOR_RIGHT_SPEED(speed) (TPM_UpdatePwmDutycycle(TPM_PWM_MOTOR, CHANNEL_PWM_MOTOR_RIGHT, kTPM_EdgeAlignedPwm,s))


/**
 * @fn void dc_motors_init(void)
 * @brief initialize motors in mode forward direction, set null the speed's motors
 *
 */
void dc_motors_init(void);


#endif /* DC_MOTOR_H_ */
