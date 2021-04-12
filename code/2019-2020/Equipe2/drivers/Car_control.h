#ifndef CAR_CONTROL_H_
#define CAR_CONTROL_H_

#include "Movement.h"
#include "ImageProcessing.h"

#define CST_FINISH_TIME 100 //100*10ms=>1s

#define Te 0.01 //sample time 10ms handler servos /!\ Te_s (sample time for rear motors is in Movement.h)
#define DEG_TO_RAD 0.0175 //degrees to radian conversion 

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
	
	/*-----------------------------------------------*/
	/*---------------wheels angle--------------------*/
	/*-----------------------------------------------*/
	float servo_angle;
	bool enable_ampli_turn;
	
	float AMPLIFIE_TURN_1;	// Constant to amplify wide turn (+ or - cam.diff)
	float AMPLIFIE_TURN_2;	// Constant to amplify tight turn (s'ajout ou se soustrait à cam.diff) - 5 Original
	float MAX_ANGLE;		// 30 Original
	int MAX_CAM_DIFF;		// 20 Original
	
	/*-----------------------------------------------*/
	/*---------------speed control-------------------*/
	/*-----------------------------------------------*/
	int T_BRAKE; 			//Threshold before braking - 200 Original
	int INCREMENT_SPEED;	//Constant speed increase (avoid car spinning) - 40 Original
	int DIV_1_SPEED; 		//Divided speed instruction to avoid car spinning in first half of Vmes=[Vslow,Vhigh/2]	- 3 Original
	int TURN_SPEED; 		//Threshold speed in turn - 1300 Original

	bool enable_brake;

	int Vset;
	int V_old;
	int V_mes;
	int Vslow;			//Speed in turns
	int Vhigh;			//Speed in strait lines
	int mode_speed;		//0 : manu, 1: auto, 2: auto incr
	float delta_speed;	//Value for the rear differential
	
	
	/*-----------------------------------------------*/
	/*---------------PID controller------------------*/
	/*-----------------------------------------------*/
	
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

	/**
	  * @brief  PID
	  * @param  none
	  * @retval PID output, aka servo_angle
	  */
	float PIDController_update(float setpoint, float measurement);
	
	//########### Functions ###########//
	void init(void);
	
	

	/**
	  * @brief  Set deplacement value using myMovement object
	  * 		speed can be positive or negative (if break) configurated in Movement.cpp
	  * @param  finish :true/false <= màj dans Detect_state()
	  * @retval state_car_turn : 0/1/2
	  * 		enable_brake : true/false
	  * 		enable_ampli_turn : true/false
	  */
	void Set_deplacement(void);
	
	/**
	  * @brief  Process every actions (set speed,angle wheels etc) for the car every 10ms
	  * @param  none
	  * @retval none
	  */
	void Car_handler(void);
	
	
	/**
	  * @brief  Select debug param with keyboard
	  * @param  none
	  * @retval none
	  */
	void Car_debug(void); 

private:
	
	/*-----------------------------------------------*/
	/*---------------wheels angle--------------------*/
	/*-----------------------------------------------*/

	/**
	  * @brief  Calulate wheel instruction + PI before store the in servo_angle
	  * @param  None
	  * @retval None
	  */
	void Caculate_angle_wheel(void);
	
	
	/*-----------------------------------------------*/
	/*--------------------Speed----------------------*/
	/*-----------------------------------------------*/
	

	/**
	  * @brief  Calculate speed instruction depending on wheels angle
	  * 		Corrector in Movement.cpp =>regulate()
	  * @param  None
	  * @retval None
	  */
	void Calculate_speed(void); 
	
	/**
	  * @brief  Calculate Vslow et Vhigh and return to Calculate_speed
	  * @param  None
	  * @retval None
	  */
	void Set_speed(void);
	

	/**
	  * @brief  Calculate and instance differential speed
	  * @param  None
	  * @retval None
	  */
	void Set_diff_speed(void);
	
	
	/*------------------------------------------------*/
	/*---------------State of the car-----------------*/
	/*------------------------------------------------*/

	int state_turn_car; //2=>hard turn //1 soft turn //0=>strait line
	

	/**
	  * @brief  Detect turns and slip (ie ESP) only in strait lines
	  * @param  None
	  * @retval state_car_turn : 0/1/2
	  * 		enable_brake : true/false
	  * 		enable_ampli_turn : true/false
	  */
	void Detect_state(void);
	
	/**
	  * @brief  Data acquisition 
	  * @param  None
	  * @retval V_mes
	  *			cam
	  */
	void Process_data(void);
		
	
	
	/*------------------------------------------------*/
	/*---------------------Debug----------------------*/
	/*------------------------------------------------*/
	int mode_debug;

	/**
	  * @brief  Show debug
	  * @param  none
	  * @retval none
	  */
	void Aff_debug(void);

	/**
	  * @brief  Initialisation
	  * @param  none
	  * @retval none
	  */
	void Aff_debug_init(void);
		
};

// Others
int sng(int a);

#endif /* CAR_CONTROL_H_ */
