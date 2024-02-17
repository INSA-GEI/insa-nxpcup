/*
 * ImageProcessing.cpp
 *
 *  Created on: 22 janv. 2024
 *      Author: Ordi Axel
 */

#include <ImageProcessing/ImageProcessing.hpp>
#include <servo/driver_servo.h>


#define PI 						3.14159265358979323846	// value of PI

//Camera 1 : Proche ADC0
#define CAMERA_1_ADC ADC0

int i,j;


void ImageProcessing::capture(void) {
	/* capture des données provenant d'une caméra en utilisant l'ADC.
	 * Il configure le canal 11 de l'ADC pour la capture des pixels de la caméra,
	 * et stocke les valeurs des pixels dans le tableau ImageData.
	 * 128 valeurs sont stockées correspondant à une ligne de la caméra.
	 */

    // Configuration spécifique pour le canal 11 de l'ADC
    const adc16_channel_config_t adc0_config_ch_11 = {
        .channelNumber = 11,
        .enableInterruptOnConversionCompleted = false,
        .enableDifferentialConversion = false,
    };

    // Sélectionner le côté B du MUX pour le canal 11
    ADC16_SetChannelMuxMode(ADC0, kADC16_ChannelMuxB);

    // Activer la ligne SI (Shift In) de la caméra
    CAM_SI_HIGH;
    CAM_DELAY; // Attente pour le délai CAM

    // Activer l'horloge de la caméra
    CAM_CLK_HIGH;
    CAM_DELAY; // Attente pour le délai CAM

    // Désactiver la ligne SI de la caméra
    CAM_SI_LOW;
    CAM_DELAY; // Attente pour le délai CAM

    // Entrée des données de la caméra pour le premier pixel
    ADC16_SetChannelConfig(ADC0, ADC0_Channel_Group, &adc0_config_ch_11);
    while (0U == (kADC16_ChannelConversionDoneFlag &
                  ADC16_GetChannelStatusFlags(ADC0, ADC0_Channel_Group))) {
        // Attente de la fin de la conversion pour prendre la valeur
    }
    ImageData[0] = ADC16_GetChannelConversionValue(ADC0, ADC0_Channel_Group);
    CAM_CLK_LOW;

    // Boucle pour entrer les données de la caméra (un pixel à la fois)
    for (int i = 1; i < 128; i++) {
        CAM_DELAY; // Attente pour le délai CAM

        CAM_CLK_HIGH; // Activer l'horloge de la caméra

        // Entrée des données de la caméra (un pixel à chaque itération de la boucle)
        ADC16_SetChannelConfig(ADC0, ADC0_Channel_Group, &adc0_config_ch_11);
        while (0U == (kADC16_ChannelConversionDoneFlag &
                      ADC16_GetChannelStatusFlags(ADC0, ADC0_Channel_Group))) {
            // Attente de la fin de la conversion pour prendre la valeur
        }
        ImageData[i] = ADC16_GetChannelConversionValue(ADC0, ADC0_Channel_Group);
        CAM_CLK_LOW; // Désactiver l'horloge de la caméra
    }
}

void ImageProcessing::affiche_image(void){
	for (int i = 0 ; i<128;i++){
		PRINTF("| %d |",ImageData[i]);

	}
	PRINTF("\n");
}

