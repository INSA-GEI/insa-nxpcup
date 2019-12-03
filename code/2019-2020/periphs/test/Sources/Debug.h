/*
 * Debug.h
 *
 *  Created on: Nov 30, 2019
 *      Author: User
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <MKL25Z4.h>


#define DEBUG_RED_Pin		(1 << 18)
#define DEBUG_GREEN_Pin		(1 << 19)
#define DEBUG_BLUE_Pin		(1 << 1)

#define DEBUG_RED_OFF		(GPIOB_PSOR |= DEBUG_RED_Pin)
#define DEBUG_RED_ON		(GPIOB_PCOR |= DEBUG_RED_Pin)

#define DEBUG_GREEN_OFF		(GPIOB_PSOR |= DEBUG_GREEN_Pin)
#define DEBUG_GREEN_ON		(GPIOB_PCOR |= DEBUG_GREEN_Pin)

#define DEBUG_BLUE_OFF		(GPIOD_PSOR |= DEBUG_BLUE_Pin)
#define DEBUG_BLUE_ON		(GPIOD_PCOR |= DEBUG_BLUE_Pin)

void debug_init();

unsigned char debug_getRotarySW();

#endif /* DEBUG_H_ */
