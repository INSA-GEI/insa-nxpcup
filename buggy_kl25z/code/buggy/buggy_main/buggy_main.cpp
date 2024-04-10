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
#include "monitor/bluetooth_bee.h"
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
int n=0;
int c=0;
int cnt=0;

/* Variable for receiving command from Bluetooth Bee */
uint8_t bufferCommand[BEE_CMD_LENGTH];

/* Flag to indicate what data is monitoring */
uint8_t watch_flag = 0;

/* Data for test */
int pos_servo_test;


void buggy_run(void){
	// BASE
	//LIDAR_Init();
	/*
	cam_led_init();

	bee_initCommunication(buggy_readCMD, bufferCommand);
	bee_startReceivingData();


	Camera_Initiate();

	//Camera_Initialise_Middle();

	movement_init();
	movement_set(Vstart, 0);
	movement_regulate();
	//bee_enableSendCameraData(test_data, lengthDatatest);
	*/

// Servomotor Interrupt 50Hz
	//-----TEST---- Pas necessaire--------

	servo_init();
	servo_setPos(4050);

	//MOTOR_Left_Speed_Forward(20);
	//MOTOR_Right_Speed_Forward(20);
	//while(1){
	//Camera_Calculate_Servo_Angle();
	//}
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


void buggy_readCMD(void){
	uint8_t id_cmd;
	uint8_t dataMSB;
	uint8_t dataLSB;
	uint8_t checksum;

	id_cmd = bufferCommand[0];
	dataMSB = bufferCommand[1];
	dataLSB = bufferCommand[2];
	checksum = bufferCommand[3];

	if (checksum != (id_cmd ^ dataMSB ^ dataLSB)){
		return;
	}

	switch (id_cmd)
	{
		case CMD_ID_CAMERA_NEAR_DATA_DIFF:
			watch_flag = CMD_ID_CAMERA_NEAR_DATA_DIFF;
			bee_enableSendData(Camera_Get_ImageDataDiff(CAM_NEAR_ID), 256);
			break;
		case CMD_ID_CAMERA_NEAR_DATA:
			watch_flag = CMD_ID_CAMERA_NEAR_DATA;
			bee_enableSendData(Camera_Get_ImageData(CAM_NEAR_ID), 256);
			break;
		case CMD_ID_CAMERA_NEAR_OTHERS:
			watch_flag = CMD_ID_CAMERA_NEAR_OTHERS;
			bee_enableSendData(Camera_Get_OthersInfo(CAM_NEAR_ID), 8);
		case CMD_ID_CAMERA_NEAR_NUM_BORDERS:
			watch_flag = CMD_ID_CAMERA_NEAR_NUM_BORDERS;
			bee_enableSendData(Camera_Get_NbrEdges(CAM_NEAR_ID), 2);

		case CMD_ID_CAMERA_FAR_DATA_DIFF:
			watch_flag = CMD_ID_CAMERA_FAR_DATA_DIFF;
			bee_enableSendData(Camera_Get_ImageDataDiff(CAM_FAR_ID), 256);
			break;
		case CMD_ID_CAMERA_FAR_DATA:
			watch_flag = CMD_ID_CAMERA_FAR_DATA;
			bee_enableSendData(Camera_Get_ImageData(CAM_FAR_ID), 256);
			break;
		case CMD_ID_CAMERA_FAR_OTHERS:
			watch_flag = CMD_ID_CAMERA_FAR_OTHERS;
			bee_enableSendData(Camera_Get_OthersInfo(CAM_FAR_ID), 8);
		case CMD_ID_CAMERA_FAR_NUM_BORDERS:
			watch_flag = CMD_ID_CAMERA_FAR_NUM_BORDERS;
			bee_enableSendData(Camera_Get_NbrEdges(CAM_FAR_ID), 2);
		case CMD_ID_STOP_WATCH:
			watch_flag = CMD_ID_STOP_WATCH;
			bee_disableSendData();
		default:
			break;
	}
}


void buggy_afficheData(void){

		servo_setPos(4100);

		volatile uint32_t j = 0;
		for (j = 0; j < 1200000; ++j)
		{
			__asm("NOP"); // delay
		}
/*
	servo_setPos(2900);

	volatile uint32_t i = 0;
	for (i = 0; i < 1200000; ++i)
	{
		__asm("NOP"); // delay
	}
*/
/*
	servo_setPos(3950);

	volatile uint32_t j = 0;
	for (j = 0; j < 1200000; ++j)
	{
		__asm("NOP"); // delay
	}

	servo_setPos(4850);

	volatile uint32_t k = 0;
	for (k = 0; k < 1200000; ++k)
	{
		__asm("NOP"); // delay
	}

	servo_setPos(3950);

	volatile uint32_t h = 0;
	for (h = 0; h < 1200000; ++h)
	{
		__asm("NOP"); // delay
	}
*/
}


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

	if (watch_flag != 0){
		bee_sendData();
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
