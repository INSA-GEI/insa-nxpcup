/*
 * driver_mouvement.h
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam
 */

#ifndef MOVEMENT_DRIVER_MOVEMENT_H_
#define MOVEMENT_DRIVER_MOVEMENT_H_

#include "motor/dc_motor.h"

#define MOVEMENT_ENTRAXE_COEFF 0.005//0.0056 	// E=15cm
#define MOVEMENT_CORR_THRESHOLD 6 		// correct the speed only when we are more than 1 cm/s off target speed
#define MOVEMENT_CORR_KP 1			// amount of error to correct each iteration
#define SPEED_LIMIT 9000.00				//	mm/s


void movement_init(void);
void movement_set(int speed, float angle);
void movement_setSpeed(int speed);
void movement_stop(void);
void movement_regulate(void);




#endif /* MOVEMENT_DRIVER_MOVEMENT_H_ */
