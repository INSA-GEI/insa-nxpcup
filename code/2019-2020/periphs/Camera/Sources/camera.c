#include "camera.h"
int ImageData[128];
int ImageDataDiff[128];
int nbEdges;
int edgesLoc[4];
void camera_init(){
	
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


// Capture LineScan Image
void camera_capture(void)
	{
		unsigned char i;
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

		for(i=1;i<128;i++)
		{
			CAM_DELAY;
			CAM_DELAY;
			CAM_CLK_HIGH;
			CAM_DELAY;
			CAM_DELAY;
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

int camera_getRawData(int index){
return ImageData[index];
}

int camera_getDataDiff(int index){
return ImageDataDiff[index];
}
int camera_getEdges(int index){
return edgesLoc[index];
}
void camera_processData(void){

	for(int i=0;i<=127;i++){
		if(i<5 || i>120){
			ImageDataDiff[i] =0;
		}else{
		ImageDataDiff[i] = 10*abs (-(ImageData[i-1])/2 + (ImageData[i+1])/2);
		}
	}
	nbEdges=0;
	int over=0;
	for(int i=1;i<=126;i++){
		if(ImageDataDiff[i]>THRESHOLD ){
			over=1;
			edgesLoc[nbEdges]=i;
		}else{
			if(over==1)nbEdges++;
			if(nbEdges>3)nbEdges=3;
			over=0;
		}
	}
	edgesLoc[0]=(edgesLoc[0]+edgesLoc[1])/2;
	edgesLoc[0]=(edgesLoc[2]+edgesLoc[3])/2;
}
