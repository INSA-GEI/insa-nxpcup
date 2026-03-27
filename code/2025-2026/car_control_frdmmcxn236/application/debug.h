/**
 * @file debug.h
 * @author Sebastien DI MERCURIO
 * @version V1.0
 * @date 14 November 2023
 *
 * @brief Debug functions.
 * This file contains the declarations for debug functions.
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "app.h"

void DEBUG_Init();

/**
 * @brief Print a string via ITM.
 *
 * @param str The string to print.
 */
void DEBUG_Print(char *str);

/**
 * @brief Print periodic debug information via ITM.
 * This function collects from Freertos and prints periodic debug information,
 * including task states and sensor data.
 */
void DEBUG_PrintPeriodicInfo(void);

/**
 * @brief Handle a panic situation.
 * This function is called when a panic situation occurs, printing the file and line number.
 *
 * @param file The file where the panic occurred.
 * @param line The line number where the panic occurred.
 */
void DEBUG_Panic(uint8_t *file, uint32_t line);

/**
 * @brief Run time counter overflow handler.
 * This function handles the overflow of the run time counter used by FREERTOS for task statistics.
 */
void runTimeCounterOverflowHandler(void);

void Error_Handler(void);

#endif /* DEBUG_H_ */
