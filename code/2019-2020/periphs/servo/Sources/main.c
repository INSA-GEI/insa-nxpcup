#include <MKL25Z4.h>
#include "servo.h"
#include "Debug.h"
#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (1000000)
#define BLINK_DELAY     FAST_BLINK

void clock_init();
void delay_time(int);

int main (void){
	debug_init();
	servo_init();
	debug_displaySendNb(0);
	delay_time(SLOW_BLINK);
	float a=0.0;
	servo_setPos(a);
	char str[10];
	while(1){
		if(uart_read(str,1)>0){
			switch(str[0]){
			case '+':
				a+=5.0;
				break;
			case '-':
				a-=5.0;
				break;

			default:
				break;
			}
			servo_setPos(a);
			uart_writeNb((int)a);
			uart_write("\r\n",2);
			delay_time(FAST_BLINK);
		}
	}
}

void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}
