#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <stdint.h>

// Motor control parameters
// direction : -100 = tourner totalement à gauche, 0 = tout droit, +100 = tourner totalement à droite
// speed : 0..100 correspond à 1000 µs .. 1200 µs (bridé)

void Init_pwm_motor(void);
void motor_update(int direction, uint16_t speed);

#endif // MOTOR_CONTROL_H_
