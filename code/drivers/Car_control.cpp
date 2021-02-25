#include "Car_control.h"
#include "Debug.h"

/* RIO 2020-2021*/


//#################################### Var ###################
//################ var aux #############
int c=0;
int c_ESP=0;
int old_ESP=0;
float old_servo_angle=0.0;
int N_calc_speed=0;
//Wheel PI
float K_camdiff=0.0;
float K_camdiffold=0.0;

int n=0;//Allow us to use the debug with Putty

//Not implemented yet
int Count=0; //count how many time we were not to close to the black line

int C_finish=0;

//Debug Flag
bool FLAG_ENABLE_LOG_IMG=false;
bool FLAG_ENABLE_LOG_SERVO=true;

//############## Wheel var #################
bool FLAG_SEND_IMG=false;

//PID VAR
float ypk=0.0;
float yik=0.0;
float yikold=0.0;
float ydk=0.0;
float ydkold=0.0;
float Kyd=0.0;
float Ked=0.0;
float Kei=0.0;

Car::Car(){
	servo_angle=0;
	servo_angle_moy=0.0;
	Vset=0;
	V_old=0;
	Vslow=VSLOW;
	Vhigh=VHIGH;
	mode_speed=1;
	delta_speed=0;
	mode_debug=0;
	ESP=0;
	state_turn_car=0;
	detect_ESP=false;
	active_ESP=false;
	enable_ampli_turn=false;
	enable_brake=false;
	enable_finish=false;
	stop=true;
}

//################## Functions ####################

void Car::init(float Te){
	myMovement.init();
	cam.init();
	myMovement.set(Vset,0.0);

	//Coeff PI servo_angle
	//K_camdiff=(float)((2*Kp+Te*Ki)/2);
	//K_camdiffold=(float)((Te*Ki-2*Kp)/2);
	
	Kyd=(2.0*Kd-Te*N)/(2.0*Kd+Te*N);
	Ked=2.0*N*Kd;
	Kei=(Te/2.0)*Ki;
	
	//Calcul nb itération avant le calcul de la vitesse
	N_calc_speed=(int)(Te_calc_speed/Te)+1;
}

//############### SPEED ########################

//Calcule la consigne de vitesse en fonction de l'angle des roues
//Le correcteur est présent dans Movement.cpp =>regulate()
void Car::Calculate_speed(void){
	//Linear mode
	V_old=abs(Vset);
				
	Vset=(int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle_moy))+Vhigh;		
	if (enable_brake){
		Vset=-VBRAKE_min;
	}else if (Vset>V_old+INCREMENT_SPEED){
		if ((V_old<(Vhigh+Vset)/2)){
			Vset=V_old+(int)(INCREMENT_SPEED/DIV_1_SPEED); //Temps de montée max 100ms//évite de glisser
		}else{
			Vset=V_old+INCREMENT_SPEED;
		}
	}
	if (state_turn_car==3){
		Vset=Vslow;
	}
}

//Calcul Vslow et Vhigh et renvoie à Calculate_speed
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
		Calculate_speed();
	}
}

