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
	//Coeff PI rear_motors
	speed=0;
	err_L=0;
	err_R=0;
	err_old_L=0;
	err_old_R=0;
	v_L=0;
	v_R=0;
}

void Movement::init(float Te_s) {
	motor_init();
	servo_init();
	encoder.init();
	MOTOR_LEFT_ENABLE;
	MOTOR_RIGHT_ENABLE;
	
	K_e_s=((2.0*MOVEMENT_CORR_KP+Te_s*MOVEMENT_CORR_KI)/2.0);
	K_e_s_old=((Te_s*MOVEMENT_CORR_KI-2.0*MOVEMENT_CORR_KP)/2.0);
}

void Movement::set(int speed, float angle) {
	setAngle(angle);
	//setSpeed(speed);//important : set angle before speed, as differential speed is based on angle
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
	targetSpeedL=speed+delta;
	targetSpeedR=speed-delta;
}

void Movement::setAngle(float angle) {
	if(angle>SERVO_MAX_RIGHT_ANGLE)angle=SERVO_MAX_RIGHT_ANGLE;
	if(angle<SERVO_MAX_LEFT_ANGLE)angle=SERVO_MAX_LEFT_ANGLE;
	servo_setPos(angle);
}

void Movement::stop(void) {
	v_L=0;
	v_R=0;
	err_L=0;
	err_R=0;
	err_old_L=0;
	err_old_R=0;
	targetSpeedL=0;
	targetSpeedR=0;
	actualSpeedL=0;
	actualSpeedR=0;
	MOTOR_LEFT_FSPEED(0);
	MOTOR_RIGHT_FSPEED(0);
}


void Movement::regulate(void) {
	if (speed!=0){
		FGPIOB->PTOR = DEBUG_RED_Pin;
		//LEFT
		err_old_L=err_L;
		v_L=encoder.getLeftSpeed();		
		err_L=targetSpeedL-v_L;//calculate error	
		
		actualSpeedL=actualSpeedL+(int)(err_L*K_e_s)+(int)(err_old_L*K_e_s_old); //compensate real speed command
		
		//RIGHT
		err_old_R=err_R;
		v_R=encoder.getRightSpeed();
		err_R=targetSpeedR-v_R;
		
		actualSpeedR=actualSpeedR+(int)(err_R*K_e_s)+(int)(err_old_R*K_e_s_old); //compensate real speed command
			
	}else{
		stop();
	}
	
	applySpeeds();
}

void Movement::applySpeeds(void) {
	if(actualSpeedL>SPEED_LIMIT)actualSpeedL=SPEED_LIMIT;
	if(actualSpeedR>SPEED_LIMIT)actualSpeedR=SPEED_LIMIT;
	if(actualSpeedL<-SPEED_LIMIT)actualSpeedL=-SPEED_LIMIT;
	if(actualSpeedR<-SPEED_LIMIT)actualSpeedR=-SPEED_LIMIT;
	
	//On regarde si on avance ou on freine
	if (actualSpeedL>=0){
		MOTOR_LEFT_FORWARD;
		MOTOR_LEFT_FSPEED(actualSpeedL*MOTOR_CAL_SPEED);
	}else{
		MOTOR_LEFT_BACKWARD;
		MOTOR_LEFT_BSPEED((-actualSpeedL)*MOTOR_CAL_SPEED);
	}
	if (actualSpeedR>=0){
		MOTOR_RIGHT_FORWARD;
		MOTOR_RIGHT_FSPEED(actualSpeedR*MOTOR_CAL_SPEED);
	}else{
		MOTOR_RIGHT_BACKWARD;
		MOTOR_RIGHT_BSPEED((-actualSpeedR)*MOTOR_CAL_SPEED);
	}
}
