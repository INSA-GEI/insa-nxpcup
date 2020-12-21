/*
 * Direction.c
 *
 *  Created on: Jan 13, 2020
 *      Author: Guest
 */
#include "Movement.h"
#include "math.h"

int speed=0;

Movement::Movement() {
	targetSpeedL=0;
	targetSpeedR=0;
	actualSpeedL=targetSpeedL;
	actualSpeedR=targetSpeedR;
}

void Movement::init(void) {
	motor_init();
	servo_init();
	encoder.init();
	MOTOR_LEFT_ENABLE;
	MOTOR_RIGHT_ENABLE;
}

void Movement::set(int speed, float angle) {
	if(speed!=0)setAngle(angle);
	setSpeed(speed);//important : set angle before speed, as differential speed is based on angle
}

void Movement::setSpeed(int speed) {
	if(speed<0){
		MOTOR_RIGHT_BACKWARD;
		MOTOR_LEFT_BACKWARD;
	}else{
		MOTOR_LEFT_FORWARD;
		MOTOR_RIGHT_FORWARD;
	}
	
}

void Movement::setDiff(int v,float delta) {
	speed=(int) v;
	if (speed<0){
		targetSpeedL=-speed-delta;
		targetSpeedR=-speed+delta;
	}else{
		targetSpeedL=speed+delta;
		targetSpeedR=speed-delta;
	}
}

void Movement::setAngle(float angle) {
	if(angle>SERVO_MAX_RIGHT_ANGLE)angle=SERVO_MAX_RIGHT_ANGLE;
	if(angle<SERVO_MAX_LEFT_ANGLE)angle=SERVO_MAX_LEFT_ANGLE;
	servo_setPos(angle);
}

void Movement::stop(void) {
	targetSpeedL=0;
	targetSpeedR=0;
	actualSpeedL=0;
	actualSpeedR=0;
	MOTOR_LEFT_FSPEED(0);
	MOTOR_RIGHT_FSPEED(0);
	MOTOR_LEFT_DISABLE;
	MOTOR_RIGHT_DISABLE;
}


void Movement::regulate(void) {
	/*if (speed>0){
		GPIOB_PTOR = DEBUG_RED_Pin;
		int err=encoder.getLeftSpeed();
		if(err<0){	//detect invalid speed readings
			err=0;
		}
		err=targetSpeedL-err;//calculate error
		if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD){//if error needs correction
	
			actualSpeedL=actualSpeedL+err*MOVEMENT_CORR_KP;//compensate real speed command
		}
	
		err=encoder.getRightSpeed();
		if(err<0){	//detect invalid speed readings
			err=0;
		}
		err=targetSpeedR-err;
		if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD){
			actualSpeedR=actualSpeedR+err*MOVEMENT_CORR_KP;
		}
	}else{
		actualSpeedR=targetSpeedR;
		actualSpeedL=targetSpeedL;
	}*/
	//Maintenant le régulateur est un PID dans carControl.cpp
	actualSpeedR=targetSpeedR;
	actualSpeedL=targetSpeedL;
	applySpeeds();
}

void Movement::applySpeeds(void) {
	if(actualSpeedL<0)actualSpeedL=0;
	if(actualSpeedR<0)actualSpeedR=0;
	
	if (speed>=0){
		if(actualSpeedL>SPEED_LIMIT)actualSpeedL=SPEED_LIMIT;
		if(actualSpeedR>SPEED_LIMIT)actualSpeedR=SPEED_LIMIT;
		MOTOR_LEFT_FSPEED(actualSpeedL*MOTOR_CAL_SPEED);
		MOTOR_RIGHT_FSPEED(actualSpeedR*MOTOR_CAL_SPEED);
	}else{
		actualSpeedL*=2;
		actualSpeedR*=2;
		if(actualSpeedL>SPEED_LIMIT)actualSpeedL=SPEED_LIMIT;
		if(actualSpeedR>SPEED_LIMIT)actualSpeedR=SPEED_LIMIT;
		MOTOR_LEFT_BSPEED(actualSpeedL*MOTOR_CAL_SPEED);
		MOTOR_RIGHT_BSPEED(actualSpeedR*MOTOR_CAL_SPEED);
	}
}
