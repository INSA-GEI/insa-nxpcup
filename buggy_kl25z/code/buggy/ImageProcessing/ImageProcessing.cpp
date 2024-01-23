/*
 * ImageProcessing.cpp
 *
 *  Created on: 22 janv. 2024
 *      Author: Ordi Axel
 */

#include "ImageProcessing.h"

ImageProcessing::ImageProcessing() {
	// TODO Auto-generated constructor stub

}

ImageProcessing::~ImageProcessing() {
	// TODO Auto-generated destructor stub
}

void ImageProcessing::capture(void){
	ADC16_SetChannelMuxMode(ADC0,kADC16_ChannelMuxB); // Sélectionner le côté B du MUX
	CAM_SI_HIGH; // Activer la ligne SI (Shift In) de la caméra
	CAM_DELAY; // Attente pour le délai CAM
	CAM_CLK_HIGH; // Activer l'horloge de la caméra
	CAM_DELAY; // Attente pour le délai CAM
	CAM_SI_LOW; // Désactiver la ligne SI de la caméra
	CAM_DELAY; // Attente pour le délai CAM

	// inputs data from camera (first pixel)

	ImageData[0] = ADC16_GetChannelConversionValue(ADC0,11);
	CAM_CLK_LOW;

	// Boucle pour entrer les données de la caméra (un pixel à la fois)
	    for(int i = 1; i < 128; i++){
	        CAM_DELAY;                               // Attente pour le délai CAM
	        CAM_CLK_HIGH;                            // Activer l'horloge de la caméra

	        // Entrée des données de la caméra (un pixel à chaque itération de la boucle)

	        ImageData[i] = ADC16_GetChannelConversionValue(ADC0,11);                  // Stocker la valeur retournée dans le tableau ImageData
	        CAM_CLK_LOW;                             // Désactiver l'horloge de la caméra
	        // Créé un tableau de 128 contenant la valeur des pixel d'une ligne de la caméra
	    }
}

void affiche_image(void){
	for (int i = 0 ; i<128;i++){
		PRINTF("%d",ImageData[i]);

	}
	PRINTF("/n");
}


