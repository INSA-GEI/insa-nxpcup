/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#include <MKL25Z4.h>

// Defines for Direction PD Servo Control Loop
#define KP_S						50			// Proportional coefficient
#define KDP_S						20			// Differential coefficient

#define KP_V						46		// Proportional coefficient
#define KDP_V						60			// Differential coefficient

// Defining the change margin for left/right turn
#define LEFT_TURN_MARGIN 			15			
#define RIGHT_TURN_MARGIN 			20
#define TRACK_WIDTH_ESTIMATE 		80

// Defining the standard speed and differential speeds
#define STANDARD_SPEED 				140
#define DIFF_HIGH					140
#define DIFF_LOW					70

// Camera gradient threshold
#define THRESHOLD_classic  			60	// standard threshold for camera detection
