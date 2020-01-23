/*
 * encoder.h
 *
 *  Created on: Jan 23, 2020
 *      Author: thomas
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <MKL25Z4.h>

#define ENCODER_MASK_TPM2_PRESCALER 3 	//temporary value...
#define ENCODER_ARR 4096				//temporary value...

#define SET_CHANNEL	0x04			//Set these bits to configure channel 0 on "Input Capture" 
										//with "Capture on Rising Edge Only" configuration



/* This function initialises both encoders*/
void encoder_config(void);



#endif /* ENCODER_H_ */
