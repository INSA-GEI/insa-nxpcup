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


/************* Low Power Timer (LPTMR) **************/
#define CORE_CLOCK 48000000UL
#define f_timer 	1 		// 0.4Hz to 11.5kHz max setting
#define PSC_LPTMR 	2048
#define PSC_POWER 	11
#define ARR_LPTMR 	(CORE_CLOCK/(f_timer*(PSC_LPTMR+1)))
#define LPTMR_ARR 	65535

void lptmr_conf(void);

/************* ADC0 **************/
#define BATT_VOLTAGE_MAX 	7.2
#define ADC_SCALING 		(3.3*(2.2+4.7)*1000.0/2.2)
#define ADC_RESOLUTION 		1023		//10 bits
#define BATT_SEUIL 			BATT_VOLTAGE_MAX * ADC_RESOLUTION * 0.5	//50% of battery


void BatteryVoltage(void);


#endif /* DEBUG_DRIVER_DEBUG_H_ */
