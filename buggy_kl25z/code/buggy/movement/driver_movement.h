/*
 * driver_mouvement.h
 *
 *  Created on: 25 janv. 2024
 *      Author: TANG Huong Cam
 */

#ifndef MOVEMENT_DRIVER_MOVEMENT_H_
#define MOVEMENT_DRIVER_MOVEMENT_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "motor/dc_motor.h"
#include "encoder/driver_encoder.h"
#include "servo/driver_servo.h"


/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

#define MOVEMENT_ENTRAXE_COEFF 		0.005		// 0.0056 	// Distance between 2 wheels E=15cm
#define MOVEMENT_CORR_THRESHOLD 	6.0 		// correct the speed only when we are more than 60 mm/s off target speed
#define MOVEMENT_CORR_KP 			1			// amount of error to correct each iteration
#define MOVEMENT_SPEED_LIMIT_MM_S 	9000.0		// mm/s ~ 50% PWM
#define MOVEMENT_SPEED_LIMIT_PWM	50.0		// 50% ~ 9000 mm/s


/***********************************************************************************************************************
 * Exported functions
 **********************************************************************************************************************/

/**
 * @fn void movement_init(void)
 * @brief initialize the necessary peripherals for the movement
 */
void movement_init(void);

/**
 * @fn void movement_set(float speed, float angle)
 * @brief set the speed and angle target for the command
 * @param speed : float in mm/s
 * 		  angle : float in degree
 */
void movement_set(float speed, float angle);

/**
 * @fn void movement_setSpeed(float speed)
 * @brief set the speed target for the command
 * @param speed in mm/s
 */
void movement_setSpeed(float speed);

/**
 * @fn void movement_stop(void)
 * @brief stop the movement
 */
void movement_stop(void);

/**
 * @fn void movement_regulate(void)
 * @brief regulate the movement to adapt the command
 */
void movement_regulate(void);




#endif /* MOVEMENT_DRIVER_MOVEMENT_H_ */