void ImageProcessing::init(){

	/* Initialisation pour ImageProcessing
	 *  - ADC0 channel 11 en mode single conversion. Entrée de l'ADC sur PORTC 2
	 *  - PORTB 8 en sortie GPIO digitale. Controle le SI( Shift - In) de la caméra.
	 *  - PORTB 9 en sortie GPIO digitale. Controle le clock de la caméra.
	 */

	// ------------------- VARIABLES LOCALES ----------------------------------

	// Configuration pour ADC0
	const adc16_config_t adc0_config =
	{
	    // Utilisation des broches Vref externes (VrefH et VrefL) comme source de tension de référence
	    .referenceVoltageSource = kADC16_ReferenceVoltageSourceVref,

	    // Utilisation de ALT1 clk bus/2 comme source d'horloge d'entrée
	    .clockSource = kADC16_ClockSourceAlt1,

	    // Activation de la sortie d'horloge asynchrone
	    .enableAsynchronousClock = false,

	    // Configuration du diviseur d'horloge à 2, divisant la source d'horloge d'entrée
	    .clockDivider = kADC16_ClockDivider1,

	    // Utilisation du mode de résolution 10 bits en mode simple-ended
	    .resolution = kADC16_ResolutionSE10Bit,

	    // Désactivation du mode d'échantillonnage long
	    .longSampleMode = kADC16_LongSampleDisabled,

		// Désactivation du mode haute vitesse
	    .enableHighSpeed = false,

	    // Désactivation du mode basse puissance
	    .enableLowPower = false,

	    // Désactivation du mode de conversion continue, effectue une seule conversion
	    .enableContinuousConversion = false,
	};

	// Configurations GPIO pour les broches d'entrée et de sortie
	const gpio_pin_config_t gpio_pin_input =
	{
	    // Configuration de la broche en entrée numérique
	    .pinDirection = kGPIO_DigitalInput,
	};

	const gpio_pin_config_t gpio_pin_output =
	{
	    // Configuration de la broche en sortie numérique avec logique à 0
	    .pinDirection = kGPIO_DigitalOutput,
	    .outputLogic = 0,
	};

	// ---------------------------------------------------------------------------

	// Initialisation et Configuration de l'ADC
	ADC16_Init(ADC0, &adc0_config);
	ADC16_SetChannelMuxMode(ADC0, kADC16_ChannelMuxB); // Sélectionne le Mux B bit 5 ADC0_CFG2

	// Configuration de l'horloge et des ports
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortB);

	// Muxage des ports pour les broches ADC et GPIO
	PORT_SetPinMux(PORTC, 2u, kPORT_PinDisabledOrAnalog); // Broche 2 de PORTC comme broche ADC
	PORT_SetPinMux(PORTB, 8u, kPORT_MuxAsGpio);          // Broche 8 de PORTB comme broche GPIO
	PORT_SetPinMux(PORTB, 9u, kPORT_MuxAsGpio);          // Broche 9 de PORTB comme broche GPIO

	// Initialisation GPIO
	GPIO_PinInit(GPIOC, 2u, &gpio_pin_input);
	GPIO_PinInit(GPIOB, 8u, &gpio_pin_output);
	GPIO_PinInit(GPIOB, 9u, &gpio_pin_output);

}

void ImageProcessing::differentiate(void){

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
				gaussian1 = (1.0/(SIGMA_1 * sqrt(2.0*PI))) * exp(-(pow(i,2.0))/(2.0*pow(SIGMA_1,2.0)));
				gaussian2 = (1/(SIGMA_2 * sqrt(2*PI))) * exp(-(pow(i,2.0))/(2.0*pow(SIGMA_2,2.0))); // @suppress("Invalid arguments")

				ImageDataDifference[i] = abs ( (int) (round ( (ImageData[i] * gaussian1 - ImageData[i] * gaussian2) ) ) );
			}
		}
	}	/*	End of function "Fill_ImageDataDifference"	*/

