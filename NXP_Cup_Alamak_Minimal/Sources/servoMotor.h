/*
 * servoMotor.h
 *
 *  Created on: Feb 16, 2019
 *      Author: val
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

/*
 * servo.h allows you to use the servo motors 
 * 
 * How to use it :
 * 
 */
 


#include "derivative.h" /* include peripheral declarations */


//define macros 
#define SERVO_CENTER 8600



//this function needs to be called at the beginning of the program 
//it configures the servo to allow you tu use it
//in : void
//out : void
void initServo(void);


//this function set the angle based on the servo's angle that you want
//max wheel's angle : +/-40°
//correspond to +/-7° on the servo
//positive angle is on the left
//in : angle rotation wanted based on central position
//out : void  
void setPositionServo(int angle);


//this function set the compare value that you want
//in : compare value offset of timer
//out : void  
void setCompareValueServo(int cmpValueOffset,int cmpValueOffsetOld);

#endif /* SERVOMOTOR_H_ */
