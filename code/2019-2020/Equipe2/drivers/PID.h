#ifndef PID_H_
#define PID_H_

#include "Car_control.h"
#include "ImageProcessing.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"


// Controller Gains
#define Kp 1.6
#define Ki 0.8
#define Kd 0.2
	
// Derivative low-pass filter time constant
#define tau 2*Te
	
// Limits
float PID_min, PID_max;
float integrator_max, integrator_min;
	
// Controller 'memory'
float Integrator;
float old_error;
float Differentiator;
float old_measurement;
	
// Controller output
float PID_output;


void PIDController_init(void);
float PIDController_update(float setpoint, float measurement);



#endif /* PID_H_ */
