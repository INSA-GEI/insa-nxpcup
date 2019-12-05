
#ifndef CAMERA_H_
#define CAMERA_H_

// Defines for LineScan Camera
#define CAM_DELAY				asm ("nop")				// minimal delay time
#define	CAM_SI_HIGH			GPIOB_PDOR |= (1<<8)	// SI on PTB8
#define	CAM_SI_LOW				GPIOB_PDOR &= ~(1<<8)	// SI on PTB8
#define	CAM_CLK_HIGH			GPIOB_PDOR |= (1<<9)	// CLK on PTB9
#define	CAM_CLK_LOW			GPIOB_PDOR &= ~(1<<9)	// CLK on PTB9

void camera_init();

void ImageCapture(void);

#endif /* CAMERA_H_ */