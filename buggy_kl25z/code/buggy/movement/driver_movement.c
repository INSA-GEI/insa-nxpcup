/*
 * driver_mouvement.c
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam
 */


//in public for testing purposes only

float targetAngle;//	degrees
int targetSpeedL; //	mm/s
int targetSpeedR; //	mm/s
int actualSpeedL; //	mm/s
int actualSpeedR; //	mm/s


void movement_init(void)
{
	targetAngle=0.0;
	targetSpeedL=0;
	targetSpeedR=0;
	actualSpeedL=targetSpeedL;
	actualSpeedR=targetSpeedR;

	dc_motors_init();
	//servo_init();
	//encoder_init();

}

void movement_set(int speed, float angle) {
	if(speed!=0)
	{
		setAngle(angle);
	}
	//important : set angle before speed, as differential speed is based on angle
	movement_setSpeed(speed);
}


void movement_setSpeed(int speed) {
	if(speed<0)
	{
		stop();
		return;
	}

	if(speed>SPEED_LIMIT)
	{
		speed=SPEED_LIMIT;
	}

	MOTOR_RIGHT_DIRECTION_FORWARD;
	MOTOR_LEFT_DIRECTION_BACKWARD;

	int deltaSpeed=targetAngle*MOVEMENT_ENTRAXE_COEFF*speed;
	targetSpeedL=speed+deltaSpeed;
	targetSpeedR=speed-deltaSpeed;
}


void movement_stop(void) {
	targetSpeedL=0;
	targetSpeedR=0;
	actualSpeedL=0;
	actualSpeedR=0;
	MOTOR_LEFT_SPEED_FORWARD(0);
	MOTOR_RIGHT_SPEED_FORWARD(0);
}


void movement_regulate(void) {
	//GPIOB_PTOR = DEBUG_RED_Pin;
	int err=getLeftSpeed();
	if(err<0){	//detect invalid speed readings
		err=0;
	}

	err=targetSpeedL-err;//calculate error
	if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD)
	{//if error needs correction

		actualSpeedL=actualSpeedL+err*MOVEMENT_CORR_KP;//compensate real speed command
	}

	err=getRightSpeed();
	if(err<0)
	{	//detect invalid speed readings
		err=0;
	}
	err=targetSpeedR-err;
	if(err>MOVEMENT_CORR_THRESHOLD || err<-MOVEMENT_CORR_THRESHOLD){
		actualSpeedR=actualSpeedR+err*MOVEMENT_CORR_KP;
	}

	applySpeeds();
}

void applySpeeds(void)
{
	if(actualSpeedL<0)actualSpeedL=0;
	if(actualSpeedR<0)actualSpeedR=0;
	if(actualSpeedL>SPEED_LIMIT)actualSpeedL=SPEED_LIMIT;
	if(actualSpeedR>SPEED_LIMIT)actualSpeedR=SPEED_LIMIT;

	MOTOR_LEFT_SPEED_FORWARD(actualSpeedL*MOTOR_CAL_SPEED);
	MOTOR_RIGHT_SPEED_FORWARD(actualSpeedR*MOTOR_CAL_SPEED);

}
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
	//servo_setPos(angle);

}
