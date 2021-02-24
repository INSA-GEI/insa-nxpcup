
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_
/* RIO 2020-2021*/
#include "Movement.h"
#include "ImageProcessing.h"
#include "Interrupt.h"

#define CST_FINISH_TIME 100 //100*10ms=>1s

#define INCREASE_SPEED_MAX_MIN 400//Nb of time ok before we increase the speed handler every 10ms
#define MAX_DIFF_BEFORE_SLOWDOWN 10 
#define MAX_ANGLE 30.0
#define MAX_CAM_DIFF 20

//####################### Wheels #################################
#define Kp 								1.5 	//PI=1.8 //entre 1.3 et 2.0 //P of the PID
#define Ki								0.05//0.05		//PI=0.9 // 1.5 max	 //I of the PID
#define Kd								0.15//0.15		//Dérivée
#define N								7.0 	//Filtre dérivée

//#################### SPEED #############################
#define Te_calc_speed 	0.01 //100Hz Consigne Vset

#define VSLOW 1000
#define VHIGH 2500
#define VBRAKE_min 8000

#define T_BRAKE 200 //Threshold before braking
#define INCREMENT_SPEED 40 //Constante d'augmentation de la vitesse (évite le patinage)
#define DIV_1_SPEED 3 //Divise la consigne de vitesse pour éviter le patinage sur la premiere moitié Vmes=[Vslow,Vhigh/2]
#define SPEED_BRAKE_BEG 1300 //Vitesse seuil dans les virages
#define SPEED_BRAKE_END 100 //Vitesse seuil dans les virages


#define DEG_TO_RAD 0.0175 //conversion Degré vers radian

#define CARRE(x) ((x)*(x))

class Car{
public:
	//Objects
	Movement myMovement;
	Img_Proc cam;
	
	Car();
	
	//############# functions #########################
		void init(float Te);
		
		//Process acquisiton des données
		void Process_data(void);
		
		//Actualise le déplacement grâce à l'objet myMovement
		//La vitesse peut être négative (si freiange) ou positive, tout est paramétré dans Movement.cpp
		//Arg : finish :true/false <= màj dans Detect_state()
		void Set_deplacement(void);
		
		//Process every actions (set speed,angle wheels etc) for the car every 10ms
		void Car_handler(void);
		
		//choix des options de Putty
		void Car_debug(void); //Commande Putty
		
		//Debug
		int mode_debug;
		void Set_debug_mode(int i); //i=>0 : Cam+ange_servo  //i=>1 : Cam[i] //i=>2 : 
		void Aff_debug(void);
		void Aff_debug_init(void);
		
		void Demarre(void);

private:
		//###### var #####
			bool enable_finish;
			bool finish;//indicates if we are at the end of the circuit
			
			bool stop;
			
			//############ angle wheels ###########
			float servo_angle;
			float servo_angle_moy;
			bool enable_ampli_turn;
			
			//######### Speed ###############
				//Speed of the car
				int Vset;//=0
				int V_old;
				int V_mes;
				//Speed in turn
				int Vslow;//=500
				//Speed in strait line
				int Vhigh;//=1500
				bool enable_brake;
				
				float delta_speed;//Value for the rear differential
				
				int mode_speed;//Mode 0=>speed manual //1=> speed auto
			
			//########## ESP #############
				int ESP;
				bool detect_ESP;
				bool active_ESP;
	
	//########### wheels angle #############
		//Calcul la commande des roues et opère un PI avant de stocker la valeur dans servo_angle
		void Caculate_angle_wheel(void);
	
	//################ Speed ############
		//Calcule la consigne de vitesse en fonction de l'angle des roues
		//Le correcteur est présent dans Movement.cpp =>regulate()
		void Calculate_speed(void); 
		//Calcul Vslow et Vhigh (pas encore opérationnel) et renvoie à Calculate_speed
		void Set_speed(void);
		//Calcul et instancie la vitesse du différentiel
		void Set_diff_speed(void);
	
	//######### State of the car ###########
		int state_turn_car; //2=>hard turn //1 soft turn //0=>strait line
		void Detect_state(void); //Detect the turns //Detect slip (ie ESP) only in strait lines
		
		
};

int sng(int a);

#endif /* CAR_CONTROL_H_ */
