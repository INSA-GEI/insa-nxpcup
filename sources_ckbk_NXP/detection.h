/*

 * detection.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Cao Kha Bao Khanh
 */

#ifndef DETECTION_H_
#define DETECTION_H_

#define STRAIGHT					2
#define CURVE						1
#define CROSS						0
#define UNDEFINE_CASE				6
#define	ENDLINE						3
#define MAX_DETECTION				30
#define MIN_DETECTION				0
#define	DETECTION_TRIGGER			24

void update_corrector_type(int *number_detection);

/*ADD 3 variables in MAIN:
int *nbr_detection_straight;
int *nbr_detection_curve;
int *type_detection;

in the init add this code:
*nbr_detection_straight=100;
*nbr_detection_curve=50;
*type=STRAIGHT;

use "type" as a variable to choose the corrector depending on the case;

use update_corrector_type in image_processing algorithm

*/

#endif /* DETECTION_H_ */
