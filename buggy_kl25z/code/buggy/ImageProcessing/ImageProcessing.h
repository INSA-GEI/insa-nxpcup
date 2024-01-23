/*
 * ImageProcessing.h
 *
 *  Created on: 22 janv. 2024
 *      Author: Ordi Axel
 */

#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_


#define CAM_DELAY				asm ("nop")				// minimal delay time
#define	CAM_SI_HIGH 			GPIO_SetPinsOutput(GPIOB,(1<<8)) // SI on PTB8
#define	CAM_SI_LOW				GPIO_ClearPinsOutput(GPIOB,(1<<8)) // SI on PTB8*
#define	CAM_CLK_HIGH			GPIO_SetPinsOutput(GPIOB,(1<<9))	// CLK on PTB9
#define	CAM_CLK_LOW				GPIO_ClearPinsOutput(GPIOB,(1<<9))	// CLK on PTB9


const adc16_config_t adc0_config = {
	.clockDivider = kADC16_ClockDivider2,
	.resolution = kADC16_ResolutionSE10Bit,
	.enableContinuousConversion = false,

};

class ImageProcessing {
public:
	ImagProc();
	virtual ~ImagProc();
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

private:
	int CompareData_classic;			// set data for comparison to find max IN BASE ALGORITHM
	int CompareData_low;				// set data for comparison to find max with low threshold
	int CompareData_high;				// set data for comparison to find max with high threshold
	int validate_gradient;				// used in image processing to validate some parameters

	float gaussian1;					// gaussian filters used in gaussian differences method
	float gaussian2;

};

#endif /* IMAGEPROCESSING_H_ */
