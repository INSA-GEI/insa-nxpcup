
#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_


#include <MKL25Z4.h>
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

#define Plausibily_check 40 //For Roadmiddle

#define CAM_DELAY				asm ("nop")				// minimal delay time
#define	CAM_SI_HIGH				GPIOB_PDOR |= (1<<8)	// SI on PTB8
#define	CAM_SI_LOW				GPIOB_PDOR &= ~(1<<8)	// SI on PTB8
#define	CAM_CLK_HIGH			GPIOB_PDOR |= (1<<9)	// CLK on PTB9
#define	CAM_CLK_LOW				GPIOB_PDOR &= ~(1<<9)	// CLK on PTB9
#define CSV						false //display data

// Define thresholds for Camera Black Line recognition
#define THRESHOLD_classic			0			// standard threshold : used in the basic image processing function
#define MAX_VALUE					100
#define DELTA_OUT					3.5

#define CST_RECAL_T 500
#define TAILLE_BANDE 10 //taille bande noir en pixel
#define TAILLE_BANDE_MAX 30

class Img_Proc{
public:
	//constructeur
	Img_Proc();
	
	int ImageData [128];				// array to store the LineScan image
	int ImageDataDifference [128];		// array to store the PineScan pixel difference
	int Imageflou [128];				// array to store the PineScan pixel => blur
	int LBP[128];						//
	
	int diff;							// actual difference from line middle position
	int diff_old;						//
	int threshold;						//Moyenne des échantillons
	int threshold_sun;						//Moyenne des échantillons soleil
	float delta;						//Ecart-type peut servir pour savoir si on est en dehors de la route ou pas		
	int threshold_old;
	
	int RoadMiddle;						// calculated middle of the road
	int RoadMiddle_old;					// save the last "Middle of the road" position
	int BlackLineRight;					// position of the black line on the right side (127)
	int BlackLineLeft;					// position of the black line on the left side
	int number_edges;					// Nombre de lignes
	int number_edges_old;

	void init(int f_mode);					//initializes the camera
	void capture(void);					//retrieves data from the camera
	void differentiate(void);			//computes differential
	void process(void);					//detects edges
	void calculateMiddle(void);			//guesses the middle
	void processAll(void);				//executes all camera related operations in order. Takes approx 940µs to complete
	
	/*** 2020 - 2021 ***/
	void display_camera_data(void);
	void display_gradient(void);
	
	
private:
	//Mode de détection des lignes
	int functionning_mode;
	
	int validate_gradient;				// used in image processing to validate some parameters
	bool detect_sun;					//Un rayon de soleil est détecté
};

/* PROCESS
*	Retrieves the image, applies algorithms to find local maximums and thus define the position of black lines. 
*	PARAMETERS : operating mode : 1 = classic algorithm (same as the NXP_minimal) 
*								  2 = using a gradient by direct differences (application of the filter : [-1 , 0 , 1] -> P(x) = -1*P(x-1)+0*P(x)+1*P(x+1))
*								  3 = using a gradient by centered differences (application of the filter :[-1/2 , 0 , 1/2] -> P(x) = (-1/2)*P(x-1)+0*P(x)+(1/2)*P(x+1))
								  4 = using the Gaussian difference method
*				 diff : pointer to a variable "diff" defined in main. 
*				 diff_old : pointer to a variable "diff_old" defined in main. 
*
*/ 
/*

	Two threshold functionning : 
		For a pixel P(x), having gradient magnitude G, following conditions exists to detect a pixel as edge :
			- if G < threshold_low then discard the edge
			- if G > threshold_high then keep the edge
			- if threshold_low < G < threshold_high and if any neighbour three units away have gradient magnitude greater than threshold_high, keep the edge
			- if no neighbour in this regions have gradient > threshold_high, search the 5 units away for threshold_low < gradient < threshold_high. 
				If so, keep the edge
			- else : discard the edge. 

*/

/* DIFFERENTIATE
*
*				GAUSSIAN DIFFERENCES METHOD  :
*
*
*		calculates two Gaussian filters for different variances and then calculates their difference (absolute value) for each pixel (128).
*		puts the values in each cell of the "image_data_difference" table
*
*		To be used by modifying the variance values to obtain a satisfactory result because the model is too complex to model 
*		(need to know the probability of the value given by each pixel between 0 and 255). 
*/

#endif /* IMAGEPROCESSING_H_ */
