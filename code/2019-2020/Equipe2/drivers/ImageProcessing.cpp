#include "ImageProcessing.h"
#include "Debug.h"
//#include <stdlib.h>
//#include <stdio.h>

int i,j;
int c_t=0;//counter for the threshold
int CompareData_high=140;
int CompareData_low=100;


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
	threshold=150;

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
			/*for(i=1;i<=126;i++){	
				Imageflou[i] = (uint16_t) abs (0.5*ImageData[i-1] + ImageData[i] + 0.5*ImageData[i+1])/2;
			}
			
			Imageflou[0] = ImageData[0];
			Imageflou[127] = ImageData[127];*/
			
			/*if (c_t<CST_RECAL_T){
				DEBUG_GREEN_ON;
				c_t=0;
				threshold=0;
				for(int i=0;i<=127;i++){
					threshold+=ImageData[i];
				}
				threshold=threshold/128;
				if (threshold<THRESHOLD_classic)threshold=THRESHOLD_classic;
			}else if (c_t>CST_RECAL_T/2){
				DEBUG_GREEN_OFF;
			}*/
			
			//Test blanc ou noir
			for(int i=0;i<=127;i++){
				if (ImageData[i]>threshold){
					ImageDataDifference[i]=1; //white
				}else{
					ImageDataDifference[i]=0;//black
				}
			}
		}
		if (functionning_mode == 2){
			for(i=2;i<=125;i++){							// using a gradient by direct differences (application of the filter : [-2, -1 ,0 ,1 , 2] -> P(x) = -2*P(x-2)-1*P(x-1)+0*P(x)+1*P(x+1)+2*P(x-2)
				ImageDataDifference[i] = abs (-2*ImageData[i-2] - ImageData[i-1] + ImageData[i+1] + 2*ImageData[i+2]);
			}
			ImageDataDifference[0] = ImageData[0];	// first value does not have "gradient" for this method
			ImageDataDifference[1] = ImageData[1];
			ImageDataDifference[126] = ImageData[126];
			ImageDataDifference[127] = ImageData[127];	// last value does not have "gradient" for this method
		}
	}	/*	End of function "Fill_ImageDataDifference"	*/

void Img_Proc::process (void){
		number_edges = 0;		// reset the number of peaks to 0
		if (functionning_mode == 1){
			BlackLineRight = 128;
			BlackLineLeft = -1;
			int i=1;
			while (BlackLineLeft==-1 && i<127){
				if (ImageDataDifference[i]==1 && ImageDataDifference[i-1]==0){
					BlackLineLeft=i;
					number_edges++;
				}else{
					i++;
				}
			}
			i=126;
			while (BlackLineRight==128 && (i>0 && i>BlackLineLeft)){
				if (ImageDataDifference[i]==1 && ImageDataDifference[i+1]==0){
					BlackLineRight=i;
					number_edges++;
				}else{
					i--;
				}
			}
			//Nb transistions
			i=BlackLineLeft+1+TAILLE_BANDE;
			bool ok=false;
			while (i<BlackLineRight-1-TAILLE_BANDE){
				if (ImageDataDifference[i-1]!=ImageDataDifference[i]){
					ok=true;
					//On regarde les TAILLE_BANDE prochains pixels 
					for (int j=i;j<=(i+TAILLE_BANDE);j++){
						if (ImageDataDifference[j]==1){
							ok=false;
						}
					}
					if (ok){
						number_edges++;
					}
					i+=4;
				}else{
					i++;
				}
			}
		}
		
	//################### mode 2 ##########################
		if (functionning_mode == 2){
			// Find black line on the right side

			BlackLineRight = 128;
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

			// image processing with the algorithm seen at the beginning. 
			BlackLineLeft = -1;
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

	
	// if no line on left and right side
	if (number_edges == 0){
		RoadMiddle = RoadMiddle_old;
	}
	if ((BlackLineRight > 127) && (BlackLineLeft < 0)){
		RoadMiddle = RoadMiddle_old;		// we continue on the same trajectory as before 
	}

	// Store old value
	diff_old = diff;							// store old difference
	
	// Find difference from real middle
	diff = RoadMiddle - 64;						// calculate actual difference
	
	if (abs(diff-diff_old)>Plausibily_check){
		diff=diff_old;
	}
}


void Img_Proc::display_camera_data(void) {
	//uart_write("Raw data : ",11);
	if (CSV){
		for (int i=0;i<128;i++) {
			uart_writeNb(ImageData[i]);
			uart_write(";",1);
			uart_writeNb(ImageDataDifference[i]);
			uart_write("\r\n",2);
		}
		for (int i=0;i<40;i++) {
			uart_writeNb(0);
			uart_write(";",1);
			uart_writeNb(0);
			uart_write("\r\n",2);
		}
	}else{
		for (int i=0;i<128;i++) {
			uart_write("$",1);
			//uart_writeNb(ImageData[i]);
			//uart_write(" ",1);
			uart_writeNb(ImageDataDifference[i]);
			uart_write(";",1);
		}
		for (int i=0;i<40;i++) {
				uart_write("$",1);
				uart_writeNb(0);
				uart_write(" ",1);
				uart_writeNb(0);
				uart_write(";",1);
		}
		uart_write("\r\n",2);
	}
}

void Img_Proc::display_gradient(void) {
	//uart_write("Gradient : ",11);
	for (int i=0;i<128;i++) {
		uart_write("$",1);
		uart_writeNb(ImageDataDifference[i]);
		uart_write(";",1);
	}
	uart_write("\r\n",2);
}

/*void Img_Proc::export_raw_data(void) {
    FILE* fichier = NULL;
	
	fichier = fopen("camera_raw_data.txt", "w+");
	// si on veut que le fichier ne soit pas écrasé à chaque fois : 
	// fichier = fopen("camera_raw_data.txt", "a+");
	if (fichier != NULL)
	{
		//Ecriture des data brutes dans le fichier
		fputs("START\n", fichier);
		for (int i=0;i<128;i++) {
	 		fprintf(fichier, "%d ", ImageData[i]);
		}
		fputs(" ;\nSTOP\n", fichier);
		fclose(fichier);
	}
	else
	{
		uart_write("Erreur enregistrement des données brutes de la caméra",42);
	}
	    
}*/

void Img_Proc::gradient(void){

		if (functionning_mode == 1){
			for(i=1;i<=126;i++){	// différence simple
				ImageDataDifference[i] = abs (-ImageData[i] + ImageData[i+1]);
			}
			ImageDataDifference[0] = abs (- ImageData[0] + ImageData[1]);	// first value doesnt have "gradient" for this method
			ImageDataDifference[127] = abs (- ImageData[126] + ImageData[127]);	// last value doesnt have "gradient" for this method
		}else if (functionning_mode == 2){
			for(i=1;i<=126;i++){	// using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
				ImageDataDifference[i] = abs (-ImageData[i-1] + ImageData[i+1]);
			}
			ImageDataDifference[0] = abs (- ImageData[0] + ImageData[1]);	// first value doesnt have "gradient" for this method
			ImageDataDifference[127] = abs (- ImageData[126] + ImageData[127]);	// last value doesnt have "gradient" for this method
		}
	}	/*	End of function "Fill_ImageDataDifference"	*/


void Img_Proc::processAll(void) {
	c_t++;
	capture();
	differentiate();
	process();
	//uart_write("ok\n\r",4);
	calculateMiddle();
	
}
