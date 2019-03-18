/*
 * FRDM-KL25 Freedom Board NXP Cup Minimal Program
 * (c) THD Technische Hochschule Deggendorf
 * (c) DIT Deggendorf Institute of Technology
 * Version 2.1, 09.01.2018
 * Change: ported to NXP Cup and Alamank Car


	File : Camera.c 

	Objectives : 
		- capture the 128 pixels intensity from the camera, every period from Timer 1 : every 10 ms
		- offers different algorithms to process the image and find the black bars. 
		- Then, in the "hand" file, the vehicle position (actuator position) must be updated. 

	Camera Properties : 
		- 1D camera : 128 pixels (photodiodes) from left to right.
		- each pixel is defined by an intensity value between 0 and 255 from an 8-bit ADC.

	
	Author : Vincent P
	Date : 2019 / 02 / 20

 */

#include "camera.h"	/* include camera functions definition */
#include "math.h"	/* used for different calculations, including the difference of Gaussian with roots, exponential and PI */
#include "stdio.h"
#include "stdlib.h"


// Variable declaration
int i, j;									// counters for loops
int ImageData [128];						// array to store the LineScan image
int ImageDataDifference [128];				// array to store the PineScan pixel difference

int CompareData_classic;					// set data for comparison to find max IN BASE ALGORITHM
int CompareData_low;						// set data for comparison to find max with low threshold
int CompareData_high;						// set data for comparison to find max with high threshold
int validate_gradient;						// used in image processing to validate some parameters
	
float gaussian1;								// gaussian filters used in gaussian differences method
float gaussian2;

int ckbk; 

/*  variables from pointers (main) used in this file   */ 
// diff -> int			 actual difference from line middle position
// diff_old -> int		 previous difference from line middle position
// BlackLineRight -> int	 position of the black line on the right side
// BlackLineLeft -> int	     position of the black line on the left side

/*

	Two threshold functionning : 
		For a pixel P(x), having gradient magnitude G, following conditions exists to detect a pixel as edge :
			- if G < threshold_low then discard the edge
			- if G > threshold_high then keep the edge
			- if threshold_low < G < threshold_high and if any neighbour three units away have gradient magnitude greater than threshold_high, keep the edge
			- if no neighbour in this regions have gradient > threshold_high, search the 5 units away for threshold_low < gradient < threshold_high. 
				If so, keep the edge
			- else : discard the edge. 

*/

void switchLed(int red, int green, int blue) {
	GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off
	GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
	GPIOD_PDOR |= GPIO_PDOR_PDO(1<<1);    // blue LED off
	if(red == 1) {
		GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<18);  // red LED on
	}
	if (green == 1) {
		GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<19);  // green LED on
	}	
	if (blue == 1) {
		GPIOD_PDOR &= ~GPIO_PDOR_PDO(1<<1);   // blue LED on
	}
}

void fill_ImageDataDifference(void)
{
	if (functionning_mode == 1)
	{
		for(i=0;i<=126;i++)							// classic algorithm (same as the NXP_minimal) 
		{
			ImageDataDifference[i] = abs (ImageData[i] - ImageData[i+1]);
		}
		ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method
	}
	else if (functionning_mode == 2)
	{
		for(i=1;i<=126;i++)							// using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
		{
			ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
		}
		ImageDataDifference[0] = ImageData[0];	// first value doesnt have "gradient" for this method
		ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method
	}
	else if (functionning_mode == 3)
	{
		for(i=1;i<=126;i++)							// using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
		{
			ImageDataDifference[i] = abs (-(ImageData[i-1])/2 + (ImageData[i+1])/2);
		}
		ImageDataDifference[0] = ImageData[0];	// first value doesnt have "gradient" for this method
		ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method
	}
	else if (functionning_mode == 4)
	{
		for(i=0;i<=127;i++)							// using the Gaussian difference method
		{
			gaussian1 = (1/(SIGMA_1 * sqrt(2*PI))) * exp(-(pow(i,2))/(2*pow(SIGMA_1,2)));
			gaussian2 = (1/(SIGMA_2 * sqrt(2*PI))) * exp(-(pow(i,2))/(2*pow(SIGMA_2,2)));

			ImageDataDifference[i] = abs ( (int) (round ( (ImageData[i] * gaussian1 - ImageData[i] * gaussian2) ) ) );
		}

	}
}	/*	End of function "Fill_ImageDataDifference"	*/


