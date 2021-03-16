/*
 * Sensor.h
 *
 *  Created on: Mar 16, 2021
 *      Author: carol
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Debug.h"

/* Predefined I2C address
 * */
#define I2C_ADDR 0x52


class Obstacle{
public: 
	/* @brief: Calibration function for the given sensor 
	 * @param: 	- 	none
	 * */
	void init(void);

	uint8_t I2C1_data_send(uint8_t data);
	uint8_t I2C1_data_read(void);

	
private:
	void I2C_clock_init(void);
	void I2C_init_port_right(void);
	void I2C_init_master_right(void);
	void I2C_delay_us(uint16_t usec_time);
};


#endif /* SENSOR_H_ */
