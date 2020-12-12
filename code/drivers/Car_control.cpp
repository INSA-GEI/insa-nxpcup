#include "Car_control.h"
#include "Movement.h"
#include "Debug.h"
#include "ImageProcessing.h"

Movement myMovement;
Img_Proc cam;

//#################################### Var ###################
//################ var aux #############
int c=0;
int cnt=0;
int n=0;//Allow us to use the debug with Putty

int Count=0; //count how many time we were not to close to the black line

bool FLAG_ENABLE_LOG_IMG=false;
bool FLAG_ENABLE_LOG_SERVO=false;

//############## Wheel var #################
bool FLAG_SEND_IMG=false;

//################## Functions ####################

void Car::init(void){
	myMovement.init();
	cam.init();
	myMovement.set(Vset,0.0);
	servo_angle=0;
	Vset=0;
	Vslow=VSLOW;
	Vhigh=VHIGH;
	mode_speed=0;
}

void Car::Set_speed(void){
	//We notice if we have been near the black lines or not
	if (mode_speed!=0){
		/*if (abs(cam.diff)<15){
			Count++;
			if ((Count%INCREASE_SPEED)==0){
				Vslow+=200;
				Vhigh+=200;
			}
		}else{
			Vslow-=200;
			Vhigh-=200;
		}*/
		
		//On regarde si on est dans un virage ou pas
		if (abs(servo_angle) < MAX_ANGLE_BEFORE_SLOWDOWN){
			Vset=Vhigh;
		}else{
			Vset=Vslow;
		}
	}	
	
}

void Car::Set_deplacement(void){
	Set_speed();
	myMovement.set(Vset,servo_angle);
	TPM1_SC |= TPM_SC_TOF_MASK;
}

//##################### Wheels ###############

void Car::Caculate_angle_wheel(void){
	cam.processAll();
	// plausibility check
	if (abs (cam.diff - cam.diff_old) > 50){
		cam.diff = cam.diff_old;
	}else{
		//PID
		servo_angle=K*(float)cam.diff+(Ki*Te-K)*(float)cam.diff_old+servo_angle;
		//previous algo
		/*servo_angle=KP_TURN*(float)cam.diff + KDP_TURN*(float)(cam.diff-cam.diff_old);*/
		
		if(servo_angle<SERVO_MAX_LEFT_ANGLE)servo_angle=SERVO_MAX_LEFT_ANGLE;
		if(servo_angle>SERVO_MAX_RIGHT_ANGLE)servo_angle=SERVO_MAX_RIGHT_ANGLE;
	}
}


//################ Handler ##########################
void Car::Car_handler(void){
	//servo interrupt, 100Hz
	//Clear the bit of the interrupt FTM1;
	Caculate_angle_wheel();
	c++;
	cnt++;
	if(c>50){
		c=0;
		FLAG_SEND_IMG=true;
			
	}
	if(cnt>100){
		cnt=0;
		uart_write("$",1);
		uart_writeNb((int)servo_angle);
		uart_write(" ",1);
		uart_writeNb(cam.diff-cam.diff_old);
		uart_write(" ",1);
		uart_writeNb(cam.diff);
		uart_write(" ",1);
		uart_writeNb(cam.RoadMiddle);
		uart_write(";",1);
	}
	Set_deplacement();
}


void FTM2_IRQHandler() {//encoder interrupt 6kHz
	myMovement.encoder.interruptHandler();
	myMovement.regulate();

}
//#################### Debug ###############################

void Car::Car_debug(void){
	char str[10];
			if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_IMG){
				for(int i=0;i<128;i++){
					uart_write("$",1);
					uart_writeNb(cam.ImageData[i]);
					uart_write(" ",1);
					if(cam.BlackLineLeft==i ||cam.RoadMiddle==i ||cam.BlackLineRight==i){
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
					Vhigh+=100;
					uart_write("Vhigh : ",7);
					uart_writeNb(Vhigh);
					uart_write("\r\n",2);
					break;
				case 'm':	//increment speed
					if (Vhigh>Vslow){
						Vhigh-=100;
					}
					uart_write("Vhigh : ",7);
					uart_writeNb(Vhigh);
					uart_write("\r\n",2);
					break;
				case 'n':	//increment speed
					if (Vslow>200){
						Vslow-=100;
					}else{
						Vslow=0;
					}
					uart_write("Vslow : ",7);
					uart_writeNb(Vslow);
					uart_write("\r\n",2);
					break;
				case 'b':	//increment speed
					if (Vslow<Vhigh){
						Vslow+=100;
					}
					uart_write("Vslow : ",7);
					uart_writeNb(Vslow);
					uart_write("\r\n",2);
					break;
				case ' ':	//emergency stop
					Vset=0;
					mode_speed=0;
					uart_write("Stop !",6);
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
				case 'x':	//decrement speed
					if(mode_speed==0){
						mode_speed++;
						uart_write("speed_auto\n",11);
					}else{
						mode_speed=0;
						uart_write("speed_mano\n",11);
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
			}
}
