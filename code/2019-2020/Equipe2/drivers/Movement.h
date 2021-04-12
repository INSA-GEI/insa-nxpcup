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
#define MOVEMENT_CORR_KP 7.0			//1.0 P
#define MOVEMENT_CORR_KI 10000.0		// I
#define SPEED_LIMIT 6000 				//max = 9000 in mm/s
#define Te_s (float)1/6000 				//sample time 6Khz handler rear motors 0.2ms

class Movement{
public:
	
	/**
	  * @brief  constructor Movement object
	  * @param  none
	  * @retval none
	  */
	Movement();
	
	
	/**
	  * @brief  Initialisation 
	  * @param  none
	  * @retval none
	  */
	void init(void);
	
	
	/**
	  * @brief  Set car speed and wheels angle
	  * @param  int speed = car speed to set
	  * 		float angle = wheels angle to set
	  * @retval none
	  */
	void set(int speed, float angle);
	
	/**
	  * @brief  Set car speed 
	  * @param  int speed = car speed to set
	  * @retval none
	  */
	void setSpeed(int speed);
	
	/**
	  * @brief  Set each wheel speed 
	  * @param  int v = car speed
	  * 		float delta = speed delta between right and left wheel
	  * @retval none
	  */
	void setDiff(int speed,float delta);
	
	/**
	  * @brief  Stop the car
	  * @param  none
	  * @retval none
	  */
	void stop(void);
	
	/**
	  * @brief  motor PI controller 
	  * @param 	none
	  * @retval none
	  */
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
	int v_L;
	int v_R;
	
private:
	
	/**
	  * @brief 	Apply speed calculated in previous functions to motors
	  * @param 	none
	  * @retval none
	  */
	void applySpeeds(void);
	
	/**
	  * @brief  Set wheels angle
	  * @param  float angle
	  * @retval none
	  */
	void setAngle(float angle);
	
};

#endif /* MOVEMENT_H_ */
