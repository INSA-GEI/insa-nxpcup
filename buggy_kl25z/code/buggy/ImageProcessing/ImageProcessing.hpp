/*
 * ImageProcessing.hpp
 *
 *  Created on: 22 janv. 2024
 *      Author: Ordi Axel
 */

#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_adc16.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

#include <MKL25Z4.h>
#include "math.h"
//#include <cmath>
#include "stdio.h"
#include "stdlib.h"




#define CAM_DELAY				asm ("nop")				// minimal delay time
#define	CAM_SI_HIGH 			GPIO_SetPinsOutput(GPIOB,(1<<8)) // SI on PTB8
#define	CAM_SI_LOW				GPIO_ClearPinsOutput(GPIOB,(1<<8)) // SI on PTB8*
#define	CAM_CLK_HIGH			GPIO_SetPinsOutput(GPIOB,(1<<9))	// CLK on PTB9
#define	CAM_CLK_LOW				GPIO_ClearPinsOutput(GPIOB,(1<<9))	// CLK on PTB9

#define ADC0_Channel_Group 0u // Utilisé pour le receuil de donnée de l'ADC0. Seul channel group avec software trigger
#define PORT_ADC PORTC
#define PORT_GPIO PORTB
#define PIN_CLOCK 9u
#define PIN_SI 8u


//#define KP_STRAIGHT						50			// Proportional coefficient in straight line
//#define KDP_STRAIGHT					15			// Differential coefficient in straight line


// Loi de control derivee proportionnel
#define KP_TURN 						.7 	// Proportional coefficient in turn
#define KDP_TURN 						.6		// Differential coefficient in turn



// Define thresholds for Camera Black Line recognition
#define THRESHOLD_high				140			// Higher threshold : does not capture noise but may not capture all maximums.
#define THRESHOLD_low				50			// Lower threshold : May capture more maximums than High threshold but can capture noise too.

#define THRESHOLD_classic			120			// standard threshold : used in the basic image processing function

#define functionning_mode			2			// operating mode: from 1 to 4: algorithm more and more precise but heavy
// Functionning mode 1: Problème de virage à droite
// Functionning mode 2: Tour à gauche et droite effectuée

#define SIGMA_1	 					2			// square root of the variance for the first gaussian filter
#define SIGMA_2 					2.5			// square root of the variance for the second gaussian filter.


#define THRESHOLD_FINISH_MIN 5				//Minimal threshold of edges for the finish
#define THRESHOLD_FINISH_MAX 9				//Maximal threshold of edges for the finish
#define COUNTER_THRESHOLD_FINISH 10
#define BLACK_RECTANGLE_MIDDLE_1 40		//(124+94/2)mm*128/550mm=171*128/550=40
#define BLACK_RECTANGLE_MIDDLE_2 88		//(550-(124+94/2))mm*128/550mm=379*128/550=88
#define RECT_WIDTH 22				//(94*128)/550=22

class ImageProcessing {
public:

	uint16_t ImageData [128];				// array to store the LineScan image
	uint16_t ImageDataDifference [128];		// array to store the PineScan pixel difference

	bool finish;						//indicates if we are at the end of the circuit
	int edges_cnt;						//counter when the edges are currently detected between 7 and 10
	int diff;							// actual difference from line middle position
	int diff_old;
	int threshold;				// actual position of the servo relative to middle
	int black_middle_pos_rect1;
	int black_middle_pos_rect2;
	float servo_angle;
	uint16_t RoadMiddle;						// calculated middle of the road
	uint16_t RoadMiddle_old;					// save the last "Middle of the road" position
	uint16_t BlackLineRight;					// position of the black line on the right side (127)
	uint16_t BlackLineLeft;					// position of the black line on the left side
	uint16_t number_edges;


	void init(void);					//initializes the camera
	void capture(void);					//retrieves data from the camera
	void differentiate(void);			//computes differential
	void process(void);					//detects edges
	void calculateMiddle(void);			//guesses the middle
	void processAll(void);				//executes all camera related operations in order. Takes approx 940�s to complete
	bool test_FinishLine_Detection(void);
	void compute_data_threshold(void);
	void affiche_image(void); // Affiche image en mode débug sur serial terminal
	void affiche_edge(void);

private:
	int CompareData_classic;			// set data for comparison to find max IN BASE ALGORITHM
	int CompareData_low;				// set data for comparison to find max with low threshold
	int CompareData_high;				// set data for comparison to find max with high threshold
	int validate_gradient;				// used in image processing to validate some parameters

	float gaussian1;					// gaussian filters used in gaussian differences method
	float gaussian2;

};

#endif /* IMAGEPROCESSING_H_ */

