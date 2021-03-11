#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
Car car;

#define Te 0.002//sample time 2ms Car_handler/!\ Te_s (sample time for rear motors is in Movement.h)

int MODE=-1;
//void delay_time(int number);

//La led rouge indique qu'il faut changer la batterie, on affiche aussi B sur l'afficheur 7seg;
int Init_tot(void){
	//######## INIT ###########
	MODE=debug_init(); 		//retourne le mode
	car.myMovement.init(Te);
	int f_mode=1;//MODE; 	//Définit le functionning mode
	if (f_mode==-1){
		f_mode=1;
	}
	car.cam.init(f_mode);
	car.init(Te,MODE);
	Timer_init (Te);
	car.myMovement.encoder.init_SENS(); //ATTENTION à laisser en dernier!!
	IT_PORTD_init();
	
	return 0;
}

int main(){	
	Init_tot();
	//######## While (1) pour débug #########
	for(;;) {
		car.Car_debug();
	}

	return 0;
}

//############# handlers ##############
int count_dem=0;
void PORTD_IRQHandler(void){
	DEBUG_GREEN_ON;
	PORTD_PCR3 |= 1<<24;
	count_dem++;
	
}

//100Hz
//Servo handler
void FTM1_IRQHandler() {
	if (count_dem>0){
		count_dem++;
		//2 secondes
		if (count_dem>200){
			count_dem=0;
			uart_write("OK\n\r",4);
			car.Demarre();
		}
	}
	
	TPM1_SC |= TPM_SC_TOF_MASK;//Clear IT
}

//speed handlers
void FTM2_IRQHandler() {//encoder interrupt à max 6Hz
	
	car.myMovement.encoder.interruptHandler();
	
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



