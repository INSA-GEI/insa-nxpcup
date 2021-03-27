#include "Car_control.h"
#include "Debug.h"

//#################################### Var ###################
int c=0;
float old_servo_angle=0.0;
int n=0;	//Allow us to use the debug with Putty/XCTU
int C_finish=0;

//Debug Flag
bool FLAG_START_DEBUG = false;

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

	// PID
	PID_max = MAX_ANGLE;
	PID_min = -MAX_ANGLE;
	Integrator = 0.0;
	old_error = 0.0;
	Differentiator = 0.0;
	old_measurement = 0.0;
	PID_output = 0.0;
	
	enable_finish=false;
	stop=true;
}

//############### SPEED ########################

//Calcule la consigne de vitesse en fonction de l'angle des roues
//Le correcteur est présent dans Movement.cpp =>regulate()
void Car::Calculate_speed(void){
	//Linear mode
	V_old=abs(Vset);
				
	Vset=(int)((-(Vhigh-Vslow))/MAX_ANGLE)*(abs(servo_angle))+Vhigh;		
	if (enable_brake){
		Vset=-(abs(Vset-V_old))-Vslow;
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
	//delta_speed=servo_angle*MOVEMENT_ENTRAXE_COEFF*Vset;
	//##################### Changement ############
	if (state_turn_car==0){
		//Strait line
		delta_speed=0;
	}else if(state_turn_car==2){
		//Hard turn => 
		float r=LENGHT_CAR/(abs(servo_angle)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(Vset*L_ENTRAXE)/(1.5*r+L_ENTRAXE);//On l'aide à tourner
	}else{
		//Soft turn
		float r=LENGHT_CAR/(abs(servo_angle)*DEG_TO_RAD); //r=radius of the turn
		delta_speed=(Vset*L_ENTRAXE)/(2.0*r+L_ENTRAXE);//théorique 
	}
	
	//Left turn servoangle<0
	if (servo_angle<0){
		delta_speed=-delta_speed;
	}
}

//##################### Wheels ###############
//Calcul la commande des roues et opère un PI avant de stocker la valeur dans servo_angle
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

		// PID -> Consigne de 0 (rester au milieu)
		servo_angle = PIDController_update(0, cam.diff);

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
	V_mes=(int)(myMovement.encoder.getLeftSpeed()+myMovement.encoder.getRightSpeed())/2;
	cam.processAll();
}

//Permet la dectection de l'état et de où se trouve la voiture
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
		if ((cam.number_edges)==4 && state_turn_car!=2){//Nb de bandes noires (+1 pour chaque côté)
			finish=true;
			uart_write("Fin !",5);
		}
	}
}

//Actualise le déplacement grâce à l'objet myMovement
//La vitesse peut être négative (si freinage) ou positive, tout est paramétré dans Movement.cpp
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
	Process_data();//Acquisition des données
	//On regarde si on est en ligne droite ou non
	Detect_state();
	if (!(stop)){
		//On met à jour les param de la voiture
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

//Affiche le débug
void Car::Aff_debug(void){
	if(FLAG_START_DEBUG){
		uart_write("#####car#####\n\r",15);
		uart_write("Vset=",5);
		uart_writeNb(Vset);
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
		uart_write("ecart type=",11);
		uart_writeNb(cam.ecart_type);
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
	FLAG_START_DEBUG = false;
}

//On choisit les param de débug (ex x:mode_speed +:plus vite etc....)
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
						Vset = 1000;
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
				case 'd':	// Debug
					FLAG_START_DEBUG = true;
					break;
				case 'g':	// Lights toggle
					uart_write("Lights ON\r\n",13);
					DEBUG_CAM_LED_ON;
					break;
					/*
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


//########### PID ###############
float Car::PIDController_update(float setpoint, float measurement) {
	
	// ########## Error signal ########## //
	float error = setpoint - measurement;
	
	// ########## Proportional ########## //
	float Proportional = Kp * error;
	
	// ########## Integral ########## //
	Integrator = Integrator + 0.5 * Ki * Te * (error + old_error);
	
	// Anti wind-up via clamping
		// Compute limits
	/*if (PID_min > Proportional) integrator_max = PID_max - Proportional;
	else integrator_max = 0.0;
	
	if (PID_min < Proportional) integrator_min = PID_min - Proportional;
	else integrator_min = 0.0;
	
		// Clamp Integrator
	if (Integrator > integrator_max) Integrator = integrator_max;
	else if (Integrator < integrator_min) Integrator = integrator_min;*/
	
	
	// ########## Derivative ########## //
	// Note : on measurement !!
//	Differentiator = -(2.0 * Kd * (measurement - old_measurement)
//					 +(2.0 * tau - Te) * Differentiator)
//					 /(2.0 * tau + Te);
	Differentiator = (2.0 * Kd * (measurement - old_measurement)
					 +(Te) * Differentiator)
					 /(Te);
	
	
	
	// ########## Output ########## //
	// Compute & apply limits
	PID_output = Proportional + Integrator + Differentiator;
	if (PID_output > PID_max) PID_output = PID_max;
	if (PID_output < PID_min) PID_output = PID_min;
	
	// Store error and measurement
	old_error = error;
	old_measurement = measurement;
	
	return PID_output;	
}


