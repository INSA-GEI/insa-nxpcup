/*
 * detection.c
 *
 *  Created on: Mar 14, 2019
 *      Author: MasterChief
 */


void update_corrector_type(int *nbr_detection_s, int* nbr_detection_c, int MODE, int *type)
{
	if (MODE==STRAIGHT)
	{
		if (*nbr_detection_s<=100)
		{
			*nbr_detection_s+=1;
		}
		if (*nbr_detection_c>=0)
		{
			*nbr_detection_c-=1;
		}
	}
	
	else if (MODE==CURVE)
	{
		if (*nbr_detection_c<=100)
				{
					*nbr_detection_c+=1;
				}
				if (*nbr_detection_s>=0)
				{
					*nbr_detection_s-=1;
				}
	}
	
	if (*nbr_detection_straight_s>50)
	{
		*type=STRAIGHT;
	}
	if (*nbr_detection_c>80)
	{
		*type=CURVE;
	}
}
