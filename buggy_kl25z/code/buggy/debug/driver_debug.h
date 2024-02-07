/*
 * driver_debug.h
 *
 *  Created on: 1 févr. 2024
 *      Author: thc18
 */

#ifndef DEBUG_DRIVER_DEBUG_H_
#define DEBUG_DRIVER_DEBUG_H_

#include "fsl_adc16.h"
#include "fsl_lptmr.h"
#include "fsl_port.h"
#include "fsl_device_registers.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"


/************* Low Power Timer (LPTMR) **************/

void LPTMR_Enable(void);


/************* ADC0 **************/

#define DEBUG_RED_Pin		18
#define DEBUG_GREEN_Pin		19
#define DEBUG_BLUE_Pin		1
#define DEBUG_CAM_LED_Pin   12

#define BATT_VOLTAGE_MAX 	7.2
#define ADC_SCALING 		(3.3*(2.2+4.7)*1000.0/2.2)
#define ADC_RESOLUTION 		1023		//10 bits
#define BATT_SEUIL 			BATT_VOLTAGE_MAX * ADC_RESOLUTION * 0.5	//50% of battery


void BatteryVoltage(void);


#define DISP_CLK_PIN		5
#define DISP_SIN_PIN 		6
#define DISP_LATCH_PIN 		10
void Debug_Init(void);

// Fonctions pour contrôler les LEDs
void debug_red_on();
void debug_red_off();
void debug_green_on();
void debug_green_off();
void debug_blue_on();
void debug_blue_off();

// Fonctions pour contrôler les signaux d'affichage
void disp_clk_on();
void disp_clk_off();
void disp_sin_on();
void disp_sin_off();
void disp_latch_on();
void disp_latch_off();



#endif /* DEBUG_DRIVER_DEBUG_H_ */
