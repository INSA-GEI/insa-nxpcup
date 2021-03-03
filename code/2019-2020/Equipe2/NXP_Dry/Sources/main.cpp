#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

Car car;

int main(){
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
	DEBUG_CAM_LED_OFF;
	car.init();
	
	for(;;) {
		car.Car_debug();
	}

	return 0;
}

//############# handlers ##############
//100Hz
void FTM1_IRQHandler() {
	car.Car_handler(); //Define Vset and servo_angle.
	TPM1_SC |= TPM_SC_TOF_MASK;//Clear IT
}

//Differential speed handlers
//6Khz
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond à la vitesse aux moteurs
}


