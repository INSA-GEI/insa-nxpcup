
#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

#define VSLOW 500
#define VHIGH 1500
#define VSET 0
#define INCREASE_SPEED 50//Nb of time ok before we increase the speed
#define MAX_ANGLE_BEFORE_SLOWDOWN 8 

#define Te 0.001 //sample time

class Car{
public:	
	bool finish;//indicates if we are at the end of the circuit
	float servo_angle;
	//Speed of the car
	unsigned int Vset;//=0
	//Speed in turn
	unsigned int Vslow;//=500
	//Speed in strait line
	unsigned int Vhigh;//=1500
	
	int mode_speed=0;
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
