#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"
#include "interrupt.h"



int dejafe = 0;

Car car;
VL53L1_DEV Device;
VL53L1_DEV *pDevice = &Device;



int main(){
	//_I2CInit(pDevice);
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
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
void FTM2_IRQHandler() {	//encoder interrupt 6kHz
	car.myMovement.encoder.interruptHandler();
	car.myMovement.regulate(); //Applique la PWM correspond à la vitesse aux moteurs
	car.tof.tick_count++;
}

//100Hz
void SysTick_Handler() {
	car.Car_handler();		//Define Vset and servo_angle.
	SYST_CSR &= 0xFFFEFFFF;	// Clears IT
	
}
