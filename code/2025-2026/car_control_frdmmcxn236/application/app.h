/*
 * app.h
 *
 *  Created on: 25 mars 2026
 *      Author: dimercur
 */

#ifndef APP_H_
#define APP_H_

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "peripherals.h"

void APP_Init(void);

void APP_CameraFrameReceived(void);
void APP_Computelines(void);
void APP_CarControl(void);

#endif /* APP_H_ */
