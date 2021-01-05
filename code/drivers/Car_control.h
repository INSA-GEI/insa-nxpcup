
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_
/* RIO 2020-2021*/
#include "Movement.h"
#include "ImageProcessing.h"


#define INCREASE_SPEED_MAX_MIN 400//Nb of time ok before we increase the speed handler every 10ms
#define MAX_DIFF_BEFORE_SLOWDOWN 10 
#define MAX_ANGLE 30.0
#define MAX_CAM_DIFF 20

//######### ESP ####################################
#define LIMIT_ESP 4 //between 2 and 10
#define TIME_ACTIVE_ESP	50 //+10)*10ms
#define COEFF_ANGLE_ESP 5.0 //Angle = Max_angle/coeff_angle_esp

//#################### SPEED #############################
#define VSLOW 800
#define VHIGH 3500
//#define VSET 0
#define T_BRAKE 200 //Threshold before braking
#define INCREMENT_SPEED 40
#define TURN_SPEED 1200
#define AMPLIFIE_TURN 10


#define Te 0.01 //sample time 10ms handler rear motors
#define DEG_TO_RAD 0.0175

#define CARRE(x) ((x)*(x))

class Car{
public:
	//Objects
	Movement myMovement;
	Img_Proc cam;
	
	//###### var #####
	bool finish;//indicates if we are at the end of the circuit
	float servo_angle;
	//Speed of the car
	int Vset;//=0
	int V_old;
	int V_mes;
	//Speed in turn
	int Vslow;//=500
	//Speed in strait line
	int Vhigh;//=1500
	
	//Etat
	int state_turn_car;
	
	int ESP;
	bool detect_ESP;
	bool active_ESP;
	
	bool enable_brake;
	
	bool enable_ampli_turn;
	
	float delta_speed;//Value for the rear differential
	
	int mode_speed;//Mode 0=>speed manual //1=> speed auto
	
	//functions
	void init(void);
	
	
	void processESP(void);
	
	void Set_deplacement(void);
	//Process every actions (set speed,angle wheels etc) for the car every 10ms
	void Car_handler(void);
	
	//debug
	void Car_debug(void); //Commande Putty

private:
<<<<<<< HEAD
	void Calculate_speed(void);
=======
	//PID direction
	float Ywi;
	float Ywd;
	
	//PID speed
	float e;
	float e_old;
	float Ysi;
	float Ysd;
	
	//########### wheels angle #############
	void Caculate_angle_wheel(void);
	//################ Speed ############
	void Calculate_speed(void); //PID
>>>>>>> e2bb5fc9f22e2e7ce99f1449e2e55b72208af524
	void Set_speed(void);
	void Set_diff_speed(void);
	
	//######### State of the car ###########
	int state_turn_car; //2=>hard turn //1 soft turn //0=>strait line
	void Detect_state(void); //Detect the turns //Detect slip (ie ESP) only in strait lines
	
	
	//Debug
	int mode_debug;
	void Set_debug_mode(int i); //i=>0 : Cam+ange_servo  //i=>1 : Cam[i] //i=>2 : 
	void Aff_debug(void);
	void Detect_state(void);
};

int sng(int a);

//####################### Wheels #################################

<<<<<<< HEAD
#define K 								1.8 //2 //P of the PID
#define Ki								1.0 //I of the PID
=======
#define K 								1.8 //1.8 //P of the PI
#define Ki								1 //1 //I of the PI
#define Kd								1 //D of PID
#define N_Kd							10//filtre D PID

//PID speed
#define K_s 							1.8 //1.8 //P of the PI
#define Ki_s							1 //1 //I of the PI
#define Kd_s							1 //D of PID
#define N_Kd_s							10//filtre D PID
>>>>>>> e2bb5fc9f22e2e7ce99f1449e2e55b72208af524


#endif /* CAR_CONTROL_H_ */
