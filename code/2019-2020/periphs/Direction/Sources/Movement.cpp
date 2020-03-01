/*
 * Direction.c
 *
 *  Created on: Jan 13, 2020
 *      Author: Guest
 */
#include "Movement.h"



Movement::Movement() {
	targetAngle=0.0;
	targetSpeedL=0;
	targetSpeedR=0;
	interruptCounter=0;
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
	setAngle(angle);
	setSpeed(speed);//important : set angle before speed, as differential speed is based on angle
}

void Movement::setSpeed(int speed) {
	if(speed<0){
		stop();
		return;
	}
	if(speed>SPEED_LIMIT)speed=SPEED_LIMIT;
	MOTOR_LEFT_FORWARD;
	MOTOR_RIGHT_FORWARD;
	int deltaSpeed=targetAngle*MOVEMENT_ENTRAXE_COEFF*speed;

	/*int dl=speed+deltaSpeed;
	int dr=speed-deltaSpeed;
	
	actualSpeedL+=dl-targetSpeedL;
	actualSpeedR+=dl-targetSpeedR;
	targetSpeedL=dl;
	targetSpeedR=dr;*/
	targetSpeedL=speed+deltaSpeed;
	targetSpeedR=speed-deltaSpeed;
	actualSpeedL=targetSpeedL;
	actualSpeedR=targetSpeedR;
	applySpeeds();

}

void Movement::setAngle(float angle) {
	if(angle>SERVO_MAX_RIGHT_ANGLE)angle=SERVO_MAX_RIGHT_ANGLE;
	if(angle<SERVO_MAX_LEFT_ANGLE)angle=SERVO_MAX_LEFT_ANGLE;
	targetAngle=angle;
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
	GPIOB_PTOR = DEBUG_RED_Pin;
	if(++interruptCounter>=MOVEMENT_INTERRUPT_MOD){
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
		
		applySpeeds();
		interruptCounter=0;
	}

}

void Movement::applySpeeds(void) {
	if(actualSpeedL<0)actualSpeedL=0;
	if(actualSpeedR<0)actualSpeedR=0;
	if(actualSpeedL>SPEED_LIMIT)actualSpeedL=SPEED_LIMIT;
	if(actualSpeedR>SPEED_LIMIT)actualSpeedR=SPEED_LIMIT;

	MOTOR_LEFT_FSPEED(actualSpeedL*MOTOR_CAL_SPEED);
	MOTOR_RIGHT_FSPEED(actualSpeedR*MOTOR_CAL_SPEED);
}
