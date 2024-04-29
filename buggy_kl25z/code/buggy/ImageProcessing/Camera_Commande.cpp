/*
 * ImageProcessing_Commande.c
 *
 *  Created on: 15 févr. 2024
 *      Author: Ordi Axel
 */

#include <ImageProcessing/Camera_Commande.hpp>
#include <movement/driver_movement.h>
#include "monitor/bluetooth_bee.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "servo/driver_servo.h"

int flag_turn_detection =0;

//Create 2 objects camera
ImageProcessing Camera_Near(1);
ImageProcessing Camera_Far(2);

#define CAMERA_NEAR_MIDDLE   61
#define CAMERA_FAR_MIDDLE    54


void Camera_Initiate(void){
	if (Nombre_de_Camera == 1){
		Camera_Near.init();
	}
	else if (Nombre_de_Camera == 2){
		Camera_Near.init();
		Camera_Far.init();
	}
}

float Camera_Calculate_Servo_Angle(void){


	// Capture des données sur les deux caméra.
	// Capture en séquentiel car les 2 caméra sur le même ADC
	Camera_Near.capture();
	Camera_Far.capture();

	//Traitement de la caméra 1
	Camera_Near.differentiate();
	Camera_Near.process();
	Camera_Near.calculateMiddle();
	//Camera_Near.affiche_image();
	//Camera_Near.affiche_edge();

	//Traitement de la caméra 2
	Camera_Far.differentiate();
	Camera_Far.process();
	Camera_Far.calculateMiddle();
	//Camera_Far.affiche_image();
	//Camera_Far.affiche_edge();

	//Option 1 du calcul servo_angle
	//Prend la moyenne des deux milieux de route obtenue sans se soucier du FOV(field of view) des caméras.
	//Camera_Actualise_Servo_2_Camera_Moyenne_Simple();


	//Option 2 moyenne ponderee avec valeur arbitraire K_CAMERA_NEAR et K_CAMERA_FAR dans ImageProcessing.hpp
	Camera_Actualise_Servo_2_Camera_Moyenne_Ponderee_1();

	//actualisation threshold
	Camera_Near.compute_data_threshold();
	Camera_Far.compute_data_threshold();

	return Camera_Near.servo_angle;
}

void  Camera_Actualise_Servo_2_Camera_Moyenne_Simple (void){
	// Option apres calcumateMiddle pour deux camera
	// Permet de changer l'angle du servo

	// Store old value
	Camera_Near.diff_old_k_2 = Camera_Near.diff_old;
	Camera_Near.diff_old = Camera_Near.diff;
	//Calcul de la différence de la voiture au centre de la route
	// Ici centre de la route estimé par moyenne des roadmiddle des deux cameras
	Camera_Near.diff =  64 - (Camera_Near.RoadMiddle + Camera_Far.RoadMiddle) ;

	// plausibility check
	if (abs (Camera_Near.diff - Camera_Near.diff_old) > 50){
		Camera_Near.diff = Camera_Near.diff_old;
	}else{
		Camera_Near.servo_angle=(ImageProcessing::KP*(float)Camera_Near.diff + ImageProcessing::KD*(float)(Camera_Near.diff-Camera_Near.diff_old));
		if(Camera_Near.servo_angle<SERVO_MAX_LEFT_ANGLE)Camera_Near.servo_angle=SERVO_MAX_LEFT_ANGLE;
		if(Camera_Near.servo_angle>SERVO_MAX_RIGHT_ANGLE)Camera_Near.servo_angle=SERVO_MAX_RIGHT_ANGLE;
	}
}

