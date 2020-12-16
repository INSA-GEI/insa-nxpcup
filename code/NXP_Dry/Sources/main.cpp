#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"
#include "ImageProcessing.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)

Car car;
Img_Proc camera;

//void delay_time(int number);

int main(){
	int p=0; //???? pour l'affichage
	int i=0;
	debug_init();
	debug_displaySendNb(p);
	DEBUG_CAM_LED_OFF;
	
	car.init();
	
	for(;;) {
		car.Car_debug();
		if(i>500){
			i=0;
			camera.display_camera_data();
		}else{
			i++;
		}
	}

	return 0;
}

void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}

//############# handlers ##############
void FTM1_IRQHandler() {
	car.Car_handler();
}



