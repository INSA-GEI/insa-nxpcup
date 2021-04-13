#include "ImageProcessing.h"
#include "Debug.h"

#define TIM_CaG_D 2*80
#define TIM_CaG_G 100
#define TIM_CaG_TD 40

#define TIM_CaD_G 2*80
#define TIM_CaD_D 100
#define TIM_CaD_TD 40

int i,j;
int c_t=0;//counter for the threshold
int CompareData_high=140;
int CompareData_low=100;
int dejafait = 0;
int calibration = 0;
int tab_threshold[nb_echantillons_threshold];
int tab_threshold_count = 0;
int data_max[100];
int total_data_max = 0;
int cubeagauche = 0;
int cubeadroite = 0;
// Detection de l'emplacement du cube
bool isthefuckingcubeadroite = false;
bool isthefuckingcubeagauche = false;
// Cube a gauche -> routine pour coller la droite
int timer_cubeagauche_alleradroite = TIM_CaG_D;
int timer_cubeagauche_alleragauche = TIM_CaG_G;
int timer_cubeagauche_allertoutdroit = TIM_CaG_TD;
// Cube a droite -> routine pour coller la gauche
int timer_cubeadroite_alleragauche = TIM_CaD_G;
int timer_cubeadroite_alleradroite = TIM_CaD_D;
int timer_cubeadroite_allertoutdroit = TIM_CaD_TD;



/**
  * @brief  Initialisation
  * @param  None
  * @retval None
  */
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
	for (i=0; i<nb_echantillons_threshold; i++) tab_threshold[i] = 150; 

}	/*	END of the function "init"	*/


/**
  * @brief  Capture one frame
  * @param  None
  * @retval None
  */
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
  * @brief  Processes differents modes
  * 		Modes 1 to 9 : Team 1
  * 		Modes A to F : Team 2
  * 		
  * 		Mode A - Slow Mode
  * 		Mode B - Regular Mode
  * 		Mode C - Fast Mode
  * 		Mode D - Obstacle Avoidance
  * 		Mode E - Affichage de la route style _____***********_____
  * 		Mode F - Affichage des valeurs de la camera pour excel
  * 					Aide : nouveau fichier -> selection colonne A -> Donnees -> Convertir -> Suivant -> cocher seulement 'point virgule' -> Suivant -> Terminer
  * 					Reset la voiture -> 'clear session' sur XCTU (croix en haut � droite) -> attente de 5 � 10s -> CTRL+A -> copier/coller sur excel sur colonne A -> insertion -> courbe 2D
  * @param  None
  * @retval None
  */
