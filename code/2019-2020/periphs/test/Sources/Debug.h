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

#define DEBUG_RED_OFF		(GPIOB_PSOR = DEBUG_RED_Pin)
#define DEBUG_RED_ON		(GPIOB_PCOR = DEBUG_RED_Pin)
#define DEBUG_GREEN_OFF		(GPIOB_PSOR = DEBUG_GREEN_Pin)
#define DEBUG_GREEN_ON		(GPIOB_PCOR = DEBUG_GREEN_Pin)
#define DEBUG_BLUE_OFF		(GPIOD_PSOR = DEBUG_BLUE_Pin)
#define DEBUG_BLUE_ON		(GPIOD_PCOR = DEBUG_BLUE_Pin)

#define DISP_CLK_PIN		(1<<5)
#define DISP_SIN_PIN 		(1<<6)
#define DISP_LATCH_PIN 		(1<<10)

#define DISP_CLK_OFF		(GPIOC_PCOR = DISP_CLK_PIN)
#define DISP_CLK_ON			(GPIOC_PSOR = DISP_CLK_PIN)
#define DISP_SIN_OFF		(GPIOC_PCOR = DISP_SIN_PIN)
#define DISP_SIN_ON			(GPIOC_PSOR = DISP_SIN_PIN)
#define DISP_LATCH_OFF		(GPIOC_PCOR = DISP_LATCH_PIN)
#define DISP_LATCH_ON		(GPIOC_PSOR = DISP_LATCH_PIN)


void debug_init();

unsigned char debug_getRotarySW();
unsigned char debug_getUserSW1(void);
unsigned char debug_getUserSW2(void);

void debug_displaySendRaw(unsigned int data);
void debug_displaySendNb(unsigned int nb);

#endif /* DEBUG_H_ */
