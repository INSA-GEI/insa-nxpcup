#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
int z=0;
Car car;

#define Te 0.01 //sample time 10ms Car_handler/!\ Te_s (sample time for rear motors is in Movement.h)

//void delay_time(int number);

int main(){
	//int p=0; //???? pour l'affichage
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
	DEBUG_CAM_LED_OFF;
	Timer_init (Te);
	car.init(Te);
	
	for(;;) {
		car.Car_debug();
	}

	return 0;
}

//############# handlers ##############
//100Hz
void FTM1_IRQHandler() {
	//car.Car_handler(); //Define Vset and servo_angle.
	TPM1_SC |= TPM_SC_TOF_MASK;//Clear IT
}

//Differential speed handlers
//6Khz
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond à la vitesse aux moteurs
}

//
void SysTick_Handler(){
	car.Car_handler(); //Define Vset and servo_angle.
	
	SYST_CSR &=0xFFFEFFFF; //Clear IT
}


//##### others #####
void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}



