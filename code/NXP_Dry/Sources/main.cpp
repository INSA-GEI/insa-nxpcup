#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"
#include "ImageProcessing.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
int z=0;
Car car;
Img_Proc camera;

//void delay_time(int number);

int main(){
<<<<<<< HEAD
	int p=0; //???? pour l'affichage
	//int i=0;
=======
	//int p=0; //???? pour l'affichage
>>>>>>> int_team_1
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
	DEBUG_CAM_LED_OFF;
	
	car.init();
	
	for(;;) {
		car.Car_debug();
		/*if(i>500){
			i=0;
			camera.processAll();
			camera.display_camera_data();
		}else{
			i++;
		}*/
	}
	return 0;
}

//############# handlers ##############
//100Hz
void FTM1_IRQHandler() {
	car.Car_handler(); //Define Vset and servo_angle.
	TPM1_SC |= TPM_SC_TOF_MASK;//Clear IT
}

<<<<<<< HEAD
=======
//Differential speed handlers
//6Khz
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond à la vitesse aux moteurs
}


//##### others #####
void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}


>>>>>>> int_team_1

