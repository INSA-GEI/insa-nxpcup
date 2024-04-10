/*
 * buggy_source.c
 *
 *  Created on: 2 févr. 2024
 *      Author: Triet NGUYEN
 */


//#include <ImageProcessing/ImageProcessing.hpp>
#include <ImageProcessing/Camera_Commande.hpp>
#include "buggy_main.hpp"
#include "camera_led/cam_led.h"
#include "MKL25Z4.h"
#include "lidar/driver_lidar.hpp"
//#include "movement/driver_movement.h"

unsigned int Vstart=2500;	// Entre 1000 et 9000 // Vitese initiale
unsigned int Vtarget=3000; // Vitesse target

//unsigned int V=0;	// Entre 1000 et 9000 // Vitese initiale
//unsigned int Vset=0; // Vitesse target
 unsigned int Vturn=2700;
// unsigned int VslowTH=500;
// const float ADAPTIVE_SPEED_ANGLE = 10.0;
// const float ADAPTIVE_SPEED_HYST = 2.0;

int cnt_ostacle=0;

void buggy_run(void){
	// BASE
	//LIDAR_Init();
	cam_led_init();
	Camera_Initiate();
	//Camera_Initialise_Middle();
	movement_init();
	movement_set(Vstart, 0);
	movement_regulate();

}


void Ostacle_Detection(void){

	if(LIDAR_CheckObstacle())
	{
		cnt_ostacle++;
		if (cnt_ostacle > 5)
		{
			movement_stop();
		}
	}
	else
	{
		cnt_ostacle = 0;
	}

}

// Servomotor Interrupt 50Hz
void TPM1_IRQHandler(){
	float angle_servo = Camera_Calculate_Servo_Angle();
	if (angle_servo > 20 || angle_servo < -22)
	{
		movement_set(Vturn,angle_servo);
	}
	else
	{
		movement_set(Vtarget,angle_servo);
	}

	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);

}

// Encoder Interrupt
void TPM2_IRQHandler(){
	encoders_IRQHandler();
	movement_regulate();
}

void Buggy_Set_Vstart(int v)
{
	Vstart = v;
}

void Buggy_Set_Vtarget(int v)
{
	Vtarget = v;
}

void Buggy_Set_Vturn(int v)
{
	Vturn = v;
}
