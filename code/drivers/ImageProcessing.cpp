#include "ImageProcessing.h"

int i,j;

void Img_Proc::init(){
	
	// turn on ADC0 clock
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM_SCGC5 = SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTB_MASK;
	
	PORTC_PCR2  |= PORT_PCR_MUX(0);		// Camera 1 PTC2 ADC0_SE11
	
	PORTB_PCR8  |= PORT_PCR_MUX(1);	// PTB8 Camera SI
	PORTB_PCR9  |= PORT_PCR_MUX(1);	// PTB9 Camera Clock
	GPIOB_PDDR |= (1<<8);			// PTB8 Camera SI
	GPIOB_PDDR |= (1<<9);			// PTB9 Camera Clock
	
	
	// ADC0 clock configuration : 													WARNING : maybe not compatible with 48MHz system clock ! to check
	ADC0_CFG1 |= 0x01;				// clock is bus clock divided by 2 = 24 MHz
	
	// ADC0 resolution    
	ADC0_CFG1 |= 0x08;				// resolution 10 bit, max. value is 1023

	// ADC0 conversion mode
	ADC0_SC3 = 0x00;				// single conversion mode
	
	
	diff=0;
	diff_old=0;
	RoadMiddle=0;
	RoadMiddle_old=0;
	BlackLineRight=127;
	BlackLineLeft=0;
	number_edges=0;
	edges_cnt=0;
	finish=false;
	CompareData_high = THRESHOLD_high;
	CompareData_low = THRESHOLD_low;
	black_edge_left_pos_rect1=0;
	black_edge_right_pos_rect1=0;
	black_edge_left_pos_rect2=0;
	black_edge_right_pos_rect2=0;

}

void Img_Proc::capture(void){
		ADC0_CFG2 |= 0x10;							// select B side of the MUX
		CAM_SI_HIGH;
		CAM_DELAY;
		CAM_CLK_HIGH;
		CAM_DELAY;
		CAM_SI_LOW;
		CAM_DELAY;
		// inputs data from camera (first pixel)
		ADC0_SC1A  =  11;							// set ADC0 channel 11
		while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
		ImageData[0] = ADC0_RA;						// return value
		CAM_CLK_LOW;

		for(i=1;i<128;i++){
			CAM_DELAY;
			CAM_CLK_HIGH;
			 // inputs data from camera (one pixel each time through loop)
			ADC0_SC1A  =  11;							// set ADC0 channel 11
			while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
			ImageData[i] = ADC0_RA;						// return value
			CAM_CLK_LOW;
		}
	
		CAM_DELAY;
		CAM_DELAY;
		CAM_CLK_HIGH;
		CAM_DELAY;
		CAM_DELAY;
		CAM_CLK_LOW;
		/*
		//generating dummy data here
		for(i=0;i<128;i++){
			int data;
			if((i>32 && i<48) || (i>80 && i<96)){
				data=150+rand()%10;
			}else{
				data=50+rand()%10;
			}
			ImageData[i]=data;
		}
		*/
}

void Img_Proc::differentiate(void){
		if (functionning_mode == 1){
			for(i=1;i<=126;i++){	
				ImageDataDifference[i] = abs (ImageData[i-1] + ImageData[i] + ImageData[i+1])/3;
			}
			
		}
		if (functionning_mode == 2){
			for(i=1;i<=126;i++){							// using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
				ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
			}
			ImageDataDifference[0] = ImageData[0];	// first value doesnt have "gradient" for this method
			ImageDataDifference[127] = ImageData[127];	// last value doesnt have "gradient" for this method
		}
	}	/*	End of function "Fill_ImageDataDifference"	*/

void Img_Proc::process (void){
		number_edges = 0;		// reset the number of peaks to 0
		
		if (functionning_mode == 2){
			// Find black line on the right side

			//CompareData_low = THRESHOLD_low;					// threshold_low
			//CompareData_high = THRESHOLD_high;					// threshold_high

			BlackLineRight = 127;
			for(i=126;i>=64;i--){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineRight = i;
	   				(number_edges) ++;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i >= 67 && i < 124){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							BlackLineRight = i;
	   							(number_edges) ++;
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
	   								BlackLineRight = i;
	   								(number_edges) ++;
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;
	   						}
	   					}
	   				}
	   			}		/* END else if ... */
			}	/* END for (i=126;i>=64;i--) */

	   		// Find black line on the left side
			//CompareData_low = THRESHOLD_low;					// threshold_low
			//CompareData_high = THRESHOLD_high;					// threshold_high

			// image processing with the algorithm seen at the beginning. 
			BlackLineLeft = 0;
			for(i=1;i<=64;i++){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineLeft = i;
	   				(number_edges) ++;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i > 3 && i <= 61){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							BlackLineLeft = i;
	   							(number_edges) ++;
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
	   								BlackLineLeft = i;
	   								(number_edges) ++;
	   								//CompareData_high = ImageDataDifference[i+j];
	   								//CompareData_low = ImageDataDifference[i];	 
	   							}
	   							j++;
	   						}
	   					}
	   				}
	   			}		/* END else if ... */
	   		}	/* END for (i=64;i>=1;i--) */
		}	/* END of "(IF mfunctionning_mod == 2 " */
			
	}	/*	END of the function "Image_Processing"	*/

