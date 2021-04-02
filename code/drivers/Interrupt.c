/*
 * Interrupt.c
 *
 *  Created on: Jan 25, 2021
 *      Author: Mathilde
 */

#include "Interrupt.h"
#include "Debug.h"
#include "MKL25Z4.h"

int reload=0;
const int max_reload=16777210;

void Timer_init (float Te){
	
	float F_IT=F_CPU;

	reload= ((int)(Te*F_IT))-1;
	if (reload>max_reload){reload=max_reload;}
	uart_write("reload=",7);
	uart_writeNb(reload);
	uart_write("\n\r",2);
	uart_write("Fe_theo=",8);
	uart_writeNb((int)(F_IT/reload));
	uart_write("\n\r",2);
	//Essai n 2 avec Systick
	
//	SYST->CSR |= (1<<2);			//Selects the SysTick timer clock source: 0 = external reference clock (/16). 1 = processor clock.
//	SYST_CSR |= (1<<1);			//Enables SysTick exception request: 0 = counting down to zero does not assert the SysTick exception request. 1 = counting down to zero asserts the SysTick exception request. 		//Enables the counter: 0 = counter disabled. 1 = counter enabled.
//	SYST_RVR &= 0x000000;
//	SYST_RVR |= reload;
//	SYST_CVR &= 0x000000;
//
//	SYST_CSR |= (1<<0); //Enable IT
	SysTick_Config(reload);
}


