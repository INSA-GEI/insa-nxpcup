/*
 * bluetooth_bee.c
 *
 *  Created on: 7 févr. 2024
 *      Author: Triet Nguyen (Github : trietngh)
 */


#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_lpsci.h"
#include "bluetooth_bee.h"
#include <stdbool.h>


#define BEE_PORT	PORTE
#define BEE_GPIO	GPIOE
#define BEE_PIN_TX	20
#define BEE_PIN_RX	21

#define BEE_LPSCI	UART0
#define BEE_LPSCI_CLK_FREQ CLOCK_GetPllFllSelClkFreq()
#define BEE_LPSCI_BAUD_RATE 115200
#define BEE_LPSCI_SRC_CLS	1								/* Choose IRC48M (48Mhz) as source clock*/

void bee_init(void){
	gpio_pin_config_t bee_gpio_config_output = {kGPIO_DigitalOutput,0};
	lpsci_config_t bee_lpsci_config;
	/* Enable clock for GPIO & UART0 */
	CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_SetLpsci0Clock(1);

	/* Connect PTE20 to UART0 TX and PTE21 to UART0 RX*/
	PORT_SetPinMux(BEE_PORT, BEE_PIN_TX, kPORT_MuxAlt4);
	PORT_SetPinMux(BEE_PORT, BEE_PIN_RX, kPORT_MuxAlt4);

	/* Configure GPIO Pin to Output */
	GPIO_PinInit(BEE_GPIO, BEE_PIN_TX, &bee_gpio_config_output);
	GPIO_PinInit(BEE_GPIO, BEE_PIN_RX, &bee_gpio_config_output);

	/*Init UART0 connection to BLT Bee*/
	LPSCI_GetDefaultConfig(&bee_lpsci_config);
	bee_lpsci_config.baudRate_Bps = BEE_LPSCI_BAUD_RATE;
	/* Enable clock and initial UART module follow user configure structure. */
	LPSCI_Init(BEE_LPSCI, &bee_lpsci_config, BEE_LPSCI_CLK_FREQ);
	LPSCI_EnableTx(BEE_LPSCI, true);
	LPSCI_EnableRx(BEE_LPSCI, true);
}

void bee_sendData(uint8_t * data, uint8_t data_length){
	LPSCI_WriteBlocking(BEE_LPSCI, data, 2);
}
