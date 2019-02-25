


#ifndef CAMERA_H_
#define CAMERA_H_

#include "derivative.h" /* include peripheral declarations */


/* 
*
*	DEFINES : Can be in "main.c",
*	"camera.c" or "camera.h".
*
*/


// Define thresholds for Camera Black Line recognition
#define THRESHOLD_high				130			// Higher threshold : does not capture noise but may not capture all maximums.
#define THRESHOLD_low				80			// Lower threshold : May capture more maximums than High threshold but can capture noise too.

#define THRESHOLD_classic			120			// standard threshold : used in the basic image processing function

#define functionning_mod			1			// operating mode: from 1 to 3: algorithm more and more precise but heavy



void ImageCapture(void); // capture linescan image
/*
*	Capture linescan image at a given time. 
*	The image is stored in the form of a 128 pixel table, whose value varies from 0 to 255 depending on the intensity
*
*/

void image_processing (int mode , int * diff, int * diff_old);
/*
*	Retrieves the image, applies algorithms to find local maximums and thus define the position of black lines. 
*	PARAMETERS : operating mode : 1 = classic algorithm (same as the NXP_minimal) 
*								  2 = using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
*								  3 = using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
*				 diff : pointer to a variable "diff" defined in main. 
*				 diff_old : pointer to a variable "diff_old" defined in main. 
*
*/ 

#endif /* CAMERA_H_ */
