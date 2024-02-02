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
    ADC16_StartConversion(ADC0, channelGroup);

    // Wait for conversion to be done
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, channelGroup))) {}

    // Get the result
    uint16_t BattMeasurement = ADC16_GetChannelConversionValue(ADC0, channelGroup);

    // Your scaling calculation
    BattMeasurement = (int)((ADC_SCALING * BattMeasurement) / ADC_RESOLUTION);


    // Configure ADC for the camera (channel 11, for example)
    adcChannelConfigStruct.channelNumber = 11;
    ADC16_SetChannelConfig(ADC0, channelGroup, &adcChannelConfigStruct);

    /*
    // Trigger ADC conversion
    ADC16_StartConversion(ADC0, channelGroup);

    // Wait for conversion to be done
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, channelGroup))) {}

    // Get the result
    uint16_t CameraMeasurement = ADC16_GetChannelConversionValue(ADC0, channelGroup);

    // Your scaling calculation for camera measurement
    CameraMeasurement = (int)((ADC_SCALING * CameraMeasurement) / ADC_RESOLUTION);

    // Do something with BattMeasurement and CameraMeasurement
     */

}



void lptmr_conf(void) {
    lptmr_config_t lptmrConfig;
    port_pin_config_t portConfig;

    // Enable clock for Port A
    CLOCK_EnableClock(kCLOCK_PortA);

    // Configure pin PTA19 for LPTMR0
    portConfig = PORT_PCR_MUX(kPORT_MuxAlt6);
    PORT_SetPinConfig(PORTA, 19, &portConfig);

    // LPTMR Configuration
    LPTMR_GetDefaultConfig(&lptmrConfig);

    // Set the prescaler
    lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
    lptmrConfig.value = PSC_LPTMR; // Set the Compare Value

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



