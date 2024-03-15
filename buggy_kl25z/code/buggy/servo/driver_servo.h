/*
 * driver_servo.h
 *
 *  Created on: 30 janv. 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */


#ifndef SERVO_DRIVER_SERVO_H_
#define SERVO_DRIVER_SERVO_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_tpm.h"
#include <MKL25Z4.h>
#include "pin_mux.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/* Definition of the clock source */
#define CLOCK_SOURCE_MCGFLLCLK 	1
/* Definition of the clock source frequency */
#define SERVO_TPM_CLOCK_SOURCE 	48000000UL
/* Servo TPM interrupt vector ID (number). */
#define SERVO_TPM_IRQN 			TPM1_IRQn
/* Servo TPM interrupt handler identifier. */
#define SERVO_TPM_IRQHANDLER 	TPM1_IRQHandler

#define SERVO_TPM_PWM 			TPM1

#define SERVO_CHANNEL_PWM 		0

#define SERVO_PWM_PORT 			PORTA
#define SERVO_PWM_GPIO 			GPIOA
#define SERVO_PWN_PIN			12


/*
#define SERVO_CENTER_POS 		3500		// initial servo position (center)
#define SERVO_HARD_LEFT 		2950
#define SERVO_HARD_RIGHT 		3800
*/

#define SERVO_FREQUENCY 		50			//Changer à 100 selon servo !!!!!!!!!!!!!!!!!!!!!


/*Les angles de braquage max sont à remesurer en fonction des voitures, les deux côtés
ne sont pas symétriques en général, on prend donc ici le plus petit angle des deux côtés pour
piloter la voiture de manière symétrique à gauche et à droite */

/* Pour travailler avec des angles positifs uniquement, on considère l'angle 0 comme
 * L'angle max à droite .
 */
#define SERVO_MAX_LEFT_ANGLE -22
#define SERVO_MAX_RIGHT_ANGLE 22

/*
#define SERVO_MAX_LEFT_ANGLE 28
#define SERVO_MAX_RIGHT_ANGLE -22
*/
/***********************************************************************************************************************
 * Exported functions
 **********************************************************************************************************************/

void servo_init(void);
void servo_setPos(int angle);

#ifdef __cplusplus
}
#endif

#endif /* SERVO_DRIVER_SERVO_H_ */


