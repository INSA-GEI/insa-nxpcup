#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "ImageProcessing.h"
#include "Movement.h"

#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (1000000)


unsigned int V=1000;
unsigned int Vset=1000;
unsigned int Vslow=500;
unsigned int VslowTH=500;
const float ADAPTIVE_SPEED_ANGLE = 10.0;
const float ADAPTIVE_SPEED_HYST = 2.0;

int n=0;
int c=0;
int cnt=0;
bool FLAG_SEND_IMG=false;
bool FLAG_ENABLE_LOG_IMG=false;
bool FLAG_ENABLE_LOG_SERVO=false;
Movement myMovement;
Img_Proc camera;

void delay_time(int number);

int main(){

	debug_init();
	debug_displaySendNb(n);
	DEBUG_CAM_LED_OFF;
	myMovement.init();
	camera.init();
	myMovement.set(V,0.0);
	char str[10];
	for(;;) {

		if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_IMG){
			for(int i=0;i<128;i++){
				uart_write("$",1);
				uart_writeNb(camera.ImageData[i]);
				uart_write(" ",1);
				if(camera.BlackLineLeft==i ||camera.RoadMiddle==i ||camera.BlackLineRight==i){
					uart_writeNb(200);
				}else{
					uart_writeNb(0);
				}
				uart_write(";",1);
			}
			FLAG_SEND_IMG=false;
		}

		if(uart_read(str,1)>0){
			switch(str[0]){
			case '+':	//increment speed
				Vset+=250;
				uart_write("Vset : ",7);
				uart_writeNb(Vset);
				uart_write("\r\n",2);
				n++;
				break;
			case 'p':	//increment speed
				VslowTH+=100;
				uart_write("Vslow : ",7);
				uart_writeNb(VslowTH);
				uart_write("\r\n",2);
				break;
			case 'm':	//increment speed
				VslowTH-=100;
				uart_write("Vslow : ",7);
				uart_writeNb(VslowTH);
				uart_write("\r\n",2);
				break;

			case ' ':	//emergency stop
				Vset=0;
				uart_write("Stop !",6);
				V=0;
				n=0;
				break;

			case '-':	//decrement speed
				if(n>0){
					Vset-=250;
					uart_write("Vset : ",7);
					uart_writeNb(Vset);
					uart_write("\r\n",2);
					n--;
				}
				break;

			case 'l':	//lights toggle
				GPIOC_PTOR =DEBUG_CAM_LED_Pin;
				break;
			case 'i':
				FLAG_ENABLE_LOG_IMG=!FLAG_ENABLE_LOG_IMG;
				FLAG_ENABLE_LOG_SERVO=false;
				break;
			case 's':
				FLAG_ENABLE_LOG_SERVO=!FLAG_ENABLE_LOG_SERVO;
				FLAG_ENABLE_LOG_IMG=false;
				break;
			default:
				break;
			}
			/*Vslow=Vset*.3;
			if(Vslow<VslowTH)Vslow=VslowTH;
			debug_displaySendNb(n);*/
		}
	}

	return 0;
}

void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}

void FTM1_IRQHandler() {//servo interrupt, 100Hz
	//Clear the bit of the interrupt FTM1;
	camera.processAll();
	c++;
	cnt++;
	if(c>50){
		c=0;
		FLAG_SEND_IMG=true;
		
	}if(FLAG_ENABLE_LOG_SERVO && cnt>10){
		cnt=0;
		uart_write("$",1);
		uart_writeNb((int)camera.servo_angle);
		uart_write(" ",1);
		uart_writeNb(camera.diff-camera.diff_old);
		uart_write(" ",1);
		uart_writeNb(camera.diff);
		uart_write(" ",1);
		uart_writeNb(camera.RoadMiddle);
		uart_write(";",1);
	}
	/*
	if((camera.servo_angle>(ADAPTIVE_SPEED_ANGLE+ADAPTIVE_SPEED_HYST) || camera.servo_angle < -(ADAPTIVE_SPEED_ANGLE+ADAPTIVE_SPEED_HYST) ) && Vset!=0 && V!=Vslow){
		V=Vslow;
		debug_displaySendNb(15);
	}else if(camera.servo_angle<(ADAPTIVE_SPEED_ANGLE-ADAPTIVE_SPEED_HYST) && camera.servo_angle>-(ADAPTIVE_SPEED_ANGLE-ADAPTIVE_SPEED_HYST) && V<Vset){
		V+=20;
		debug_displaySendNb(n);
	}
	*/
	myMovement.set(Vset,camera.servo_angle);

	TPM1_SC |= TPM_SC_TOF_MASK;

}
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	myMovement.encoder.interruptHandler();
	myMovement.regulate();

}
