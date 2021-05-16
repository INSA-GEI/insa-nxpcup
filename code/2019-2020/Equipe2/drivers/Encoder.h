/*
 * encoder.h
 *
 *  Created on: Jan 23, 2020
 *      Author: thomas
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <MKL25Z4.h>
#include "Debug.h"
//wheel diameter = 6.5cm
// 360/(Pi*D) fronts/m.s

//if max speed = 2m/s <=> Pulses/s=speed*360/(Pi*D)=3526 pulses/s
//Resolution souhaitee : 2000pts/65535pts tot @ 2m/s d'ou PSC=2000*Fcpu/(3526*2^16)=415 -> max is 128
// Res @ PSC=128 : Cnt=Fcpu/(PSC*3526)=106 pulses @ 2m/s

#define FCPU 48000000UL
#define ENCODER_MASK_TPM2_PRESCALER 7 	//Divides the clock by 128

#define ENCODER_MOD 65535

//Encoder cal speed=(100*FCPU*D*Pi/360/ENCODER_PRECALER)
#define ENCODER_CAL_SPEED (212712) //coeff de conversion : delta -> speed(mm/s)
//the resolution is approx <6 counts.

#define MAX_OVF 6 //If no pulse for 1sec, reset speed count to invalid.



class Encoder{
public:
	/**
	  * @brief 	Encoder object constructor
	  * @param 	none
	  * @retval none
	  */
	Encoder(void);
	/**
	  * @brief 	Initialisation of both encoder and interruptions 
	  * @param 	none
	  * @retval none
	  */
	void init(void);
	
	/**
	  * @brief 	Get left wheel speed 
	  * @param 	none
	  * @retval int : Left wheel speed
	  */
	int getLeftSpeed(void);//in cm/s
	
	/**
	  * @brief 	Get right wheel speed 
	  * @param 	none
	  * @retval int : right wheel speed
	  */
	int getRightSpeed(void);//in cm/s
	
	/**
	  * @brief 	Encoder interrupt handler 
	  * @param 	none
	  * @retval none
	  */
	void interruptHandler(void);
	
private :
	int prev_ccr1;
	int prev_ccr2;
	int delta1;
	int delta2;
	int OVF_cnt1;
	int OVF_cnt2;
};




#endif /* ENCODER_H_ */