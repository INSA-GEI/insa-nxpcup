#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
int z=0;
Car car;
Img_Proc camera;

//void delay_time(int number);

int main(){
	//int p=0; //???? pour l'affichage
	int i=0;
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
	DEBUG_CAM_LED_OFF;
	car.init();
	
	for(;;) {
		car.Car_debug();
		if(i>500000){ //mettre un seuil assez haut sinon �criture et lecture en m�me temps entre capture et display_camera_data qui fait un hardfault
			i=0;
			camera.capture();
			camera.differentiate();
			camera.process();
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
	car.Car_handler(); //Define Vset and servo_angle.
}

//Differential speed handlers
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond � la vitesse aux moteurs
}



