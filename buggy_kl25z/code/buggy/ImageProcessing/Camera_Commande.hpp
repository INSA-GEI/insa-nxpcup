/*
 * ImageProcessing_Commande.h
 *
 *  Created on: 15 févr. 2024
 *      Author: Ordi Axel
 */

#ifndef IMAGEPROCESSING_CAMERA_COMMANDE_HPP_
#define IMAGEPROCESSING_CAMERA_COMMANDE_HPP_


#include "ImageProcessing.hpp"
#include <servo/driver_servo.h>

#define KP_Straight				0.6
#define KD_Straight				0.5
#define KI_Straight				0.0

#define KP_Turn_Left					1.5		//1.5
#define KD_Turn_Left					1.8		//1.8
#define KI_Turn_Left					0.0

#define KP_Turn_Right					1.5		//1.5
#define KD_Turn_Right					1.8		//1.8
#define KI_Turn_Right					0.0

#define TURN_DETECTION_THRESHOLD		10  //7
#define THRESHOLD_LOW_PASS_FILTER       60

/* Camera_Near Info
 * Position : High
 * Vision : Near
 * ADC0 : SE11 (C6)
 * */

/* Camera_Far Info
 * Position : Low
 * Vision : Far
 * ADC0 : SE15 (C7)
 * */

#define Nombre_de_Camera 2 		// Determinate the number of the used cameras
// If 1 Camera --> ADC0 SE11 (C6)
// If 2 Cameras --> ADC0 SE11 (C6) and SE15 (C7)

#define CAM_NEAR_ID 	1
#define CAM_FAR_ID 		2


void Camera_Initiate(void);
void Camera_Initialise_Middle (void);
float Camera_Calculate_Servo_Angle(void);
void Camera_Actualise_Servo_2_Camera_Moyenne_Simple (void);
void  Camera_Actualise_Servo_2_Camera_Moyenne_Ponderee_1 (void);
uint16_t * Camera_Get_ImageData(int i);
uint16_t * Camera_Get_ImageDataDiff(int i);
uint16_t * Camera_Get_OthersInfo(int i);
uint16_t * Camera_Get_NbrEdges(int i);
void Camera_Set_KDP (float KDP);
void Camera_Set_KP (float KP);
int Camera_Turn_Detection(void);



#endif /* IMAGEPROCESSING_CAMERA_COMMANDE_HPP_ */
