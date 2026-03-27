/**
 * @file debug.c
 * @author Sebastien DI MERCURIO
 * @version V1.0
 * @date 14 November 2023
 *
 * @brief Debug functions.
 * This file contains the declarations for debug functions.
 */

#include "app.h"
#include "configuration.h"

#include "debug.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// ITM Stimulus Port pour SWO
#define ITM_STIMULUS_PORT_PRINTF 			0
#define ITM_STIMULUS_PORT_PERIODIC_DEBUG 	1

char DEBUG_Buffer[DEBUG_BUFFER_SIZE];
uint16_t runTimeCounterOverflow = 0;

size_t xFreeHeapSize;

void DEBUG_Init() {
	uint32_t *CSFUNNEL_LAR = (uint32_t *)(TPIU_BASE + 0x4000 + 0xFB0);
	*CSFUNNEL_LAR = 0xC5ACCE55;
}

/**
 * @brief Print a string via ITM.
 *
 * @param port The ITM stimulus port to use.
 * @param str The string to print.
 */
void DEBUG_PrintITM(uint8_t port, char *str);

/**
 * @brief Print a string via ITM on the default port.
 *
 * @param str The string to print.
 */
void DEBUG_PrintITM(uint8_t port, char *str) {
	if (ITM->TCR & ITM_TCR_ITMENA_Msk) { // Vérifie si l'ITM est activé
		while (*str!=0) {
			while (ITM->PORT[port].u32 == 0) {} // Attend que le port soit prêt
			ITM->PORT[port].u8 = (uint8_t)*str;   // Écrit un caractère

			str++;
		}
	}
}

/**
 * @brief Print a string via ITM on the default port.
 *
 * @param str The string to print.
 */
void DEBUG_Print(char *str) {
	DEBUG_PrintITM(ITM_STIMULUS_PORT_PRINTF, str);
}

/**
 * @brief Print periodic debug information via ITM.
 * This function collects from Freertos and prints periodic debug information,
 * including task states and sensor data.
 */
void DEBUG_PrintPeriodicInfo(void) {
	/******************************************************
	 * Collecte et affiche les informations périodiques
	 * Données liées aux taches et à la mémoire dynamique
	 * Canal de debug 1
	 **************************************************/

	vTaskList(DEBUG_Buffer); // Collecte les stats
	DEBUG_PrintITM(ITM_STIMULUS_PORT_PERIODIC_DEBUG,"Task\tState\tPrio\tStack\tNum\n");
	DEBUG_PrintITM(ITM_STIMULUS_PORT_PERIODIC_DEBUG,DEBUG_Buffer);
	DEBUG_PrintITM(ITM_STIMULUS_PORT_PERIODIC_DEBUG,"\n");

	xFreeHeapSize = xPortGetFreeHeapSize();

	// You can print this value for debugging purposes.
	snprintf(DEBUG_Buffer,DEBUG_BUFFER_SIZE-1,"Current Free Heap Size: %u bytes\n", xFreeHeapSize);
	DEBUG_PrintITM(ITM_STIMULUS_PORT_PERIODIC_DEBUG,DEBUG_Buffer);

	// You can also check if the free heap size is getting too low.
	if (xFreeHeapSize < 500) // Example threshold: 500 bytes
	{
		snprintf(DEBUG_Buffer,DEBUG_BUFFER_SIZE-1,"WARNING: Low heap memory!\n");
		DEBUG_PrintITM(ITM_STIMULUS_PORT_PERIODIC_DEBUG,DEBUG_Buffer);
	}
}

/**
 * @brief Handle a panic situation.
 * This function is called when a panic situation occurs, printing the file and line number.
 *
 * @param file The file where the panic occurred.
 * @param line The line number where the panic occurred.
 */
void DEBUG_Panic(uint8_t *file, uint32_t line) {
	snprintf(DEBUG_Buffer, DEBUG_BUFFER_SIZE - 1,
			"\r\nPANIC at line %lu in file %s\r\n", line, file);
	DEBUG_Print(DEBUG_Buffer);

	xFreeHeapSize = xPortGetFreeHeapSize();

	// You can print this value for debugging purposes.
	snprintf(DEBUG_Buffer,DEBUG_BUFFER_SIZE-1,"Current Free Heap Size: %u bytes\r\n", xFreeHeapSize);
	DEBUG_Print(DEBUG_Buffer);

	// Optionally, you can enter an infinite loop to halt the system
	while (1) {
		// Blink an LED or take other actions to indicate a panic state
	}
}

// ----- Run time stats configuration for FreeRTOS -----
// Utilisation du timer CTIMER0, à 150 Mhz
// Le timer est 32 bits, pas besoin d'overflow (overflow toutes les 23 secondes)
#define STATS_TIMER         CTIMER0
/**
 * @brief Configure the timer for run time stats.
 * This function initializes TIM7 to be used as the run time counter for FreeRTOS.
 */
void configureTimerForRunTimeStats(void)
{
	// Lancement du timer CTIMER0:

	CTIMER_StartTimer(STATS_TIMER);
}

/**
 * @brief Get the current value of the run time counter.
 * This function returns the current value of the run time counter used by FreeRTOS.
 *
 * @return unsigned long The current value of the run time counter.
 */
unsigned long getRunTimeCounterValue(void)
{
	// Utilisation du CTIMER0 en 32-bit natif :
	return (unsigned long)CTIMER_GetTimerCountValue(STATS_TIMER);
}

/**
 * @brief Hook appelé en cas de débordement de pile (Stack Overflow).
 * @param xTask Le handle de la tâche qui a causé le crash.
 * @param pcTaskName Le nom de la tâche fautive.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    /* * Le code arrive ici si le pointeur de pile d'une tâche sort de sa zone allouée.
     * ATTENTION : À ce stade, le système est instable.
     */

    // 1. Désactiver les interruptions pour figer l'état
    taskDISABLE_INTERRUPTS();

    // 2. Journaliser l'erreur (Optionnel : nécessite un port série fonctionnel)
    snprintf(DEBUG_Buffer, DEBUG_BUFFER_SIZE - 1,
    		"STACK OVERFLOW DETECTED: Task %s\n", pcTaskName);
    DEBUG_Print(DEBUG_Buffer);

    // 3. Point d'arrêt pour le débogage (indispensable en développement)
    __builtin_trap(); // Ou __asm("BKPT #0"); pour les processeurs ARM

    // 4. Boucle infinie
    for( ;; );
}
