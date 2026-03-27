/**
 * @file    tasks.c
 * @author  Sebastien DI MERCURIO
 * @version V1.0
 * @date    27 Aout 2025
 * @brief   FreeRTOS tasks, queues, semaphores and timers management.
 * This file contains the implementation of FreeRTOS tasks, queues, semaphores, and timers used in the car application.
 * It defines the tasks for application logic, debugging, ultrasonic sensor management, control loop, and calibration events.
 */

#include "configuration.h"

#include "app.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "debug.h"

#if defined (__TESTS__)
#include "tests.h"
#endif /* __TESTS__ */

/* -------------------------------------------------------------------------
 * Déclaration de la tâche TASKS_InitSystem
 * ------------------------------------------------------------------------- */
void TASKS_InitSystem(void *argument);

/* Handle vers la tâche */
static TaskHandle_t xInitSystemTaskHandle = NULL;

/* -------------------------------------------------------------------------
 * Déclaration de la tâche TASKS_CameraFrameReceived
 * ------------------------------------------------------------------------- */
void TASKS_CameraFrameReceived(void *argument);

/* Handle vers la tâche */
static TaskHandle_t xCameraFrameReceivedTaskHandle = NULL;

/* -------------------------------------------------------------------------
 * Déclaration de la tâche TASKS_DebugLoop
 * ------------------------------------------------------------------------- */
void TASKS_DebugLoop(void *argument);

/* Handle vers la tâche */
static TaskHandle_t xDebugLoopTaskHandle = NULL;

/* -------------------------------------------------------------------------
 * Déclaration de la tâche TASKS_Computelines
 * ------------------------------------------------------------------------- */
void TASKS_Computelines(void *argument);

/* Handle vers la tâche */
static TaskHandle_t xComputelinesTaskHandle = NULL;

/* -------------------------------------------------------------------------
 * Déclaration de la tâche TASKS_MotorsControlLoop
 * ------------------------------------------------------------------------- */
void TASKS_MotorsControlLoop(void *argument);

/* Handle vers la tâche */
static TaskHandle_t xMotorsControlLoopTaskHandle = NULL;

/* -------------------------------------------------------------------------
 * Déclaration du sémaphore de reception d'une image
 * ------------------------------------------------------------------------- */
SemaphoreHandle_t xCameraFrameReceivedSemaphore = NULL;

/* -------------------------------------------------------------------------
 * Déclaration du sémaphore pour le traitement des lignes
 * ------------------------------------------------------------------------- */
SemaphoreHandle_t xComputelinesSemaphore = NULL;

/* -------------------------------------------------------------------------
 * Déclaration du sémaphore de transfert DMA - LCD
 * ------------------------------------------------------------------------- */
SemaphoreHandle_t xLCDTransfertSemaphore = NULL;

/* -------------------------------------------------------------------------
 * Déclaration du timer pour l'envoi de la mesure de la batterie (statique)
 * ------------------------------------------------------------------------- */
//static void BatteryTimerCallback(TimerHandle_t xTimer);
//static StaticTimer_t xBatteryTimerBuffer;
//static TimerHandle_t xBatteryTimer   = NULL;

/*
 * @brief  Initialize tasks, queues, semaphores and timers.
 * This function creates the necessary FreeRTOS components for the application.
 * It sets up tasks, queues, semaphores, and timers used in the application.
 */
