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
#include "Debug.h"

#define MOVEMENT_ENTRAXE_COEFF 0.075 	// E=15cm : Vdiff=E/2*speed*tan(theta) approx.= E/2*speed*theta

#define MOVEMENT_CORR_THRESHOLD 6 		// correct the speed only when we are more than 1 cm/s off target speed
#define MOVEMENT_CORR_KP .1			// amount of error to correct each iteration
#define SPEED_LIMIT 9000 				//	mm/s
#define MOVEMENT_INTERRUPT_MOD 1		//Modulo for interrupts regulation, divide from approx 6kHz to 1kHz //Maybe not a good idea 

class Movement{
public:
	Movement();
	void init(void);
	void set(int speed, float angle);
	void setSpeed(int speed);
	void setAngle(float angle);
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
	float targetAngle;//	degrees
	int interruptCounter;//	interrupt counter to reduce  
	
};

#endif /* MOVEMENT_H_ */
