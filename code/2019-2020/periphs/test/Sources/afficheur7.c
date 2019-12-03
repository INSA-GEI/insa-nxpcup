/*
 * afficheur7.c
 *
 *  Created on: Dec 3, 2019
 *      Author: thoma
 */

#include "afficheur7.h"
#include <MKL25Z4.h>



void delay(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}



void send_data(int data){
	
		//Initialisation de la CLK
		PORTC_PCR5 = PORT_PCR_MUX(1);
		GPIOC_PSOR |= DISP_CLK_PIN;
		GPIOC_PDDR |= DISP_CLK_PIN;		//Configuration en output
		
		//Initialisation de SIN (pour la data)
		PORTC_PCR6 = PORT_PCR_MUX(1);
		GPIOC_PSOR |= DISP_SIN_PIN;
		GPIOC_PDDR |= DISP_SIN_PIN;		//Configuration en output
		
		//Initialisation du latch
		PORTC_PCR10 = PORT_PCR_MUX(1);
		GPIOC_PSOR = DISP_LATCH_PIN;
		GPIOC_PDDR |= DISP_LATCH_PIN;	//Configuration en output
		
		DISP_LATCH_OFF;
		DISP_CLK_OFF;
		//delay
		for (int i=0; i<7;i++){
			
			
			if(data & (1<<i))		//On check si le bit est à 1
			{
				DISP_SIN_ON;
				
			}else {
				DISP_SIN_OFF;
			}			
			//delay
			DISP_CLK_ON;
			//délai?
			DISP_CLK_OFF;
		}
		DISP_LATCH_ON;
		

}
