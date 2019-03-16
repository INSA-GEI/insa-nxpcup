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
//#include "detection.h"


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


	void image_processing (int * diff, int * diff_old, int * BlackLineLeft, int * BlackLineRight, int * RoadMiddle, int* number_edges)
	{
		*number_edges = 0;		// reset the number of peaks to 0
		
		if (functionning_mode == 1)
		{
			// Find black line on the right side
			CompareData_classic = THRESHOLD_classic;					// threshold
			*BlackLineRight = 126;
			for(i=64;i<=125;i++)
			{
	   			if (ImageDataDifference[i] > CompareData_classic)
	   			{
	   				CompareData_classic = ImageDataDifference[i];
	   				*BlackLineRight = i;
	   				*number_edges++;
	   			}
			}
	
			// Find black line on the left side
			CompareData_classic = THRESHOLD_classic;					// threshold
			*BlackLineLeft = 1;
			for(i=64;i>=3;i--)							// only down to pixel 3, not 1
			{
			   	if (ImageDataDifference[i] > CompareData_classic)
	 		  	{
	 	 	 		CompareData_classic = ImageDataDifference[i];
	 		  		*BlackLineLeft = i;
	 		  		*number_edges++;
	 	  		}
			}
			
			GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off
			GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
			GPIOD_PDOR &= ~GPIO_PDOR_PDO(1<<1);   // blue LED on		
			
		}	/* END of "(IF mfunctionning_mod == 1)" */
	
/****************************************************************************************************************************************************

		Mode number 2 or 3 : same type of operation (gradient differences)
		mode 2 : using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
		mode 3 : using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
			
*****************************************************************************************************************************************************/

		else if (functionning_mode == 2 || functionning_mode == 3)	
		{
			// Find black line on the right side

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			*BlackLineRight = 126;
			for(i=126;i>=64;i--)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineRight = i;
	   				*number_edges ++;
	   			}
	   			else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high )
	   			{
	   				if (i >= 67 && i < 124)
	   				{
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3)
	   					{
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high)
	   						{
	   							*BlackLineRight = i;
	   							*number_edges ++;
	   							//CompareData_high = ImageDataDifference[i+j];	
	   							validate_gradient = 1;	
	   							
	   						}
	   						j++;
	   					}
	   				}

	   				if (validate_gradient != 1)
	   				{
	   					if (i >= 69 && i < 122)
	   					{
	   						j=1;
	   						while (j <= 5)
	   						{
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high))
	   							{
	   								*BlackLineRight = i;
	   								*number_edges ++;
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;

	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
			}	/* END for (i=126;i>=64;i--) */


	   		// Find black line on the left side

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			*BlackLineLeft = 1;
			for(i=1;i<=64;i++)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineLeft = i;
	   				*number_edges ++;
	   			}
	   			else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high )
	   			{
	   				if (i > 3 && i <= 61)
	   				{
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3)
	   					{
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high)
	   						{
	   							*BlackLineLeft = i;
	   							*number_edges ++;
	   							//CompareData_high = ImageDataDifference[i+j];
	   							//CompareData_low = ImageDataDifference[i];	   		
	   							validate_gradient = 1;				
	   						}
	   						j++;
	   					}
	   				}

	   				if (validate_gradient != 1)
	   				{
	   					if (i > 5 && i <= 59)
	   					{
	   						j=1;
	   						while (j <= 5)
	   						{
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high))
	   							{
	   								*BlackLineLeft = i;
	   								*number_edges ++;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;
	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
	   		}	/* END for (i=64;i>=1;i--) */

			GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
			GPIOD_PDOR |= GPIO_PDOR_PDO(1<<1);    // blue LED off	
			GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<18);	// red led on
			
		}	/* END of "(IF mfunctionning_mod == 2 || functionning_mode == 3)" */


/****************************************************************************************************************************************************

		Mode number 4 : about the same as mode 2 and 3, but the calculation is made on two additional indices (0 and 127)
		mode 4 : using the Gaussian difference method
			
*****************************************************************************************************************************************************/

		else if (functionning_mode == 4)
		{
			// Find black line on the right side

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			*BlackLineRight = 126;
			for(i=127;i>=64;i--)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineRight = i;
	   			}
	   			else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high )
	   			{
	   				if (i >= 67 && i <= 124)
	   				{
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3)
	   					{
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high)
	   						{
	   							*BlackLineRight = i;
	   							//CompareData_high = ImageDataDifference[i+j];	
	   							validate_gradient = 1;				
	   						}
	   						j++;
	   					}
	   				}

	   				if (validate_gradient != 1)
	   				{
	   					if (i >= 69 && i <= 122)
	   					{
	   						j=1;
	   						while (j <= 5)
	   						{
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high))
	   							{
	   								*BlackLineRight = i;
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;

	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
			}	/* END for (i=126;i>=64;i--) */


	   		// Find black line on the left side

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			*BlackLineLeft = 1;
			for(i=0;i<=64;i++)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineLeft = i;
	   			}
	   			else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high )
	   			{
	   				if (i >= 3 && i <= 61)
	   				{
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3)
	   					{
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high)
	   						{
	   							*BlackLineLeft = i;
	   							//CompareData_high = ImageDataDifference[i+j];
	   							//CompareData_low = ImageDataDifference[i];	   		
	   							validate_gradient = 1;				
	   						}
	   						j++;
	   					}
	   				}

	   				if (validate_gradient != 1)
	   				{
	   					if (i >= 5 && i <= 59)
	   					{
	   						j=1;
	   						while (j <= 5)
	   						{
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high))
	   							{
	   								*BlackLineLeft = i;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;
	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
	   		}	/* END for (i=64;i>=1;i--) */

			
			GPIOB_PDOR |= GPIO_PDOR_PDO(1<<19);   // green LED off
			GPIOB_PDOR |= GPIO_PDOR_PDO(1<<18);   // red LED off
			GPIOD_PDOR &= ~GPIO_PDOR_PDO(1<<1);   // blue LED on	
			
			
		} /* END of "if (functionning_mode == 4)"  */
			
	}	/*	END of the function "Image_Processing"	*/



/*void plot_ImageData (void)
{
	for (i=0;i<=127;i++)
	{
		if (i==0)
		{
			printf("ImageData (0 to 127) : %d ",ImageData[i]);
		}
		else if (i == 127)
		{
			printf("%d \n", ImageData[i]);
		}
		else 
		{
			printf("%d ",ImageData[i]);
		}
	}
}	*/


/*	END of function "plot_ImageData"	*/


/*void plot_ImageDataDifference (void)
{
	for (i=0;i<=127;i++)
	{
		if (i==0)
		{
			printf("ImageDataDifference (0 to 127) : %d ",ImageDataDifference[i]);
		}
		else if (i == 127)
		{
			printf("%d \n", ImageDataDifference[i]);
		}
		else 
		{
			printf("%d ",ImageDataDifference[i]);
		}
	}
}	*/

/*	END of function "plot_ImageDataDifference"	*/
























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
