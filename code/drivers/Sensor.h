/*
 * Sensor.h
 *
 *  Created on: Mar 16, 2021
 *      Author: carol
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "API_ST_VL53L1X/vl53l1_api.h"
#include "API_ST_VL53L1X/vl53l1_platform.h"
#include "API_ST_VL53L1X/vl53l1_api_calibration.h"
#include "API_ST_VL53L1X/vl53l1_api_debug.h"
#include "API_ST_VL53L1X/vl53l1_api_preset_modes.h"
#include "API_ST_VL53L1X/vl53l1_core_support.h"
#include "API_ST_VL53L1X/vl53l1_core.h"
#include "API_ST_VL53L1X/vl53l1_def.h"
#include "Debug.h"

/* Predefined I2C address
 * */
#define I2C_ADDR 0x52


class Obstacle{
public: 
	/*One sensor is defined as:
	 *  typedef struct {
	 *	VL53L1_DevData_t   	Data;
	 *	uint8_t   			I2cDevAddr;
	 *	uint8_t   			comms_type;
	 *	uint16_t  			comms_speed_khz;
	 *	uint32_t  			new_data_ready_poll_duration_ms;
	 *	I2C_HandleTypeDef*	I2cHandle;
	 *  } VL53L1_Dev_t;
	 *	
	 *	typedef struct {
	 *	   uint32_t 		dummy;
	 *	} I2C_HandleTypeDef;
	 * */
	//Right sensor
	VL53L1_Dev_t	devR;
	VL53L1_DEV	DevR = &devR; //passer par un constructeur
	//Left sensor
	VL53L1_Dev_t	devL;
	VL53L1_DEV	DevL = &devL;
	
	/* @brief: Calibration function for the given sensor 
	 * @param: 	- 	none
	 * */
	void init(void);
	
	/* @brief: Calibration function for the given sensor 
	 * @param: 	- 	VL53L1_DEV Dev			: Device Name
	 * */
	void setup(VL53L1_DEV Dev);
	
	/* @brief: Gets the ranging information from the given sensor 
	 * @param: 	- 	VL53L1_DEV Dev			: Device Name
	 * */
	VL53L1_RangingMeasurementData_t & getRange(VL53L1_DEV Dev);

	uint8_t I2C1_data_send(uint8_t data);
	uint8_t I2C1_data_read(void);
	void I2C_delay_us(uint16_t usec_time);
	
private:
	void I2C_clock_init(void);
	void I2C_init_port_right(void);
	void I2C_init_master_right(void);
	
};


#endif /* SENSOR_H_ */
