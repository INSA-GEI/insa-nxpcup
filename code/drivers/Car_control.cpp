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

//PID wheels angle
float coeff_i=0.0;
float coeff_d_1=0.0;
float coeff_d_2=0.0;

//PID speed
float coeff_i_s=0.0;
float coeff_d_1_s=0.0;
float coeff_d_2_s=0.0;

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
	enable_brake=false;
	Ywi=0;
	Ywd=0;
	K_camdiff=(float)((2*K+Te*Ki)/2);
	K_camdiffold=(float)((Te*Ki-2*K)/2);
	//PID Direction;
	coeff_i=Ki*Te/2;
	coeff_d_1=(2*Kd-N_Kd*Te)/(N_Kd*Te+2*Kd); //Coeff terme en k-1
	coeff_d_2=(2*N_Kd*Kd)/(N_Kd*Te+2*Kd); //Coeff sur ek
	
	//PID speed;
	e=0.0;
	e_old=0.0;
	coeff_i_s=Ki_s*Te_encoder/2;
	coeff_d_1_s=(2*Kd_s-N_Kd_s*Te_encoder)/(N_Kd_s*Te_encoder+2*Kd_s); //Coeff terme en k-1
	coeff_d_2_s=(2*N_Kd_s*Kd_s)/(N_Kd_s*Te_encoder+2*Kd_s); //Coeff sur ek
	
}

void Car::Calculate_speed (void){
	//On mesure la vitesse
	e_old=e;
	V_mes=(myMovement.encoder.getLeftSpeed()+myMovement.encoder.getRightSpeed())/2;
	//Negative speed => go back
	V_old=abs(Vset);
	//Calcul rampe => commande
	Vset=(int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle))+Vhigh;
	//PID
	e=Vset-V_mes;
	Ysi=Ysi+coeff_i_s*(e+e_old);
	Ysd=coeff_d_1_s*Ysd+coeff_d_2_s*(e-e_old);
	Vset=-K_s*e+Ysi+Ysd;
}

void Car::Set_speed(void){
	
	//We notice if we have been near the black lines or not
	if (mode_speed!=0){
		/*if (mode_speed==2){
			if (abs(cam.diff)<MAX_DIFF_BEFORE_SLOWDOWN){
				Count++;
				if ((Count%INCREASE_SPEED_MAX_MIN)==0){
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

		if (enable_brake){
			Vset=-(Vhigh-Vset+Vslow);
		}/*else if (Vset>V_old+INCREMENT_SPEED){
			Vset=V_old+INCREMENT_SPEED; //Temps de montée max 100ms
		}*/
	}
}

void Car::Set_diff_speed(void){
	//Calcul du diff
	//We calculate the delta_speed of the rear wheels
	//delta_speed=servo_angle*MOVEMENT_ENTRAXE_COEFF*Vset;
	//##################### Changement #########
	if (abs(servo_angle)<MAX_ANGLE/3){
		//Strait line
		delta_speed=0;
	}else if(abs(servo_angle)>2*MAX_ANGLE/3){
		//Hard turn => turn with r=2*Entraxe
		delta_speed=Vset/3;
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

void Car::Set_deplacement(void){
	
	//########### On actualise le déplacement #################
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
		old_servo_angle=servo_angle;
		//PI Approx bilinéaire
		servo_angle=servo_angle+(float)cam.diff*K_camdiff+(float)cam.diff_old*K_camdiffold;
		
		//PID Approx bilinéaire
		//################ erreur = 0-Cam.diff ###################### consigne 0
		/*Ywi=Ywi+coeff_i*(float)(cam.diff+cam.diff_old);
		Ywd=coeff_d_1*Ywd+coeff_d_2*(float)(cam.diff-cam.diff_old);
		servo_angle=K*(float)cam.diff+Ywi+Ywd;*/
		//############### ou ######################
		Ywi=Ywi-coeff_i*(float)(cam.diff+cam.diff_old);
		Ywd=coeff_d_1*Ywd-coeff_d_2*(float)(cam.diff-cam.diff_old);
		servo_angle=-K*(float)cam.diff+Ywi+Ywd;
//##################### Changement valeurs  ##########################
		if(servo_angle<-MAX_ANGLE)servo_angle=(-MAX_ANGLE);
		if(servo_angle>MAX_ANGLE)servo_angle=MAX_ANGLE;
	}
}

//############### ESP (oscillation en ligne droite) ############
void Car::processESP(){
	if (active_ESP){
		//############## ESP #################
		if (abs (servo_angle)>MAX_ANGLE/COEFF_ANGLE_ESP && abs(old_servo_angle)>MAX_ANGLE/COEFF_ANGLE_ESP && sng(servo_angle)!=sng(old_servo_angle)){
			ESP++;
		}
		
		//On regarde si on a détecté une oscillation/ glissement sur T=10*10ms
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
		//Action en fonction
		if (detect_ESP){
			if (mode_speed!=0){
				//On regarde si on est en ligne droite ou en virage
				if (state_turn_car==2){
					Vset=(Vslow+Vset)/2;
				}else{
					Vset=Vslow;
				}
			}
			
			//Debug
			uart_write("C_ESP : ",8);
			uart_writeNb(c_ESP);
			uart_write("\r\n",2);
			
			ESP=0;
			old_ESP=0;
		}
	}
}

//############# Test Turn? strait line? Brake? ##################
void Car::Detect_state(void){
	//Test braking #####################################
	if (Vset<V_old-T_BRAKE && abs(V_mes)>TURN_SPEED){
		enable_brake=true;	
	}else{
		enable_brake=false;
	}
	
	//##################### Test Turn #########
	if (abs(servo_angle)<MAX_ANGLE/3){
		//Strait line
		state_turn_car=0;
	}else if(abs(servo_angle)>2*MAX_ANGLE/3 || cam.BlackLineRight==127 || cam.BlackLineLeft==0){
		//Hard turn 
		state_turn_car=2;
	}else{
		//Soft turn
		state_turn_car=1;
	}
	
	//Test ESP
	//On active l'ESP
	if (Vset>TURN_SPEED && (!(enable_brake)) ){
		active_ESP=true;
	}else{
		active_ESP=false;
	}
}

//################ Handler ##########################
void Car::Car_handler(void){
	//servo//rear motors interrupt, 100Hz => Te=10ms
	//Debug
	c++;
	c_ESP++;
	if(c>500){
		c=0;
		FLAG_SEND_IMG=true;		
	}
	//
	Caculate_angle_wheel();
	//if Vset=0 => stop
	if (Vset!=0){
		Calculate_speed();
	
		Detect_state();
		//ESP at the end because it changes Vset and delta_speed
		processESP();
		
		//We apply a speed
		Set_speed();
		//Calcul du diff en fonction
		Set_diff_speed();
	}
	//Debug
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
			cam.display_camera_data();
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
	if (Vset<0){
		/*uart_write("Vold : ",7);
		uart_writeNb(V_old);
		uart_write(" / ",3);*/
		uart_write("Brake ! ",8);
		uart_write("Vset : ",7);
		uart_writeNb(Vset);
		uart_write(" / ",3);
		uart_write("Vold : ",7);
		uart_writeNb(V_old);
		/*uart_write("b : ",4);
		uart_writeNb(Vhigh);
		uart_write(" / ",3);
		uart_write("Vset : ",6);
		uart_writeNb((int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle))+Vhigh);*/
		uart_write("\r\n",2);
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

//########### others ###############

int sng(int a){
	if (a<=0){
		return 1;
	}else{
		return -1;
	}
}
