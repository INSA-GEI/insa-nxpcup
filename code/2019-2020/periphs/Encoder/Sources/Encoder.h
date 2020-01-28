/*
 * encoder.h
 *
 *  Created on: Jan 23, 2020
 *      Author: thomas
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <MKL25Z4.h>

#define RAY 3.25*0.01					//in meter
#define PI 3.1415926535					//						
#define IMPULSE_TIME	2*PI*RAY/360	// =2*Pi*R/360 s	due to :
										// 360 fronts/tr
										// 360/(2*Pi*R) fronts/m
										// 360/(2*Pi*R) fronts/m.s

#define ENCODER_MASK_TPM2_PRESCALER 7 	//Divides the clock by 128
#define ENCODER_ARR 5000				//temporary value...

#define SET_CHANNEL	0x04			//Set these bits to configure channel 0 on "Input Capture" 
										//with "Capture on Rising Edge Only" configuration



/* This function initialises both encoders*/
void encoder_config(void);



#endif /* ENCODER_H_ */
