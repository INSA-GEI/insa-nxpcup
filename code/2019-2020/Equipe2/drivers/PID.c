#include "PID.h"


void PIDController_init(void) {
	Integrator = 0.0f;
	old_error = 0.0f;
	
	Differentiator = 0.0f;
	old_measurement = 0.0f;
	
	PID_output = 0.0f;
}



float PIDController_update(float setpoint, float measurement) {
	
	// ########## Error signal ########## //
	float error = setpoint - measurement;
	
	
	
	// ########## Proportional ########## //
	float Proportional = Kp * error;
	
	// ########## Integral ########## //
	Integrator = Integrator + 0.5f * Ki * Te * (error + old_error);
	
	// Anti wind-up via clamping
		// Compute limits
	if (PID_min > Proportional) integrator_max = PID_max - Proportional;
	else integrator_max = 0.0f;
	
	if (PID_min < Proportional) integrator_min = PID_min - Proportional;
	else integrator_min = 0.0f;
	
		// Clamp Integrator
	if (Integrator > integrator_max) Integrator = integrator_max;
	else if (Integrator < integrator_min) Integrator = integrator_min;
	
	
	// ########## Derivative ########## //
	// Note : on measurement !!
	Differentiator = -(2.0f * Kd * (measurement - old_measurement)
					 +(2.0f) * tau - Te) * Differentiator
					 /(2.0f * tau + Te);
	
	
	
	// ########## Output ########## //
	// Compute & apply limits
	PID_output = Proportional + Integrator + Differentiator;
	if (PID_output > PID_max) PID_output = PID_max;
	if (PID_output < PID_min) PID_output = PID_min;
	
	// Store error and measurement
	old_error = error;
	old_measurement = measurement;
	
	return PID_output;	
}
