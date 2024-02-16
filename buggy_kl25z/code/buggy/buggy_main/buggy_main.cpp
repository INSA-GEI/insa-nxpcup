/*
 * buggy_source.c
 *
 *  Created on: 2 févr. 2024
 *      Author: Triet NGUYEN$$
 */


//#include <ImageProcessing/ImageProcessing.hpp>
#include "buggy_main.hpp"
#include "camera_led/cam_led.h"
#include "ImageProcessing/ImageProcessing_Commande.hpp"
#include "MKL25Z4.h"
//#include "movement/driver_movement.h"

unsigned int V=1800;	// Entre 1000 et 9000 // Vitese initiale
unsigned int Vset=2800; // Vitesse target
// unsigned int Vslow=500;
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

	//-----TEST---- Pas necessaire--------
	//servo_init();
	//servo_setPos(22);
	//MOTOR_Left_Speed_Forward(20);
	//MOTOR_Right_Speed_Forward(20);
	//while(1){
	//Camera_Calculate_Servo_Angle();
	//}

}

void TPM1_IRQHandler(){
	movement_set(Vset,Camera_Calculate_Servo_Angle());
	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);
}
void TPM2_IRQHandler(){
	encoders_IRQHandler();
	movement_regulate();
}

