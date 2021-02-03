/*
 * Direction.c
 *
 *  Created on: Jan 13, 2020
 *      Author: Guest
 */
#include "Movement.h"
#include "math.h"

int speed=0;
float K_e_s=0.0;
float K_e_s_old=0.0;

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
	//Coeff PI rear_motors
	speed=0;
	err_L=0;
	err_R=0;
	err_old_L=0;
	err_old_R=0;
	v_L=0;
	v_R=0;
	K_e_s=((2.0*MOVEMENT_CORR_KP+Te_s*MOVEMENT_CORR_KI)/2.0);
	K_e_s_old=((Te_s*MOVEMENT_CORR_KI-2.0*MOVEMENT_CORR_KP)/2.0);
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
	if (speed!=0){
		GPIOB_PTOR = DEBUG_RED_Pin;
		//LEFT
		err_old_L=err_L;
		v_L=encoder.getLeftSpeed();
		if(v_L<0){	//detect invalid speed readings
			err_L=0;
		}
		err_L=targetSpeedL-v_L;//calculate error
		//if(err_L>MOVEMENT_CORR_THRESHOLD || err_L<-MOVEMENT_CORR_THRESHOLD){//if error needs correction
			
			actualSpeedL=actualSpeedL+(int)(err_L*K_e_s)+(int)(err_old_L*K_e_s_old); //compensate real speed command
			//actualSpeedL=actualSpeedL+err_L*MOVEMENT_CORR_KP;
		//}
		
		//RIGHT
		err_old_R=err_R;
		v_R=encoder.getRightSpeed();
		if(v_R<0){	//detect invalid speed readings
			err_R=0;
		}
		err_R=targetSpeedR-v_R;
		//if(err_R>MOVEMENT_CORR_THRESHOLD || err_R<-MOVEMENT_CORR_THRESHOLD){
			actualSpeedR=actualSpeedR+(int)(err_R*K_e_s)+(int)(err_old_R*K_e_s_old); //compensate real speed command
			//actualSpeedR=actualSpeedR+err_R*MOVEMENT_CORR_KP;
		//}
	}else{
		actualSpeedR=0;
		actualSpeedL=0;
	}
	
	applySpeeds();
}

void Movement::applySpeeds(void) {
	if(actualSpeedL>SPEED_LIMIT)actualSpeedL=SPEED_LIMIT;
	if(actualSpeedR>SPEED_LIMIT)actualSpeedR=SPEED_LIMIT;
	if(actualSpeedL<0)actualSpeedL=0;
	if(actualSpeedR<0)actualSpeedR=0;
	
	if (speed>=0){
		MOTOR_LEFT_FSPEED(actualSpeedL*MOTOR_CAL_SPEED);
		MOTOR_RIGHT_FSPEED(actualSpeedR*MOTOR_CAL_SPEED);
	}else{
		MOTOR_LEFT_BSPEED(actualSpeedL*MOTOR_CAL_SPEED);
		MOTOR_RIGHT_BSPEED(actualSpeedR*MOTOR_CAL_SPEED);
	}
}