void Img_Proc::calculateMiddle (void){

	// Store old RoadMiddle value
	RoadMiddle_old = RoadMiddle;

	// Find middle of the road, 64 for strait road
	RoadMiddle = (BlackLineLeft + BlackLineRight)/2;

	// if a line is only on the the right side
	/*if (BlackLineLeft < 3){
		RoadMiddle = BlackLineRight - 50;
	}
	// if a line is only on the the left side
	if (BlackLineRight > 124){
		RoadMiddle = BlackLineLeft + 50;
	}*/
	// if no line on left and right side
	if (number_edges == 0){
		RoadMiddle = RoadMiddle_old;
		//for (i = 0 ; i < 1000000 ; i++);
	}
	if ((BlackLineRight > 124) && (BlackLineLeft < 3)){
		RoadMiddle = RoadMiddle_old;		// we continue on the same trajectory as before 
	}

	// Store old value
	diff_old = diff;							// store old difference
	
	// Find difference from real middle
	diff = RoadMiddle - 64;						// calculate actual difference

}

//You may need to adjust the values of "CompareData_high" by modifying the macro "THRESHOLD_high".
bool Img_Proc::test_FinishLine_Detection (void){
	
	threshold = 60;	
	
	for (int i=BlackLineLeft+5;i<BlackLineRight-5;i++){
			if (ImageDataDifference[i] >= threshold){
				edges_cnt++;
			}
	}	
	
	//finish = false at the initialization
	if (edges_cnt>=COUNTER_THRESHOLD_FINISH){
		finish = true;
	} 
	edges_cnt=0;
				
	return finish;
	/*black_edge_left_pos_rect1=BlackLineLeft+(124)*(BlackLineRight-BlackLineLeft+1)/530;
	black_edge_right_pos_rect1=BlackLineLeft+(124+94)*(BlackLineRight-BlackLineLeft+1)/530;
	black_edge_left_pos_rect2=BlackLineLeft+(124+94+74)*(BlackLineRight-BlackLineLeft+1)/530;
	black_edge_right_pos_rect2=BlackLineLeft+(124+94+74+94)*(BlackLineRight-BlackLineLeft+1)/530;

		for (int i=0;i<=10;i++){
			if (ImageDataDifference[black_edge_left_pos_rect1+i] >= threshold || ImageDataDifference[black_edge_left_pos_rect1-i] >= threshold){
				edges_cnt++;
				i=10;
			} else {edges_cnt=0;}
		}	
		for (int i=0;i<=10;i++){
			if (ImageDataDifference[black_edge_right_pos_rect1+i] >= threshold || ImageDataDifference[black_edge_right_pos_rect1-i] >= threshold){
				edges_cnt++;
				i=20;
			} else {edges_cnt=0;}
}	
		for (int i=0;i<=10;i++){
			if (ImageDataDifference[black_edge_left_pos_rect2+i] >= threshold || ImageDataDifference[black_edge_left_pos_rect2-i] >= threshold){
				edges_cnt++;
				i=20;
			} else {edges_cnt=0;}
		}	
		for (int i=0;i<=10;i++){
			if (ImageDataDifference[black_edge_right_pos_rect2+i] >= threshold || ImageDataDifference[black_edge_right_pos_rect2-i] >= threshold){
				edges_cnt++;
				i=20;
				} else {edges_cnt=0;}
		}	
	
	//finish = false at the initialization
	if (edges_cnt>=COUNTER_THRESHOLD_FINISH){
		finish = true;
		edges_cnt=0;
	}
	
	return finish;
	*/
	
}

//To add at the end of  process() in order to test the variation of the thresholds towards the number of edges detected.
void Img_Proc::compute_data_threshold(void){
	
	if(number_edges >= 2 && not(finish)){
		CompareData_high += 12;
		threshold = CompareData_high;
		CompareData_low += 10;
		if (CompareData_high > 200) CompareData_high=200;
		if (CompareData_low > 80) CompareData_low=80;
	}
	else if(number_edges > 0 || number_edges < 2){
		CompareData_high -= 3;
		threshold = CompareData_high;
		CompareData_low -= 3;
		if (CompareData_high < 20) CompareData_high=20;
		if (CompareData_low < 5) CompareData_low=5;
	}
	else {
		CompareData_high = THRESHOLD_high;
		threshold = CompareData_high;
		CompareData_low = THRESHOLD_low;
	}
}


void Img_Proc::processAll(void) {
	capture();
	differentiate();
	process();
	calculateMiddle();
	//compute_data_threshold();
	test_FinishLine_Detection();
}
