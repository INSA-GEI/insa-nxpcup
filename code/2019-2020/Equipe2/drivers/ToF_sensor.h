/*
 * Tof_sensor.h
 *
 *  Created on: Mar 22, 2021
 *      Author: Arthur ZAPPA/Amelie MAIER
 */

#ifndef _TOF_SENSOR_H_
#define _TOF_SENSOR_H_

#include "api/core/vl53l1_api.h"

class TOF {
	
public : 
	static uint32_t tick_count; // tick_count increment at 6kHz
	uint32_t getTickCount(void);
};

#ifdef __cplusplus

extern "C" {
#endif
	uint32_t call_C_getTickCount(TOF *p); // return the value of "tick_count" in C file
}
#ifdef __cplusplus
#endif

#endif 