void ImageProcessing::process (void){
		number_edges = 0;		// reset the number of peaks to 0

		if (functionning_mode == 1){
			// Find black line on the right side
			CompareData_classic = THRESHOLD_classic;					// threshold
			BlackLineRight = 126;
			for(i=64;i<=125;i++){
	   			if (ImageDataDifference[i] > CompareData_classic){
	   				CompareData_classic = ImageDataDifference[i];
	   				BlackLineRight = i;
	   				(number_edges)++;
	   			}
			}
			// Find black line on the left side
			CompareData_classic = THRESHOLD_classic;					// threshold
			BlackLineLeft = 1;
			for(i=64;i>=3;i--){							// only down to pixel 3, not 1
			   	if (ImageDataDifference[i] > CompareData_classic){
	 	 	 		CompareData_classic = ImageDataDifference[i];
	 		  		BlackLineLeft = i;
	 		  		(number_edges)++;
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

			//CompareData_low = THRESHOLD_low;					// threshold_low
			//CompareData_high = THRESHOLD_high;					// threshold_high

			BlackLineRight = 126;
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
			BlackLineLeft = 1;
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
		}	/* END of "(IF mfunctionning_mod == 2 || functionning_mode == 3)" */


/****************************************************************************************************************************************************

		Mode number 4 : about the same as mode 2 and 3, but the calculation is made on two additional indices (0 and 127)
		mode 4 : using the Gaussian difference method

*****************************************************************************************************************************************************/

		else if (functionning_mode == 4){
			// Find black line on the right side

			//CompareData_low = THRESHOLD_low;					// threshold_low
			//CompareData_high = THRESHOLD_high;					// threshold_high
			BlackLineRight = 126;
			for(i=127;i>=64;i--){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineRight = i;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i >= 67 && i <= 124){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							BlackLineRight = i;
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
	   								BlackLineRight = i;
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
			BlackLineLeft = 1;
			for(i=0;i<=64;i++){
	   			if (ImageDataDifference[i] > CompareData_high){
	   				//CompareData_high = ImageDataDifference[i];
	   				BlackLineLeft = i;
	   			}else if (ImageDataDifference[i] > CompareData_low && ImageDataDifference[i] < CompareData_high ){
	   				if (i >= 3 && i <= 61){
	   					j = 1;
	   					validate_gradient = 0;
						while (j <= 3){
	   						if (ImageDataDifference[i+j] > CompareData_high || ImageDataDifference[i-j] > CompareData_high){
	   							BlackLineLeft = i;
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
		} /* END of "if (functionning_mode == 4)"  */
	}	/*	END of the function "Image_Processing"	*/

void ImageProcessing::calculateMiddle (void){

	int pixel_piste = 50;
	// Store old RoadMiddle value
	RoadMiddle_old = RoadMiddle;

	// Find middle of the road, 64 for strait road
	RoadMiddle = (BlackLineLeft + BlackLineRight)/2;

	// if a line is only on the the right side
	if (BlackLineLeft < 3){
		RoadMiddle = BlackLineRight - pixel_piste;
	}
	// if a line is only on the the left side
	if (BlackLineRight > 124){
		RoadMiddle = BlackLineLeft + pixel_piste;
	}
	// if no line on left and right side
	if (number_edges == 0){
		RoadMiddle = RoadMiddle_old;
	}
	if ((BlackLineRight > 124) && (BlackLineLeft < 3)){
		RoadMiddle = RoadMiddle_old;		// we continue on the same trajectory as before
	}

	// Store old value
	diff_old = diff;							// store old difference

	// Find difference from real middle
	diff =  64 - RoadMiddle ;						// calculate actual difference

	// plausibility check
	if (abs (diff - diff_old) > pixel_piste){
		diff = diff_old;
	}else{
		servo_angle=(KP_TURN*(float)diff + KDP_TURN*(float)(diff-diff_old));
		if(servo_angle<SERVO_MAX_LEFT_ANGLE)servo_angle=SERVO_MAX_LEFT_ANGLE;
		if(servo_angle>SERVO_MAX_RIGHT_ANGLE)servo_angle=SERVO_MAX_RIGHT_ANGLE;
	}
}
//You may need to adjust the values of "CompareData_high" by modifying the macro "THRESHOLD_high".
bool ImageProcessing::test_FinishLine_Detection (void){

	threshold = 10;
	black_middle_pos_rect1=181*BlackLineRight/550;
	black_middle_pos_rect2=349*(127-BlackLineLeft)/550;

	for(i=0; i<(RECT_WIDTH/4); i++){
		if (BlackLineLeft+BLACK_RECTANGLE_MIDDLE_2<127-RECT_WIDTH/4){ //Max Value of BlackLineLeft=34
			if (ImageDataDifference[BlackLineLeft + BLACK_RECTANGLE_MIDDLE_1+i] >= threshold || ImageDataDifference[BlackLineLeft+BLACK_RECTANGLE_MIDDLE_1-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
			if (ImageDataDifference[BlackLineLeft + BLACK_RECTANGLE_MIDDLE_2+i] >= threshold || ImageDataDifference[BlackLineLeft+BLACK_RECTANGLE_MIDDLE_1-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
		}
		else if (BlackLineRight-(127-BLACK_RECTANGLE_MIDDLE_1)>=RECT_WIDTH/4){//Max Value of BlackLineRight=92
			if (ImageDataDifference[BlackLineRight -(127-BLACK_RECTANGLE_MIDDLE_2)+i] >= threshold || ImageDataDifference[127-BlackLineRight+(128-BLACK_RECTANGLE_MIDDLE_2)-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
			if (ImageDataDifference[BlackLineLeft+RECT_WIDTH/4+i] >= threshold || ImageDataDifference[BlackLineLeft+RECT_WIDTH/4-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
		}else{

		}

	}
	//finish = false at the initialization
	if (edges_cnt>=COUNTER_THRESHOLD_FINISH && number_edges>=4){
		finish = true;
		edges_cnt=0;
	}

	return finish;


	/*for(i=0; i<(RECT_WIDTH/4); i++){
		if (BlackLineLeft+BLACK_RECTANGLE_MIDDLE_2<127-RECT_WIDTH/4){ //Max Value of BlackLineLeft=34
			if (ImageDataDifference[BlackLineLeft + BLACK_RECTANGLE_MIDDLE_1+i] >= threshold || ImageDataDifference[BlackLineLeft+BLACK_RECTANGLE_MIDDLE_1-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
			if (ImageDataDifference[BlackLineLeft + BLACK_RECTANGLE_MIDDLE_2+i] >= threshold || ImageDataDifference[BlackLineLeft+BLACK_RECTANGLE_MIDDLE_1-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
		}
		else if (BlackLineRight-(127-BLACK_RECTANGLE_MIDDLE_1)>=RECT_WIDTH/4){//Max Value of BlackLineRight=92
			if (ImageDataDifference[BlackLineRight -(127-BLACK_RECTANGLE_MIDDLE_2)+i] >= threshold || ImageDataDifference[127-BlackLineRight+(128-BLACK_RECTANGLE_MIDDLE_2)-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
			if (ImageDataDifference[BlackLineLeft+RECT_WIDTH/4+i] >= threshold || ImageDataDifference[BlackLineLeft+RECT_WIDTH/4-i] >= threshold){
				edges_cnt++;
			} else {
				edges_cnt=0;
			}
		}else{

		}

	}
	//finish = false at the initialization
	if (edges_cnt>=COUNTER_THRESHOLD_FINISH && number_edges>=4){
		finish = true;
		edges_cnt=0;
	}

	return finish;*/
}

//To add at the end of  process() in order to test the variation of the thresholds towards the number of edges detected.
void ImageProcessing::compute_data_threshold(void){

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


void ImageProcessing::processAll(void) {
	capture();
	differentiate();
	process();
	calculateMiddle();
	compute_data_threshold();
	affiche_image();
	//test_FinishLine_Detection();
}

void ImageProcessing::affiche_edge(void){
	/*int Tableau_edge[128];
	for (int i=0;i<=BlackLineLeft;i++){
		Tableau_edge[i]= 1;
	}
	for (int i=BlackLineLeft;i<=BlackLineRight;i++){
		Tableau_edge[i]= 0;
	}
	for (int i=BlackLineRight;i<=127;i++){
			Tableau_edge[i]= 1;
		}
	for (int i = 0 ; i<128;i++){
			PRINTF("| %d |",Tableau_edge[i]);

		}
		PRINTF("\n");*/
	PRINTF(" || Right : %d ",BlackLineLeft);
	PRINTF(" Left : %d ||",BlackLineRight);
	PRINTF(" Middle : %d",RoadMiddle);


}


