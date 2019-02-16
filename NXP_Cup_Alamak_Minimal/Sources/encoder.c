/*
 * encoder.c

 *
 *  Created on: Feb 3, 2019
 *      Author: jbsaillan
 */

#include "encoder.h"


/* Variables delcarées pour obtenir la vitesse de moteurs */
int first_measure = 1; //if this is the first measure we sould not calculate the speed
int lastValue_M1 = 0;	//Last value of the timer will be stored
int lastValue_M2 = 0;
int countOverflows_M1 = 0; //Number of overflows will be stored
int countOverflows_M2 = 0;
int previousM1 = 0;	//Previous value retourned by the encoder
int previousM2 = 0;
int actualM1 = 0;	//Actual value returned by the encoder
int actualM2 = 0;

/*Variables pour controler la vitesse */
int speedCmd_M1 = 10; //desired speed in cm/s for M1
int speedCmd_M2 = 10; //desired speed in cm/s for M2
int pwmCmd_M1 = 10; //Cmd sent directly via PWm to the motors
int pwmCmd_M2 = 10;
int speedMeasured_M1; //Real speed measured by the motor (or -1 if we can't calculate it)
int speedMeasured_M2; 

int speed_print1 = -1;
int speed_print2 = -1;
int front1 = -1;
int front2 = -1;
int front_test = 0;

int getFrontTest() {
	return front_test;
}

void switchLed(char c) {
	if(c == 'r') {
		GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<18);  // red LED on
		GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
		GPIOD_PDOR |= GPIO_PDOR_PDO(1<<1);    // blue LED off	
	} else if (c == 'b') {
		GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off
		GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
		GPIOD_PDOR &= ~GPIO_PDOR_PDO(1<<1);   // blue LED on
	}else if (c == 'g') {
		GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off
		GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<19);  // green LED on
		GPIOD_PDOR |= GPIO_PDOR_PDO(1<<1);    // blue LED off	
	}
}


/*
 * Configure everything so you can use the encoders to calculate the speed
 * - We configure 2 GPIOs : C_5 and A_1
 * - We configure the timer 2
 * This function has to be called before the main loop
 */
void confSpeedEncoder() {
	/*
	 * Configuration à revoir notement u niveau des 2 GPIO :
	 * 	- on veut PORTC_PCR5 et PORTA_PCR1 comme input
	 * 	- on veut lancer le Timer 2 et autoriser les interruptions à l'overflow
	 */
	
	//PTC4 SPEED 1
	PORTC_PCR5 |= PORT_PCR_MUX(1); //Config GPIOs function 
	PORTC_PCR5 |= (1) + (1<<1);
	//PTC1 SPEED 2
	PORTA_PCR1 |= PORT_PCR_MUX(1); //Config GPIOs function 
	PORTA_PCR1 |= (1) + (1<<1);
	
	//Set to input
	GPIOC_PDDR &= ~(1<<5); //PTC4 SPEED 1
	GPIOA_PDDR &= ~(1<<1); //PTA1 SPEED 2

	//Config of TIMER2 as a time reference such as it has a 10ms period
	TPM2_SC |= TPM_SC_CMOD(1);		//Enable TIMER2
	TPM2_SC |= 3; 					//Prescale Factor Selection
	TPM2_SC |= TPM_SC_TOIE_MASK;	//Enable interrupt when overlow
	TPM2_SC &= ~TPM_SC_CPWMS_MASK;	//Up-counting mode
	TPM2_MOD= 53332;				//Overflow at maximum value	
	
	//NVIC Config for TIMER 2
	NVIC_ICPR |= (1 << 19);	// clear pending interrupt 19
	NVIC_ISER |= (1 << 19);	//Enable interrupt 19 (related to TIM2)
}


/*
 * This interrupt routine allows to count the number of overflows
 */
void FTM2_IRQHandler() {
	//Clear ISR Flag
	TPM2_SC |= 0x80; 
	
	//We add an overflow
	countOverflows_M1++;
	countOverflows_M2++;
}


/*
 * This function adapt the pwm sent to the motors to match the desired speed
 * - we try to measure the speed with the encoder
 * - we calculate the error (cmd - real_speed)
 * - we change the pwm by applying a corrector to the error
 */
