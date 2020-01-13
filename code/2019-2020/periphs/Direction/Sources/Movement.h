/*
 * Movement.h
 *
 *  Created on: Jan 13, 2020
 *      Author: Guest
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "servo.h"
#include "Motor.h"

#define MOVEMENT_ENTRAXE_COEFF 0.01 // E=15cm

void movement_init(void);
void movement_set(int speed, float angle);
void movement_stop(void);

#endif /* MOVEMENT_H_ */
