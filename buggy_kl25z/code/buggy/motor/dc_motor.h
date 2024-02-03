/*
 * dc_motor.h
 *
 *  Created on: 3 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "MKL25Z4.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_tpm.h"

/**
 * Board's configurations for DC motor used in this drivers
 * 	- PTA4 : Motor Right In 1 (PWM for speed)
 * 	- PTA5 : Motor Right In 2 (GPIO for direction)
 * 	- PTC7 : Motor Right Enable
 * 	- PTA9 : Motor Left In 2 (PWM for speed)
 * 	- PTA8 : Motor Left In 1 (GPIO for direction)
 * 	- PTC0 : Motor Right Enable
 * 	- TPM0 : PWM for both motors
 * 		+ Channel 1 : PWM for motor Right
 * 		+ Channel 5 : PWM for motor Left
 *
 *
 *  Attention :
 *  The buggy uses 2 Half-Bridge to control each motor because the H-Bridge doesn't have a Direction pin.
 *  Therefore, the Direction Pin in this code is actually a second PWM signal for the motor.
 *  The logic works like this:
 *  	- When Direction = Forward (i.e second PWM has 100% duty cycle), the speed of the motor is (100% - duty cycle of PWM pin)
 *  	- When Direction = Backward (i.e second PWM has 0% duty cycle), the speed of the motor is (duty cycle of PWM pin)
 *  This explains why we need 2 different functions for changing the speed of a motor (1 for Forward and 1 for Backward)
 */

/*Motors's Constants*/
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
 * @fn void dc_motors_init(void)
 * @brief initialize motors in mode forward direction, set null the speed's motors
 *
 */
void MOTOR_init(void);

/**
 * @fn void MOTOR_Left_Enable(void)
 * @brief Enable left motor
 */
void MOTOR_Left_Enable(void);
/**
 * @fn void MOTOR_Right_Enable(void)
 * @brief Enable right motor
 */
void MOTOR_Right_Enable(void);

/**
 * @fn void MOTOR_Left_Disable(void)
 * @brief Disable left motor
 */
void MOTOR_Left_Disable(void);

/**
 * @fn void MOTOR_Right_Disable(void)
 * @brief Disable right motor
 */
void MOTOR_Right_Disable(void);


/**
 * @fn void MOTOR_Left_Direction_Forward (void)
 * @brief Set direction for left motor to Forward
 */
void MOTOR_Left_Direction_Forward(void);

/**
 * @fn void MOTOR_Right_Direction_Forward (void)
 * @brief Set direction for right motor to Forward
 */
void MOTOR_Right_Direction_Forward(void);

/**
 * @fn void MOTOR_Left_Direction_Backward(void)
 * @brief Set direction for left motor to Backward
 */
void MOTOR_Left_Direction_Backward(void);

/**
 * @fn void MOTOR_Right_Direction_Backward(void)
 * @brief Set direction for right motor to Backward
 */
void MOTOR_Right_Direction_Backward(void);

/**
 * @fn void MOTOR_Left_Speed_Forward(speed)
 * @brief Set the speed for left motor for Forward rotation
 * @param speed Speed to set, must be from 0 to 100
 */
void MOTOR_Left_Speed_Forward(uint8_t speed);

/**
 * @fn void MOTOR_Right_Speed_Forward(speed)
 * @brief Set the speed for right motor for Forward rotation
 * @param speed Speed to set, must be from 0 to 100
 */
void MOTOR_Right_Speed_Forward(uint8_t speed);

/**
 * @fn void MOTOR_Left_Speed_Backward(speed)
 * @brief Set the speed for left motor for Backward rotation
 * @param speed Speed to set, must be from 0 to 100
 */
void MOTOR_Left_Speed_Backward(uint8_t speed);

/**
 * @fn void MOTOR_Right_Speed_Backward(speed)
 * @brief Set the speed for right motor for Backward rotation
 * @param speed Speed to set, must be from 0 to 100
 */
void MOTOR_Right_Speed_Backward(uint8_t speed);

#ifdef __cplusplus
}
#endif

#endif /* DC_MOTOR_H_ */
