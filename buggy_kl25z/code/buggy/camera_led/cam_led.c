/*
 * cam_led.c
 *
 *  Created on: 14 févr. 2024
 *      Author: Ordi Axel
 */

#include "cam_led.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

#define CAM_LED_PORT PORTC
#define CAM_LED_GPIO GPIOC
#define CAM_LED_PIN  12

void cam_led_init(void){
	CLOCK_EnableClock(kCLOCK_PortC); // enable clock for PORTC (Motor left : speed and direction; Enable : Motor right and left)

	gpio_pin_config_t config_output_gpio = {kGPIO_DigitalOutput,0}; // output logic, 0 at default
	PORT_SetPinMux(CAM_LED_PORT,CAM_LED_PIN,kPORT_MuxAsGpio); // PTC12 CAM Led  (GPIO output)
	GPIO_PinInit(CAM_LED_GPIO,CAM_LED_PIN,&config_output_gpio);
	// Activer LED CAMERA
	GPIO_SetPinsOutput(CAM_LED_GPIO, 1<<CAM_LED_PIN);
}
