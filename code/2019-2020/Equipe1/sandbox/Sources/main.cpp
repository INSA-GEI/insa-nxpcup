#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "ImageProcessing.h"
#include "Movement.h"

#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (1000000)


unsigned int V=500;
int n=2;
int c=0;
bool FLAG_SEND_IMG=false;
bool FLAG_ENABLE_LOG_IMG=false;
bool FLAG_ENABLE_LOG_SERVO=false;
Movement myMovement;
Img_Proc camera;

void delay_time(int number);

int main(){

	debug_init();
	myMovement.init();
	camera.init();
	myMovement.set(V,0.0);
	DEBUG_CAM_LED_OFF;
	debug_displaySendNb(n);
	char str[10];
	for(;;) {

		if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_IMG){
			for(int i=0;i<128;i++){
				uart_write("$",1);
				uart_writeNb(camera.ImageData[i]);
				uart_write(";",1);
			}
			FLAG_SEND_IMG=false;
		}

		if(uart_read(str,1)>0){
			switch(str[0]){
			case '+':	//increment speed
				V+=250;
				n++;
				break;

			case ' ':	//emergency stop
				V=0;
				n=0;
				break;

			case '-':	//decrement speed
				if(n>0){
					V-=250;
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
			debug_displaySendNb(n);
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
	if(c>50){
		c=0;
		FLAG_SEND_IMG=true;
		
	}if(FLAG_ENABLE_LOG_SERVO){
		uart_write("$",1);
		uart_writeNb(camera.BlackLineLeft);
		uart_write(" ",1);
		uart_writeNb(camera.BlackLineRight);
		uart_write(" ",1);
		uart_writeNb(camera.RoadMiddle);
		uart_write(" ",1);
		uart_writeNb(camera.servo_angle);
		uart_write(";",1);
	}
	myMovement.set(V,camera.servo_angle);

	TPM1_SC |= TPM_SC_TOF_MASK;

}
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	myMovement.encoder.interruptHandler();
	myMovement.regulate();

}
