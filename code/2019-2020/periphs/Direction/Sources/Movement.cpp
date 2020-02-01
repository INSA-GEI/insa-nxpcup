/*
 * Direction.c
 *
 *  Created on: Jan 13, 2020
 *      Author: Guest
 */
#include "Movement.h"


Encoder myEncoder;

Movement::Movement() {
	targetAngle=0.0;
	targetSpeedL=0;
	targetSpeedR=0;
}

void Movement::init(void) {
	motor_init();
	servo_init();
	myEncoder.init();
	MOTOR_LEFT_ENABLE;
	MOTOR_RIGHT_ENABLE;
}

void Movement::set(int speed, float angle) {
	setAngle(angle);
	setSpeed(speed);//important : set angle before speed, as differential speed is based on angle
}

void Movement::setSpeed(int speed) {
	if(speed<=0){
		stop();
		return;
	}
	if(speed>SPEED_LIMIT)speed=SPEED_LIMIT;
	MOTOR_LEFT_FORWARD;
	MOTOR_RIGHT_FORWARD;
	int deltaSpeed=targetAngle*MOVEMENT_ENTRAXE_COEFF*speed;
	
	targetSpeedL=speed+deltaSpeed;
	targetSpeedR=speed-deltaSpeed;

	MOTOR_LEFT_FSPEED(targetSpeedL*MOTOR_CAL_SPEED);
	MOTOR_RIGHT_FSPEED(targetSpeedR*MOTOR_CAL_SPEED);
	
}

void Movement::setAngle(float angle) {
	if(angle>SERVO_MAX_RIGHT_ANGLE)angle=SERVO_MAX_RIGHT_ANGLE;
	if(angle<SERVO_MAX_LEFT_ANGLE)angle=SERVO_MAX_LEFT_ANGLE;
	targetAngle=angle;
	servo_setPos(angle);
}

void Movement::stop(void) {
	MOTOR_LEFT_FSPEED(0);
	MOTOR_RIGHT_FSPEED(0);
	MOTOR_LEFT_DISABLE;
	MOTOR_RIGHT_DISABLE;
}


void Movement::regulate(void) {
	int err_left=targetSpeedL-myEncoder.getLeftSpeed();
	int err_right=targetSpeedR-myEncoder.getRightSpeed();
	
	if(err_left>)
	
}
