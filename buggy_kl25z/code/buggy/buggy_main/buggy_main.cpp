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
#include "monitor/bluetooth_bee.h"
#include "MKL25Z4.h"

unsigned int V=0;	// Entre 1000 et 9000 // Vitese initiale
unsigned int Vset=0; // Vitesse target
// unsigned int Vslow=500;
// unsigned int VslowTH=500;
// const float ADAPTIVE_SPEED_ANGLE = 10.0;
// const float ADAPTIVE_SPEED_HYST = 2.0;

int n=0;
int c=0;
int cnt=0;

/* CMD Flag for logging data*/
bool FLAG_CAMERA_NEAR_DATA = true;  /* !!!!!!!!!!!!!!!!!!!!  FIX THIS to false !!!!!!!!!!!*/
bool FLAG_CAMERA_NEAR_BORDER = false;
bool FLAG_CAMERA_NEAR_CENTER = false;
bool FLAG_CAMERA_FAR_DATA = false;
bool FLAG_CAMERA_FAR_BORDER = false;
bool FLAG_CAMERA_FAR_CENTER = false;
bool FLAG_CAMERA_COMBINED_CENTER = false;
bool FLAG_SPEED_LEFT = false;
bool FLAG_SPEED_RIGHT = false;
bool FLAG_SERVO_ANGLE = false;

/* Data for test */
uint16_t test_data[128];
int pos_servo_test;
uint8_t bufferCommand[4];

void buggy_run(void){
	uint32_t lengthDatatest = 256;
	//-----TEST---- 
	test_data[0] = 0xFF;
	for (int i = 1; i < 128; i++){
		test_data[i] = 0x401;
	}

	// BASE

	cam_led_init();

	bee_initCommunication(buggy_readCMD, bufferCommand);
	bee_startReceivingData();


	Camera_Initiate();

	//Camera_Initialise_Middle();

	movement_init();
	movement_set(V, 0);
	movement_regulate();
	//bee_enableSendCameraData(Camera_getData(1), lengthDatatest);
	bee_enableSendCameraData(test_data, lengthDatatest);


	//-----TEST---- Pas necessaire--------

	//servo_init();


	//MOTOR_Left_Speed_Forward(20);
	//MOTOR_Right_Speed_Forward(20);
	//while(1){
	//Camera_Calculate_Servo_Angle();
	//}
}

void buggy_readCMD(void){
	uint8_t id_CMD;
	uint8_t dataMSB;
	uint8_t dataLSB;
	uint8_t checksum;

	id_CMD = bufferCommand[0];
	dataMSB = bufferCommand[1];
	dataLSB = bufferCommand[2];
	checksum = bufferCommand[3];

	if (checksum != (id_CMD ^ dataMSB ^ dataLSB)){
		return;
	}

	switch (id_CMD)
	{
		case CMD_ID_ENGINE:
			/* code */
			break;
		case CMD_ID_CAMERA_MODE:
			/* code */
			break;
		case CMD_ID_CAMERA_KP:
			/* code */
			break;
		case CMD_ID_CAMERA_KI:
			/* code */
			break;
		case CMD_ID_CAMERA_KD:
			/* code */
			break;
		case CMD_ID_DIFFERENTIAL_KP:
			/* code */
			break;
		case CMD_ID_DIFFERENTIAL_KI:
			/* code */
			break;
		case CMD_ID_DIFFERENTIAL_KD:
			/* code */
			break;
		case CMD_ID_SPEED_START:
			/* code */
			break;
		case CMD_ID_SPEED_LIMIT:
			/* code */
			break;
		case CMD_ID_SPEED_TURN:
			/* code */
			break;

		case CMD_ID_CAMERA_NEAR_DATA:

			if (dataLSB == 0x01){
				FLAG_CAMERA_NEAR_DATA = true;
			}
			else{
				FLAG_CAMERA_NEAR_DATA = false;
			}
			break;
		case CMD_ID_CAMERA_NEAR_BORDER:
			/* code */
			break;
		case CMD_ID_CAMERA_NEAR_CENTER:
			/* code */
			break;
		case CMD_ID_CAMERA_FAR_DATA:
			/* code */
			break;
		case CMD_ID_CAMERA_FAR_BORDER:
			/* code */
			break;
		case CMD_ID_CAMERA_FAR_CENTER:
			/* code */
			break;
		case CMD_ID_CAMERA_COMBINED_CENTER:
			/* code */
			break;
		case CMD_ID_SPEED:
			/* code */
			break;
		case CMD_ID_SERVO_ANGLE:
			/* code */
			break;
	default:
		break;
	}
}


void buggy_afficheData(void){
	servo_setPos(4850);

	volatile uint32_t i = 0;
	for (i = 0; i < 1200000; ++i)
	{
		__asm("NOP"); /* delay */
	}

	servo_setPos(4050);

	volatile uint32_t j = 0;
	for (j = 0; j < 1200000; ++j)
	{
		__asm("NOP"); /* delay */
	}

	servo_setPos(3150);

	volatile uint32_t k = 0;
	for (k = 0; k < 1200000; ++k)
	{
		__asm("NOP"); /* delay */
	}

	servo_setPos(4050);

	volatile uint32_t h = 0;
	for (h = 0; h < 1200000; ++h)
	{
		__asm("NOP"); /* delay */
	}
}


void TPM1_IRQHandler(){

	movement_set(Vset,Camera_Calculate_Servo_Angle());
	if (FLAG_CAMERA_NEAR_DATA){
		bee_sendCameraData();
	}

	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);
}

void TPM2_IRQHandler(){
	encoders_IRQHandler();
	movement_regulate();
}

