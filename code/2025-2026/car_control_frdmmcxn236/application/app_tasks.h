/**
 * @file tasks.h
 * @author Sebastien DI MERCURIO
 * @version V1.0
 * @date 27 Aout 2025
 * @brief Header file for tasks.c
 * This file contains the declarations for FreeRTOS tasks, queues, semaphores, and timers used in the car application.
 */

#ifndef __TASKS_H__
#define __TASKS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* -------------------------------------------------------------------------
 * Déclaration du sémaphore de reception d'une image (statique)
 * ------------------------------------------------------------------------- */
extern SemaphoreHandle_t xCameraFrameReceivedSemaphore;

/* -------------------------------------------------------------------------
 * Déclaration du sémaphore pour le traitement des lignes (statique)
 * ------------------------------------------------------------------------- */
extern SemaphoreHandle_t xComputelinesSemaphore;

/* -------------------------------------------------------------------------
 * Déclaration du sémaphore de transfert DMA - LCD (statique)
 * ------------------------------------------------------------------------- */
extern SemaphoreHandle_t xLCDTransfertSemaphore;

void TASKS_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __TASKS_H__ */
