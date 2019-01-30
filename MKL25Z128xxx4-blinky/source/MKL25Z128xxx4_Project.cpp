 /**
 * @file    MKL25Z128xxx4_Project.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <derivative.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    int time;
    int ledverte = 19;
    int ledrouge = 18;
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; //on active le PORT B
    PORTB_PCR19 = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); //broche 53 configuré sur bit 18 du PORT B avec DSE_MASK pour que la broche puisse sortir plus decourant
    GPIOB_PDDR = (1<<ledverte); //bit 18 du PORT B en sortie
    GPIOB_PDDR = (1<<ledrouge); //bit 18 du PORT B en sortie
	GPIOB_PTOR = (1<<ledrouge);


    for(;;) // boucle infinie
    {
    	GPIOB_PTOR = (1<<ledverte);
    	GPIOB_PTOR = (1<<ledrouge);

    	time = 1000000/2;
    	while (time>=0)
    		time--; //pour perdre du temps
    }

    return 0 ;
}
