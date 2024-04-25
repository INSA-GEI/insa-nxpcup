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

unsigned int Vstart=500;	// Entre 1000 et 9000 // Vitese initiale
unsigned int Vtarget=900; // Vitesse target

//unsigned int V=0;	// Entre 1000 et 9000 // Vitese initiale
//unsigned int Vset=0; // Vitesse target
 unsigned int Vturn=750;
// unsigned int VslowTH=500;
// const float ADAPTIVE_SPEED_ANGLE = 10.0;
// const float ADAPTIVE_SPEED_HYST = 2.0;

int cnt_ostacle=0;
int n=0;
int c=0;
int cnt=0;

/* Variable for receiving command from Bluetooth Bee */
uint8_t bufferCommand[BEE_CMD_LENGTH];

/* For data monitoring */
#define LENGTH_CAMERA_DATA 256
#define LENGTH_CAMERA_OTHERS 10
#define LENGTH_WHEEL_DATA 6

uint8_t * ptr_cameraData = NULL;
uint8_t * ptr_cameraOthers = NULL;
uint16_t wheel_data[3] = {0, 0, 0}; // [0] : left, [1] : right, [2] : servo angle 

uint8_t watch_flag = 0;

/* Flag to indicate whether the motor is enabled (by remote control) */
uint8_t enable_flag = 0; // 0 if you want to enable remotely

/* Data for test */
int pos_servo_test;


void buggy_run(void){
	// BASE
	//LIDAR_Init();

	cam_led_init();

	bee_initCommunication(buggy_readCMD, bufferCommand);
	bee_startReceivingData();
	bee_enableSendData();

	Camera_Initiate();

	//Camera_Initialise_Middle();

	movement_init();
	// Comment this for remote start
//	enable_flag = 1;
//	mouvement_start();
//	movement_set(Vstart, 0);
//	//--------------------------------
//	movement_regulate();


	//watch_flag = CMD_ID_CAMERA_NEAR_DATA_DIFF;
	//bee_enableSendData(Camera_Get_ImageDataDiff(CAM_NEAR_ID), 256);
	//bee_enableSendCameraData(test_data, lengthDatatest);


// Servomotor Interrupt 50Hz
	//-----TEST---- Pas necessaire--------

//	servo_init();
//	servo_setPos(4050);

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
	float param;

	id_cmd = bufferCommand[0];
	dataMSB = bufferCommand[1];
	dataLSB = bufferCommand[2];
	checksum = bufferCommand[3];

	if (checksum != (id_cmd ^ dataMSB ^ dataLSB)){
		return;
	}

	switch (id_cmd)
	{	
		case CMD_ID_ENGINE:
			if (dataLSB == 0xAA){
				enable_flag = 1;
				mouvement_start();
				movement_set(Vstart, 0);
				movement_regulate();

			}
			else if (dataLSB == 0x55){
				enable_flag = 0;
				movement_stop();
			}
			break;
		case CMD_ID_CAMERA_KP:
			param = (float)((dataMSB << 8) | dataLSB) / 100.0;
			Camera_Set_KP(param);
			break;
		case CMD_ID_CAMERA_KD:
			param = (float)((dataMSB << 8) | dataLSB) / 100.0;
			Camera_Set_KDP(param);
			break;
		case CMD_ID_SPEED_START:
			Buggy_Set_Vstart((dataMSB << 8) | dataLSB);
			break;
		case CMD_ID_SPEED_TURN:
			Buggy_Set_Vturn((dataMSB << 8) | dataLSB);
			break;
		case CMD_ID_SPEED_TARGET:
			Buggy_Set_Vtarget((dataMSB << 8) | dataLSB);
			break;
		case CMD_ID_CAMERA_NEAR_DATA_DIFF:
			watch_flag = 1;
			ptr_cameraData = (uint8_t *)Camera_Get_ImageDataDiff(CAM_NEAR_ID);
			ptr_cameraOthers = (uint8_t *)Camera_Get_OthersInfo(CAM_NEAR_ID);
			break;
		case CMD_ID_CAMERA_NEAR_DATA:
			watch_flag = 1;
			ptr_cameraData = (uint8_t *)Camera_Get_ImageData(CAM_NEAR_ID);
			ptr_cameraOthers = (uint8_t *)Camera_Get_OthersInfo(CAM_NEAR_ID);
			break;
		case CMD_ID_CAMERA_FAR_DATA_DIFF:
			watch_flag = 1;
			ptr_cameraData = (uint8_t *)Camera_Get_ImageDataDiff(CAM_FAR_ID);
			ptr_cameraOthers = (uint8_t *)Camera_Get_OthersInfo(CAM_FAR_ID);
			break;
		case CMD_ID_CAMERA_FAR_DATA:
			watch_flag = 1;
			ptr_cameraData = (uint8_t *)Camera_Get_ImageData(CAM_FAR_ID);
			ptr_cameraOthers = (uint8_t *)Camera_Get_OthersInfo(CAM_FAR_ID);
			break;
		case CMD_ID_STOP_WATCH:
			watch_flag = CMD_ID_STOP_WATCH;
			bee_disableSendData();
			break;
		default:
			break;
	}
}


void buggy_afficheData(void){
//		servo_setPos(-27);
//
//		volatile uint32_t j = 0;
//		for (j = 0; j < 1200000; ++j)
//		{
//			__asm("NOP"); // delay
//		}
//
//	servo_setPos(0);
//
//	volatile uint32_t i = 0;
//	for (i = 0; i < 1200000; ++i)
//	{
//		__asm("NOP"); // delay
//	}
//
//
//	servo_setPos(27);
//
//	volatile uint32_t n = 0;
//	for (n = 0; n < 1200000; ++n)
//	{
//		__asm("NOP"); // delay
//	}
//
//	servo_setPos(0);
//
//	volatile uint32_t k = 0;
//	for (k = 0; k < 1200000; ++k)
//	{
//		__asm("NOP"); // delay
//	}
	/*
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

	if (enable_flag == 1){
		if (angle_servo > 30 || angle_servo < -30)
		{
			movement_set(Vturn,angle_servo);
		}
		else
		{
			movement_set(Vtarget,angle_servo);
		}
	}
	if (watch_flag != 0){
		wheel_data[0] = (uint16_t)movement_getSpeedLeft();
		wheel_data[1] = (uint16_t)movement_getSpeedRight();
		wheel_data[2] = (uint16_t)angle_servo;
		bee_sendData(ptr_cameraData, LENGTH_CAMERA_DATA);
		bee_sendData(ptr_cameraOthers, LENGTH_CAMERA_OTHERS);
		bee_sendData((uint8_t *)wheel_data, LENGTH_WHEEL_DATA);
	}

	TPM_ClearStatusFlags(TPM1, kTPM_Chnl0Flag);

}


// Encoder Interrupt
void TPM2_IRQHandler(){
	encoders_IRQHandler();
	if (enable_flag == 1){
		movement_regulate();
	}
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
