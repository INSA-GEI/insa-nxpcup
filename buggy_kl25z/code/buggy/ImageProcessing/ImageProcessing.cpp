/*
 * ImageProcessing.cpp
 *
 *  Created on: 22 janv. 2024
 *      Author: Ordi Axel
 */

#include "ImageProcessing.h"

ImageProcessing::ImageProcessing() {
	// TODO Auto-generated constructor stub

}

ImageProcessing::~ImageProcessing() {
	// TODO Auto-generated destructor stub
}

void ImageProcessing::capture(void){
// ------------------- VARIABLES LOCALES ----------------------------------
	//Configuration for channel 11
	const adc16_channel_config_t adc0_config_ch_11 =
	{
			.channelNumber=11,
			.enableInterruptOnConversionCompleted = false,
			.enableDifferentialConversion=false,
	};
// ------------------------------------------------------------------------


	ADC16_SetChannelMuxMode(ADC0,kADC16_ChannelMuxB); // Sélectionner le côté B du MUX
	CAM_SI_HIGH; // Activer la ligne SI (Shift In) de la caméra
	CAM_DELAY; // Attente pour le délai CAM
	CAM_CLK_HIGH; // Activer l'horloge de la caméra
	CAM_DELAY; // Attente pour le délai CAM
	CAM_SI_LOW; // Désactiver la ligne SI de la caméra
	CAM_DELAY; // Attente pour le délai CAM

	// inputs data from camera (first pixel)

	ADC16_SetChannelConfig(ADC0,ADC0_Channel_Group,&adc0_config_ch_11);//Trigger la conversion sur channel 11
	while (0U == (kADC16_ChannelConversionDoneFlag &
					  ADC16_GetChannelStatusFlags(ADC0,ADC0_Channel_Group)))
			{
				// Polling attente de fin de conversion pour prendre la valeur
			}
	ImageData[0] = ADC16_GetChannelConversionValue(ADC0,ADC0_Channel_Group);
	CAM_CLK_LOW;

	// Boucle pour entrer les données de la caméra (un pixel à la fois)
	for(int i = 1; i < 128; i++){
		CAM_DELAY;                               // Attente pour le délai CAM
		CAM_CLK_HIGH;                            // Activer l'horloge de la caméra

		// Entrée des données de la caméra (un pixel à chaque itération de la boucle)
		ADC16_SetChannelConfig(ADC0,ADC0_Channel_Group,&adc0_config_ch_11);
		while (0U == (kADC16_ChannelConversionDoneFlag &
					  ADC16_GetChannelStatusFlags(ADC0,ADC0_Channel_Group)))
				{
						// Polling attente de fin de conversion pour prendre la valeur
				}
		ImageData[i] = ADC16_GetChannelConversionValue(ADC0,ADC0_Channel_Group);                  // Stocker la valeur retournée dans le tableau ImageData
		CAM_CLK_LOW;                             // Désactiver l'horloge de la caméra
		// Créé un tableau de 128 contenant la valeur des pixel d'une ligne de la caméra
	}
}

void ImageProcessing::affiche_image(void){
	for (int i = 0 ; i<128;i++){
		PRINTF("%d",ImageData[i]);

	}
	PRINTF("/n");
}

void ImageProcessing::init(){
// ------------------- VARIABLES LOCALES ----------------------------------
	// Configuration for ADC0
	const adc16_config_t adc0_config =
	{
	    .referenceVoltageSource = kADC16_ReferenceVoltageSourceVref, // Use external Vref pins (VrefH and VrefL) as the reference voltage source
	    .clockSource = kADC16_ClockSourceAlt1, // Use ALT1 clk bus/2 as the input clock source
	    .enableAsynchronousClock = false, // Enable the asynchronous clock output
	    .clockDivider = kADC16_ClockDivider1, // Set the clock divider to 2, dividing the input clock source
	    .resolution = kADC16_ResolutionSE10Bit, // Use single-ended 10-bit resolution mode
	    .longSampleMode = kADC16_LongSampleDisabled, // Disable long sample mode
	    .enableContinuousConversion = false, // Disable continuous conversion mode, perform a single conversion
	    .enableHighSpeed = false, // Disable high-speed mode
	    .enableLowPower = false, //Disable low power mode
	};

	const gpio_pin_config_t gpio_pin_input =
		{
			.pinDirection = kGPIO_DigitalInput,

			};

	const gpio_pin_config_t gpio_pin_output =
		{
			.pinDirection = kGPIO_DigitalOutput,
			.outputLogic=0,
			};
---------------------------------------------------------------------------
	ADC16_Init(ADC0,&adc0_config);
	ADC16_SetChannelMuxMode(ADC0,kADC16_ChannelMuxB);// Selectionner le Mux B bit 5 ADC0_CFG2


	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortB);

	PORT_SetPinMux(PORTC, 2u, kPORT_PinDisabledOrAnalog);
	PORT_SetPinMux(PORTB, 8u, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, 9u, kPORT_MuxAsGpio);

	GPIO_PinInit(GPIOC,2u,&gpio_pin_input);
	GPIO_PinInit(GPIOB,8u,&gpio_pin_output);
	GPIO_PinInit(GPIOB,9u,&gpio_pin_output);

}


