/*
 * ImageProcessing_Commande.h
 *
 *  Created on: 15 févr. 2024
 *      Author: Ordi Axel
 */

#ifndef IMAGEPROCESSING_IMAGEPROCESSING_COMMANDE_HPP_
#define IMAGEPROCESSING_IMAGEPROCESSING_COMMANDE_HPP_




#include "ImageProcessing.hpp"
#include <servo/driver_servo.h>

#define Nombre_de_Camera 2 // Donne le nombre de caméra sur la voiture ( 1 ou 2).
// Si 1 Camera --> ADC0 SE11
// Si 2 Camera --> ADC0 SE11 et SE15




void Camera_Initiate(void);
void Camera_Initialise_Middle (void);
float Camera_Calculate_Servo_Angle(void);
void Camera_Actualise_Servo_2_Camera_Moyenne_Simple (void);
void  Camera_Actualise_Servo_2_Camera_Moyenne_Ponderee_1 (void);



#endif /* IMAGEPROCESSING_IMAGEPROCESSING_COMMANDE_HPP_ */
