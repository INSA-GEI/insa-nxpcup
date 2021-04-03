#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

#include "Movement.h"
#include "ImageProcessing.h"

#define CST_FINISH_TIME 100 //100*10ms=>1s

#define Te 0.01 //sample time 10ms handler servos /!\ Te_s (sample time for rear motors is in Movement.h)
#define DEG_TO_RAD 0.0175 //conversion Degré vers radian

#define CARRE(x) ((x)*(x))





class Car{
public:
	//########### Objects ###########//
	Movement myMovement;
	Img_Proc cam;
	
	//########### Variables ###########//
	bool enable_finish;
	bool finish;//indicates if we are at the end of the circuit
	bool stop;
	
	// Angle wheels
	float servo_angle;
	bool enable_ampli_turn;
	

	//  Wheels
	float AMPLIFIE_TURN_1;	// Constante pour amplifier les virages tranquilles (s'ajout ou se soustrait à cam.diff)
	float AMPLIFIE_TURN_2;	// Constante pour amplifier les virages serrés (s'ajout ou se soustrait à cam.diff) - 5 Original
	float MAX_ANGLE;		// 30 Original
	int MAX_CAM_DIFF;		// 20 Original
	
	// Speed
		int T_BRAKE; 			//Threshold before braking - 200 Original
		int INCREMENT_SPEED;	//Constante d'augmentation de la vitesse (évite le patinage) - 40 Original
		int DIV_1_SPEED; 		//Divise la consigne de vitesse pour éviter le patinage sur la premiere moitié Vmes=[Vslow,Vhigh/2]	- 3 Original
		int TURN_SPEED; 		//Vitesse seuil dans les virages - 1300 Original


		bool enable_brake;
		
		//Speed of the car
		int Vset;
		int V_old;
		int V_mes;
		int Vslow;			//Speed in turns
		int Vhigh;			//Speed in strait lines
		int mode_speed;		//0 : manu, 1: auto, 2: auto incr
		float delta_speed;	//Value for the rear differential
	
	// PID baby !
		// Gains
		float Kp;
		float Ki;
		float Kd;
		
		// Saturation
		float PID_max, PID_min;
		float integrator_max, integrator_min;
					
		// Controller 'memory'
		float Integrator;
		float old_error;
		float Differentiator;
		float old_measurement;
			
		// Controller output
		float PID_output;

		float PIDController_update(float setpoint, float measurement);
	
	//########### Functions ###########//
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
	
	// Angle wheels
		//Calcul la commande des roues et opère un PI avant de stocker la valeur dans servo_angle
		void Caculate_angle_wheel(void);
	
	// Speed
		//Calcule la consigne de vitesse en fonction de l'angle des roues
		//Le correcteur est présent dans Movement.cpp =>regulate()
		void Calculate_speed(void); 
		//Calcul Vslow et Vhigh (pas encore opérationnel) et renvoie à Calculate_speed
		void Set_speed(void);
		//Calcul et instancie la vitesse du différentiel
		void Set_diff_speed(void);
	
	// State of the car
		int state_turn_car; //2=>hard turn //1 soft turn //0=>strait line
		void Detect_state(void); //Detect the turns //Detect slip (ie ESP) only in strait lines
		void Process_data(void);
		
	// Debug
		int mode_debug;
		void Aff_debug(void);
		void Aff_debug_init(void);
		
};

// Others
int sng(int a);

#endif /* CAR_CONTROL_H_ */
