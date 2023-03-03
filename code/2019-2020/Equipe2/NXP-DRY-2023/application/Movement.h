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
#include "Debug.h"

#include "Encoder.h"

#define MOVEMENT_ENTRAXE_COEFF 0.005//0.0056 	// E=15cm 

#define MOVEMENT_CORR_THRESHOLD 6 		// correct the speed only when we are more than 1 cm/s off target speed
#define MOVEMENT_CORR_KP 1			// amount of error to correct each iteration
#define SPEED_LIMIT 9000 				//	mm/s
 

class Movement{
public:
	Movement();
	void init(void);
	void set(int speed, float angle);
	void setSpeed(int speed);
	void stop(void);
	void regulate(void);
	Encoder encoder; // needed in public for interrupt access
	
	//in public for testing purposes only
	int targetSpeedL; //	mm/s
	int targetSpeedR; //	mm/s
	int actualSpeedL; //	mm/s
	int actualSpeedR; //	mm/s
	
private:
	void applySpeeds(void);
	void setAngle(float angle);
	float targetAngle;//	degrees
	
};

#endif /* MOVEMENT_H_ */
