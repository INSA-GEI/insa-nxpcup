/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MKL25Z4_Project.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* insert other include files here. */
#include <drivers_perso/Debug.h>
#include <drivers_perso/servo.h>
#include <drivers_perso/Car_control.h>
/* insert other definitions and declarations here. */
/* Constantes */
Car car;
#define Fe					500.0
#define Fe_IT_PWM			100000.0
#define Fe_PWM_servo_cam	50.0

#define Te 					1.0/Fe					//sample time 2ms Car_handler/!\ Te_s (sample time for rear motors is in Movement.h)
#define Te_IT_PWM			1.0/Fe_IT_PWM			//100kHz 10µs
#define Te_PWM_servo_cam	1.0/Fe_PWM_servo_cam	//20ms

int CST_TE; 								//cst Pour le car.handler()
int CST_TE_PWM;
int CST_PWM_HIGH=150;

int MODE=-1;

/* Fonctions */
int Init_tot();

/*
 * @brief   Application entry point.
 */
int main(void) {
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("############ NXP CUP PROJECT #############\n\r");

    //############ INIT #####################
    Init_tot();

    while(1) {
    	car.Car_debug();
    }
    return 0 ;
}


//################ Fonctions ##############

//La led rouge indique qu'il faut changer la batterie, on affiche aussi B sur l'afficheur 7seg;
int Init_tot(void){
	//######## INIT ###########
	//ATTENTION l'ordre est important!
	MODE=debug_init(); 		//retourne le mode
	car.myMovement.init(Te);
	int f_mode=1;//MODE; 	//Définit le functionning mode
	if (f_mode==-1){
		f_mode=1;
	}
	car.cam.init(f_mode);
	car.init(Te,MODE);
	car.myMovement.encoder.init_SENS();
	//Init de GPIO
	IT_PORTD_init();
	init_servo_cam();

	//Init IT
	Timer_init (Te_IT_PWM);

	//Reload constante
	CST_TE=(int)(Fe_IT_PWM/Fe);
	CST_TE_PWM=(int)(Fe_IT_PWM/Fe_PWM_servo_cam);

	return 0;
}


//############# HANDLERS ##############
int count_dem=0;
void PORTD_IRQHandler(void){
	DEBUG_GREEN_ON;
	PORTD->PCR[3] |= 1<<24;
	count_dem++;

}

//10kHz
void FTM0_IRQHandler() {

	TPM0->SC |= TPM_SC_TOF_MASK;//Clear IT
}

//100Hz
//Servo handler
void FTM1_IRQHandler() {
	if (count_dem>0){
		count_dem++;
		//2 secondes
		if (count_dem>200){
			count_dem=0;
			uart_write("OK\n\r",4);
			car.Demarre();
		}
	}

	TPM1->SC |= TPM_SC_TOF_MASK;//Clear IT
}

//speed handlers
void FTM2_IRQHandler() {//encoder interrupt à max 6Hz Te variable!!!

	car.myMovement.encoder.interruptHandler();

}

//Calcul var de la voiture + MAJ
int cpt_car_handler=0;
//PWM servo
int count_FTM0=0;
bool etat=true;
void SysTick_Handler(){
	//Incr cpt
	cpt_car_handler++;
	count_FTM0++;

	// car handler
	if (cpt_car_handler>CST_TE){
		//500Hz
		cpt_car_handler=0;
		car.Car_handler(); //Define Vset and servo_angle.
	}else{

	}

	//###### PWM ##############

	//pas de 0.1 ms
	//1.5ms
	if (count_FTM0>CST_TE_PWM){
		//50Hz => 20ms //Une période de PWM
		count_FTM0=0;
		etat=false;
	}else if (count_FTM0<=CST_PWM_HIGH){
		etat=true;
	}else{
		etat=false;
	}

	//Actualisation
	if (etat){
		SERVO_CAM_PWM_ON;
	}else{
		SERVO_CAM_PWM_OFF;
	}

	SysTick->CTRL &=0xFFFEFFFF; //Clear IT
}

