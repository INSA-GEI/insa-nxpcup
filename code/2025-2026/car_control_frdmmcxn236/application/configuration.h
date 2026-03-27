/**
 * @file configuration.h
 * @author Sebastien DI MERCURIO
 * @version V1.0
 * @date 20 Aout 2023
 * @brief Configuration file for the car application.
 * This file contains definitions and configurations for the car's hardware and software components.
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "app.h"
#include "FreeRTOS.h"

// Application version
#define APP_VERSION "1.0.0"
#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0

// Periodic events, in ms
#define MOTORS_CONTROL_PERIOD_MS 	10		// Period in ms for motorol control loop
#define DEBUG_LOOP_PERIOD_MS		1000	// Debug loop period in ms

// Tasks, semaphores, queues constants

// Tasks stack sizes
#define CAMERA_FRAME_RECEIVED_TASK_STACK_SIZE 	configMINIMAL_STACK_SIZE + 100   // en mots de 32 bits
#define COMPUTE_LINES_TASK_STACK_SIZE  			configMINIMAL_STACK_SIZE + 100	 // en mots de 32 bits. Pas besoin d'une stack énorme
#define MOTORS_CONTROL_TASK_STACK_SIZE 			configMINIMAL_STACK_SIZE + 100   // en mots de 32 bits. Pour les calculs de la boussole
#define DEBUGLOOP_TASK_STACK_SIZE 				configMINIMAL_STACK_SIZE + 300 	 // en mots de 32 bits. Besoin de pas mal d'espace pour la fonction sprintf

// Tasks priorities
#define CAMERA_FRAME_RECEIVED_TASK_PRIORITY 	(tskIDLE_PRIORITY + 6)
#define COMPUTE_LINES_TASK_PRIORITY 			(tskIDLE_PRIORITY + 5)
#define MOTORS_CONTROL_TASK_PRIORITY			(tskIDLE_PRIORITY + 4)
#define DEBUGLOOP_TASK_PRIORITY 				(tskIDLE_PRIORITY + 3) // Lowest priority
// pour info, la tache IDLE a une priorité de tskIDLE_PRIORITY
// et les soft timers ont une priorité de MaxPriority

// Taille du buffer de debug
#define DEBUG_BUFFER_SIZE 	1024

#endif /* CONFIGURATION_H_ */
