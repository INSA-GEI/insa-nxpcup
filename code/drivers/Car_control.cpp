#include "Car_control.h"
#include "Debug.h"



//#################################### Var ###################
//################ var aux #############
int c=0;
int c_ESP=0;
int old_ESP=0;
float old_servo_angle=0.0;
float K_camdiff=0.0;
float K_camdiffold=0.0;
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
	V_old=0;
	Vslow=VSLOW;
	Vhigh=VHIGH;
	mode_speed=0;
	delta_speed=0;
	mode_debug=0;
	ESP=0;
	detect_ESP=false;
	active_ESP=false;
	K_camdiff=(float)((2*K+Te*Ki)/2);
	K_camdiffold=(float)((Te*Ki-2*K)/2);
	
}

void Car::Set_speed(void){
	//uart_write("$",1);
	//We notice if we have been near the black lines or not
	if (mode_speed!=0){
		/*if (mode_speed==2){
			if (abs(cam.diff)<MAX_DIFF_BEFORE_SLOWDOWN){
				Count++;
				if ((Count%INCREASE_SPEED)==0){
					Vslow+=200;
					Vhigh+=200;
				}
			}else{
				Count--;
				//Vslow-=200;
				//Vhigh-=200;
			}
		}*/
		
		//Linear mode
		V_old=Vset;
		if (Vset!=0){
			Vset=(int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle))+Vhigh;
			//Test#####################################
			if (Vset>V_old){
				Vset=0.01*Vset+0.99*V_old; //Temps de montée max 100ms
			}else if(abs(Vset-V_old)>300){
				Vset=-Vset;
			}
			/*uart_write("Vold : ",7);
			uart_writeNb(V_old);
			uart_write(" / ",3);*/
			uart_write("Vset : ",7);
			uart_writeNb(Vset);
			/*uart_write(" / ",3);
			uart_write("b : ",4);
			uart_writeNb(Vhigh);
			uart_write(" / ",3);
			uart_write("Vset : ",6);
			uart_writeNb((int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle))+Vhigh);*/
			uart_write("\r\n",2);
		}
	}
	
	//Calcul du diff
	//We calculate the delta_speed of the rear wheels
	//delta_speed=servo_angle*MOVEMENT_ENTRAXE_COEFF*Vset;
	//##################### Changement #########
	if (abs(servo_angle)<MAX_ANGLE/3){
		//Strait line
		delta_speed=0;
	}else if(abs(servo_angle)>2*MAX_ANGLE/3){
		//Hard turn => turn with r=Entraxe
		delta_speed=Vset/2;
	}else{
		//Soft turn
		float r=LENGHT_CAR/(abs(servo_angle)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(Vset*L_ENTRAXE)/(2*r+L_ENTRAXE);
	}
	
	//Left turn servoangle<0
	if (servo_angle<0){
		delta_speed=-delta_speed;
	}
}

void Car::Braking(void){
	//Utiliser dans le main	
	MOTOR_LEFT_BSPEED(200);
	MOTOR_RIGHT_BSPEED(200);
}

void Car::Set_deplacement(void){
	//##################### Changement ??????????????????????????????????????#########
	if (cam.edges_cnt>10){
		Vset=0;
		mode_speed=0;
		uart_write("Fin !",5);
		servo_angle=0;
	}else{
		myMovement.set(Vset,servo_angle);
		myMovement.setDiff(Vset,delta_speed);
	}
	
	
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
		old_servo_angle=servo_angle;
		servo_angle=K*(float)cam.diff+(Ki*Te-K)*(float)cam.diff_old+servo_angle;
		//PID Approx bilinéaire
		//servo_angle=servo_angle+(float)cam.diff*K_camdiff+(float)cam.diff_old*K_camdiffold;
//##################### Changement valeurs  ##########################
		if(servo_angle<-MAX_ANGLE)servo_angle=(-MAX_ANGLE);
		if(servo_angle>MAX_ANGLE)servo_angle=MAX_ANGLE;
	}
}

