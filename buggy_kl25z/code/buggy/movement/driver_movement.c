/*
 * driver_mouvement.c
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#include "driver_movement.h"

const float SPEED_TO_PWM = MOVEMENT_SPEED_LIMIT_PWM/MOVEMENT_SPEED_LIMIT_MM_S;


float servoAngle;	//	degrees
float targetSpeedL; //	mm/s
float targetSpeedR; //	mm/s
float actualSpeedL; //	mm/s
float actualSpeedR; //	mm/s
float commandeSpeedL;
float commandeSpeedR;
float erreurIntegralL;
float erreurIntegralR;


//void (*ptrServoIRQ_Handler)(void);

void setAngle(float angle)
{
	if(angle>SERVO_MAX_RIGHT_ANGLE)
	{
		angle=SERVO_MAX_RIGHT_ANGLE;
	}
	if(angle<SERVO_MAX_LEFT_ANGLE)
	{
		angle=SERVO_MAX_LEFT_ANGLE;
	}

	servoAngle=angle;
	servo_setPos(angle);

}

void applySpeeds(void)
{
	if(commandeSpeedL<0.0)commandeSpeedL=0.0;
	if(commandeSpeedR<0.0)commandeSpeedR=0.0;
	if(commandeSpeedL>MOVEMENT_SPEED_LIMIT_MM_S)commandeSpeedL=MOVEMENT_SPEED_LIMIT_MM_S;
	if(commandeSpeedR>MOVEMENT_SPEED_LIMIT_MM_S)commandeSpeedR=MOVEMENT_SPEED_LIMIT_MM_S;

	MOTOR_Left_Speed_Forward((int)(commandeSpeedL*SPEED_TO_PWM));
	MOTOR_Right_Speed_Forward((int)(commandeSpeedR*SPEED_TO_PWM));
}

void movement_init()
{
	servoAngle=0.0;
	targetSpeedL=0.0;
	targetSpeedR=0.0;
	actualSpeedL=0.0;
	actualSpeedR=0.0;
	commandeSpeedL=0.0;
	commandeSpeedR=0.0;
	erreurIntegralL=0.0;
	erreurIntegralR=0.0;

	MOTOR_init();
	servo_init();
	encoders_init();
	//ptrServoIRQ_Handler = ptrIRQ_Servo;
}

void movement_set(float speed, float angle) {
	if(speed != 0.0)
	{
		setAngle(angle);
	}
	//important : set angle before speed, as differential speed is based on angle
	movement_setSpeed(speed);

}


void movement_setSpeed(float speed) {

	float deltaSpeed = 0;
	if(speed<0.0)
	{
		movement_stop();
		return;
	}

	if(speed>MOVEMENT_SPEED_LIMIT_MM_S)
	{
		speed=MOVEMENT_SPEED_LIMIT_MM_S;
	}

	if(speed > 1800)
	{
		deltaSpeed = servoAngle*MOVEMENT_DIFF_GAIN_STRAIGHT*speed;
	}
	else
	{
		deltaSpeed = servoAngle*MOVEMENT_DIFF_GAIN_TURN*speed;
	}

	targetSpeedL=speed+deltaSpeed;
	targetSpeedR=speed-deltaSpeed;
}

void mouvement_start(void){
	MOTOR_Left_Enable();
	MOTOR_Right_Enable();
}


void movement_stop(void) {
	servoAngle = 0.0;
	targetSpeedL=0.0;
	targetSpeedR=0.0;
	actualSpeedL=0.0;
	actualSpeedR=0.0;
	commandeSpeedL=0.0;
	commandeSpeedR=0.0;
	erreurIntegralL=0.0;
	erreurIntegralR=0.0;
	servo_setPos(0);

	MOTOR_Left_Disable();
	MOTOR_Right_Disable();
}


void movement_regulate(void) {
	//GPIOB_PTOR = DEBUG_RED_Pin;

	float err = 0;
	actualSpeedL=encoder_getLeftSpeed();
	actualSpeedR=encoder_getRightSpeed();

	if(actualSpeedL<0.0){	//detect invalid speed readings
		actualSpeedL=0.0;
	}

	err=targetSpeedL-actualSpeedL;//calculate error
	if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD)
	{//if error needs correction
		erreurIntegralL = erreurIntegralL + MOVEMENT_CORR_KI*err;
		commandeSpeedL=err*MOVEMENT_CORR_KP + erreurIntegralL;//compensate real speed command
	}


	if(actualSpeedR<0.0)
	{	//detect invalid speed readings
		actualSpeedR=0.0;
	}
	err=targetSpeedR-actualSpeedR;
	if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD){
		erreurIntegralR = erreurIntegralR + MOVEMENT_CORR_KI*err;
		commandeSpeedR=err*MOVEMENT_CORR_KP + erreurIntegralR;
	}

	applySpeeds();

}

float movement_getServoAngle(void)
{
	return servoAngle;
}

float movement_getSpeedLeft(void)
{
	return (actualSpeedL);
}

float movement_getSpeedRight(void)
{
	return (actualSpeedR);
}
