#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)

Car car;

//void delay_time(int number);

int main(){
	int p=0; //???? pour l'affichage
	debug_init();
	debug_displaySendNb(p);
	DEBUG_CAM_LED_OFF;
	car.init();
	
	for(;;) {
		car.Car_debug();
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



