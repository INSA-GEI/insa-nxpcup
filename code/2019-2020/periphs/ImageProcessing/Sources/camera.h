
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


#define THRESHOLD 400

void camera_init();

void camera_capture(void);//Capture duration : approx 480us

int camera_getRawData(int index);

#endif /* CAMERA_H_ */
