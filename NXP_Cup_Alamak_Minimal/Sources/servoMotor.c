/*
 * servoMotor.c
 *
 *  Created on: Feb 16, 2019
 *      Author: val
 */


#include "servoMotor.h"





//this function needs to be called at the beginning of the program 
//it configures the servo to allow you tu use it
//in : void
//out : void
void initServo(void){
	
	// set PWM outputs
	PORTA_PCR12 |= PORT_PCR_MUX(3);	// Servo Motor 1 Out  PTA12 TPM1_CH0
	
	// set TPM prescaler before enabling the timer
	TPM1_SC |= 3;					// prescaler for TPM1 (Servo) is 8
	
	// TPM modulo register, set frequency
	TPM1_MOD = 53332;				// modulo TPM1 (Servo), periode = 10 ms (100 Hz)
									// en se basant sur 48Mhz pour le systeme
									// MOD=(Tt*Fclk)/(PSC+1) - 1
	
	// set TPM clock mode to enable timer
	TPM1_SC |= TPM_SC_CMOD(1);		// enable TPM1 (Servo)
	
	// configure TPM channel outputs high-true pulses
	TPM1_C0SC = 0x28;				// TPM1 channel0 Servo 1
	
	// TPM channel value registers, sets duty cycle
	TPM1_C0V = SERVO_CENTER;			// TPM1 channel0 Servo 1 ca. 1.5 ms (middle)
									// en se basant sur 48 MHz
									
	// configure interrupts in TPM1
	TPM1_SC |= TPM_SC_TOIE_MASK;	// enable overflow interrupt in TPM1 (10 ms rate)
	    
	// enable interrupts 18 (TPM = FTM1)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 18);			// clear pending interrupt 18
	NVIC_ISER |= (1 << 18);			// enable interrupt 18								

}


//this function set the angle based on the servo's angle that you want
//max wheel's angle : +/-40°
//correspond to +/-7° on the servo
//positive angle is on the left
//in : angle rotation wanted based on central position
//out : void  
void setPositionServo(int angle){
	//int maxDutyCycleCMP = 9760;
	//int minDutyCycleCMP = 6186;
	int compareValue, servoAngle;
	int centralPosition=90; //degrees
	if (angle > 7){
		angle = 7;
	} else if (angle < -7){
		angle = -7;
	}
	
	servoAngle=centralPosition+angle;	//the central position for the servo is 90 degrees 
										//so the wanted angle is 90+angle
	
	compareValue = SERVO_CENTER*servoAngle/centralPosition;
	
	TPM1_C0V = compareValue;
		
}



//this function set the compare value that you want
//in : compare value offset of timer
//out : void  
void setCompareValueServo(int cmpValueOffset, int cmpValueOffsetOld){
	
	if(cmpValueOffset<-1000)
		{
			cmpValueOffset=-1000;
		}
		else if (cmpValueOffset>1000)
		{
			cmpValueOffset=1000;
		}
	
	//prevent saturation of variation of servo
		if((cmpValueOffset - cmpValueOffsetOld) > 250)
		{
			cmpValueOffset = cmpValueOffsetOld + 250;
		}
		else if ((cmpValueOffset - cmpValueOffsetOld) < -250)
		{
			cmpValueOffset = cmpValueOffsetOld - 250;
		}
		
	// Set channel 0 PWM_Servo position
	TPM1_C0V  = SERVO_CENTER - cmpValueOffset ; 		// set channel 0 PWM_Servo
}


