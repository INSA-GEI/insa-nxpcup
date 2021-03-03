#include "Car_control.h"
#include "Debug.h"

/* RIO 2020-2021*/


//#################################### Var ###################
//################ var aux #############
int c=0;
float old_servo_angle=0.0;
//Wheel PI
float K_camdiff=0.0;
float K_camdiffold=0.0;

int n=0;//Allow us to use the debug with Putty

//Not implemented yet
int Count=0; //count how many time we were not to close to the black line

int C_finish=0;

//Debug Flag
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
	mode_speed=1; //0 : manu, 1: auto, 2: auto incr
	delta_speed=0;
	mode_debug=0;
	state_turn_car=0;
	enable_ampli_turn=false;
	enable_brake=false;
	
	//Coeff PI servo_angle
	K_camdiff=(float)((2*K+Te*Ki)/2);
	K_camdiffold=(float)((Te*Ki-2*K)/2);
	
	enable_finish=false;
	stop=true;
}

//############### SPEED ########################

//Calcule la consigne de vitesse en fonction de l'angle des roues
//Le correcteur est pr�sent dans Movement.cpp =>regulate()
void Car::Calculate_speed(void){
	//Linear mode
	V_old=abs(Vset);
				
	Vset=(int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle))+Vhigh;		
	if (enable_brake){
		Vset=-(abs(Vset-V_old))-Vslow;
	}else if (Vset>V_old+INCREMENT_SPEED){
		if ((V_old<(Vhigh+Vset)/2)){
			Vset=V_old+(int)(INCREMENT_SPEED/DIV_1_SPEED); //Temps de mont�e max 100ms//�vite de glisser
		}else{
			Vset=V_old+INCREMENT_SPEED;
		}
	}
	if (state_turn_car==3){
		Vset=Vslow;
	}
}

//Calcul Vslow et Vhigh et renvoie � Calculate_speed
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

