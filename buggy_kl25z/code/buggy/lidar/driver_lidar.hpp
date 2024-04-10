/*
 * Driver_Lidar.h
 *
 *  Created on: 23 mars 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#ifndef LIDAR_DRIVER_LIDAR_HPP_
#define LIDAR_DRIVER_LIDAR_HPP_

/**
 * @attention : this driver is created for 2 LiDARs always in running (xshut is always high)
 * @configuration : LiDAR1 -> I2C1 and LiDAR2 -> I2C0 (vl53l4cd_class.h)
 * @reference : https://github.com/stm32duino/VL53L4CD/tree/main/src
 * @use : call the function Init at first, then call GetDistance to get the measured distance
 */


void LIDAR_Init(void);

int LIDAR_GetDistance(void);

int LIDAR_CheckObstacle(void);


#endif /* LIDAR_DRIVER_LIDAR_HPP_ */
