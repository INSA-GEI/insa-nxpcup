/*
 * Obstacle_detection.h
 *
 *  Created on: Feb 3, 2021
 *      Author: Carole Meyer
 */

#ifndef OBSTACLE_DETECTION_H_
#define OBSTACLE_DETECTION_H_

#include <API_ST_VL53L1X/vl53l1_api.h>

class Obstacle{
public: 
	
	/* Calibration function for the sensor */
	void init(void);
private:
	int notused;
};


#endif /* OBSTACLE_DETECTION_H_ */
