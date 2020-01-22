/*
 * ImageProcessing.h
 *
 *  Created on: Jan 22, 2020
 *      Author: User
 */

#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_
#include <MKL25Z4.h>
#include <stdlib.h> 
#include "camera.h"



void img_differentiate(int mode);
void img_process(int mode);
void img_getEdges(int mode);
int img_getDiffData(int index);
int img_getProcData(int index);

#endif /* IMAGEPROCESSING_H_ */
