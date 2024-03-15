/*
 * ImageProcessing_Commande.c
 *
 *  Created on: 15 févr. 2024
 *      Author: Ordi Axel
 */

#include <ImageProcessing/ImageProcessing_Commande.hpp>
#include "monitor/bluetooth_bee.h"


// Crée 2 objets caméra
ImageProcessing Camera_1(1);
ImageProcessing Camera_2(2);

void Camera_Initiate(void){
	if (Nombre_de_Camera == 1){
		Camera_1.init();
	}
	else if (Nombre_de_Camera == 2){
		Camera_1.init();
		Camera_2.init();
	}
}

float Camera_Calculate_Servo_Angle(void){
	if (Nombre_de_Camera == 1){
		Camera_1.capture();
		Camera_1.differentiate();
		Camera_1.process();
		Camera_1.calculateMiddle();
		Camera_1.Actualise_Servo_1_Camera();
		Camera_1.compute_data_threshold();
		//Camera_1.affiche_image();
		}
	else if (Nombre_de_Camera == 2){

		// Capture des données sur les deux caméra.
		// Capture en séquentiel car les 2 caméra sur le même ADC
		Camera_1.capture();
		Camera_2.capture();

		//Traitement de la caméra 1
		Camera_1.differentiate();
		Camera_1.process();
		Camera_1.calculateMiddle();
		//Camera_1.affiche_image();

		//Traitement de la caméra 2
		Camera_2.differentiate();
		Camera_2.process();
		Camera_2.calculateMiddle();
		//Camera_2.affiche_image();

		//Option 1 du calcul servo_angle
		//Prend la moyenne des deux milieux de route obtenue sans se soucier du FOV(field of view) des caméras.
		//Camera_Actualise_Servo_2_Camera_Moyenne_Simple();


		//Option 2 moyenne ponderee avec valeur arbitraire K_CAM_1 et K_CAM_2 dans ImageProcessing.hpp
		Camera_Actualise_Servo_2_Camera_Moyenne_Ponderee_1();

		//actualisation threshold
		Camera_1.compute_data_threshold();
		Camera_2.compute_data_threshold();
		}
	return Camera_1.servo_angle;
}

void  Camera_Actualise_Servo_2_Camera_Moyenne_Simple (void){
	// Option apres calcumateMiddle pour deux camera
	// Permet de changer l'angle du servo

	// Store old value
	Camera_1.diff_old = Camera_1.diff;
	//Calcul de la différence de la voiture au centre de la route
	// Ici centre de la route estimé par moyenne des roadmiddle des deux cameras
	Camera_1.diff =  64 - (Camera_1.RoadMiddle + Camera_2.RoadMiddle) ;

	// plausibility check
	if (abs (Camera_1.diff - Camera_1.diff_old) > 50){
		Camera_1.diff = Camera_1.diff_old;
	}else{
		Camera_1.servo_angle=(KP_TURN*(float)Camera_1.diff + KDP_TURN*(float)(Camera_1.diff-Camera_1.diff_old));
		if(Camera_1.servo_angle<SERVO_MAX_LEFT_ANGLE)Camera_1.servo_angle=SERVO_MAX_LEFT_ANGLE;
		if(Camera_1.servo_angle>SERVO_MAX_RIGHT_ANGLE)Camera_1.servo_angle=SERVO_MAX_RIGHT_ANGLE;
	}
}

void  Camera_Actualise_Servo_2_Camera_Moyenne_Ponderee_1 (void){
	// Option apres calcumateMiddle pour deux camera
	// Permet de changer l'angle du servo

	// Store old value
	Camera_1.diff_old = Camera_1.diff;
	//Calcul de la différence de la voiture au centre de la route
	// Ici centre de la route estimé par moyenne des roadmiddle des deux cameras
	Camera_1.diff =  64 - (K_CAM_1 *Camera_1.RoadMiddle + K_CAM_2*Camera_2.RoadMiddle) ;

	// plausibility check
	if (abs (Camera_1.diff - Camera_1.diff_old) > 50){
		Camera_1.diff = Camera_1.diff_old;
	}else{
		Camera_1.servo_angle=(KP_TURN*(float)Camera_1.diff + KDP_TURN*(float)(Camera_1.diff-Camera_1.diff_old));
		if(Camera_1.servo_angle<SERVO_MAX_LEFT_ANGLE)Camera_1.servo_angle=SERVO_MAX_LEFT_ANGLE;
		if(Camera_1.servo_angle>SERVO_MAX_RIGHT_ANGLE)Camera_1.servo_angle=SERVO_MAX_RIGHT_ANGLE;
	}
}

void Camera_Initialise_Middle (void){
	for (int i =0;i<10;i++){
		//Captuire dans le vide pour initialiser threshold
		Camera_Calculate_Servo_Angle();
	}
	Camera_Calculate_Servo_Angle();
	if (Nombre_de_Camera == 1){
			Camera_1.initial_middle=(Camera_1.BlackLineLeft + Camera_1.BlackLineRight) / 2;
		}
		else if (Nombre_de_Camera == 2){
			Camera_1.initial_middle=Camera_1.initial_middle=(Camera_1.BlackLineLeft + Camera_1.BlackLineRight) / 2;
			Camera_2.initial_middle=Camera_2.initial_middle=(Camera_2.BlackLineLeft + Camera_2.BlackLineRight) / 2;
		}

}

uint16_t * Camera_getData(int ID_Camera){
	if (ID_Camera == 1){
		return Camera_1.ImageData;
	}
	else if (ID_Camera == 2){
		return Camera_2.ImageData;
	}
	return NULL;
}


