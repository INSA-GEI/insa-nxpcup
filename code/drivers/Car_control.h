
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

#include "Movement.h"
#include "ImageProcessing.h"


#define INCREASE_SPEED_MAX_MIN 400//Nb of time ok before we increase the speed handler every 10ms
#define MAX_DIFF_BEFORE_SLOWDOWN 10 
#define MAX_ANGLE 30.0

//######### ESP ####################################
#define LIMIT_ESP 5 //between 1 and 10
#define TIME_ACTIVE_ESP	50 //+10)*10ms
#define COEFF_ANGLE_ESP 4.0 //Angle = Max_angle/coeff_angle_esp

//#################### SPEED #############################
#define VSLOW 800
#define VHIGH 3500
//#define VSET 0
#define T_BRAKE 200 //Threshold before braking
#define INCREMENT_SPEED 40
#define TURN_SPEED 1100


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
	
	int ESP;
	bool detect_ESP;
	bool active_ESP;
	
	bool enable_brake;
	
	float delta_speed;//Value for the rear differential
	
	int mode_speed;//Mode 0=>speed manual //1=> speed auto
	
	//functions
	void init(void);
	void Caculate_angle_wheel(void);
	void Set_deplacement(void);
	void Car_debug(void);
	void Car_handler(void);
	void processESP(void);

private:
	void Set_speed(void);
	void Set_diff_speed(void);
	int mode_debug;
	void Set_debug_mode(int i); //i=>0 : Cam+ange_servo  //i=>1 : Cam[i] //i=>2 : 
	void Aff_debug(void);
};

int sng(int a);

//####################### Wheels #################################

#define K 								1.8 //2 //P of the PI
#define Ki								1 //I of the PI



#endif /* CAR_CONTROL_H_ */
