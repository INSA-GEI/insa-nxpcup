/*
 * driver_lidar.cpp
 *
 *  Created on: 23 mars 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */


#include "driver_lidar.hpp"
#include "vl53l4cd_class.hpp"


#define OBSTACLE_DETECTION_THRESHOLD		700              //Detect obstacles at a distance of 70cm

static VL53L4CD lidar1(1);
static VL53L4CD lidar2(2);

void LIDAR_Init(void)
{
    lidar1.Init();
    lidar2.Init();
}

int LIDAR_GetDistance(void)
{
	int distance1, distance2;
	distance1 = lidar1.getDistance();
	distance2 = lidar2.getDistance();
	if (distance1 > distance2)
	{
		return distance2;
	}
	else
	{
		return distance1;
	}

}

int LIDAR_CheckObstacle(void)
{
	int distance = LIDAR_GetDistance();

	if(distance < OBSTACLE_DETECTION_THRESHOLD)
	{
		return 1;
	}
	return 0;

}
