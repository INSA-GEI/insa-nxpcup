/*
 * encoder.h
 *
 *  Created on: Feb 3, 2019
 *      Author: jbsaillan
 */


/*
 * Encoder.h is allows you to use encoders to calculate speed of motors
 * 
 * How to use it :
 * - use "confSpeedEncoder()" in the beginning of the "main()"
 * - use "adaptSpeed()" in the main loop "for(;;)"
 * - use "setSpeedM*()" at any moment to change the desired speed
 * 
 * Note that you may have to change the corrector in "adaptSpeed()"
 */



#ifndef ENCODER_H_
#define ENCODER_H_


#include "derivative.h" /* include peripheral declarations */


#define NMBR_HOLES 1
#define WHEEL_DIAMETER 6.4
#define TPM_MOD_MOTEUR 600
#define MAX_RPM 16000 //rpm //found this in the spec with a +/- 3200 rpm ^^
#define REDUCTION_RATIO (0.2) //Rapport de reduction des engrenages : 17/89


int getFrontTest();

void switchLed(char c);

/*
 * Configure everything so you can use the encoders to calculate the speed
 * - We configure 2 GPIOs : C_5 and A_1
 * - We configure the timer 2
 * This function has to be called before the main loop
 */
void confSpeedEncoder();

/*
 * This interrupt routine allows to count the number of overflows
 */
void FTM2_IRQHandler();


/*
 * This function adapt the pwm sent to the motors to match the desired speed
 *  /!\ you have to call it everytime in the main loop
 *  
 *  How it works :
 * - we try to measure the speed with the encoder
 * - we calculate the error (cmd - real_speed)
 * - we change the pwm by applying a corrector to the error
 */
void adaptSpeed();



/*
 * You choose the desired speed for Motor in cm/s
 * It will update the cmd and later the pwm sent to the motor
 * 
 */
void setSpeed_M1(int speed);
void setSpeed_M2(int speed);



/*
 * --> You don't have to use this function (adaptSpeed already use it) <--
 * Return the speed of the Motor in cm/s
 * /!\We can calculate the speed every falling edge of the encoder
 * /!\If we can't calculate the speed, we return -1
 */
int calculateSpeed_M1();
int calculateSpeed_M2();

/*
 * This fonction traduce the speed in cm/s in duty cycle for the motor's PWM * 
 */
void setDutyCyle(int speed, int numMotor);


#endif /* ENCODER_H_ */