void Img_Proc::process (void){
	number_edges = 0;	// Reset the number of peaks to 0
	
	//################### Modes A B C ###################//
	if ((functioning_mode == 0xA) || (functioning_mode == 0xB) || (functioning_mode == 0xC)){
		// Inversement de la camera
		for(i=0;i<128;i++) ImageDataBuff[i] = ImageData[i];
		for(i=127; i>=0; i--) ImageData[i] = ImageDataBuff[127-i];
		
		// Calcul du threshold entre noir & blanc : moyennage
		for(i=0;i<128;i++) threshold += ImageData[i];
		threshold /= 128;
		
		// Calcul de l'�cart type
		for(i=0;i<128;i++) ecart_type += (ImageData[i]-threshold)*(ImageData[i]-threshold);
		ecart_type /= 128;
		ecart_type = sqrt(ecart_type);
		
		// Calcul moyenne threshold pour attenuer les gros changements
		tab_threshold[tab_threshold_count] = threshold;
		for(i=0; i<nb_echantillons_threshold; i++) threshold += tab_threshold[i];
		threshold /= nb_echantillons_threshold;
		if (tab_threshold_count < nb_echantillons_threshold) tab_threshold_count++;
		else tab_threshold_count = 0;
		
		
		// D�tection du noir et du blanc
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
	
	//################### Mode D ###################//
	if (functioning_mode == 0xD){
		// Inversement de la camera
		for(i=0;i<128;i++) ImageDataBuff[i] = ImageData[i];
		for(i=127; i>=0; i--) ImageData[i] = ImageDataBuff[127-i];
		
		//-----Algo normal + calibration sur 100 points-----//
		if (calibration < 100) {
			// Mise a 0 de la data_max n� calibration pour avoir le max de ce run
			data_max[calibration] = 0;
			
			// Calcul du threshold entre noir & blanc : moyennage + max de toutes les data de cette run
			for(i=0;i<128;i++) {
				if (data_max[calibration] < ImageData[i]) data_max[calibration] = ImageData[i];
				threshold += ImageData[i];
			}
			threshold /= 128;
			
			// Calcul moyenne threshold pour attenuer les gros changements
			tab_threshold[tab_threshold_count] = threshold;
			for(i=0; i<nb_echantillons_threshold; i++) threshold += tab_threshold[i];
			threshold /= nb_echantillons_threshold;
			if (tab_threshold_count < nb_echantillons_threshold) tab_threshold_count++;
			else tab_threshold_count = 0;
			
			calibration++;
		}
		//-----Une fois que calibration faite, on fait la moyenne des valeurs max-----//
		else if (calibration == 100) { // Si on a calibr� 100 fois, on fait la moyenne des data max
			for (i=0; i<100; i++) total_data_max += data_max[i];
			total_data_max /= 100;
			uart_write("CALIBRATION OK : ", 17);
			uart_writeNb(total_data_max);
			uart_write("\n", 2);
			calibration++;
		}
		//-----Une fois la moyenne des valeurs max faite, on reprend l'algo normal-----//
		else {
			// Reset valeurs cubeadroite et cubeagauche
			cubeadroite = 0;
			cubeagauche = 0;
			// Calcul valeur cubeadroite et cubeagauche
			for(i=0;i<64;i++) if (ImageData[i] > total_data_max+45) cubeagauche++;
			for(i=64;i<128;i++) if (ImageData[i] > total_data_max+45) cubeadroite++;
			
			// Calcul du threshold entre noir & blanc : moyennage SEULEMENT SI PAS de CUBEADROITE ou de CUBEAGAUCHE
			if ((cubeagauche == 0) && (cubeadroite == 0)) {
				for(i=0;i<128;i++) threshold += ImageData[i];
				threshold /= 128;

				// Calcul de l'�cart type
				for(i=0;i<128;i++) ecart_type += (ImageData[i]-threshold)*(ImageData[i]-threshold);
				ecart_type /= 128;
				ecart_type = sqrt(ecart_type);
				
				// Calcul moyenne threshold pour attenuer les gros changements
				tab_threshold[tab_threshold_count] = threshold;
				for(i=0; i<nb_echantillons_threshold; i++) threshold += tab_threshold[i];
				threshold /= nb_echantillons_threshold;
				if (tab_threshold_count < nb_echantillons_threshold) tab_threshold_count++;
				else tab_threshold_count = 0;
			}
		}
		
		

		//-----On continue l'algo classique-----//
		
		// D�tection du noir et du blanc
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
	}
	

	//################### Mode E ###################//
	if (functioning_mode == 0xE) {
		// On veut pouvoir r�gler la fr�quence � laquelle la fonction est appel�e
		// De base, c'est l'IT FTM1 qui est � 100Hz, mais avec if (dejafait < x) on peut diviser x fois la frequence
		if (dejafait == 0) {
			dejafait = 1;
			
			// On met des valeurs max et min pour �tre s�r qu'elles seront effac�es
			int maximum = 0;
			int minimum = 1000;
			
			// Inversement de la camera
			for(i=0;i<128;i++) ImageDataBuff[i] = ImageData[i];
			for(i=127; i>=0; i--) ImageData[i] = ImageDataBuff[127-i];
			
			// Calcul du threshold entre noir & blanc : moyennage
			for(i=0;i<128;i++) threshold += ImageData[i];
			threshold /= 128;
			
			// Calcul de l'�cart type
			for(i=0;i<128;i++) ecart_type += (ImageData[i]-threshold)*(ImageData[i]-threshold);
			ecart_type /= 128;
			ecart_type = sqrt(ecart_type);
			
			// Calcul moyenne threshold pour attenuer les gros changements
			tab_threshold[tab_threshold_count] = threshold;
			for(i=0; i<nb_echantillons_threshold; i++) threshold += tab_threshold[i];
			threshold /= nb_echantillons_threshold;
			if (tab_threshold_count < nb_echantillons_threshold) tab_threshold_count++;
			else tab_threshold_count = 0;
			
			
			// D�tection du noir et du blanc et affichage des characteres style _____***********_____
			for(i=0; i<128; i+=2){
				if (maximum < ImageData[i]) maximum = ImageData[i];
				if (minimum > ImageData[i]) minimum = ImageData[i];
				if ( ((ImageData[i-1]+ImageData[i]+ImageData[i+1])/3) > threshold) uart_write("*",1);
				else  uart_write("_",1);
			}
			uart_write("\n",2);

			// Affichage des diff�rentes valeurs calcul�es pour pouvoir comparer
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
	

	//################### Mode F ###################//
	if (functioning_mode == 0xF) {
		// On veut pouvoir r�gler la fr�quence � laquelle la fonction est appel�e
		// De base, c'est l'IT FTM1 qui est � 100Hz, mais avec if (dejafait < x) on peut diviser x fois la frequence
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
		
}	/*	END of the function "process"	*/




/**
  * @brief  Calculate the difference between the middle of the road and the position of the car 
  * @param  None
  * @retval None
  */
void Img_Proc::calculateMiddle (void){

	// Store old RoadMiddle value
	RoadMiddle_old = RoadMiddle;	

	// Find middle of the road, 64 for strait road
	RoadMiddle = (BlackLineLeft + BlackLineRight)/2;
	
	// Si detection d'osbtacle, pas besoin d'aller tout droit
	if (functioning_mode != 0xD) {
		// No line on left and right side
		if ((number_edges == 0) || (ecart_type < 20)){
			RoadMiddle = RoadMiddle_old;
		}
		if ((BlackLineRight > 127) && (BlackLineLeft < 0)){
			RoadMiddle = RoadMiddle_old;		// we continue on the same trajectory as before 
		}
	}

	// Store old value
	diff_old = diff;							// store old difference
	
	// Find difference from real middle
	diff = RoadMiddle - 64;			// calculate actual difference
	if (abs(diff-diff_old)>Plausibily_check){
		diff=diff_old;
	}
	
	if (functioning_mode == 0xD) {
		// Cube a gauche
			// On detecte le cube a gauche 1 fois
		if ((cubeadroite == 0) && (cubeagauche != 0) && (!isthefuckingcubeagauche)) isthefuckingcubeagauche = true;
			// Si le cube est a gauche
		if (isthefuckingcubeagauche) {
			if ((timer_cubeagauche_alleradroite-- > 0)) diff = 20;		// A droite toute !
			else if (timer_cubeagauche_alleragauche-- > 0) diff = -20;	// On se remet droit
			else if (timer_cubeagauche_allertoutdroit-- > 0) diff = 0;	// Tout droit Moussaillon :o
			else { 														// On reset toutes les variables
				isthefuckingcubeagauche = false;
				timer_cubeagauche_alleradroite = TIM_CaG_D;
				timer_cubeagauche_alleragauche = TIM_CaG_G;
				timer_cubeagauche_allertoutdroit = TIM_CaG_TD;
			}
		}
	
		// Cube a droite
			// On detecte le cube a droite 1 fois
		if ((cubeagauche == 0) && (cubeadroite != 0) && (!isthefuckingcubeadroite)) isthefuckingcubeadroite = true;
			// Si le cube est a droite
		if (isthefuckingcubeadroite) {
			if (timer_cubeadroite_alleragauche-- > 0) diff = -20;		// A gauche toute !
			else if (timer_cubeadroite_alleradroite-- > 0) diff = 20;	// On se remet droit
			else if (timer_cubeadroite_allertoutdroit-- > 0) diff = 0;	// Tout droit Moussaillon :o
			else { 														// On reset toutes les variables
				isthefuckingcubeadroite = false;
				timer_cubeadroite_alleragauche = TIM_CaD_G;
				timer_cubeadroite_alleradroite = TIM_CaD_D;
				timer_cubeadroite_allertoutdroit = TIM_CaD_TD;
			}
		}
	}
	
}	/*	END of the function "calculateMiddle"	*/



/**
  * @brief  Call all functions 
  * @param  None
  * @retval None
  */
void Img_Proc::processAll(void) {
	c_t++;
	capture();
	process();
	calculateMiddle();
}	/*	END of the function "processAll"	*/

