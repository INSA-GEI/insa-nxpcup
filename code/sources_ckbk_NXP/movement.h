


#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "derivative.h" /* include peripheral declarations */
#include "math.h"	/* used for different calculations, including the difference of Gaussian with roots, exponential and PI */


void middlecalculate (int * RoadMiddle, int * RoadMiddle_old, int * BlackLineLeft, int * BlackLineRight, int * diff, int * diff_old, int * number_edges);

int abs (int);


#endif /* MOVEMENT_H */
