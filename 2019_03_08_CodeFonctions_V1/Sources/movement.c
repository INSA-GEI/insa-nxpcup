	   	/*
 * FRDM-KL25 Freedom Board NXP Cup Minimal Program
 * (c) THD Technische Hochschule Deggendorf
 * (c) DIT Deggendorf Institute of Technology
 * Version 2.1, 09.01.2018
 * Change: ported to NXP Cup and Alamank Car


	File : Movement.c 

	Objectives : 
		- calculate the position of the vehicle according to the road to make the necessary corrections


	
	Author : Vincent P
	Date : 2019 / 03 / 07

 */


#include "movement.h"
//#include "detection.h"


int i = 0;				// index for counters




	/***************************************************************************
	*
	*	Processing of the found maximums: calculation of the middle of the track. 
	*
	****************************************************************************/

void middlecalculate (int * RoadMiddle, int * RoadMiddle_old, int * BlackLineLeft, int * BlackLineRight, int * diff, int * diff_old, int * number_edges)
{

	// Store old RoadMiddle value
	*RoadMiddle_old = *RoadMiddle;

	// Find middle of the road, 64 for strait road
	*RoadMiddle = (*BlackLineLeft + *BlackLineRight)/2;

	// if a line is only on the the right side
	if (*BlackLineLeft < 3)
	{
		*RoadMiddle = *BlackLineRight - 50;
	}
	// if a line is only on the the left side
	if (*BlackLineRight > 124)
	{
		*RoadMiddle = *BlackLineLeft + 50;
	}
	// if no line on left and right side
	if (number_edges == 0)
	{
		*RoadMiddle = *RoadMiddle_old;
		for (i = 0 ; i < 1000000 ; i++);
	}
	if ((*BlackLineRight > 124) && (*BlackLineLeft < 3))
	{
		*RoadMiddle = *RoadMiddle_old;		// we continue on the same trajectory as before 
	}

	// Store old value
	*diff_old = *diff;							// store old difference
	
	// Find difference from real middle
	*diff = *RoadMiddle - 64;						// calculate actual difference

	// plausibility check
	if (abs (*diff - *diff_old) > 50)
	{
		*diff = *diff_old;
	}
}


