/*
 * Motor.h
 *
 *  Created on: Dec 7, 2019
 *      Author: User
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <MKL25Z4.h>

#define MOTOR_CAL_SPEED 0.095//	de mm/s -> PWM value

#define MOTOR_LEFT_ENABLE		(GPIOC_PSOR=(1<<0))
#define MOTOR_LEFT_DISABLE		(GPIOC_PCOR=(1<<0))

#define MOTOR_RIGHT_ENABLE		(GPIOC_PSOR=(1<<7))
#define MOTOR_RIGHT_DISABLE		(GPIOC_PCOR=(1<<7))

#define MOTOR_LEFT_FORWARD		(GPIOC_PSOR=(1<<8))
#define MOTOR_LEFT_BACKWARD		(GPIOC_PCOR=(1<<8))

#define MOTOR_RIGHT_FORWARD 	(GPIOA_PSOR =(1<<5))
#define MOTOR_RIGHT_BACKWARD 	(GPIOA_PCOR =(1<<5))

//set forward speed
#define MOTOR_LEFT_FSPEED(s) (TPM0_C5V=(600-(s)))

#define MOTOR_RIGHT_FSPEED(s) (TPM0_C1V=(600-(s)))

//set backward speed
#define MOTOR_LEFT_BSPEED(s) (TPM0_C5V=(s))
#define MOTOR_RIGHT_BSPEED(s) (TPM0_C1V=(s))

void motor_init(void);
#endif /* MOTOR_H_ */
