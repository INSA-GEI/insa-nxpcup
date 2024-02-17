/*
 * buggy_source.c
 *
 *  Created on: 2 févr. 2024
 *      Author: Triet NGUYEN
 */


//#include <ImageProcessing/ImageProcessing.hpp>
#include "buggy_main.hpp"
#include "camera_led/cam_led.h"
#include "MKL25Z4.h"
//#include "movement/driver_movement.h"

ImageProcessing camera;
unsigned int V=2000;	// Entre 1000 et 9000 // Vitese initiale
unsigned int Vset=2000; // Vitesse target
unsigned int Vslow=1000;
unsigned int VslowTH=1000;
const float ADAPTIVE_SPEED_ANGLE = 10.0;
const float ADAPTIVE_SPEED_HYST = 2.0;

int n=0;
int c=0;
int cnt=0;
bool FLAG_SEND_IMG=false;
bool FLAG_ENABLE_LOG_IMG=false;
bool FLAG_ENABLE_LOG_SERVO=false;



void buggy_run(void){
	// BASE
	cam_led_init();
	movement_init();
	camera.init();
	movement_set(V, 0);
	movement_regulate();


	/*// Pour régler focale de la caméra. mettre en commentaire BASE
	camera.init();
	while (1){
		camera.processAll();
	}*/


}

void TPM1_IRQHandler(){
	camera.processAll();


	if((camera.servo_angle>(ADAPTIVE_SPEED_ANGLE+ADAPTIVE_SPEED_HYST) || camera.servo_angle < -(ADAPTIVE_SPEED_ANGLE+ADAPTIVE_SPEED_HYST) ) && Vset!=0 && V!=Vslow){
		V=Vslow;
	}else if(camera.servo_angle<(ADAPTIVE_SPEED_ANGLE-ADAPTIVE_SPEED_HYST) && camera.servo_angle>-(ADAPTIVE_SPEED_ANGLE-ADAPTIVE_SPEED_HYST) && V<Vset){
		V+=20;
	}

	movement_set(Vset, camera.servo_angle);
	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);
}
void TPM2_IRQHandler(){
	encoders_IRQHandler();
	movement_regulate();
}

