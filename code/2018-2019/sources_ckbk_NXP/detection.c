/*

 * detection.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Cao Kha Bao Khanh
 */

#include "detection.h"
#include "camera.h"	/* include camera functions definition */
#include "math.h"	/* used for different calculations, including the difference of Gaussian with roots, exponential and PI */
#include "stdio.h"
#include "stdlib.h"

//MODE for update_detection_type
int nbr_detection_straight = MAX_DETECTION;
int nbr_detection_curve = MIN_DETECTION;
int nbr_detection_endline = MIN_DETECTION;
int nbr_detection_undefine = MIN_DETECTION;
int nbr_detection_cross = MIN_DETECTION;
int type_detection = STRAIGHT;
int compteur_endline = 0;
int	nbr_detection_endline_old = 0;

void update_corrector_type(int *number_detection)
{
	
	if (nbr_detection_endline > 0)
	{
		if (nbr_detection_endline > nbr_detection_endline_old + 1)
		{
			compteur_endline = 0;
			nbr_detection_endline_old=nbr_detection_endline;
		}
		else {
			compteur_endline++;
			if (compteur_endline>=20)
			{
				nbr_detection_endline=0;
				compteur_endline=0;
			}
		}
	}
	if (*number_detection == CROSS)
	{
		if (nbr_detection_cross<MAX_DETECTION)
		{
			nbr_detection_cross+=1;
		}
		if (nbr_detection_curve>MIN_DETECTION)
		{
			nbr_detection_curve-=1;
		}
		if (nbr_detection_straight>MIN_DETECTION)
		{
			nbr_detection_straight-=1;
		}
		/*if (nbr_detection_endline>MIN_DETECTION)
		{
			nbr_detection_endline-=1;
		}*/
	}
	else if (*number_detection==STRAIGHT)
	{
		if (nbr_detection_straight<MAX_DETECTION)
		{
			nbr_detection_straight+=1;
		}
		if (nbr_detection_curve>MIN_DETECTION)
		{
			nbr_detection_curve-=1;
		}
		/*if (nbr_detection_endline>MIN_DETECTION)
		{
			nbr_detection_endline-=1;
		}*/
		if (nbr_detection_cross>MIN_DETECTION)
		{
			nbr_detection_cross-=1;
		}
	}
	
	else if (*number_detection==CURVE)
	{
		if (nbr_detection_curve<MAX_DETECTION)
		{
			nbr_detection_curve+=1;
		}
		if (nbr_detection_straight>MIN_DETECTION)
		{
			nbr_detection_straight-=1;
		}
		/*if (nbr_detection_endline>MIN_DETECTION)
		{
			nbr_detection_endline-=1;
		}*/
		if (nbr_detection_cross>MIN_DETECTION)
		{
			nbr_detection_cross-=1;
		}
	}
	
	else if (*number_detection >= ENDLINE)
	{
		if (nbr_detection_endline<MAX_DETECTION)
		{
			nbr_detection_endline+=1;
		}
		if (nbr_detection_curve>MIN_DETECTION)
		{
			nbr_detection_curve-=1;
		}
		if (nbr_detection_straight>MIN_DETECTION)
		{
			nbr_detection_straight-=1;
		}
		if (nbr_detection_cross>MIN_DETECTION)
		{
			nbr_detection_cross-=1;
		}
	}
	
	if (nbr_detection_endline>1) // && type_detection == STRAIGHT) || (nbr_detection_cross>DETECTION_TRIGGER && type_detection==CURVE))
	{
		type_detection=ENDLINE;
	}
	else if (nbr_detection_straight>DETECTION_TRIGGER || (nbr_detection_straight>(DETECTION_TRIGGER/4) && type_detection==CURVE))
	{
		if (type_detection == CURVE)
		{
		nbr_detection_curve=0;
		}
		type_detection=STRAIGHT;
	}
	else if (nbr_detection_curve>DETECTION_TRIGGER)
	{
		type_detection=CURVE;
	}
	else if (nbr_detection_cross > DETECTION_TRIGGER && type_detection == STRAIGHT )//|| (nbr_detection_cross > DETECTION_TRIGGER/2 && type_detection == CURVE))
	{
		type_detection=CROSS;
	}
}



