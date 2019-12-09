/*
 * Motor.h
 *
 *  Created on: Dec 7, 2019
 *      Author: User
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <MKL25Z4.h>


#define MOTOR_LEFT_FORWARD		(GPIOA_PCOR=(1<<5))
#define MOTOR_LEFT_BACKWARD		(GPIOA_PSOR=(1<<5))

#define MOTOR_RIGHT_FORWARD 	(GPIOC_PCOR =(1<<8))
#define MOTOR_RIGHT_BACKWARD 	(GPIOC_PSOR =(1<<8))

#define MOTOR_LEFT_SPEED(s) (TPM0_C1V=(s))
#define MOTOR_RIGHT_SPEED(s) (TPM0_C5V=(s))

void motor_init(void);

#endif /* MOTOR_H_ */
