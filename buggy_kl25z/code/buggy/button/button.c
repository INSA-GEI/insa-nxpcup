/**
 * @file button.c
 * @author Triet NGUYEN (tr_nguye@insa-toulouse.fr)
 * @brief Driver for buttons in Buggy project
 * @version 0.1
 * @date 2024-05-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "button.h"

/***********************************************************************************************************************
 * Callback functions
 **********************************************************************************************************************/
/* Callback function for SW3 and SW4 */
void (*SW3_callback)(void);
void (*SW4_callback)(void);

/***********************************************************************************************************************
 * Public functions
 **********************************************************************************************************************/

void BUTTON_Init(void (*callback_SW3)(void), void (*callback_SW4)(void)){
    CLOCK_EnableClock(kCLOCK_PortD);
    PORT_SetPinMux(SW3_PORT, SW3_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(SW4_PORT, SW4_PIN, kPORT_MuxAsGpio);

    GPIO_PinInit(SW3_GPIO, SW3_PIN, &SW3_gpio_config);
    GPIO_PinInit(SW4_GPIO, SW4_PIN, &SW4_gpio_config);

    PORT_SetPinInterruptConfig(SW3_PORT, SW3_PIN, kPORT_InterruptLogicZero);
    PORT_SetPinInterruptConfig(SW4_PORT, SW4_PIN, kPORT_InterruptLogicZero);

    SW3_callback = callback_SW3;
    SW4_callback = callback_SW4;
    NVIC_SetPriority(PORTD_IRQn, 0);
    EnableIRQ(PORTD_IRQn);
}

/***********************************************************************************************************************
 * Interrupt handlers
 **********************************************************************************************************************/
void PORTD_IRQHandler(void){
    if (PORT_GetPinsInterruptFlags(SW3_PORT) & (1U << SW3_PIN)){
        PORT_ClearPinsInterruptFlags(SW3_PORT, 1U << SW3_PIN);
        SW3_callback();
    }
    if (PORT_GetPinsInterruptFlags(SW4_PORT) & (1U << SW4_PIN)){
        PORT_ClearPinsInterruptFlags(SW4_PORT, 1U << SW4_PIN);
        SW4_callback();
    }
}

