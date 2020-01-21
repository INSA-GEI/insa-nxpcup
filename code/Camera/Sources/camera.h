
#ifndef CAMERA_H_
#define CAMERA_H_
#include <MKL25Z4.h>
#include <stdlib.h>     /* srand, rand */

// Defines for LineScan Camera
#define CAM_DELAY				asm ("nop")				// minimal delay time
#define	CAM_SI_HIGH				GPIOB_PDOR |= (1<<8)	// SI on PTB8
#define	CAM_SI_LOW				GPIOB_PDOR &= ~(1<<8)	// SI on PTB8
#define	CAM_CLK_HIGH			GPIOB_PDOR |= (1<<9)	// CLK on PTB9
#define	CAM_CLK_LOW				GPIOB_PDOR &= ~(1<<9)	// CLK on PTB9


#define THRESHOLD 25

void camera_init();

void camera_capture(void);

int camera_getRawData(int index);
int camera_getDataDiff(int index);
int *camera_getEdges();

void camera_processData(void);

#endif /* CAMERA_H_ */
