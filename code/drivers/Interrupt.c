/*
 * Interrupt.c
 *
 *  Created on: Jan 25, 2021
 *      Author: Mathilde
 */

#include "Interrupt.h"
#include "Debug.h"
int reload=0;
const int max_reload=16777210;

void Timer_init (float Te){

	reload= ((int)(Te*F_CPU))-1;
	if (reload>max_reload){reload=max_reload;}
	/*uart_write("reload=",7);
	uart_writeNb(reload);
	uart_write("\n\r",2);
	uart_write("Fe_theo=",8);
	uart_writeNb((int)(F_CPU/(reload+1)));
	uart_write("\n\r",2);*/
	//Essai n 2 avec Systick
	SYST_CSR |= (1<<2);
	//SYST_CSR &= 0xFFFFFFFFB;			//Selects the SysTick timer clock source: 0 = external reference clock (/16). 1 = processor clock.
	SYST_CSR |= (1<<1);			//Enables SysTick exception request: 0 = counting down to zero does not assert the SysTick exception request. 1 = counting down to zero asserts the SysTick exception request. 		//Enables the counter: 0 = counter disabled. 1 = counter enabled.
	SYST_RVR &= 0x000000;
	SYST_RVR |= reload;
	SYST_CVR &= 0x000000;
	
	
	/*uart_write("SYS_CSR=",8);
	uart_writeNb(SYST_CSR);
	uart_write("\n\r",2);
	uart_write("SYS_CVR=",8);
	uart_writeNb(SYST_CVR);
	uart_write("\n\r",2);
	uart_write("SYS_RVR=",8);
	uart_writeNb(SYST_RVR);
	uart_write("\n\r",2);*/
	
	SYST_CSR |= (1<<0); //Enable IT
}