void TASKS_Init(void) {
	/* Création de la tâche TASKS_CameraFrameReceived */
	xTaskCreate(
			TASKS_CameraFrameReceived,          // fonction de la tâche
			"CameraFrame",             // nom (debug)
			CAMERA_FRAME_RECEIVED_TASK_STACK_SIZE,   // taille pile (en mots de 32 bits)
			NULL,                  // paramètre d’entrée
			CAMERA_FRAME_RECEIVED_TASK_PRIORITY,     // priorité
			&xCameraFrameReceivedTaskHandle
	);

	if (xCameraFrameReceivedTaskHandle == NULL) {
		// Erreur : pas de mémoire ?
		Error_Handler();
	}

	/* Création de la tâche DebugLoop */
	xTaskCreate (
			TASKS_DebugLoop,          // fonction de la tâche
			"DebugLoop",             // nom (debug)
			DEBUGLOOP_TASK_STACK_SIZE,   // taille pile (en mots de 32 bits)
			NULL,                  // paramètre d’entrée
			DEBUGLOOP_TASK_PRIORITY,    // priorité
			&xDebugLoopTaskHandle
	);

	if (xDebugLoopTaskHandle == NULL) {
		// Erreur : pas de mémoire ?
		Error_Handler();
	}

	/* Création de la tâche Computelines */
	xTaskCreate(
			TASKS_Computelines, // fonction de la tâche
			"Computelines",             // nom (debug)
			COMPUTE_LINES_TASK_STACK_SIZE,   // taille pile (en mots de 32 bits)
			NULL,                  // paramètre d’entrée
			COMPUTE_LINES_TASK_PRIORITY,     // priorité
			&xComputelinesTaskHandle
	);

	if (xComputelinesTaskHandle == NULL) {
		// Erreur : pas de mémoire ?
		Error_Handler();
	}

	/* Création de la tâche MotorsControlLoop */
	xTaskCreate(
			TASKS_MotorsControlLoop, // fonction de la tâche
			"ControlLoop",             // nom (debug)
			MOTORS_CONTROL_TASK_STACK_SIZE,   // taille pile (en mots de 32 bits)
			NULL,                  // paramètre d’entrée
			MOTORS_CONTROL_TASK_PRIORITY,     // priorité
			&xMotorsControlLoopTaskHandle
	);

	if (xMotorsControlLoopTaskHandle == NULL) {
		// Erreur : pas de mémoire ?
		Error_Handler();
	}

	/* Création de la tâche TASKS_InitSystem*/
	xTaskCreate(
			TASKS_InitSystem,          // fonction de la tâche
			"Init",             // nom (debug)
			INITSYSTEM_TASK_STACK_SIZE,   // taille pile (en mots de 32 bits)
			NULL,                  // paramètre d’entrée
			INITSYSTEM_TASK_PRIORITY,     // priorité
			&xInitSystemTaskHandle
	);

	if (xCameraFrameReceivedTaskHandle == NULL) {
		// Erreur : pas de mémoire ?
		Error_Handler();
	}

	/*****************************************************
	 *
	 * SEMAPHORES
	 *
	 *****************************************************/

	/* Création du sémaphore de reception d'une image */
	xCameraFrameReceivedSemaphore = xSemaphoreCreateBinary();
	if (xCameraFrameReceivedSemaphore == NULL) {
		// Erreur : pas de mémoire ?
		Error_Handler();
	}

	/* Au démarrage, le sémaphore est "pris" => ok, comportement attendu */

	/* Création du sémaphore pour le traitement des lignes */
	xComputelinesSemaphore = xSemaphoreCreateBinary();
	if (xComputelinesSemaphore == NULL) {
		// Erreur : pas de mémoire?
		Error_Handler();
	}

	/* Au démarrage, le sémaphore est "pris" => Ok, comportement attendu */

	/* Création du sémaphore de transfert DMA - LCD  */
	xLCDTransfertSemaphore = xSemaphoreCreateBinary();
	if (xLCDTransfertSemaphore == NULL) {
		// Erreur : pas de mémoire  ?
		Error_Handler();
	}

	/* Au démarrage, le sémaphore est "pris".
	 * Pas le comportement souhaité, on va le liberer */

	xSemaphoreGive(xLCDTransfertSemaphore);

	vQueueAddToRegistry(xCameraFrameReceivedSemaphore, "CameraFrameSem");
	vQueueAddToRegistry(xComputelinesSemaphore, "ComputeLinesSem");
	vQueueAddToRegistry(xLCDTransfertSemaphore, "LCDTransfertSem");

	/* Timer batterie */
	//	xBatteryTimer = xTimerCreateStatic(
	//			"BatteryTimer",
	//			pdMS_TO_TICKS(BATTERY_TIMER_PERIOD_MS),
	//			pdTRUE,
	//			(void*)0,
	//			BatteryTimerCallback,
	//			&xBatteryTimerBuffer
	//	);
	//	configASSERT(xBatteryTimer != NULL);

	//	if (xTimerStart(xBatteryTimer, 0) != pdPASS) {
	//		// Erreur : pas de mémoire statique ?
	//		Error_Handler();
	//	}
}

/**
 * @brief  Task function for initializing system.
 * This function is in charge of initializing systeme
 * returns and ends
 * @param  argument: Not used
 */
void TASKS_InitSystem(void *argument ) {
	APP_Init();

	vTaskDelete(NULL); // Destroy current task
}

/**
 * @brief  Task function for the camera reception frame.
 * This function is in charge of transfering received image to LCD and
 * get slices of image for line computation.
 * Never returns.
 * @param  argument: Not used
 */
void TASKS_CameraFrameReceived(void *argument ) {
	// no waiting time here : APP_CameraFrameReceived waits on a semaphore
	for (;;) {
		APP_CameraFrameReceived();
	}
}

/**
 * @brief  Task function for the debug loop.
 * This function runs periodically to perform debug tasks.
 * It runs indefinitely, executing its logic at defined intervals.
 * @param  argument: Not used
 */
void TASKS_DebugLoop(void *argument) {
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(DEBUG_LOOP_PERIOD_MS);

	/* Initialise la référence de temps */
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {
		DEBUG_PrintPeriodicInfo();

		// Time is compensated from others events that can make processing longer
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
}

/**
 * @brief  Task function for lines computation.
 * This function is in charge of computing slice of image for line detection.
 * never returns
 * @param  argument: Not used
 */
void TASKS_Computelines(void *argument) {
	// no waiting time here : APP_Computelines waits on a semaphore
	for (;;) {
		APP_Computelines();
	}
}

/**
 * @brief  Task function for the car control loop.
 * This function runs periodically to manage the car's control system.
 * It executes the control logic at defined intervals.
 * @param  argument: Not used
 */
void TASKS_MotorsControlLoop(void *argument) {
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(MOTORS_CONTROL_PERIOD_MS);

	/* Initialise la référence de temps */
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {

		APP_CarControl();

		// Wait for next control loop period
		// Time is compensated from others events that can make processing longer
		vTaskDelayUntil(&xLastWakeTime, xPeriod);
	}
}

/**
 * @brief  Callback function for the battery timer.
 * This function is called when the battery timer expires.
 * It performs sending battery measurements.
 */
//static void BatteryTimerCallback(TimerHandle_t xTimer) {
//	/* Send battery level to application main loop, for CAN formating */
//	MEASURES_SendBatteryLevel();
//}