//Calcul et instancie la vitesse du diff�rentiel
void Car::Set_diff_speed(void){
	//Calcul du diff
	//We calculate the delta_speed of the rear wheels
	//delta_speed=servo_angle*MOVEMENT_ENTRAXE_COEFF*Vset;
	//##################### Changement ############
	if (state_turn_car==0){
		//Strait line
		delta_speed=0;
	}else if(state_turn_car==2){
		//Hard turn => 
		float r=LENGHT_CAR/(abs(servo_angle)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(Vset*L_ENTRAXE)/(1.5*r+L_ENTRAXE);//On l'aide � tourner
	}else{
		//Soft turn
		float r=LENGHT_CAR/(abs(servo_angle)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(Vset*L_ENTRAXE)/(2.0*r+L_ENTRAXE);//th�orique 
	}
	
	//Left turn servoangle<0
	if (servo_angle<0){
		delta_speed=-delta_speed;
	}
}

//##################### Wheels ###############
//Calcul la commande des roues et op�re un PI avant de stocker la valeur dans servo_angle
void Car::Caculate_angle_wheel(void){
	
	int aux_diff=cam.diff;
	// plausibility check
	if (abs (cam.diff - cam.diff_old) > 2*MAX_CAM_DIFF){
		cam.diff = cam.diff_old;
		uart_write("pb_detect !",11);
		uart_write("\n\r",2);
	}else{
		if (enable_ampli_turn){
			int aux=0;
			if (state_turn_car==1){
				aux=AMPLIFIE_TURN_1;
			}else if(state_turn_car==2){
				aux=AMPLIFIE_TURN_2;
			}
			if (servo_angle<0){
				aux_diff-=aux;
			}else{
				aux_diff+=aux;
			}
		}
		old_servo_angle=servo_angle;
		//PI Approx bilin�aire

		servo_angle=servo_angle+(float)aux_diff*K_camdiff+(float)cam.diff_old*K_camdiffold;

//##################### Changement valeurs  ##########################
		if(servo_angle<-MAX_ANGLE)servo_angle=(-MAX_ANGLE);
		if(servo_angle>MAX_ANGLE)servo_angle=MAX_ANGLE;
	}
}

//############# Test Turn? strait line? Brake? ##################
//Fait l'acquisition des donn�es
//return 	: 	V_mes
//			:	cam (� jour)
void Car::Process_data(void){
	V_mes=(int)(myMovement.encoder.getLeftSpeed()+myMovement.encoder.getRightSpeed())/2;
	cam.processAll();
}

//Permet la dectection de l'�tat et de o� se trouve la voiture
//return 	: state_car_turn : 0/1/2
//			:enable_brake :true/false
//			:enable_ampli_turn :true/false
void Car::Detect_state(void){
	
	//Test braking #####################################
	if (Vset<V_old-T_BRAKE && abs(V_mes)>TURN_SPEED){
		enable_brake=true;	
	}else if(abs(V_mes)<TURN_SPEED){
		enable_brake=false;
	}
	
	int old=state_turn_car;
	
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
	
	//Amplify the turn in Calculate_angle_wheels
	if ((old==state_turn_car && state_turn_car==2) || (cam.BlackLineRight==128 || cam.BlackLineLeft==-1)){
		if (!(enable_ampli_turn)){
			DEBUG_BLUE_ON;
			enable_ampli_turn=true;
			//uart_write("amp_turn !",10);
			//uart_write("\n\r",2);
		}
	}else if (state_turn_car==0 || Vset>TURN_SPEED){
		DEBUG_BLUE_OFF;
		enable_ampli_turn=false;
	}
	
	//######## Test finish ############
	if (enable_finish){
		if ((cam.number_edges)==4 && state_turn_car!=2){//Nb de bandes noires (+1 pour chaque c�t�)
			finish=true;
			uart_write("Fin !",5);
		}
	}
}

//Actualise le d�placement gr�ce � l'objet myMovement
//La vitesse peut �tre n�gative (si freiange) ou positive, tout est param�tr� dans Movement.cpp
//Arg : finish :true/false <= m�j dans Detect_state()

void Car::Set_deplacement(void){
	//########### On actualise le d�placement #################
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
			}
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
	if(c>500){
		c=0;		
	}
	//
	Process_data();//Acquisition des donn�es
	//On regarde si on est en ligne droite ou non
	Detect_state();
	if (!(stop)){
		//On met � jour les param de la voiture
		Caculate_angle_wheel();	
		//We calculate the speed
		Set_speed();
		//Calcul du diff en fonction
		Set_diff_speed();
	}else{
		//FLAG_SEND_IMG=true;
	}
	//Debug
	Aff_debug();
	//We refresh the deplacement's parameters. Speed +wheels Angle
	Set_deplacement();
}

//#################### Debug ###############################
//Permet de modifier le mode de d�bug et du coup l'affichage dans Putty
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

//Affiche le d�bug
void Car::Aff_debug(void){
	if(FLAG_SEND_IMG && FLAG_ENABLE_LOG_IMG){
		for(int i=0;i<128;i++){
			// /!\ marche 1 fois sur 2 car on utilise en m�me temps les vecteurs pour stocker l'image si l'IT suivante est arriv�e
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
	/*if (Vset<0){
		uart_write("Brake ! ",8);
		uart_write("Vset : ",7);
		uart_writeNb(Vset);
		uart_write(" / ",3);
		uart_write("Vold : ",7);
		uart_writeNb(V_old);
		uart_write(" / ",3);
		uart_write("V_mes : ",7);
		uart_writeNb(V_mes);
		uart_write("\r\n",2);
	}*/
	FLAG_SEND_IMG=false;
}

//On choisit les param de d�bug (ex x:mode_speed +:plus vite etc....)
void Car::Car_debug(void){
	char str[10];
	
			if(uart_read(str,1)>0){
				switch(str[0]){
				case 'p':	//Vset +
					Vset += 250;
					uart_write("Vset : ",7);
					uart_writeNb(Vset);
					uart_write("\r\n",2);
					n++;
					break;
				case 'm':	//Vset -
					Vset -= 250;
					uart_write("Vset : ",7);
					uart_writeNb(Vset);
					uart_write("\r\n",2);
					n--;
					break;
				case 'o':	//Vhigh +
					Vhigh+=100;
					uart_write("Vhigh : ",7);
					uart_writeNb(Vhigh);
					uart_write("\r\n",2);
					break;
				case 'l':	//Vhigh -
					if (Vhigh>Vslow){
						Vhigh-=100;
					}
					uart_write("Vhigh : ",7);
					uart_writeNb(Vhigh);
					uart_write("\r\n",2);
					break;
				case 'i':	//Vslow +
					if (Vslow<Vhigh){
						Vslow+=100;
					}
					uart_write("Vslow : ",7);
					uart_writeNb(Vslow);
					uart_write("\r\n",2);
					break;
				case 'k':	//Vslow -
					if (Vslow>200){
						Vslow-=100;
					}else{
						Vslow=0;
					}
					uart_write("Vslow : ",7);
					uart_writeNb(Vslow);
					uart_write("\r\n",2);
					break;
				case ' ':	//Start & Stop
					if (stop == 0) {
						stop=1;
						uart_write("Arret!\r\n",10);
						n=0;
					}
					else {
						stop=0;
						uart_write("Demarre!\r\n",12);
						Vset = 1250;
						Aff_debug_init();
						n=0;
					}
					break;
				case 'x':	//Change speed mode
					if(mode_speed==0){
						mode_speed=1;
						uart_write("Speed auto\r\n",12);
					}else if(mode_speed==1){
						mode_speed=2;
						uart_write("Speed auto incr\r\n",17);
					}else{
						mode_speed=0;
						Vset=Vslow;
						uart_write("Speed manu\r\n",12);
					}
					break;
				/*
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
				case 'f':
					enable_finish=!(enable_finish);
					uart_write("EN_finish=",10);
					uart_writeNb(enable_finish);
					uart_write("\r\n",2);
					break;*/
				default:
					break;
				}
			}
}

void Car::Aff_debug_init(void){
	uart_write("Vset : ",7);
	uart_writeNb(Vset);
	uart_write("\r\n",4);
	
	uart_write("Vhigh : ",7);
	uart_writeNb(Vhigh);
	uart_write("\r\n",4);
	
	uart_write("Vslow : ",7);
	uart_writeNb(Vslow);
	uart_write("\r\n",4);
	
	if(mode_speed==0){
		uart_write("Speed manu\r\n",12);
	}else if(mode_speed==1){
		uart_write("Speed auto\r\n",12);
	}else{
		uart_write("Speed auto incr\r\n",17);		
	}

	//uart_write("EN_finish=",10);
	//uart_writeNb(enable_finish);
	//uart_write("\r\n",2);
}

//########### others ###############

int sng(int a){
	if (a<=0){
		return 1;
	}else{
		return -1;
	}
}
