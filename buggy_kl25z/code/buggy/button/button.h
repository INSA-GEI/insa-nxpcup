/**
 * @file button.h
 * @author Triet NGUYEN (tr_nguye@insa-toulouse.fr)
 * @brief Header of driver for buttons in Buggy project
 * @version 0.1
 * @date 2024-05-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_port.h"
#include "fsl_gpio.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
#define SW3_PORT PORTD
#define SW3_GPIO GPIOD
#define SW3_PIN  3U

#define SW4_PORT PORTD
#define SW4_GPIO GPIOD
#define SW4_PIN  1U

/***********************************************************************************************************************
 * Constants
 **********************************************************************************************************************/
/* Configuration for SW3 and SW4 button */

const gpio_pin_config_t SW3_gpio_config = {
    kGPIO_DigitalInput,
    0,
};

const gpio_pin_config_t SW4_gpio_config = {
    kGPIO_DigitalInput,
    0,
};

/***********************************************************************************************************************
 * Public functions
 **********************************************************************************************************************/
/**
 * @brief Init SW3 and SW4 as input buttons
 * 
 * @param SW3_callback Callback function for SW3
 * @param SW4_callback Callback function for SW4
 */
void BUTTON_Init(void (*SW3_callback)(void), void (*SW4_callback)(void));

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H_ */
