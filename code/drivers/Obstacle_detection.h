/*
 * Obstacle_detection.h
 *
 *  Created on: Feb 3, 2021
 *      Author: Carole Meyer
 *  
 *  NOTE FOR THE NEXT NXP CUP TEAM:    
 *  The sensor is controlled with the API given by ST, called VL53L1x API. 
 *  Check the documentation on the Git 'documentation' section.
 */

#ifndef OBSTACLE_DETECTION_H_
#define OBSTACLE_DETECTION_H_

#include <API_ST_VL53L1X/vl53l1_api.h>
#include <iostream.h>
#include "Debug.h"

class Obstacle{
public: 
	
	/* @brief: Calibration function for the given sensor 
	 * @param: 	- 	VL53L1_DEV Dev			: Device Name
	 * 			- 	uint8_t DeviceAddress 	: I2C Device Adress
	 * */
	void setup(VL53L1_DEV Dev, uint8_t DeviceAddress);
	
	/* @brief: Gets the ranging information from the given sensor 
	 * @param: 	- 	VL53L1_DEV Dev			: Device Name
	 * */
	VL53L1_RangingMeasurementData_t & getRange(VL53L1_DEV Dev);
	
	/* Data: Measured range */
	static VL53L1_RangingMeasurementData_t RangingDataLeft;
	static VL53L1_RangingMeasurementData_t RangingDataRight;
	
private:
	void I2C_init_port_right(void);
	void I2C_init_port_left(void);
	void I2C_init_master_right(void);
	void I2C_init_master_left(void);
	VL53L1_RangingMeasurementData_t printRangingData(VL53L1_DEV Dev);
};


#endif /* OBSTACLE_DETECTION_H_ */
