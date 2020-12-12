
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

#include "Movement.h"
#include "ImageProcessing.h"

#define VSLOW 800
#define VHIGH 1500
#define VSET 0
#define INCREASE_SPEED 400//Nb of time ok before we increase the speed handler every 10ms
#define MAX_ANGLE_BEFORE_SLOWDOWN 8 
#define MAX_ANGLE 30.0

#define Te 0.01 //sample time 10ms handler rear motors
#define DEG_TO_RAD 0.0175

class Car{
public:
	//Objects
	Movement myMovement;
	Img_Proc cam;
	
	//###### var #####
	bool finish;//indicates if we are at the end of the circuit
	float servo_angle;
	//Speed of the car
	unsigned int Vset;//=0
	unsigned int V_old;
	//Speed in turn
	unsigned int Vslow;//=500
	//Speed in strait line
	unsigned int Vhigh;//=1500
	
	float delta_speed;//Value for the rear differential
	
	int mode_speed;//Mode 0=>speed manual //1=> speed auto
	
	//functions
	void init(void);
	void Caculate_angle_wheel(void);
	void Set_deplacement(void);
	void Car_debug(void);
	void Car_handler(void);

private:
	void Set_speed(void);
};

//####################### Wheels #################################

#define KP_TURN 						1.1			// Proportional coefficient in turn
#define KDP_TURN 						0.8			// Differential coefficient in turn

#define K 								2 //P of the PI
#define Ki								1 //I of the PI



#endif /* CAR_CONTROL_H_ */
