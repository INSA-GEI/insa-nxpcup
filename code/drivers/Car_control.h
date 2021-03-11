
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_
/* RIO 2020-2021*/
#include "Movement.h" 
#include "ImageProcessing.h"
#include "Interrupt.h"

#define CST_FINISH_TIME 100 //X*10ms=>

#define INCREASE_SPEED_MAX_MIN 		400	//Nb of time ok before we increase the speed handler every 10ms
#define MAX_DIFF_BEFORE_SLOWDOWN 	10 
#define MAX_ANGLE 					30.0
#define MAX_CAM_DIFF 				20
#define NB_LIGNES_FIN 				4
#define NB_LIGNES_NORMAL			2
#define NB_LIGNES_MAX_PB 			5
#define NB_LIGNES_MIN_PB			1

//####################### Wheels #################################
#define Kp 								1.5 	//PI=1.8 //entre 1.3 et 2.0 //P of the PID
#define Ki								0.05//0.05		//PI=0.9 // 1.5 max	 //I of the PID
#define Kd								0.15//0.15		//Dérivée
#define N								7.0 	//Filtre dérivée

//#################### SPEED #############################
#define Te_calc_speed 	0.01 //100Hz Consigne Vset //Frequence du calcul de vitesse

#define VSLOW 900
#define VHIGH 1800
#define VBRAKE_min 1500

#define T_BRAKE 600 //Threshold before braking
#define INCREMENT_SPEED 12 //Constante d'augmentation de la vitesse (évite le patinage)
#define SPEED_BRAKE_BEG 1000 //Vitesse seuil dans les virages
#define SPEED_BRAKE_END 500 //Vitesse seuil dans les virages


#define DEG_TO_RAD 0.0175 //conversion Degré vers radian

#define CARRE(x) ((x)*(x))

class Car{
public:
	//Objects
	Movement myMovement;
	Img_Proc cam;
	
	Car(); //CONSTRUCTEUR
	
	// ############ VAR ETAT ################
		bool low_batt;
		int Increment_speed;
		int MODE_car;
		
	//############# functions #########################
		void init(float Te,int MODE);
		void Demarre(void);
		void Stop(void);
		void Reset(void);
		
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
		void Set_debug_mode(int i); //i=>0 : Cam+ange_servo  //i=>1 : Cam[i] //i=>2 : 
		void Aff_debug(void);
		void Aff_debug_init(void);
		
private:
	//###### var #####
		// ###### Etat #########
			bool enable_finish;
			bool finish;//indicates if we are at the end of the circuit
			bool stop;
			bool reset;
			
			
		//############ angle wheels ###########
			float servo_angle;
			float servo_angle_moy;
		
		//######### Speed ###############
			//Speed of the car
			int Vset;//=0
			int V_old;
			int V_mes;
			int V_apply;
			//Speed in turn
			int Vslow;//=500
			//Speed in strait line
			int Vhigh;//=1500
			bool enable_brake;
			
			float delta_speed;//Value for the rear differential
			
			int mode_speed;//Mode 0=>speed manual //1=> speed auto
		
		//######### State of the car ###########
			int state_turn_car; //2=>hard turn //1 soft turn //0=>strait line
			
		//############ Debug #################
			int mode_debug;
			
	//############# FONCTIONS ###############
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
			void Detect_state(void); //Detect the turns //Detect slip (ie ESP) only in strait lines
};

int sng(int a);

#endif /* CAR_CONTROL_H_ */
