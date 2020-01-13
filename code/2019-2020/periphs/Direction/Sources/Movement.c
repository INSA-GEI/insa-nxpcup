/*
 * Direction.c
 *
 *  Created on: Jan 13, 2020
 *      Author: Guest
 */
#include "Movement.h"

void movement_init(void){
	motor_init();
	servo_init();
	MOTOR_LEFT_ENABLE;
	MOTOR_RIGHT_ENABLE;
}
void movement_set(int speed, float angle){
	if(angle>SERVO_MAX_RIGHT_ANGLE)angle=SERVO_MAX_RIGHT_ANGLE;
	if(angle<SERVO_MAX_LEFT_ANGLE)angle=SERVO_MAX_LEFT_ANGLE;
	if(speed<MOTOR_MAXSPEED && speed>-MOTOR_MAXSPEED){
		int deltaSpeed=angle*MOVEMENT_ENTRAXE_COEFF;
		servo_setPos(angle);
		if(speed>=0){
			MOTOR_LEFT_FORWARD;
			MOTOR_RIGHT_FORWARD;
			MOTOR_LEFT_FSPEED(speed+deltaSpeed);
			MOTOR_RIGHT_FSPEED(speed-deltaSpeed);
		}else{
			MOTOR_LEFT_BACKWARD;
			MOTOR_RIGHT_BACKWARD;
			MOTOR_LEFT_BSPEED(deltaSpeed-speed);
			MOTOR_RIGHT_BSPEED(-deltaSpeed-speed);
		}
	}
}

void movement_stop(void){
	MOTOR_LEFT_FSPEED(0);
	MOTOR_RIGHT_FSPEED(0);
	MOTOR_LEFT_DISABLE;
	MOTOR_RIGHT_DISABLE;
}
