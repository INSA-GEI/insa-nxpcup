#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
Car car;
#define Fe					500.0
#define Fe_IT_PWM			100000.0
#define Fe_PWM_servo_cam	50.0

#define Te 					1.0/Fe					//sample time 2ms Car_handler/!\ Te_s (sample time for rear motors is in Movement.h)
#define Te_IT_PWM			1.0/Fe_IT_PWM			//100kHz 10�s
#define Te_PWM_servo_cam	1.0/Fe_PWM_servo_cam	//20ms

int CST_TE; 								//cst Pour le car.handler() 
int CST_TE_PWM;
int CST_PWM_HIGH=150;

int MODE=-1;
//void delay_time(int number);

//La led rouge indique qu'il faut changer la batterie, on affiche aussi B sur l'afficheur 7seg;
int Init_tot(void){
	//######## INIT ###########
	//ATTENTION l'ordre est important!
	MODE=debug_init(); 		//retourne le mode
	car.myMovement.init(Te);
	int f_mode=1;//MODE; 	//D�finit le functionning mode
	if (f_mode==-1){
		f_mode=1;
	}
	car.cam.init(f_mode);
	car.init(Te,MODE);
	car.myMovement.encoder.init_SENS(); 
	//Init de GPIO
	IT_PORTD_init();
	init_servo_cam();
	
	//Init IT
	Timer_init (Te_IT_PWM);
	
	return 0;
}

int application(){
	Init_tot();
	CST_TE=(int)(Fe_IT_PWM/Fe);
	CST_TE_PWM=(int)(Fe_IT_PWM/Fe_PWM_servo_cam);
	uart_write("CST_TE=",7);
	uart_writeNb (CST_TE);
	uart_write(" | Fe_PWM=",10);
	uart_writeNb (Fe_IT_PWM/CST_TE_PWM);
	uart_write("\n\r",2);
	//######## While (1) pour d�bug #########
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

//10kHz
void FTM0_IRQHandler() {
	
	TPM0_SC |= TPM_SC_TOF_MASK;//Clear IT
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
void FTM2_IRQHandler() {//encoder interrupt � max 6Hz Te variable!!!
	
	car.myMovement.encoder.interruptHandler();
	
}

//Calcul var de la voiture + MAJ
int cpt_car_handler=0;
//PWM servo
int count_FTM0=0;
bool etat=true;
void SysTick_Handler(){
	//Incr cpt
	cpt_car_handler++;
	count_FTM0++;
	
	// car handler
	if (cpt_car_handler>CST_TE){
		//500Hz 
		cpt_car_handler=0;
		car.Car_handler(); //Define Vset and servo_angle.
	}else{
		
	}
	
	//###### PWM ##############
	
	//pas de 0.1 ms
	//1.5ms
	if (count_FTM0>CST_TE_PWM){
		//50Hz => 20ms //Une p�riode de PWM
		count_FTM0=0;
		etat=false;
	}else if (count_FTM0<=CST_PWM_HIGH){
		etat=true;
	}else{
		etat=false;
	}
	
	//Actualisation
	if (etat){
		SERVO_CAM_PWM_ON;
	}else{
		SERVO_CAM_PWM_OFF;
	}
		
	SYST_CSR &=0xFFFEFFFF; //Clear IT
}


//##### others #####
void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}



