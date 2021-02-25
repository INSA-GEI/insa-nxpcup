#include "ImageProcessing.h"
#include "Debug.h"
//#include <stdlib.h>
//#include <stdio.h>

int i,j;
int c_t=0;//counter for the threshold

Img_Proc::Img_Proc(){
	diff=0;
	diff_old=0;
	RoadMiddle=0;
	RoadMiddle_old=0;
	BlackLineRight=127;
	BlackLineLeft=0;
	number_edges=0;
	number_edges_old=0;
	threshold=THRESHOLD_classic;
	delta=1024; //maximum value
	detect_sun=false;
}

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

}

void Img_Proc::capture(void){
		ADC0_CFG2 |= 0x10;							// select B side of the MUX
		CAM_SI_HIGH;
		CAM_DELAY;
		CAM_CLK_HIGH;
		CAM_DELAY;
		CAM_SI_LOW;
		// inputs data from camera (first pixel)
		ADC0_SC1A  =  11;							// set ADC0 channel 11
		while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
		ImageData[0] = ADC0_RA;						// return value
		CAM_CLK_LOW;

		for(i=1;i<128;i++){
			CAM_CLK_HIGH;
			 // inputs data from camera (one pixel each time through loop)
			ADC0_SC1A  =  11;							// set ADC0 channel 11
			while((ADC0_SC1A & ADC_SC1_COCO_MASK) == 0);// wait until ADC is ready
			CAM_CLK_LOW;
			ImageData[i] = ADC0_RA;						// return value e
		}
	
}

void Img_Proc::differentiate(void){
	threshold=0;
	if (functionning_mode == 1){
		int x_d=0;
		int moy=0;
		int i=1;
		//Effets de bords bizarres
		for(i=1;i<127;i++){
			moy+=ImageData[i];
			x_d+=ImageData[i]*ImageData[i];
		}
		moy/=(i-1);
		x_d/=(i-1);
		delta=sqrt(x_d-(moy*moy));
		threshold=moy;
		if (delta<DELTA_OUT)threshold=-1;
	}else if (functionning_mode == 2){
		//Algo pour éviter le soleil
		int moy=0;
		int x_d=0;
		int count=0;
		ImageDataDifference[0]=0;
		ImageDataDifference[127]=0;
		ImageDataDifference[126]=0;
		for(i=1;i<126;i++){
			ImageDataDifference[i]=abs(ImageData[i+1]-ImageData[i-1]); //filtre de Sobel
			//moyenne
			moy+=ImageDataDifference[i];
			x_d+=ImageDataDifference[i]*ImageDataDifference[i];
			count++;
		}
		moy/=count;
		x_d/=count;
		delta=sqrt(x_d-(moy*moy));
		threshold=moy+4*delta;
	}
	
	if (c_t>CST_RECAL_T){
		c_t=0;
		//############### à enlever
		/*uart_write("IMG=",4);
		uart_writeNb(ImageData[0]);
		uart_write(";",1);
		uart_writeNb(ImageData[32]);
		uart_write(";",1);
		uart_writeNb(ImageData[64]);
		uart_write(";",1);
		uart_writeNb(ImageData[96]);
		uart_write(";",1);
		uart_writeNb(ImageData[127]);
		uart_write("\n\r",2);
		*/
	}
}	/*	End of function "Fill_ImageDataDifference"	*/

void Img_Proc::process (void){
		number_edges_old=number_edges;
		number_edges = 0;		// reset the number of peaks to 0
		if (functionning_mode == 1){
			BlackLineRight = 128;
			BlackLineLeft = -1;
			int i=1;
			while (BlackLineLeft==-1 && i<127){
				if (ImageData[i]>=threshold && ImageData[i-1]<threshold){
					BlackLineLeft=i;
					number_edges++;
				}else{
					i++;
				}
			}
			i=126;
			while (BlackLineRight==128 && (i>0 && i>BlackLineLeft)){	
				if (ImageData[i]>=threshold && ImageData[i+1]<threshold){						
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
				if (ImageData[i]<threshold){
					ok=true;
					//On regarde les TAILLE_BANDE prochains pixels 
					for (int j=i;j<=(i+TAILLE_BANDE);j++){
						if (ImageData[j]>=threshold){
							ok=false;
						}
					}
					if (ok){
						//Regarder s'il y a bien du blanc jusqu'à un max
						number_edges++;
					}
					i+=4;
				}else{
					i++;
				}
			}
		}else if (functionning_mode == 2){
			//####### MODE 2 ######## SUN #############
			BlackLineRight = 128;
			BlackLineLeft = -1;
			int i=1;
			while (BlackLineLeft==-1 && BlackLineRight==128 && i<127){
				if (ImageDataDifference[i]>threshold){
					if (ImageData[i-1]<ImageData[i+1]){
						BlackLineLeft=i;
					}else{
						BlackLineRight=i;
					}
					i+=TAILLE_BANDE;
					number_edges++;
				}else{
					i++;
				}
			}
			
			i=126;
			while (BlackLineRight==128 && (i>0 && i>BlackLineLeft)){
				if (ImageDataDifference[i]>threshold){
					if (ImageData[i-1]<ImageData[i+1]){
						BlackLineLeft=i;
					}else{
						BlackLineRight=i;
					}
					i-=TAILLE_BANDE;
					number_edges++;
				}else{
					i--;
				}
			}
		
			
			//Nb transistions
			i=BlackLineLeft+1+TAILLE_BANDE;
			bool ok=false;
			while (i<BlackLineRight-1-TAILLE_BANDE){
				if (ImageDataDifference[i]>threshold){
					//On regarde s'il y a un autre gradient
					int aux=i;
					while (i<=(aux+TAILLE_BANDE_MAX) && i<BlackLineRight-1-TAILLE_BANDE && !(ok)){
						if (ImageDataDifference[i]>threshold){
							ok=true;
						}
					}
					if (ok){
						//Regarder s'il y a bien du blanc jusqu'à un max
						number_edges++;
					}
				}
				i++;
			}
		}			
	}	/*	END of the function "Image_Processing"	*/

void Img_Proc::calculateMiddle (void){

	// Store old RoadMiddle value
	RoadMiddle_old = RoadMiddle;

	// Find middle of the road, 64 for strait road
	RoadMiddle = (BlackLineLeft + BlackLineRight)/2;

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

void Img_Proc::processAll(void) {
	c_t++;
	capture();
	differentiate();
	process();
	calculateMiddle();
	
}
