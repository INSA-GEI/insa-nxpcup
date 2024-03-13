/*
 * buggy_source.c
 *
 *  Created on: 2 févr. 2024
 *      Author: Triet NGUYEN
 */


//#include <ImageProcessing/ImageProcessing.hpp>
#include "buggy_main.hpp"
#include "camera_led/cam_led.h"
#include "ImageProcessing/ImageProcessing_Commande.hpp"
#include "MKL25Z4.h"
//#include "movement/driver_movement.h"

unsigned int V=1800;	// Entre 1000 et 9000 // Vitese initiale
unsigned int Vset=3000; // Vitesse target

//unsigned int V=0;	// Entre 1000 et 9000 // Vitese initiale
//unsigned int Vset=0; // Vitesse target
 unsigned int Vslow=2500;
// unsigned int VslowTH=500;
// const float ADAPTIVE_SPEED_ANGLE = 10.0;
// const float ADAPTIVE_SPEED_HYST = 2.0;

int n=0;
int c=0;
int cnt=0;
bool FLAG_SEND_IMG=false;
bool FLAG_ENABLE_LOG_IMG=false;
bool FLAG_ENABLE_LOG_SERVO=false;



void buggy_run(void){

	// BASE
	cam_led_init();
	Camera_Initiate();
	//Camera_Initialise_Middle();
	movement_init();
	movement_set(V, 0);
	movement_regulate();

	//servo_init();
}

void TPM1_IRQHandler(){

	float angle_servo = Camera_Calculate_Servo_Angle();
	if (Camera_Calculate_Servo_Angle() > 20 || Camera_Calculate_Servo_Angle() < -18)
	{
		movement_set(Vslow,angle_servo);
	}
	else
	{
		movement_set(Vset,angle_servo);
	}
	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);
}
void TPM2_IRQHandler(){
	encoders_IRQHandler();
	movement_regulate();
}