//Calcul et instancie la vitesse du différentiel
void Car::Set_diff_speed(void){
	//Calcul du diff
	//We calculate the delta_speed of the rear wheels
	//##################### Changement ############
	if (enable_brake){
		float r=LENGHT_CAR/(abs(servo_angle_moy)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(abs(Vset)*L_ENTRAXE)/(0.5*r+L_ENTRAXE);//On l'aide à tourner
	}else if (state_turn_car==0){
		//Strait line
		delta_speed=0;
	}else{
		//Soft turn
		float r=LENGHT_CAR/(abs(servo_angle_moy)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(abs(Vset)*L_ENTRAXE)/(2.0*r+L_ENTRAXE);//théorique 
	}
	
	//Left turn servoangle<0
	if (servo_angle<0){
		delta_speed=-delta_speed;
	}
}

//##################### Wheels ###############
//Calcul la commande des roues et opère un PI avant de stocker la valeur dans servo_angle
void Car::Caculate_angle_wheel(void){
	//cam.diff=ek
	yikold=yik;
	ydkold=ydk;
	
	// plausibility check
	if (abs (cam.diff - cam.diff_old) > 2*MAX_CAM_DIFF){
		cam.diff = cam.diff_old;
		uart_write("pb_detect !",11);
		uart_write("\n\r",2);
	}else{
		old_servo_angle=servo_angle;
		//PI Approx bilinéaire
		//servo_angle=servo_angle+(float)aux_diff*K_camdiff+(float)cam.diff_old*K_camdiffold;
		//PID
		ypk=Kp*cam.diff;
		yik=yikold+Kei*(cam.diff+cam.diff_old);
		ydk=Kyd*ydkold+Ked*(cam.diff-cam.diff_old);
		servo_angle=ypk+yik+ydk;
		
//##################### Changement valeurs  ##########################
		if(servo_angle<-MAX_ANGLE)servo_angle=(-MAX_ANGLE);
		if(servo_angle>MAX_ANGLE)servo_angle=MAX_ANGLE;
	}
}

//############# Test Turn? strait line? Brake? ##################
//Fait l'acquisition des données
//return 	: 	V_mes
//			:	cam (à jour)
void Car::Process_data(void){
	V_mes=(int)(myMovement.v_R+myMovement.v_L)/2;
	cam.processAll();
	if (cam.threshold==-1 && !(stop)){
		uart_write("Sortie !",8);
		stop=true;
	}
}

//Permet la dectection de l'état et de où se trouve la voiture
//return 	: state_car_turn : 0/1/2
//			:enable_brake :true/false
//			:enable_ampli_turn :true/false
//			:active_ESP : true/false
void Car::Detect_state(void){
	
	//Test braking #####################################
	if (Vset<V_old-T_BRAKE && V_mes>SPEED_BRAKE_BEG){
		enable_brake=true;
	}else if((V_mes<SPEED_BRAKE_END)&&enable_brake){
		enable_brake=false;
	}
	
	//##################### Test Turn #########
	if (abs(cam.diff)<MAX_CAM_DIFF/3){
		//Strait line
		state_turn_car=0;
	}else if(abs(cam.diff)>2*MAX_CAM_DIFF/3 || cam.BlackLineRight==128 || cam.BlackLineLeft==-1){
		//Hard turn 
		state_turn_car=2;
	}else{
		//Soft turn
		state_turn_car=1;
	}
	if ((cam.number_edges)==0){
		state_turn_car=3;
	}
	
	//######## Test finish ############
	if (enable_finish){
		if ((cam.number_edges_old)==4 && (cam.number_edges)==4 && state_turn_car!=2){//Nb de bandes noires (+1 pour chaque côté)
			finish=true;
			uart_write("Fin !",5);
		}
	}
}

//Actualise le déplacement grâce à l'objet myMovement
//La vitesse peut être négative (si freiange) ou positive, tout est paramétré dans Movement.cpp
//Arg : finish :true/false <= màj dans Detect_state()

void Car::Set_deplacement(void){
	//########### On actualise le déplacement #################
	if (stop){
		C_finish=0;
		finish=false;
		Vset=0;
		servo_angle=0;
		delta_speed=0;
		myMovement.set(Vset,servo_angle);
		myMovement.setDiff(Vset,delta_speed);
	}else{
		if (finish){
			C_finish++;
			if (C_finish>CST_FINISH_TIME){
				stop=true;
			}else if (C_finish>CST_FINISH_TIME/10){
				enable_brake=true;
			}
			myMovement.set(Vset,servo_angle);
			myMovement.setDiff(Vset,delta_speed);
		}else{
			myMovement.set(Vset,servo_angle);
			myMovement.setDiff(Vset,delta_speed);
		}
	}
}

//################ Handler ##########################
//servo//rear motors interrupt, 100Hz => Te=10ms
void Car::Car_handler(void){
	//Debug
	c++;
	c_ESP++;
	
	//
	Process_data();//Acquisition des données
	//On regarde si on est en ligne droite ou non
	Detect_state();
	if (!(stop)){
		//On met à jour les param de la voiture
		Caculate_angle_wheel();
		servo_angle_moy+=servo_angle;
		if(c>N_calc_speed){
			c=0;
			servo_angle_moy=servo_angle_moy/N_calc_speed;
			//We calculate the speed
			Set_speed();
			//Calcul du diff en fonction
			Set_diff_speed();
			servo_angle_moy=0;
		}
	}else{
		//FLAG_SEND_IMG=true;
	}
	//Debug
	Aff_debug();
	//We refresh the deplacement's parameters. Speed +wheels Angle
	Set_deplacement();
}

//#################### Debug ###############################
//Permet de modifier le mode de débug et du coup l'affichage dans Putty
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

//Affiche le débug
void Car::Aff_debug(void){
	if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_IMG){
		for(int i=0;i<128;i++){
			// /!\ marche 1 fois sur 2 car on utilise en même temps les vecteurs pour stocker l'image si l'IT suivante est arrivée
			cam.display_camera_data();
		}
	}else if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_SERVO){
		uart_write("#####car#####\n\r",15);
		uart_write("Vset=",5);
		uart_writeNb(Vset);
		//uart_write(" ",1);
		uart_write(" / ",3);
		uart_write("V_mes=",6);
		uart_writeNb(V_mes);
		uart_write(" / ",3);
		uart_write("servo=",6);
		uart_writeNb((int)servo_angle);
		uart_write(" / ",3);
		uart_write("turn=",5);
		uart_writeNb(state_turn_car);
		uart_write(" / ",3);
		uart_write("V_L=",4);
		uart_writeNb(myMovement.actualSpeedL);
		uart_write(" / ",3);
		uart_write("V_R=",4);
		uart_writeNb(myMovement.actualSpeedR);
		uart_write(" / ",3);
		uart_write("V_mesL=",7);
		uart_writeNb(myMovement.v_L);
		uart_write(" / ",3);
		uart_write("V_mesR=",7);
		uart_writeNb(myMovement.v_R);
		uart_write("\n\r",2);
		uart_write("#####cam#####\n\r",15);
		uart_write("diff=",5);
		uart_writeNb(cam.diff);
		uart_write(" / ",3);
		uart_write("L=",2);
		uart_writeNb(cam.BlackLineLeft);
		uart_write(" / ",3);
		uart_write("R=",2);
		uart_writeNb(cam.BlackLineRight);
		uart_write(" / ",3);
		uart_write("nb_cote=",8);
		uart_writeNb(cam.number_edges);
		uart_write(" / ",3);
		uart_write("seuil=",6);
		uart_writeNb(cam.threshold);
		uart_write(" / ",3);
		uart_write("delta=",6);
		uart_writeNb(cam.delta);
		/*uart_write(" ",1);
		uart_writeNb(cam.diff-cam.diff_old);
		uart_write(" ",1);
		uart_writeNb(cam.diff);
		uart_write(" ",1);*/
		
		//uart_write(" ",1);
		//uart_writeNb(cam.RoadMiddle);
		//uart_write(";",1);
		uart_write("\n\r",2);
		uart_write("\n\r",2);
	}
	
	FLAG_SEND_IMG=false;
}