void adaptSpeed() {
	int error_M2, error_M1;
	//correctors' gain
	int Kp=15;
	int Kd,Ki;
	//We try to measure the reel speed
	speedMeasured_M1 = calculateSpeed_M1();
	if(speedMeasured_M1 != -1) {
		speed_print1 = speedMeasured_M1;
		error_M1 = speedCmd_M1 - speedMeasured_M1;
		
		//We apply a proportional corrector (it has to be defined)
		pwmCmd_M1 = Kp*error_M1; //  <---------- we have to change it
		
		//We change the pwm cmd that goes to the motor
		setDutyCyle(pwmCmd_M1,1);
	}
	
	//We try to measure the reel speed
	speedMeasured_M2 = calculateSpeed_M2();
	if(speedMeasured_M2 != -1) {
		speed_print2 = speedMeasured_M2;
		error_M2 = speedCmd_M2 - speedMeasured_M2;
		//We apply a proportional corrector (it ahs to be defined)
		pwmCmd_M2 = Kp*(error_M2); //  <---------- we have to change it
		
		//We change the pwm cmd that oes to the motor
		setDutyCyle(pwmCmd_M2,2);
	}
			
}



/*
 * You choose the desired speed for Motor2 in cm/s
 * It will update the cmd and later the pwm sent to the motor
 * 
 */
void setSpeed_M2(int speed) {
	speedCmd_M2 = speed;
}

/*
 * You choose the desired speed for Motor1 in cm/s
 * It will update the cmd and later the pwm sent to the motor
 * 
 */
void setSpeed_M1(int speed) {
	speedCmd_M1 = speed;
}


/*
 * Return the speed of the Motor 1 in cm/s
 * /!\We can calculate the speed every falling edge of the encoder
 * /!\If we can't calculate the speed, we return -1
 */
int calculateSpeed_M1() {
	int elapsedTime;
	int timePerTurn;
	int speed;
	int timerCount;
	
	previousM1 = actualM1;
	actualM1 = GPIOA_PDIR & (1<<1); //we read the encoder

	
	if(previousM1 == (0<<1) && actualM1 == (1<<1)) {
		//Here, we detect a falling edge
		front_test++;
		
		//We calculate the elapsed time between 2 holes
		timerCount = TPM2_CNT &(0xFFFF);
		//Period*(number of ticks)/(tiks per period)
		elapsedTime = 10*(timerCount - lastValue_M1 + 60000*countOverflows_M1)/(60000); //Elapsed time in ms
		timePerTurn = NMBR_HOLES*elapsedTime; //Time for one whole turn 
		
		//Speed in cm/s
		speed = 1000*(3.14159265359*WHEEL_DIAMETER)/(timePerTurn); 
		
		lastValue_M1 = timerCount; //Reset the values so we can count again from now
		countOverflows_M1 = 0;
	} else {
		speed = -1;
	}
	
	return speed;
}


/*
 * Return the speed of the Motor 2 in cm/s
 * /!\We can calculate the speed every falling edge of the encoder
 * /!\If we can't calculate the speed, we return -1
 */
int calculateSpeed_M2() {
	int elapsedTime;
	int timePerTurn;
	int speed;
	int timerCount;
	
	previousM2 = actualM2;
	actualM2 = GPIOC_PDIR & (1<<5); //we read the encoder 
	
	if(previousM2 == (0<<5) && actualM2 == (1<<5)) {
		//Here, we detect a falling edge
		
		//We calculate the elapsed time between 2 holes
		timerCount = TPM2_CNT &(0xFFFF);
		//Period*(number of ticks)/(tiks per period)
		elapsedTime = 10*(timerCount - lastValue_M2 + 60000*countOverflows_M2)/(60000); //Elapsed time in ms
		timePerTurn = NMBR_HOLES*elapsedTime; //Time for one whole turn 
		
		//Speed in cm/s
		speed = 1000*(3.14159265359*WHEEL_DIAMETER)/(timePerTurn); 
		
		lastValue_M2 = timerCount; //Reset the values so we can count again from now
		countOverflows_M2 = 0;

	} else {
		speed = -1;
	}
	
	return speed;
}



/*
 * This fonction traduce the speed in cm/s in duty cycle for the motor's PWM 
 * numMotor = 1 for left motor 
 * numMotor = 2 for right motor 
 */
void setDutyCyle(int speed, int numMotor){

	int maxSpeed = 3.14*MAX_RPM*(WHEEL_DIAMETER)*REDUCTION_RATIO/60; //maximum speed in cm/s

	if (numMotor == 1 || numMotor ==2){ // check if the motor label is good 
		//H-Bridge protection
		if (speed > 0.95*maxSpeed){
			speed = 0.95*maxSpeed;
		}
		else if (speed < 0.05*maxSpeed) {
			speed = 0.05*maxSpeed;
		}
		//setting duty cycle for the choosen motor
		if (numMotor ==1 ){ //left motor
			TPM0_C1V = speed*TPM_MOD_MOTEUR/maxSpeed;
		} else if (numMotor == 2){ //rigth motor 
			TPM0_C5V = speed*TPM_MOD_MOTEUR/maxSpeed;
		}
	}
}


