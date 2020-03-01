/*
 * servo.h
 *
 *  Created on: Dec 8, 2019
 *      Author: thomas
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <MKL25Z4.h>


#define SERVO_MASK_TPM1_PRESCALER 3	//3=(11)2 => clock divided by 8 (see datasheet p553)
#define SERVO_TPM1_ARR 60000			//Value of the auto-reload of the TIMER

#define SERVO_SET_CHANNEL_0 0x28 		//Set these bits to configure channel 0 on "Edge-aligned PWM" with "high true pulses" configuration

#define  SERVO_CENTER_POS 7280		// initial servo position (center)
#define SERVO_HARD_LEFT 8030
#define SERVO_HARD_RIGHT 6530

#define SERVO_MAX_LEFT_ANGLE -35.0
#define SERVO_MAX_RIGHT_ANGLE 35.0
//Configuration of the pins/clock
void servo_init(void);

void servo_setPos(int angle);


#endif /* SERVO_H_ */
