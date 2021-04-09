/*
 * Tof_sensor.cpp
 *
 *  Created on: Mar 22, 2021
 *      Author: Amelie/Arthur
 */


#include "Tof_sensor.h"

uint32_t TOF::tick_count = 0;

uint32_t TOF::getTickCount(void) {
	return (this->tick_count);
}

extern "C" uint32_t call_C_getTickCount(TOF *p) {// wrapper function
		return p->getTickCount();
}