void  Camera_Actualise_Servo_2_Camera_Moyenne_Ponderee_1 (void){
	int commande_servo;
	// Option apres calcumateMiddle pour deux camera
	// Permet de changer l'angle du servo
	// Store old value
	Camera_Near.diff_old = Camera_Near.diff;
	//Calcul de la différence de la voiture au centre de la route
	// Ici centre de la route estimé par moyenne des roadmiddle des deux cameras
	Camera_Far.diff	 =  K_CAMERA_FAR*(CAMERA_FAR_MIDDLE - (Camera_Far.RoadMiddle));
	Camera_Near.diff =  K_CAMERA_NEAR*(CAMERA_NEAR_MIDDLE - (Camera_Near.RoadMiddle));
	Camera_Near.diff += Camera_Far.diff;
	if(Camera_Near.diff < -TURN_DETECTION_THRESHOLD){
		Camera_Set_KDP(KD_Turn_Left);
		Camera_Set_KP(KP_Turn_Left);
		flag_turn_detection = 1;
	}
		// if a line is only on the the left side
	else if (Camera_Near.diff > TURN_DETECTION_THRESHOLD){
		Camera_Set_KDP(KD_Turn_Right);
		Camera_Set_KP(KP_Turn_Right);
		flag_turn_detection = 1;

	}
	else
	{
		Camera_Set_KDP(KD_Straight);
		Camera_Set_KP(KP_Straight);
		flag_turn_detection = 0;
	}

	Camera_Near.erreurIntegral = Camera_Near.erreurIntegral + ImageProcessing::KI*Camera_Near.diff;
	commande_servo = Camera_Near.erreurIntegral + ImageProcessing::KP*(float)Camera_Near.diff + ImageProcessing::KD*(float)(Camera_Near.diff-Camera_Near.diff_old);
	if(Camera_Near.servo_angle - commande_servo > -70 && Camera_Near.servo_angle - commande_servo < 70)
	{
		Camera_Near.servo_angle=commande_servo;
	}

	if(Camera_Near.servo_angle<SERVO_MAX_LEFT_ANGLE)Camera_Near.servo_angle=SERVO_MAX_LEFT_ANGLE;
	if(Camera_Near.servo_angle>SERVO_MAX_RIGHT_ANGLE)Camera_Near.servo_angle=SERVO_MAX_RIGHT_ANGLE;

}

//void Camera_Initialise_Middle (void){
//	for (int i =0;i<10;i++){
//		//Captuire dans le vide pour initialiser threshold
//		Camera_Calculate_Servo_Angle();
//	}
//	Camera_Calculate_Servo_Angle();
//	if (Nombre_de_Camera == 1){
//			Camera_Near.initial_middle=(Camera_Near.BlackLineLeft + Camera_Near.BlackLineRight) / 2;
//		}
//		else if (Nombre_de_Camera == 2){
//			Camera_Near.initial_middle=Camera_Near.initial_middle=(Camera_Near.BlackLineLeft + Camera_Near.BlackLineRight) / 2;
//			Camera_Far.initial_middle=Camera_Far.initial_middle=(Camera_Far.BlackLineLeft + Camera_Far.BlackLineRight) / 2;
//		}
//
//}

uint16_t * Camera_Get_ImageData(int i){
	//Retourne le pointeur vers le tableau contenant les valeurs des pixels de la camera 1 ou 2
	if (i == CAM_NEAR_ID){
		return Camera_Near.ImageData;
	}
	else if (i == CAM_FAR_ID){
		return Camera_Far.ImageData;
	}
	else{
		return (uint16_t *)0;
	}
}

uint16_t * Camera_Get_ImageDataDiff(int i){
	//Retourne le pointeur vers le tableau contenant les valeurs des pixels de la camera 1 ou 2
	if (i == CAM_NEAR_ID){
		return Camera_Near.ImageDataDifference;
	}
	else if (i == CAM_FAR_ID){
		return Camera_Far.ImageDataDifference;
	}
	else{
		return (uint16_t *)0;
	}
}

uint16_t * Camera_Get_OthersInfo(int i){
	// Retourne la valeur de RoadMiddle de Camera 1 ou 2
	if (i == CAM_NEAR_ID){
		return &Camera_Near.RoadMiddle;
	}
	else if (i == CAM_FAR_ID){
		return &Camera_Far.RoadMiddle;
	}
	else{
		return NULL;
	}
}

uint16_t * Camera_Get_NbrEdges(int i){
	// Retourne la valeur de RoadMiddle de Camera 1 ou 2
	if (i == CAM_NEAR_ID){
		return &Camera_Near.number_edges;
	}
	else if (i == CAM_FAR_ID){
		return &Camera_Far.number_edges;
	}
	else{
		return NULL;
	}
}


void Camera_Set_KDP (float KDP)
{
	ImageProcessing::set_KdpTurn(KDP);
}

void Camera_Set_KP (float KP)
{
	ImageProcessing::set_KpTurn(KP);
}


int Camera_Turn_Detection(void)
{
//	if(flag_turn_detection == 0)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}
//	return 0;
	return flag_turn_detection;
}
