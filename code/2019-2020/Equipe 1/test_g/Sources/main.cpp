#include "derivative.h" /* include peripheral declarations */
#include "DRIVERS/Debug.h"
#include "DRIVERS/Movement.h"
#include "DRIVERS/ImageProcessing.h"

Movement myMovement;
Img_Proc camera;

int main(){	
	
	debug_init();
	myMovement.init();
	camera.init();
	for(;;) {
		
		
		}
	
	return 0;
}
