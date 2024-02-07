/*
 * driver_debug.c
 *
 *  Created on: 1 févr. 2024
 *      Author: thc18
 */

#include "debug/driver_debug.h"

#include "fsl_adc16.h"

void BatteryVoltage(void) {
    adc16_config_t adcConfigStruct;
    adc16_channel_config_t adcChannelConfigStruct;
    uint32_t channelGroup = 0; // Assuming channel group 0

    // Configure ADC
    ADC16_GetDefaultConfig(&adcConfigStruct);
    ADC16_Init(ADC0, &adcConfigStruct);

    // Select B side of the MUX
    ADC16_SetHardwareAverage(ADC0, kADC16_HardwareAverageCount4); // Optional: Set hardware averaging

    // Set ADC0 channel 3
    adcChannelConfigStruct.channelNumber = 3;
    adcChannelConfigStruct.enableInterruptOnConversionCompleted = false; // Optional: Enable interrupt
    ADC16_SetChannelConfig(ADC0, channelGroup, &adcChannelConfigStruct);

    // Trigger ADC conversion
    ADC16_DoAutoCalibration(ADC0);
    ADC16_GetChannelConversionValue(ADC0, channelGroup);

    // Wait for conversion to be done
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, channelGroup))) {}

    // Get the result
    uint16_t BattMeasurement = ADC16_GetChannelConversionValue(ADC0, channelGroup);

    // Your scaling calculation
    BattMeasurement = (int)((ADC_SCALING * BattMeasurement) / ADC_RESOLUTION);


    // Configure ADC for the camera (channel 11, for example)
    adcChannelConfigStruct.channelNumber = 11;
    ADC16_SetChannelConfig(ADC0, channelGroup, &adcChannelConfigStruct);

}



void LPTMR_Enable(void)
{
    lptmr_config_t lptmrConfig;
    // Enable clock for Port A
    CLOCK_EnableClock(kCLOCK_PortA);

    // Configure pin PTA19 for LPTMR0
	PORT_SetPinMux(PORTA,19,kPORT_MuxAlt6);
    // LPTMR Configuration
    LPTMR_GetDefaultConfig(&lptmrConfig);

    // Set the prescaler
    lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_0;
    lptmrConfig.value = kLPTMR_Prescale_Glitch_10; // Set the Compare Value

    // Initialize LPTMR
    LPTMR_Init(LPTMR0, &lptmrConfig);

    // Enable LPTMR interrupt
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);

    // Enable NVIC interrupt for LPTMR
    EnableIRQ(LPTMR0_IRQn);

    // Start LPTMR
    LPTMR_StartTimer(LPTMR0);
}

void LPTMR0_IRQHandler(void) {
    // Perform actions related to battery voltage measurement
    BatteryVoltage();

    // Clear LPTMR interrupt flag
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);

    //LPTMR_StartTimer(LPTMR0);
}



void debug_init() {
	gpio_pin_config_t config_ouput_gpio = {kGPIO_DigitalOutput,0}; // output logic, 0 at default
	gpio_pin_config_t config_input_gpio = {kGPIO_DigitalInput,0}; // output logic, 0 at default

    // Clock initialization
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_PortE);

    // Initialize the Red LED (PTB18)
    PORT_SetPinMux(PORTB, 18, kPORT_MuxAsGpio);
    GPIO_WritePinOutput(GPIOB, DEBUG_RED_Pin, 1);
    GPIO_PinInit(GPIOB, DEBUG_RED_Pin, &config_ouput_gpio);

    // Initialize the Green LED (PTB19)
    PORT_SetPinMux(PORTB, 19, kPORT_MuxAsGpio);
    GPIO_WritePinOutput(GPIOB, DEBUG_GREEN_Pin, 1);
    GPIO_PinInit(GPIOB, DEBUG_GREEN_Pin, &config_ouput_gpio);

    // Initialize the Blue LED (PTD1)
    PORT_SetPinMux(PORTD, 1, kPORT_MuxAsGpio);
    GPIO_WritePinOutput(GPIOD, DEBUG_BLUE_Pin, 1);
    GPIO_PinInit(GPIOD, DEBUG_BLUE_Pin, &config_ouput_gpio);

    // PTD1 (SW_USER_2) & PTD3 (SW_USER_1)
    PORT_SetPinMux(PORTD, 1, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTD, 3, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOD, 1, &config_input_gpio);
    GPIO_PinInit(GPIOD, 3, &config_input_gpio);

    // Initialize CAM LED (PTC12)
    PORT_SetPinMux(PORTC, 12, kPORT_MuxAsGpio);
    GPIO_WritePinOutput(GPIOC, DEBUG_CAM_LED_Pin, 1);
    GPIO_PinInit(GPIOC, DEBUG_CAM_LED_Pin, &config_ouput_gpio);

    // PTE2-5 : Rotary switch (2:LSB, 5:MSB)
    PORT_SetPinMux(PORTE, 2, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE, 3, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE, 4, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTE, 5, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 2, &config_input_gpio);
    GPIO_PinInit(GPIOE, 3, &config_input_gpio);
    GPIO_PinInit(GPIOE, 4, &config_input_gpio);
    GPIO_PinInit(GPIOE, 5, &config_input_gpio);

    // Display init
    PORT_SetPinMux(PORTC, 5, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 6, kPORT_MuxAsGpio);
    PORT_SetPinMux(PORTC, 10, kPORT_MuxAsGpio);
    GPIO_WritePinOutput(GPIOC, DISP_CLK_PIN, 1);
    GPIO_WritePinOutput(GPIOC, DISP_SIN_PIN, 1);
    GPIO_WritePinOutput(GPIOC, DISP_LATCH_PIN, 1);
    GPIO_PinInit(GPIOC, DISP_CLK_PIN, &config_ouput_gpio);
    GPIO_PinInit(GPIOC, DISP_SIN_PIN, &config_ouput_gpio);
    GPIO_PinInit(GPIOC, DISP_LATCH_PIN, &config_ouput_gpio);
}


void debug_red_on() {
    GPIO_WritePinOutput(GPIOB, DEBUG_RED_Pin, 1);
}

void debug_red_off() {
    GPIO_WritePinOutput(GPIOB, DEBUG_RED_Pin, 0);
}

void debug_green_on() {
    GPIO_WritePinOutput(GPIOB, DEBUG_GREEN_Pin, 1);
}

void debug_green_off() {
    GPIO_WritePinOutput(GPIOB, DEBUG_GREEN_Pin, 0);
}

void debug_blue_on() {
    GPIO_WritePinOutput(GPIOD, DEBUG_BLUE_Pin, 1);
}

void debug_blue_off() {
    GPIO_WritePinOutput(GPIOD, DEBUG_BLUE_Pin, 0);
}

void disp_clk_on() {
    GPIO_WritePinOutput(GPIOC, DISP_CLK_PIN, 1);
}

void disp_clk_off() {
    GPIO_WritePinOutput(GPIOC, DISP_CLK_PIN, 0);
}

void disp_sin_on() {
    GPIO_WritePinOutput(GPIOC, DISP_SIN_PIN, 1);
}

void disp_sin_off() {
    GPIO_WritePinOutput(GPIOC, DISP_SIN_PIN, 0);
}

void disp_latch_on() {
    GPIO_WritePinOutput(GPIOC, DISP_LATCH_PIN, 1);
}

void disp_latch_off() {
    GPIO_WritePinOutput(GPIOC, DISP_LATCH_PIN, 0);
}



