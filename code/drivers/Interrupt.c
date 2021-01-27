/*
 * Interrupt.c
 *
 *  Created on: Jan 25, 2021
 *      Author: Mathilde
 */

#include "Interrupt.h"

void Timer_init (void){

	//Essai n 2 avec Systick
	SYST_CSR |= (1<<2);			//Selects the SysTick timer clock source: 0 = external reference clock. 1 = processor clock.
	SYST_CSR |= (1<<1);			//Enables SysTick exception request: 0 = counting down to zero does not assert the SysTick exception request. 1 = counting down to zero asserts the SysTick exception request.
	SYST_CSR |= (1<<0); 		//Enables the counter: 0 = counter disabled. 1 = counter enabled.
	SYST_RVR |= SYS_RELOAD;	
}


