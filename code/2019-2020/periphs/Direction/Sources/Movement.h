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
#include "Encoder.h"

#define MOVEMENT_ENTRAXE_COEFF 0.075 // E=15cm

#define MOVEMENT_CORR_THRESHOLD 10 // correct speed only when we are more than 1 cm/s off 

const unsigned int SPEED_LIMIT=3000; //	mm/s

class Movement{
public:
	Movement();
	void init(void);
	void set(int speed, float angle);
	void setSpeed(int speed);
	void setAngle(float angle);
	void stop(void);
	void regulate(void);
private:
	Encoder myEncoder;
	int targetSpeedL; //	mm/s
	int targetSpeedR; //	mm/s
	float targetAngle;//	degrees
};

#endif /* MOVEMENT_H_ */
