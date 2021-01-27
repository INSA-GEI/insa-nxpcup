/*
 * Interrupt.h
 *
 *  Created on: Jan 25, 2021
 *      Author: Mathilde
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <MKL25Z4.h>

#define F_CPU 48000000.0 				//Fréquence CPU 48MHz

//#define SYS_RELOAD 479999			//48000 fois le clock du processeur => 1kHz

void Timer_init (float Te);


#endif /* INTERRUPT_H_ */
