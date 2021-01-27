/*
 * Interrupt.h
 *
 *  Created on: Jan 25, 2021
 *      Author: Mathilde
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <MKL25Z4.h>

#define SYS_RELOAD 479999			//48000 fois le clock du processeur => 1kHz

void Timer_init (void);


#endif /* INTERRUPT_H_ */
