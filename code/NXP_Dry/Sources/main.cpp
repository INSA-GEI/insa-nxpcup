#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "Car_control.h"
#include "Sensor.h"
#include <API_ST_VL53L1X/vl53l1_api.h>

//#define SLOW_BLINK      (10000000)
//#define FAST_BLINK      (1000000)
int z=0;
Car car;
Obstacle obs;

VL53L1_Dev_t devR;
VL53L1_DEV DevR = &devR;
VL53L1_RangingMeasurementData_t Data;

#define Te 0.01 //sample time 10ms Car_handler/!\ Te_s (sample time for rear motors is in Movement.h)

//void delay_time(int number);

int main(){
	//int p=0; //???? pour l'affichage
	devR.I2cDevAddr=I2C_ADDR;
	devR.comms_type=0;
	devR.comms_speed_khz=75;
	devR.new_data_ready_poll_duration_ms=0;
	devR.I2cHandle=NULL;
	debug_init();
	debug_displaySendNb((GPIOE_PDIR & 0x003C)>>2);
	DEBUG_CAM_LED_OFF;
	Timer_init (Te);
	obs.setup(DevR);
	car.init(Te);
	
	
	for(;;) {
		car.Car_debug();
	}

	return 0;
}

//############# handlers ##############
//100Hz
int c_sensor=0;
void FTM1_IRQHandler() {
	//car.Car_handler(); //Define Vset and servo_angle.
	c_sensor++;
	if (c_sensor>50){
		c_sensor=0;
		VL53L1_StartMeasurement(DevR);
		Data = obs.getRange(DevR);
		  //printing StreamCount
		  uart_write("Stream Count : ",15);
		  uart_writeNb(Data.StreamCount);
		  uart_write("\n\r",2);	
		  //printing Range Status
		  uart_write("RangeStatus (0=valid) : ",24);
		  uart_writeNb(Data.RangeStatus);
		  uart_write("\n\r",2);
		  //printing Range Value
		  uart_write("Ranging data (mm) : ",20);
		  uart_writeNb(Data.RangeMilliMeter);
		  uart_write("\n\r",2);
		  //printing Signal Rate
		  //uart_write("Signal rate : ",14);
		  //uart_writeNb((int)(Data.SignalRateRtnMegaCps/65536.0));
		  //uart_write("\n\r",2);	  
		  //printing Ambient Rate
		  //uart_write("Ambient rate : ",15);
		  //uart_writeNb((int)(Data.AmbientRateRtnMegaCps/65536.0));
		  //uart_write("\n\r",2);	
	}
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



