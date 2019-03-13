


#ifndef CAMERA_H_
#define CAMERA_H_

#include "derivative.h" /* include peripheral declarations */
#include "math.h"	/* used for different calculations, including the difference of Gaussian with roots, exponential and PI */
#include "stdio.h"
#include "stdlib.h"

/* 
*
*	DEFINES : Can be in "main.c",
*	"camera.c" or "camera.h".
*
*/

// Defines for LineScan Camera
#define TAOS_DELAY				asm ("nop")				// minimal delay time
#define	TAOS_SI_HIGH			GPIOB_PDOR |= (1<<8)	// SI on PTB8
#define	TAOS_SI_LOW				GPIOB_PDOR &= ~(1<<8)	// SI on PTB8
#define	TAOS_CLK_HIGH			GPIOB_PDOR |= (1<<9)	// CLK on PTB9
#define	TAOS_CLK_LOW			GPIOB_PDOR &= ~(1<<9)	// CLK on PTB9


// Define thresholds for Camera Black Line recognition
#define THRESHOLD_high				140			// Higher threshold : does not capture noise but may not capture all maximums.
#define THRESHOLD_low				50			// Lower threshold : May capture more maximums than High threshold but can capture noise too.

#define THRESHOLD_classic			120			// standard threshold : used in the basic image processing function

#define functionning_mode			2			// operating mode: from 1 to 3: algorithm more and more precise but heavy

#define SIGMA_1	 					2			// square root of the variance for the first gaussian filter
#define SIGMA_2 					2.5			// square root of the variance for the second gaussian filter. 

#define PI							3.14159265358979323846	// value of PI




void ImageCapture(void); // capture linescan image
/*
*	Capture linescan image at a given time. 
*	The image is stored in the form of a 128 pixel table, whose value varies from 0 to 255 depending on the intensity
*
*/

void fill_ImageDataDifference(void);
/*
*	Fills in the "ImageDataDifference" table according to the selected operating mode (see below)
*
*/

void test_FinishLine_Detection (void);
/*
*	lights a blue LED if the program detects the pattern of the finish / start line
*	total track width = 550 mm
*	width of each black band on the sides = 20 mm
*	width of the "white" part = 510 mm
*
*	finish line / start = 2 * rectangles of 94 mm side
*	the rectangle starts 124 mm from the end of the black band (144 mm from the beginning of the track)
*	There are 74 mm centred in the middle of the track between the two black rectangles of the finish/start line
*
*/


void plot_ImageData (void);
/*
*
*	plot the 128 pixels data from the table "ImageData"
*
*/

void plot_ImageDataDifference (void);
/*
*	Plot the 128 pixels data from the table "ImageDataDifference"
*
*/


void image_processing (int * diff, int * diff_old, int * BlackLineLeft, int * BlackLineRight, int * RoadMiddle, int * number_edges);
/*
*	Retrieves the image, applies algorithms to find local maximums and thus define the position of black lines. 
*	PARAMETERS : operating mode : 1 = classic algorithm (same as the NXP_minimal) 
*								  2 = using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
*								  3 = using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
								  4 = using the Gaussian difference method
*				 diff : pointer to a variable "diff" defined in main. 
*				 diff_old : pointer to a variable "diff_old" defined in main. 
*
*/ 


/*
*
*				GAUSSIAN DIFFERENCES METHOD  :
*
*
*		calculates two Gaussian filters for different variances and then calculates their difference (absolute value) for each pixel (128).
*		puts the values in each cell of the "image_data_difference" table
*
*		To be used by modifying the variance values to obtain a satisfactory result because the model is too complex to model 
*		(need to know the probability of the value given by each pixel between 0 and 255). 
*/


#endif /* CAMERA_H_ */
