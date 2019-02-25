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




// Variable declaration
int i, j;									// counters for loops
int ImageData [128];						// array to store the LineScan image
int ImageDataDifference [128];				// array to store the PineScan pixel difference
int BlackLineRight;							// position of the black line on the right side
int BlackLineLeft;							// position of the black line on the left side
int RoadMiddle = 0;							// calculated middle of the road
int diff = 0;								// actual difference from line middle position
int diff_old = 0;							// previous difference from line middle position
int CompareData_classic;					// set data for comparison to find max IN BASE ALGORITHM
int CompareData_low;						// set data for comparison to find max with low threshold
int validate_gradient;						// used in image processing to validate some parameters
int CompareData_high;						// set data for comparison to find max with high threshold


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


	GPIOB_PDOR &= ~GPIO_PDOR_PDO(1<<18);  // red LED on

	void image_processing (functionning_mod, *diff, *diff_old)
	{
		if (functionning_mod == 1)
		{
			// Find black line on the right side
			for(i=126;i>=64;i--)							// calculate difference between the pixels
			{
				ImageDataDifference[i] = abs (ImageData[i] - ImageData[i+1]);
			}
			CompareData = THRESHOLD_classic;					// threshold
			BlackLineRight = 126;
			for(i=126;i>=64;i--)
			{
	   			if (ImageDataDifference[i] > CompareData)
	   			{
	   				CompareData = ImageDataDifference[i];
	   				BlackLineRight = i;
	   			}
			}
	
			// Find black line on the left side
			for(i=0;i<=64;i++)							// calculate difference between the pixels
			{
				ImageDataDifference[i] = abs (ImageData[i] - ImageData[i-1]);
			}
			CompareData = THRESHOLD_classic;					// threshold
			BlackLineLeft = 1;
			for(i=3;i<=64;i++)							// only down to pixel 3, not 1
			{
			   	if (ImageDataDifference[i] > CompareData)
	 		  	{
	 	 	 		CompareData = ImageDataDifference[i];
	 		  		BlackLineLeft = i;
	 	  		}
			}
	
			// Find middle of the road, 64 for strait road
			RoadMiddle = (BlackLineLeft + BlackLineRight)/2;
	
			// if a line is only on the the left side
			if (BlackLineRight > 124)
			{
				RoadMiddle = BlackLineLeft + 50;
			}
			// if a line is only on the the right side
			if (BlackLineLeft < 3)
			{
				RoadMiddle = BlackLineRight - 50;
			}
			// if no line on left and right side
			if ((BlackLineRight > 124) && (BlackLineLeft < 3))
			{
				RoadMiddle = 64;
			}
	
			// Store old value
			diff_old = diff;							// store old difference
		
			// Find difference from real middle
			diff = RoadMiddle - 64;						// calculate actual difference
	
			// plausibility check
			if (abs (diff - diff_old) > 50)
			{
				diff = diff_old;
			}

		}	/* end IF mfunctionning_mod == 1 */
	
/**********************************************************************************


		Mode number 2 : direct differences. (filter : [-1 ; 0 ; 1])
		one of two heavy algorithms to measure local maximums while reducing noise. 


**********************************************************************************/

		else if (functionning_mod == 2)			// Gradient by direct differences ( [-1 ; 0 ; 1] )
		{
			// Find black line on the right side
			for(i=126;i>=64;i--)							// calculate difference between the pixels
			{
				ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
			}
			ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			BlackLineRight = 126;
			for(i=126;i>=64;i--)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineRight = i;
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
	   							BlackLineRight = i;
	   							//CompareData_high = ImageDataDifference[i+j];
	   							//CompareData_low = ImageDataDifference[i];	   		
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
	   								BlackLineRight = i;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;

	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
			}	/* END for (i=126;i>=64;i--) */


	   		// Find black line on the left side
			for(i=1;i<=64;i++)							// calculate difference between the pixels
			{
				ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
			}
			ImageDataDifference[0] = ImageData[0];	// first value doesnt have "gradient" for this method

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			BlackLineLeft = 1;
			for(i=0;i<=64;i++)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineLeft = i;
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
	   							BlackLineLeft = i;
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
	   								BlackLineLeft = i;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;
	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
	   		}	/* END for (i=64;i>=1;i--) */


			// Find middle of the road, 64 for strait road
			RoadMiddle = (BlackLineLeft + BlackLineRight)/2;
	
			// if a line is only on the the left side
			if (BlackLineRight > 124)
			{
				RoadMiddle = BlackLineLeft + 50;
			}
			// if a line is only on the the right side
			if (BlackLineLeft < 3)
			{
				RoadMiddle = BlackLineRight - 50;
			}
			// if no line on left and right side
			if ((BlackLineRight > 124) && (BlackLineLeft < 3))
			{
				RoadMiddle = 64;
			}
	
			// Store old value
			diff_old = diff;							// store old difference
		
			// Find difference from real middle
			diff = RoadMiddle - 64;						// calculate actual difference
	
			// plausibility check
			if (abs (diff - diff_old) > 50)
			{
				diff = diff_old;
			}

		}	/* end IF mfunctionning_mod == 2 */


/**********************************************************************************


		Mode number 3 : Centered differences. (filter : [-1/2 ; 0 ; 1/2])
		one of two heavy algorithms to measure local maximums while reducing noise. 


**********************************************************************************/

		else if (functionning_mod == 3)			// Gradient by centered differences ( [-1/2 ; 0 ; 1/2] )
		{
			// Find black line on the right side
			for(i=126;i>=64;i--)							// calculate difference between the pixels
			{
				ImageDataDifference[i] = abs (-(ImageData[i-1])/2 + (ImageData[i+1])/2);
			}
			ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			BlackLineRight = 126;
			for(i=126;i>=64;i--)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineRight = i;
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
	   							BlackLineRight = i;
	   							//CompareData_high = ImageDataDifference[i+j];
	   							//CompareData_low = ImageDataDifference[i];	   		
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
	   								BlackLineRight = i;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;

	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
			}	/* END for (i=126;i>=64;i--) */


	   		// Find black line on the left side
			for(i=1;i<=64;i++)							// calculate difference between the pixels
			{
				ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
			}
			ImageDataDifference[0] = ImageData[0];	// first value doesnt have "gradient" for this method

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			BlackLineLeft = 1;
			for(i=0;i<=64;i++)
			{
	   			if (ImageDataDifference[i] > CompareData_high)
	   			{
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineLeft = i;
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
	   							BlackLineLeft = i;
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
	   								BlackLineLeft = i;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;
	   						}

	   					}
	   				
	   				}
	   			}		/* END else if ... */
	   		}	/* END for (i=64;i>=1;i--) */


			// Find middle of the road, 64 for strait road
			RoadMiddle = (BlackLineLeft + BlackLineRight)/2;
	
			// if a line is only on the the left side
			if (BlackLineRight > 124)
			{
				RoadMiddle = BlackLineLeft + 50;
			}
			// if a line is only on the the right side
			if (BlackLineLeft < 3)
			{
				RoadMiddle = BlackLineRight - 50;
			}
			// if no line on left and right side
			if ((BlackLineRight > 124) && (BlackLineLeft < 3))
			{
				RoadMiddle = 64;
			}
	
			// Store old value
			diff_old = diff;							// store old difference
		
			// Find difference from real middle
			diff = RoadMiddle - 64;						// calculate actual difference
	
			// plausibility check
			if (abs (diff - diff_old) > 50)
			{
				diff = diff_old;
			}

		}	/* end IF mfunctionning_mod == 3 */












	}


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