/* line_list array of 10 peaks */
void image_processing (int *diff, int * diff_old, int * BlackLineLeft, int * BlackLineRight, int * RoadMiddle, int* number_edges, int * OldLineLeft, int * OldLineRight)
{
	
	/* sum default inits*/
	*BlackLineLeft = 0;
	*BlackLineRight = 128;
	*diff_old = *diff;
	
	/* create peak (containing local maxima that passes certain threshold) array and initialise zhem all 0*/
	*number_edges = 0;
	int peak[10];
	for (i = 0; i < 10; ++i) {
		peak[i] = 0;
	}
	
	/* determine the local maxima, bound by 3 and put them into the peak if they surpasses threshold */
	int found = 0;
	while (i < 124) {
		// reinit found = 0 for next run to find the local maxima
		found = 0;
		// iterate through local bound to find maxima
		for (j = 1; j < 4; ++j) {
			if (ImageDataDifference[i-j] < ImageDataDifference[i] && ImageDataDifference[i+j] < ImageDataDifference[i]) {
				found = 1;
			}else {
				found = 0;
				break;
			}
		}
		/* if at this stage found = 1, it means the point is the local maxima
		 * which means we should check if it passes the threshold
		 */
		if (found == 1 && ImageDataDifference[i] > THRESHOLD_classic) {
			peak[(*number_edges)++] = i;
			i = i + 10;
		}else {
			i++;
		}
	}
	
	/* then depending on how many edges we detect, let's do sum shit */
	if (*number_edges == 0) { /* can't see s*** => just assume a straight line*/
		*BlackLineLeft = *OldLineLeft;
		*BlackLineRight = *OldLineRight;
		switchLed(1,0,0); // red
	}else if (*number_edges == 1) { /* see one line, probably a turn to make */
		int diff_left = peak[0] - *OldLineLeft; 
		int diff_right = peak[0] - *OldLineRight; 
		if (peak[0] < 64 && abs(diff_left) < 20) {
			*BlackLineLeft = peak[0];
			*BlackLineRight = *BlackLineLeft + 80;
			switchLed(0,1,0); // green
		}else if (peak[0] >= 64 && abs(diff_right) < 20) {
			*BlackLineRight = peak[0];
			*BlackLineLeft = *BlackLineRight - 80;
			switchLed(0,1,0); // green
		}else if (abs(diff_left) < 30) {
			*BlackLineLeft = peak[0];
			*BlackLineRight = *BlackLineLeft + 80;
			switchLed(0,0,1); // blue
		}else if (abs(diff_right) < 30) {
			*BlackLineRight = peak[0];
			*BlackLineLeft = *BlackLineRight - 80;
			switchLed(0,0,1); // blue
		}
	}else if (*number_edges == 2) { /* the first one is the left line and the second one is the right line */
		if (peak[0] < 64 && peak[1] >= 64) { /* make sure that s*** doesn't diverge */
			*BlackLineLeft = peak[0];
			*BlackLineRight = peak[1];
			switchLed(1,1,1); // white
		}else { /* probably some errors*/
			*BlackLineLeft = *OldLineLeft;
			*BlackLineRight = *OldLineRight;
			switchLed(0,1,1); // nothing
		}
	}else if (*number_edges > 2) { /* for now we don't know yet what to do */
		*BlackLineLeft = *OldLineLeft;
		*BlackLineRight = *OldLineRight;
		if (*number_edges > 4) {
			switchLed(1,1,0); // nothing
		}else {
			switchLed(0,0,0);
		}	
	}
	
	/* update the condition of the last detected lines */
	*OldLineLeft = *BlackLineLeft;
	*OldLineRight = *BlackLineRight;
	
	*diff = (*BlackLineRight + *BlackLineLeft)/2 - 64; 	
}	/*	END of the function "Image_Processing"	*/


// Capture LineScan Image
void ImageCapture(void)
	{
	    unsigned char i;
  		ADC0_CFG2 |= 0x10;							// select B side of the MUX
 		TAOS_SI_HIGH;
 		TAOS_DELAY;
  		TAOS_CLK_HIGH;
  		TAOS_DELAY;
  		TAOS_SI_LOW;
   		TAOS_DELAY;
  		// inputs data from camera (first pixel)
		ADC0_SC1A  =  11;							// set ADC0 channel 11
		while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
		ImageData[0] = ADC0_RA;						// return value
		TAOS_CLK_LOW;

		for(i=1;i<128;i++)
   		{
      	  	TAOS_DELAY;
        	TAOS_DELAY;
       		TAOS_CLK_HIGH;
       		TAOS_DELAY;
       		TAOS_DELAY;
      		 // inputs data from camera (one pixel each time through loop)
    		ADC0_SC1A  =  11;							// set ADC0 channel 11
    		while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
    		ImageData[i] = ADC0_RA;						// return value
        	TAOS_CLK_LOW;
   		}
    
    	TAOS_DELAY;
    	TAOS_DELAY;
    	TAOS_CLK_HIGH;
    	TAOS_DELAY;
    	TAOS_DELAY;
    	TAOS_CLK_LOW;
}
