
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_
/* RIO 2020-2021*/
#include "Movement.h"
#include "ImageProcessing.h"


#define INCREASE_SPEED_MAX_MIN 400//Nb of time ok before we increase the speed handler every 10ms
#define MAX_DIFF_BEFORE_SLOWDOWN 10 
#define MAX_ANGLE 30.0
#define MAX_CAM_DIFF 20

//####################### Wheels #################################
#define K 								1.8//1.8 //2 //P of the PID
#define Ki								1.0 //1.0 //I of the PID

#define AMPLIFIE_TURN_1 0 //Constante pour amplifier les virages tranquilles (s'ajout ou se soustrait à cam.diff)
#define AMPLIFIE_TURN_2 5 //Constante pour amplifier les virages serrés (s'ajout ou se soustrait à cam.diff)

//######### ESP ####################################
#define LIMIT_ESP 3 //between 2 and 10
#define TIME_ACTIVE_ESP	50 //+10)*10ms
#define COEFF_ANGLE_ESP 5.0 //Angle = Max_angle/coeff_angle_esp

//#################### SPEED #############################
#define VSLOW 800
#define VHIGH 3500
//#define VSET 0
#define T_BRAKE 200 //Threshold before braking
#define INCREMENT_SPEED 30 //Constante d'augmentation de la vitesse (évite le patinage)
#define TURN_SPEED 1200 //Vitesse seuil dans les virages



#define Te 0.01 //sample time 10ms handler servos /!\ Te_s (sample time for rear motors is in Movement.h)
#define DEG_TO_RAD 0.0175 //conversion Degré vers radian

#define CARRE(x) ((x)*(x))

class Car{
public:
	//Objects
	Movement myMovement;
	Img_Proc cam;
	
	//###### var #####
	bool enable_finish;
	bool finish;//indicates if we are at the end of the circuit
	
	//############ angle wheels ###########
	float servo_angle;
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
	
	
	//############# functions #########################
		void init(void);
		
		//Tente de détecter des oscillations dans les lignes droites dû au patinage des roues
		//return : modifie Vset
		void processESP(void);
		
		//Actualise le déplacement grâce à l'objet myMovement
		//La vitesse peut être négative (si freiange) ou positive, tout est paramétré dans Movement.cpp
		//Arg : finish :true/false <= màj dans Detect_state()
		void Set_deplacement(void);
		
		//Process every actions (set speed,angle wheels etc) for the car every 10ms
		void Car_handler(void);
		
		//choix des options de Putty
		void Car_debug(void); //Commande Putty

private:
	
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
		void Process_data(void);
		
		//Debug
		int mode_debug;
		void Set_debug_mode(int i); //i=>0 : Cam+ange_servo  //i=>1 : Cam[i] //i=>2 : 
		void Aff_debug(void);
};

int sng(int a);

#endif /* CAR_CONTROL_H_ */
