/*
 * Motor.h
 *
 *  Created on: Dec 7, 2019
 *      Author: User
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <MKL25Z4.h>

#define MOTOR_CAL_SPEED 0.058//	de mm/s -> PWM value

#define MOTOR_LEFT_ENABLE		(GPIOC->PSOR=(1<<0))
#define MOTOR_LEFT_DISABLE		(GPIOC->PCOR=(1<<0))

#define MOTOR_RIGHT_ENABLE		(GPIOC->PSOR=(1<<7))
#define MOTOR_RIGHT_DISABLE		(GPIOC->PCOR=(1<<7))

#define MOTOR_LEFT_FORWARD		(GPIOC->PSOR=(1<<8))
#define MOTOR_LEFT_BACKWARD		(GPIOC->PCOR=(1<<8))

#define MOTOR_RIGHT_FORWARD 	(GPIOA->PSOR =(1<<5))
#define MOTOR_RIGHT_BACKWARD 	(GPIOA->PCOR =(1<<5))

//set forward speed
#define MOTOR_LEFT_FSPEED(s) (TPM0->CONTROLS[5].CnV=(600-(s)))

#define MOTOR_RIGHT_FSPEED(s) (TPM0->CONTROLS[1].CnV=(600-(s)))

//set backward speed
#define MOTOR_LEFT_BSPEED(s) (TPM0->CONTROLS[5].CnV=(s))
#define MOTOR_RIGHT_BSPEED(s) (TPM0->CONTROLS[1].CnV=(s))

void motor_init(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTOR_H_ */
