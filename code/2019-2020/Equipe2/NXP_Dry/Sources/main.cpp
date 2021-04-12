#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"
#include "interrupt.h"

Car car;
int tempo_main = 0;

int main(){
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
	
	// Petite attente d'environ 5s avant de démarrer le code
	while (tempo_main < 5*1800000) tempo_main++;

	Timer_init(0.005);
	car.init();
	
	for(;;) {
		car.Car_debug();
	}

	return 0;
}

//############# handlers ##############
//100Hz
void FTM1_IRQHandler() {
	TPM1_SC |= TPM_SC_TOF_MASK;//Clear IT
}

//Differential speed handlers
//6Hz
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond à la vitesse aux moteurs
}

//100Hz
void SysTick_Handler() {
	car.Car_handler();		//Define Vset and servo_angle.
	SYST_CSR &= 0xFFFEFFFF;	// Clears IT
}
