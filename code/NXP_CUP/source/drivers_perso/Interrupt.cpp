/*
 * Interrupt.c
 *
 *  Created on: Jan 25, 2021
 *      Author: Mathilde
 */

#include <drivers_perso/Debug.h>
#include "Interrupt.h"
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

	SysTick_Config(reload);
}


