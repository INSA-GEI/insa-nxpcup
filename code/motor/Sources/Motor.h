/*
 * Motor.h
 *
 *  Created on: Dec 7, 2019
 *      Author: User
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <MKL25Z4.h>


#define MOTOR_LEFT_FORWARD		(GPIOA_PCOR =(1<<5))
#define MOTOR_LEFT_BACKWARD		(GPIOA_PSOR =(1<<5))


void motor_init(void);

#endif /* MOTOR_H_ */
