


#ifndef CONSTANTS_DEFINE_H
#define CONSTANTS_DEFINE_H

#include "derivative.h" /* include peripheral declarations */
#include "math.h"	/* used for different calculations, including the difference of Gaussian with roots, exponential and PI */


/* 
*
*	DEFINES : Can be in "main.c",
*	"camera.c" or "camera.h".
*
*/

// Defines for LineScan Camera
#define TAOS_DELAY				asm ("nop")				// minimal delay time
#define	TAOS_SI_HIGH			GPIOB_PDOR |= (1<<8)	// SI on PTB8
#define	TAOS_SI_LOW				GPIOB_PDOR &= ~(1<<8)	// SI on PTB8
#define	TAOS_CLK_HIGH			GPIOB_PDOR |= (1<<9)	// CLK on PTB9
#define	TAOS_CLK_LOW			GPIOB_PDOR &= ~(1<<9)	// CLK on PTB9


// Define thresholds for Camera Black Line recognition
#define THRESHOLD_high				140			// Higher threshold : does not capture noise but may not capture all maximums.
#define THRESHOLD_low				50			// Lower threshold : May capture more maximums than High threshold but can capture noise too.

#define THRESHOLD_classic			120			// standard threshold : used in the basic image processing function

#define functionning_mode			2			// operating mode: from 1 to 3: algorithm more and more precise but heavy

#define SIGMA_1	 					2			// square root of the variance for the first gaussian filter
#define SIGMA_2 					2.5			// square root of the variance for the second gaussian filter. 

#define PI							3.14159265358979323846	// value of PI



// Defines for speed coefficients (differential)
#define L_TURN_R_LANE_THRESHOLD		70
#define L_TURN_L_LANE_THRESHOLD		10
#define R_TURN_R_LANE_THRESHOLD		120
#define R_TURN_L_LANE_THRESHOLD		35
#define END_L_LANE_THRESHOLD		30
#define END_R_LANE_THRESHOLD		100

#define L_TURN_L_MOTOR_SPEED		80
#define L_TURN_R_MOTOR_SPEED		80
#define R_TURN_L_MOTOR_SPEED		80
#define R_TURN_R_MOTOR_SPEED		80

#define FORWARD_MOTOR_SPEED			150


#endif /* CONSTANTS_DEFINE_H */
