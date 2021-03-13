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
#include "Debug.h"

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
	//VL53L1_Dev_t*	DevR = &devR; //passer par un constructeur
	//Left sensor
	VL53L1_Dev_t	devL;
	//VL53L1_Dev_t*	DevL = &devL;
	
	//Obstacle();
	
	/* @brief: Calibration function for the given sensor 
	 * @param: 	- 	VL53L1_DEV Dev			: Device Name
	 * */
	void setup(VL53L1_DEV Dev);
	
	/* @brief: Calibration function for the given sensor 
	 * @param: 	- 	none
	 * */
	void init(void);
	
	/* @brief: Gets the ranging information from the given sensor 
	 * @param: 	- 	VL53L1_DEV Dev			: Device Name
	 * */
	VL53L1_RangingMeasurementData_t & getRange(VL53L1_DEV Dev);
	
	/* Data: Measured range */
	static VL53L1_RangingMeasurementData_t RangingDataLeft;
	static VL53L1_RangingMeasurementData_t RangingDataRight;
	
	void I2C_clock_init(void);
	void I2C_init_port_right(void);
	void I2C_init_master_right(void);
	
private:

	void I2C_init_port_left(void);

	void I2C_init_master_left(void);
	VL53L1_RangingMeasurementData_t printRangingData(VL53L1_DEV Dev);

	void I2C0_start(void);
	void I2C0_repeat_start(void);
	void I2C0_stop(void);
	void I2C1_start(void);
	void I2C1_repeat_start(void);
	void I2C1_stop(void);
	static void I2C_delay_us(uint16_t usec_time);
	static uint8_t I2C0_data_read(void);
	static uint8_t I2C1_data_read(void);
	static uint8_t I2C0_data_send(uint8_t data);
	static uint8_t I2C1_data_send(uint8_t data);
	uint8_t I2C0_byte_read(uint32_t mem_loc, uint8_t *read_status);
	uint8_t I2C1_byte_read(uint32_t mem_loc, uint8_t *read_status);
	void I2C0_byte_write(uint32_t mem_loc, uint8_t byte, uint8_t *write_status);
	void I2C1_byte_write(uint32_t mem_loc, uint8_t byte, uint8_t *write_status);
	 
};


#endif /* OBSTACLE_DETECTION_H_ */