//On choisit les param de débug (ex x:mode_speed +:plus vite etc....)
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
					stop=1;
					uart_write("Arret!",6);
					uart_write("\r\n",2);
					n=0;
					break;
				case 13:	//GO! touche entrée
					stop=0;
					uart_write("Demarre!  ",10);
					Aff_debug_init();
					uart_write("Vset : ",7);
					uart_writeNb(Vset);
					n=0;
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
					FLAG_ENABLE_LOG_SERVO=!FLAG_ENABLE_LOG_SERVO;
					if (FLAG_ENABLE_LOG_SERVO){
						uart_write("debug_servo_on\n\r",16);
					}else{
						uart_write("debug_servo_off\n\r",17);
					}
					FLAG_ENABLE_LOG_IMG=false;
					break;
				case 'v':
					FLAG_SEND_IMG=true;
					break;
				case 'f':
					enable_finish=!(enable_finish);
					uart_write("EN_finish=",10);
					uart_writeNb(enable_finish);
					uart_write("\r\n",2);
					break;
				default:
					break;
				}
			}
}

void Car::Aff_debug_init(void){
	uart_write("Vset : ",7);
	uart_writeNb(Vset);
	uart_write(" / ",3);
	
	uart_write("Vhigh : ",7);
	uart_writeNb(Vhigh);
	uart_write(" / ",3);
	
	uart_write("Vslow : ",7);
	uart_writeNb(Vslow);
	uart_write("\r\n",2);
	
	if(mode_speed==0){
		uart_write("speed_mano\n\r",12);
		
	}else if(mode_speed==1){
		uart_write("speed_auto\n\r",12);
	}else{
		uart_write("speed_auto_incr\n\r",17);		
	}

	uart_write("EN_finish=",10);
	uart_writeNb(enable_finish);
	uart_write("\r\n",2);
}

//################ IT ###################
void Car::Demarre(void){
	mode_speed=1;
	enable_finish=true;
	stop=0;
}

//########### others ###############

int sng(int a){
	if (a<=0){
		return 1;
	}else{
		return -1;
	}
}