void Car::processESP(){
	if (active_ESP){
		//############## ESP #################
		if (abs (servo_angle-old_servo_angle)>MAX_ANGLE/4 && sng(servo_angle)!=sng(old_servo_angle)){
			ESP++;
		}
		
		if(c_ESP>10){
			c_ESP=0;
			if (ESP==old_ESP){
				ESP=0;
				detect_ESP=false;
				old_ESP=0;
			}else if (ESP>LIMIT_ESP){
				detect_ESP=true;
				c_ESP=-TIME_ACTIVE_ESP;
				old_ESP=ESP;
			}
		}
		if (detect_ESP){
			if (mode_speed!=0){
				Vset=300;
			}
			delta_speed=0;
			if(ESP!=0){
				uart_write("C_ESP : ",8);
				uart_writeNb(c_ESP);
				uart_write("\r\n",2);
			}
			ESP=0;
			old_ESP=0;
		}
	}
}


//################ Handler ##########################
void Car::Car_handler(void){
	//servo//rear motors interrupt, 100Hz => Te=10ms
	//
	Caculate_angle_wheel();
	
	//Debug
	c++;
	c_ESP++;
	if(c>500){
		c=0;
		FLAG_SEND_IMG=true;		
	}
	
	Set_speed();
	//ESP at the end because it changes Vset and delta_speed
	processESP();
	
	//TEST si on est en marche arrière
	if (Vset>0){
		MOTOR_LEFT_FORWARD;
		MOTOR_RIGHT_FORWARD;
	}

	
	Aff_debug();
	//We refresh the deplacement's parameters. Speed +wheels Angle
	Set_deplacement();
}



//#################### Debug ###############################

void Car::Set_debug_mode(int i){
	mode_debug=i;
	if (mode_debug==0){
		FLAG_ENABLE_LOG_IMG=0;
		FLAG_ENABLE_LOG_SERVO=1;
	}else if (mode_debug==1){
		FLAG_ENABLE_LOG_IMG=1;
		FLAG_ENABLE_LOG_SERVO=0;
	}
}

void Car::Aff_debug(void){
	if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_IMG){
		for(int i=0;i<128;i++){
			uart_write("$",1);
			//uart_writeNb(cam.ImageData[i]);
			/*uart_write(" ",1);
			if(cam.BlackLineLeft==i ||cam.RoadMiddle==i ||cam.BlackLineRight==i){
				uart_writeNb(200);
			}else{
				uart_writeNb(0);
			}*/
			uart_write(";",1);
		}
	}else if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_SERVO){
		uart_write("$",1);
		uart_writeNb(Vset);
		uart_write(" ",1);
		uart_writeNb((int)servo_angle);
		/*uart_write(" ",1);
		uart_writeNb(cam.diff-cam.diff_old);
		uart_write(" ",1);
		uart_writeNb(cam.diff);
		uart_write(" ",1);
		uart_writeNb(cam.number_edges);
		uart_write(" ",1);
		uart_writeNb(cam.RoadMiddle);*/
		uart_write(";",1);
	}
	FLAG_SEND_IMG=false;
}
void Car::Car_debug(void){
	char str[10];
	
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
					servo_angle=0;
					break;

				case '-':	//decrement speed
					if(true){//n>0){
						Vset-=250;
						uart_write("Vset : ",7);
						uart_writeNb(Vset);
						uart_write("\r\n",2);
						n--;
					}
					break;
				case 'x':	//decrement speed
					if(mode_speed==0){
						mode_speed=1;
						uart_write("speed_auto\n\r",12);
					}else if(mode_speed==1){
						mode_speed=2;
						uart_write("speed_auto_incr\n\r",17);
					}else{
						mode_speed=0;
						Vset=Vslow;
						uart_write("speed_mano\n\r",12);
					}
					break;
				case 'e':
					uart_write("ESP actif\n\r",11);
					active_ESP=true;
					break;
				case 'l':	//lights toggle
					GPIOC_PTOR =DEBUG_CAM_LED_Pin;
					break;
				case 'i':
					uart_write("debug_img\n\r",11);
					FLAG_ENABLE_LOG_IMG=!FLAG_ENABLE_LOG_IMG;
					FLAG_ENABLE_LOG_SERVO=false;
					break;
				case 's':
					uart_write("debug_servo\n\r",13);
					FLAG_ENABLE_LOG_SERVO=!FLAG_ENABLE_LOG_SERVO;
					FLAG_ENABLE_LOG_IMG=false;
					break;
				case 'v':
					FLAG_SEND_IMG=true;
					break;
				default:
					break;
				}
			}
}

int sng(int a){
	if (a<=0){
		return 1;
	}else{
		return -1;
	}
}
