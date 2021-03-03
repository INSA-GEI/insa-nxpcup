#include "ImageProcessing.h"
#include "Debug.h"

int i,j;
int c_t=0;//counter for the threshold
int CompareData_high=140;
int CompareData_low=100;
int dejafait = 0;
// Valeurs de calibration
int calibree = 0;
int bande_blanche_totale = 0;
int bande_noire_gauche[2] = {30,40};
int milieu[2] = {40,80};
int bande_noire_droite[2] = {80,90};
int threshold_noir_gauche = 0;
int threshold_blanc = 0;
int threshold_noir_droit = 0;
int threshold = 50;
bool ok;

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



/**
  * @brief	Differencie le blanc du noir
  * @param  None
  * @retval None
  */
void Img_Proc::differentiate(void){
	threshold_noir_gauche = ImageData[bande_noire_gauche[0]];
	for (i=bande_noire_gauche[0];i<bande_noire_gauche[1];i++) {
		threshold_noir_gauche = (threshold_noir_gauche + ImageData[i+1])/2;
	}
	
//	threshold_blanc = ImageData[milieu[0]];
//	for (i=milieu[0];i<milieu[1];i++) {
//		threshold_blanc = (threshold_blanc + ImageData[i+1])/2;
//	}
	
	threshold_noir_droit = ImageData[bande_noire_droite[0]];
	for (i=bande_noire_droite[0];i<bande_noire_droite[1];i++) {
		threshold_noir_droit = (threshold_noir_droit + ImageData[i+1])/2;
	}
	
	threshold = (threshold_noir_gauche+threshold_noir_droit + threshold_blanc)/3;
	
//	threshold = ImageData[bande_noire_gauche[0]];
//	for (i=bande_noire_gauche[0]; i<bande_noire_droite[1]; i++) {
//		threshold = (threshold + ImageData[i+1])/2;
//	}
	
	
}	/*	End of function "differentiate"	*/




/**
  * @brief	Selection des diffents process, comme un case
  * 		int_team_1 = [0-9]
  * 		int_team_2 = [A-F]
  * 			Functioning mode A - Romain, voiture fonctionnelle mais merite des improvements sur le PI
  * @param  None
  * @retval None
  */
void Img_Proc::process (void){		
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
	   			}
			}

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
	   			}
	   		}
		}
		
		
		//################### mode A ##########################
		if (functioning_mode == 0xA){
				
			// On veut pouvoir r�gler la fr�quence � laquelle la fonction est appel�e
			// De base, c'est l'IT FTM1 qui est � 100Hz, mais avec if (dejafait < x) on peut diviser x fois la frequence
			/*if (dejafait == 0) {
				dejafait = 1;
				
				// On met des valeurs max et min pour �tre s�r qu'elles seront effac�es
				int maximum = 0;
				int minimum = 100;
				// Lancement de la capture cam�ra
				capture();
				
				// Calcul de la moyenne
				for(i=1;i<=126;i++){							// using a gradient by direct differences (application of the filter : [-2, -1 ,0 ,1 , 2] -> P(x) = -2*P(x-2)-1*P(x-1)+0*P(x)+1*P(x+1)+2*P(x-2)
					ImageData[i] = (ImageData[i-1] + ImageData[i] + ImageData[i+1])/3;
				}
				
				// Calibration une seule fois des valeurs de la camera
				if (calibree == 0) {
					calibree = 1;
					threshold_noir_gauche = ImageData[bande_noire_gauche[0]];
					threshold_blanc = ImageData[milieu[0]];
					threshold_noir_droit = ImageData[bande_noire_droite[0]];
					
					for (i=bande_noire_gauche[0];i<bande_noire_gauche[1];i++) {
						threshold_noir_gauche = (threshold_noir_gauche + ImageData[i+1])/2;
					}
					for (i=milieu[0];i<milieu[1];i++) {
						threshold_blanc = (threshold_blanc + ImageData[i+1])/2;
					}
					for (i=bande_noire_droite[0];i<bande_noire_droite[1];i++) {
						threshold_noir_droit = (threshold_noir_droit + ImageData[i+1])/2;
					}
				}
				
				// Affichage
					// On est oblig� de faire 1 pixel sur 2 car sinon on rentre dans un HardFault
				for (i=0;i<128;i+=2) {
					uart_writeNb(ImageData[i]);
					uart_write(";",1);
					if (maximum < ImageData[i]) maximum = ImageData[i];
					if (minimum > ImageData[i]) minimum = ImageData[i];
				}
				uart_write("\r\n",2);*/
				
				// Affichage gr�ce au treshold calcul� : si la voiture est au milieu, on devrait avoir quelque chose comme :
				// **__*********__**
				/*for (i = 0;i<128;i+=2) {
					if ((ImageData[i] < threshold_noir_droit) || (ImageData[i] < threshold_noir_gauche)) uart_write("_",1);	// Noir
					else {
						uart_write("*",1);	// Blanc
						bande_blanche_totale++;
					}
				}
				if (bande_blanche_totale < 10) calibree = 0;
				bande_blanche_totale = 0;
				uart_write("\r\n",2);*/
				
				// Affichage des diff�rentes valeurs calcul�es pour pouvoir comparer
				/*uart_write("\r\n",2);
				uart_write("Threshold : ", 12);
				uart_writeNb(threshold);
				uart_write(" // ",4);
				uart_write("MAX : ",6);
				uart_writeNb(maximum);
				uart_write(" // ",4);
				uart_write("MIN : ",6);
				uart_writeNb(minimum);
				uart_write("\r\n",2);*/
			/*}
			else if (dejafait < 25) dejafait++;
			else dejafait = 0;*/
			
			for(int i=0;i<=127;i++){
				if (ImageData[i]>threshold){
					ImageDataDifference[i]=1; //white
				}
				else{
					ImageDataDifference[i]=0;//black
				}
			}
			
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


void Img_Proc::processAll(void) {
	c_t++;
	capture();
	differentiate();
	process();
	calculateMiddle();
}

