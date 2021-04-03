#include "ImageProcessing.h"
#include "Debug.h"

int i,j;
int c_t=0;//counter for the threshold
int CompareData_high=140;
int CompareData_low=100;
int dejafait = 1;
int tab_threshold[nb_echantillons_threshold];
int tab_threshold_count = 0;

void Img_Proc::init(){
	
	// turn on ADC0 clock
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM_SCGC5 = SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTB_MASK;
	
	PORTC_PCR2  |= PORT_PCR_MUX(0);	// Camera 1 PTC2 ADC0_SE11
	
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
	ecart_type = 0;
	for (i=0; i<nb_echantillons_threshold; i++) tab_threshold[i] = 200; 

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
}

void Img_Proc::differentiate(void){
}

void Img_Proc::process (void){
		number_edges = 0;		// reset the number of peaks to 0
		if (functioning_mode == 1){
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
		if (functioning_mode == 2){
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
		}	/* END of "(IF functioning_mod == 2 " */
		
		
		//################### mode A ##########################
		if ((functioning_mode == 0xA) || (functioning_mode == 0xB)){
			// Inversement de la camera
			for(i=0;i<128;i++) ImageDataBuff[i] = ImageData[i];
			for(i=127; i>=0; i--) ImageData[i] = ImageDataBuff[127-i];
			
			// Calcul du threshold entre noir & blanc : moyennage
			for(i=0;i<128;i++) threshold += ImageData[i];
			threshold /= 128;
			
			// Calcul de l'écart type
			for(i=0;i<128;i++) ecart_type += (ImageData[i]-threshold)*(ImageData[i]-threshold);
			ecart_type /= 128;
			ecart_type = sqrt(ecart_type);
			
			// Calcul moyenne threshold pour attenuer les gros changements
			tab_threshold[tab_threshold_count] = threshold;
			for(i=0; i<nb_echantillons_threshold; i++) threshold += tab_threshold[i];
			threshold /= nb_echantillons_threshold;
			if (tab_threshold_count < nb_echantillons_threshold) tab_threshold_count++;
			else tab_threshold_count = 0;
			
			
			// Détection du noir et du blanc
			for(i=0;i<=127;i++){
				if (ImageData[i]>threshold){
					ImageDataDifference[i]=1; //white
				}
				else{
					ImageDataDifference[i]=0;//black
				}
			}
			
			BlackLineRight = 128;
			BlackLineLeft = -1;
			i=1;
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
		
		if (functioning_mode == 0xE) {
			// On veut pouvoir régler la fréquence à laquelle la fonction est appelée
			// De base, c'est l'IT FTM1 qui est à 100Hz, mais avec if (dejafait < x) on peut diviser x fois la frequence
			if (dejafait == 0) {
				dejafait = 1;
				
				// On met des valeurs max et min pour être sûr qu'elles seront effacées
				int maximum = 0;
				int minimum = 1000;
				
				// Inversement de la camera
				for(i=0;i<128;i++) ImageDataBuff[i] = ImageData[i];
				for(i=127; i>=0; i--) ImageData[i] = ImageDataBuff[127-i];
				
				// Calcul du threshold entre noir & blanc : moyennage
				for(i=0;i<128;i++) threshold += ImageData[i];
				threshold /= 128;
				
				// Calcul de l'écart type
				for(i=0;i<128;i++) ecart_type += (ImageData[i]-threshold)*(ImageData[i]-threshold);
				ecart_type /= 128;
				ecart_type = sqrt(ecart_type);
				
				// Calcul moyenne threshold pour attenuer les gros changements
				tab_threshold[tab_threshold_count] = threshold;
				for(i=0; i<nb_echantillons_threshold; i++) threshold += tab_threshold[i];
				threshold /= nb_echantillons_threshold;
				if (tab_threshold_count < nb_echantillons_threshold) tab_threshold_count++;
				else tab_threshold_count = 0;
				
				
				// Détection du noir et du blanc
				for(i=0; i<128; i+=2){
					if (maximum < ImageData[i]) maximum = ImageData[i];
					if (minimum > ImageData[i]) minimum = ImageData[i];
					if ( ((ImageData[i-1]+ImageData[i]+ImageData[i+1])/3) > threshold) uart_write("*",1);
					else  uart_write("_",1);
				}
				uart_write("\n",2);

				// Affichage des différentes valeurs calculées pour pouvoir comparer
				uart_write("\r\n",2);
				uart_write("Threshold : ", 12);
				uart_writeNb(threshold);
				uart_write(" // ",4);
				uart_write("MAX : ",6);
				uart_writeNb(maximum);
				uart_write(" // ",4);
				uart_write("MIN : ",6);
				uart_writeNb(minimum);
				uart_write("\r\n",2);
			}
			else if (dejafait < 100) dejafait++;
			else dejafait = 0;
		}
		
		
		
		if (functioning_mode == 0xF) {
			// On veut pouvoir régler la fréquence à laquelle la fonction est appelée
			// De base, c'est l'IT FTM1 qui est à 100Hz, mais avec if (dejafait < x) on peut diviser x fois la frequence
			if (dejafait == 0) {
				dejafait = 1;
				
				// Inversement de la camera
				for(i=0; i<=127; i++) ImageDataBuff[i] = ImageData[i];
				for(i=127; i>=0; i--) ImageData[i] = ImageDataBuff[127-i];
				
				// Affichage des valeurs et calcul des min/max
				for (i=0;i<128;i+=2) {
					uart_writeNb(ImageData[i]);
					uart_write(";",1);
				}
				uart_write("\r\n",2);
			}
			else if (dejafait < 25) dejafait++;
			else dejafait = 0;
		}
		
	}	/*	END of the function "Image_Processing"	*/

void Img_Proc::calculateMiddle (void){

	// Store old RoadMiddle value
	RoadMiddle_old = RoadMiddle;

	// Find middle of the road, 64 for strait road
	RoadMiddle = (BlackLineLeft + BlackLineRight)/2;

	// if no line on left and right side
	if ((number_edges == 0) || (ecart_type < 20)){
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


void Img_Proc::processAll(void) {
	c_t++;
	capture();
	differentiate();
	process();
	calculateMiddle();
}

