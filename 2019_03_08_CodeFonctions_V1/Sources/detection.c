/*
 * detection.c
 *
 *  Created on: Mar 14, 2019
 *      Author: MasterChief
 */
#include "detection.h"
//MODE for update_detection_type
int nbr_detection_straight=80;
int nbr_detection_curve=0;
int type_detection=STRAIGHT;

void update_corrector_type(int MODE)
{
	if (MODE==STRAIGHT)
	{
		if (nbr_detection_straight<100)
		{
			nbr_detection_straight+=1;
		}
		if (nbr_detection_curve>0)
		{
			nbr_detection_curve-=1;
		}
	}
	
	else if (MODE==CURVE)
	{
		if (nbr_detection_curve<100)
				{
					nbr_detection_curve+=1;
				}
				if (nbr_detection_straight>0)
				{
					nbr_detection_straight-=1;
				}
	}
	
	if (nbr_detection_straight>80)
	{
		type_detection=STRAIGHT;
	}
	if (nbr_detection_curve>80)
	{
		type_detection=CURVE;
	}
}
