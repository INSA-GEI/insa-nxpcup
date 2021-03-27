#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

#include "Movement.h"
#include "ImageProcessing.h"

#define CST_FINISH_TIME 100 //100*10ms=>1s

//####################### Wheels #################################
//#define K 								1.6	//P of the PI -> Vitesse vers le point d'équilibre - 1.6 Original
//#define Ki								0.8 	//I of the PI -> Vitesse à laquelle il va tourner  - 1 Original

#define AMPLIFIE_TURN_1 2	// Constante pour amplifier les virages tranquilles (s'ajout ou se soustrait à cam.diff)
#define AMPLIFIE_TURN_2 5	// Constante pour amplifier les virages serrés (s'ajout ou se soustrait à cam.diff) - 5 Original
#define MAX_CAM_DIFF 30		// 20 Original
#define MAX_ANGLE 30.0		// 30 Original


//#################### SPEED #############################
#define VSLOW 1200	// 1000 Original
#define VHIGH 2500	// 2500 Original
#define T_BRAKE 200 //Threshold before braking - 200 Original
#define INCREMENT_SPEED 40 //Constante d'augmentation de la vitesse (évite le patinage) - 40 Original
#define DIV_1_SPEED 3 //Divise la consigne de vitesse pour éviter le patinage sur la premiere moitié Vmes=[Vslow,Vhigh/2]	- 3 Original
#define TURN_SPEED 1400 //Vitesse seuil dans les virages - 1300 Original



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
	
	bool stop;
	
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
	
	
	//############# functions #########################
		void init(void);
		
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
		void Aff_debug(void);
		void Aff_debug_init(void);
};

int sng(int a);

#endif /* CAR_CONTROL_H_ */
