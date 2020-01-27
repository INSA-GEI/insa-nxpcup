/*
 * ImageProcessing.c
 *
 *  Created on: Jan 22, 2020
 *      Author: User
 */
#include "ImageProcessing.h"


int i, j;									// counters for loops
int ImageData [128];						// array to store the LineScan image
int ImageDataDifference [128];				// array to store the PineScan pixel difference


int CompareData_classic;					// set data for comparison to find max IN BASE ALGORITHM
int CompareData_low;						// set data for comparison to find max with low threshold
int CompareData_high;						// set data for comparison to find max with high threshold
int validate_gradient;						// used in image processing to validate some parameters
	
float gaussian1;								// gaussian filters used in gaussian differences method
float gaussian2;

int img_getDiffData(int index){
	return ImageDataDifference[index];
}


void img_differentiate(void){
		
		camera_capture();
		for(i=0;i<=127;i++)ImageData[i]=camera_getRawData(i);
		ImageDataDifference[0]=0;
		ImageDataDifference[127]=0;
		if (functionning_mode == 1){
			for(i=0;i<=126;i++){							// classic algorithm (same as the NXP_minimal) 
				ImageDataDifference[i] = abs (ImageData[i] - ImageData[i+1]);
			}
			ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method
		}else if (functionning_mode == 2){
			for(i=1;i<=126;i++){							// using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
				ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
			}
			ImageDataDifference[0] = ImageData[0];	// first value doesnt have "gradient" for this method
			ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method
		}else if (functionning_mode == 3){
			for(i=1;i<=126;i++){							// using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
				ImageDataDifference[i] = abs (-(ImageData[i-1])/2 + (ImageData[i+1])/2);
			}
			ImageDataDifference[0] =0;	// first value doesnt have "gradient" for this method
			ImageDataDifference[127] = 0;	// last value doesnt have "gradient" for this method
		}else if (functionning_mode == 4){
			for(i=0;i<=127;i++){							// using the Gaussian difference method
				gaussian1 = (1/(SIGMA_1 * sqrt(2*PI))) * exp(-(pow(i,2))/(2*pow(SIGMA_1,2)));
				gaussian2 = (1/(SIGMA_2 * sqrt(2*PI))) * exp(-(pow(i,2))/(2*pow(SIGMA_2,2)));

				ImageDataDifference[i] = abs ( (int) (round ( (ImageData[i] * gaussian1 - ImageData[i] * gaussian2) ) ) );
			}
		}
	}	/*	End of function "Fill_ImageDataDifference"	*/


	void img_process (int * diff, int * diff_old, int * BlackLineLeft, int * BlackLineRight, int * RoadMiddle, int* number_edges){
		*number_edges = 0;		// reset the number of peaks to 0
		
		if (functionning_mode == 1){
			// Find black line on the right side
			CompareData_classic = THRESHOLD_classic;					// threshold
			*BlackLineRight = 126;
			for(i=64;i<=125;i++){
	   			if (ImageDataDifference[i] > CompareData_classic){
	   				CompareData_classic = ImageDataDifference[i];
	   				*BlackLineRight = i;
	   				*number_edges++;
	   			}
			}
			// Find black line on the left side
			CompareData_classic = THRESHOLD_classic;					// threshold
			*BlackLineLeft = 1;
			for(i=64;i>=3;i--){							// only down to pixel 3, not 1
			   	if (ImageDataDifference[i] > CompareData_classic){
	 	 	 		CompareData_classic = ImageDataDifference[i];
	 		  		*BlackLineLeft = i;
	 		  		*number_edges++;
	 	  		}
			}
		}	/* END of "(IF mfunctionning_mod == 1)" */
	
/****************************************************************************************************************************************************

		Mode number 2 or 3 : same type of operation (gradient differences)
		mode 2 : using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
		mode 3 : using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
			
*****************************************************************************************************************************************************/

		else if (functionning_mode == 2 || functionning_mode == 3){
			// Find black line on the right side

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high

			*BlackLineRight = 126;
			for(i=126;i>=64;i--){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineRight = i;
	   				*number_edges ++;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i >= 67 && i < 124){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							*BlackLineRight = i;
	   							*number_edges ++;
	   							//CompareData_high = ImageDataDifference[i+j];	
	   							validate_gradient = 1;
	   						}
	   						j++;
	   					}
	   				}
	   				if (validate_gradient != 1){
	   					if (i >= 69 && i < 122){
	   						j=1;
	   						while (j <= 5){
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high)){
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
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineLeft = i;
	   				*number_edges ++;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i > 3 && i <= 61){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							*BlackLineLeft = i;
	   							*number_edges ++;
	   							//CompareData_high = ImageDataDifference[i+j];
	   							//CompareData_low = ImageDataDifference[i];	   		
	   							validate_gradient = 1;				
	   						}
	   						j++;
	   					}
	   				}
	   				if (validate_gradient != 1){
	   					if (i > 5 && i <= 59){
	   						j=1;
	   						while (j <= 5){
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high)){
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
		}	/* END of "(IF mfunctionning_mod == 2 || functionning_mode == 3)" */


/****************************************************************************************************************************************************

		Mode number 4 : about the same as mode 2 and 3, but the calculation is made on two additional indices (0 and 127)
		mode 4 : using the Gaussian difference method
			
*****************************************************************************************************************************************************/

		else if (functionning_mode == 4){
			// Find black line on the right side

			CompareData_low = THRESHOLD_low;					// threshold_low
			CompareData_high = THRESHOLD_high;					// threshold_high
			*BlackLineRight = 126;
			for(i=127;i>=64;i--){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineRight = i;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i >= 67 && i <= 124){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							*BlackLineRight = i;
	   							//CompareData_high = ImageDataDifference[i+j];	
	   							validate_gradient = 1;				
	   						}
	   						j++;
	   					}
	   				}
	   				if (validate_gradient != 1){
	   					if (i >= 69 && i <= 122){
	   						j=1;
	   						while (j <= 5){
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high)){
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
			for(i=0;i<=64;i++){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				*BlackLineLeft = i;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i >= 3 && i <= 61){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							*BlackLineLeft = i;
	   							//CompareData_high = ImageDataDifference[i+j];
	   							//CompareData_low = ImageDataDifference[i];	   		
	   							validate_gradient = 1;				
	   						}
	   						j++;
	   					}
	   				}

	   				if (validate_gradient != 1){
	   					if (i >= 5 && i <= 59){
	   						j=1;
	   						while (j <= 5){
	   							if ((ImageDataDifference[i+j] > CompareData_low && ImageDataDifference[i+j] < CompareData_high) || (ImageDataDifference[i-j] > CompareData_low && ImageDataDifference[i-j] < CompareData_high)){
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
		} /* END of "if (functionning_mode == 4)"  */			
	}	/*	END of the function "Image_Processing"	*/


