#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
Car car;

#define Te 0.002 //sample time 10ms Car_handler/!\ Te_s (sample time for rear motors is in Movement.h)

int MODE=-1;
//void delay_time(int number);

int main(){
	debug_init();
	
	//########## Choix MODE ########
	MODE=((GPIOE_PDIR & 0x003C)>>2);
			
	if (MODE>3 && MODE==0) {
		debug_displaySendNb(16);
		//affichage de la barre du milieu
		MODE=-1;
	} else {
		debug_displaySendNb(MODE);
	}
	
	//######## INIT ###########
	DEBUG_CAM_LED_OFF;
	car.init(Te);
	Timer_init (Te);
	car.myMovement.encoder.init_SENS(); //ATTENTION à laisser en dernier!!
	
	//######## While (1) pour débug #########
	for(;;) {
		car.Car_debug();
	}

	return 0;
}

//############# handlers ##############
//100Hz
//Servo handler
void FTM1_IRQHandler() {
	
	TPM1_SC |= TPM_SC_TOF_MASK;//Clear IT
}

//speed handlers
void FTM2_IRQHandler() {//encoder interrupt à max 6Hz
	
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond à la vitesse aux moteurs
}

//Calcul var de la voiture + MAJ
void SysTick_Handler(){
	car.Car_handler(); //Define Vset and servo_angle.
	
	SYST_CSR &=0xFFFEFFFF; //Clear IT
}


//##### others #####
void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}



