/*
 * servo.h
 *
 *  Created on: Dec 8, 2019
 *      Author: thomas
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <MKL25Z4.h>


#define MASK_TPM1_PRESCALER 3	//3=(11)2 => clock divided by 8 (see datasheet p553)
#define TPM1_ARR 60000			//Value of the auto-reload of the TIMER

#define SET_CHANNEL_0 0x28 		//Set these bits to configure channel 0 on "Edge-aligned PWM" with "high true pulses" configuration


//Configuration of the pins/clock
void servo_init(void);


#endif /* SERVO_H_ */
