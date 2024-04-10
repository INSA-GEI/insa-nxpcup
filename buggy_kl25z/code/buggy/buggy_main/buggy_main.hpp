/*
 * buggy_main.h
 *
 *  Created on: 2 févr. 2024
 *      Author: Triet NGUYEN
 */

#ifndef BUGGY_MAIN_H_
#define BUGGY_MAIN_H_
#include "movement/driver_movement.h"
#include <ImageProcessing/ImageProcessing.hpp>

void Camera_IRQHandler();
void buggy_run(void);
void Buggy_Set_Vstart(int v);
void Buggy_Set_Vtarget(int v);
void Buggy_Set_Vturn(int v);
void Ostacle_Detection(void);


#endif /* BUGGY_MAIN_H_ */
