/*
 * driver_mouvement.c
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#include "driver_movement.h"

const float SPEED_TO_PWM = MOVEMENT_SPEED_LIMIT_PWM/MOVEMENT_SPEED_LIMIT_MM_S;


float targetAngle;	//	degrees
float targetSpeedL; //	mm/s
float targetSpeedR; //	mm/s
float actualSpeedL; //	mm/s
float actualSpeedR; //	mm/s

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

	targetAngle=angle;
	servo_setPos(angle);

}

void applySpeeds(void)
{
	if(actualSpeedL<0.0)actualSpeedL=0.0;
	if(actualSpeedR<0.0)actualSpeedR=0.0;
	if(actualSpeedL>MOVEMENT_SPEED_LIMIT_MM_S)actualSpeedL=MOVEMENT_SPEED_LIMIT_MM_S;
	if(actualSpeedR>MOVEMENT_SPEED_LIMIT_MM_S)actualSpeedR=MOVEMENT_SPEED_LIMIT_MM_S;

	MOTOR_Left_Speed_Forward((int)(actualSpeedL*SPEED_TO_PWM));
	MOTOR_Right_Speed_Forward((int)(actualSpeedR*SPEED_TO_PWM));
	//MOTOR_Left_Speed_Forward(20);
	//MOTOR_Right_Speed_Forward(20);
}

void movement_init()
{
	targetAngle=0.0;
	targetSpeedL=0.0;
	targetSpeedR=0.0;
	actualSpeedL=targetSpeedL;
	actualSpeedR=targetSpeedR;

	MOTOR_init();
	servo_init();
	encoders_init();
	//ptrServoIRQ_Handler = ptrIRQ_Servo;
}

void movement_set(float speed, float angle) {
	if(speed!=0.0)
	{
		setAngle(angle);
	}
	//important : set angle before speed, as differential speed is based on angle
	movement_setSpeed(speed);
	MOTOR_Left_Speed_Forward((int)(targetSpeedL*SPEED_TO_PWM));
	MOTOR_Right_Speed_Forward((int)(targetSpeedL*SPEED_TO_PWM));
}


void movement_setSpeed(float speed) {
	if(speed<0.0)
	{
		movement_stop();
		return;
	}

	if(speed>MOVEMENT_SPEED_LIMIT_MM_S)
	{
		speed=MOVEMENT_SPEED_LIMIT_MM_S;
	}

	//MOTOR_Right_Direction_Forward();
	//MOTOR_Left_Direction_Forward();

	float deltaSpeed=targetAngle*MOVEMENT_ENTRAXE_COEFF*speed;
	targetSpeedL=speed+deltaSpeed;
	targetSpeedR=speed-deltaSpeed;
}


void movement_stop(void) {
	targetSpeedL=0.0;
	targetSpeedR=0.0;
	actualSpeedL=0.0;
	actualSpeedR=0.0;
	MOTOR_Left_Speed_Forward(0);
	MOTOR_Right_Speed_Forward(0);
	MOTOR_Left_Disable();
	MOTOR_Right_Disable();
}


void movement_regulate(void) {
	//GPIOB_PTOR = DEBUG_RED_Pin;
	float err=encoder_getLeftSpeed();
	if(err<0.0){	//detect invalid speed readings
		err=0.0;
	}

	err=targetSpeedL-err;//calculate error
	if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD)
	{//if error needs correction

		actualSpeedL=actualSpeedL+err*MOVEMENT_CORR_KP;//compensate real speed command
	}

	err=encoder_getRightSpeed();
	if(err<0.0)
	{	//detect invalid speed readings
		err=0.0;
	}
	err=targetSpeedR-err;
	if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD){
		actualSpeedR=actualSpeedR+err*MOVEMENT_CORR_KP;
	}

	applySpeeds();
}

