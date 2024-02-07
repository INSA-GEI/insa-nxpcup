/*
 * buggy_source.c
 *
 *  Created on: 2 févr. 2024
 *      Author: Triet NGUYEN$$
 */


//#include <ImageProcessing/ImageProcessing.hpp>
#include "buggy_main.hpp"
#include "MKL25Z4.h"
//#include "movement/driver_movement.h"

ImageProcessing camera;
unsigned int V=1500;
unsigned int Vset=1500;
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
	movement_init();
	camera.init();
	movement_set(V, 20);



	//-----TEST---- Pas necessaire--------
	//servo_init();
	//MOTOR_Left_Speed_Forward(20);
	//MOTOR_Right_Speed_Forward(20);
	movement_regulate();
}

void TPM1_IRQHandler(){
	camera.processAll();
	movement_set(Vset, camera.servo_angle);
	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);
}
void TPM2_IRQHandler(){
	encoders_IRQHandler();
	movement_regulate();
}

