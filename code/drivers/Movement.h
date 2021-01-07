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

#define MOVEMENT_ENTRAXE_COEFF 0.005//0.0056 	// E=15cm 
#define LENGHT_CAR 200 //en mm
#define L_ENTRAXE 150 //en mm 

#define MOVEMENT_CORR_THRESHOLD 6 		// correct the speed only when we are more than 1 cm/s off target speed
#define MOVEMENT_CORR_KP 1.0			// P
#define MOVEMENT_CORR_KI 600.0// I
#define SPEED_LIMIT 9000				//	mm/s
#define Te_s (float)1/6000 //sample time 6Khz handler rear motors 0.2ms

class Movement{
public:
	Movement();
	void init(void);
	void set(int speed, float angle);
	void setSpeed(int speed);
	void setDiff(int speed,float delta);
	void stop(void);
	void regulate(void);
	Encoder encoder; // needed in public for interrupt access
	
	//in public for testing purposes only
	int targetSpeedL; //	mm/s
	int targetSpeedR; //	mm/s
	int actualSpeedL; //	mm/s
	int actualSpeedR; //	mm/s
	
	//Pour regulate() pour le PI
	int err_L;
	int err_R;
	int err_old_L;
	int err_old_R;
	
private:
	void applySpeeds(void);
	void setAngle(float angle);
	
};

#endif /* MOVEMENT_H_ */
