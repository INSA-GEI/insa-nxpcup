/*
 * driver_encoder.h
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */
#ifndef ENCODER_DRIVER_ENCODER_H_
#define ENCODER_DRIVER_ENCODER_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_tpm.h"
#include "fsl_port.h"
#include "movement/driver_movement.h"
/**
 * Attention :
 * In the movement, we use max speed = 9 m/s ~ 50% PWM
 *
 * Board's configurations for Encoder used in this drivers
 *	- TPM2 : Inputs capture compare for Encoders
 * 		+ Channel 1 : Input for signal A of Right Encoder
 * 		+ Channel 0 : Input for signal A of Left Encoder
 *	- Interrupt enable :
 *		+ Interrupt TPM2
 *		+ Interrupt channel 0 TPM2
 *		+ Interrupt channel 1 TPM2
 *		+ Interrupt Overflow TPM2
 *
 */

#define NUMBER_RISING_FRONT_PER_ROUND		360.0					//Resolution of the encoder : 1 degree
#define PI 									3.14159265359			//Constant Pi
#define WHEEL_DIAMETER 						65.0					//Wheel diameter in mm
#define CPU_FREQUENCY 						48000000UL				//Frequency of Intern Clock
#define ENCODERS_TPM_PRESCALER 				128 					//Divides the clock by 8
#define ENCODERS_TPM_AUTORELOAD 			65535
#define ENCODERS_MAX_OVF 					6 						//If no pulse for 1sec, reset speed count to invalid.
#define ENCODER_PORT 						PORTB
#define ENCODER_GPIO 						GPIOB
#define ENCODER_PIN_SA_LEFT 				2						//PB2 : CH0 TPM2
#define ENCODER_PIN_SA_RIGHT 				3						//PB3 : CH1 TPM2
#define ENCODERS_TPM 						TPM2
#define ENCODERS_TPM_CHANNEL_LEFT 			0
#define ENCODERS_TPM_CHANNEL_RIGHT			1

void encoders_IRQHandler(void);


/**
 * @fn void encoders_init(void)
 * @brief initialize encoders
 *
 */
void encoders_init(void);

/**
 * @fn float encoder_getLeftSpeed(void)
 * @brief calculate the speed from the left encoder
 * @return Left Motor's Speed in mm/s :float
 */
float encoder_getLeftSpeed(void);

/**
 * @fn float encoder_getLeftSpeed(void)
 * @brief calculate the speed from the left encoder
 * @return Right Motor's Speed in mm/s :float
 */
float encoder_getRightSpeed(void);

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_DRIVER_ENCODER_H_ */


