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
#include "fsl_dma.h"
#include "fsl_dmamux.h"
#include "bluetooth_bee.h"
#include <stdbool.h>
#include <string.h>

#define BEE_PORT	PORTE
#define BEE_GPIO	GPIOE
#define BEE_PIN_TX	20
#define BEE_PIN_RX	21

#define BEE_LPSCI	UART0
#define BEE_LPSCI_CLK_FREQ CLOCK_GetPllFllSelClkFreq()
#define BEE_LPSCI_BAUD_RATE 115200
#define BEE_LPSCI_SRC_CLK	1								/* Choose IRC48M (48Mhz) as source clock*/

#define BEE_DMA_RECEIVE_SOURCE		2							/* See RM p.64 (DMA MUX Request Source) */
#define BEE_DMA_RECEIVE_CHANNEL		2

/* Callback function to call upper layer function */
void (*bee_receiveCallback)(void);
uint8_t * ptrDataToSend = NULL;
uint16_t bee_lengthDataToSend;

/* Handle for DMA */
dma_handle_t bee_dmaReceiveHandle;
dma_transfer_config_t bee_dmaReceiveTransferConfig;

/* Callback function for DMA, this function will be called when a transfer is completed */
void bee_dmaReceiveCallback(dma_handle_t *handle, void *userData){
	bee_receiveCallback();
	DMA_SubmitTransfer(&bee_dmaReceiveHandle, &bee_dmaReceiveTransferConfig, kDMA_EnableInterrupt);
	DMA_EnableChannelRequest(DMA0, BEE_DMA_RECEIVE_CHANNEL);
}

void bee_initCommunication(void (*callback)(void), uint8_t * receiveBuffer){
	gpio_pin_config_t bee_gpio_config_output = {kGPIO_DigitalOutput,0};
	lpsci_config_t bee_lpsci_config;


	/* Enable clock for GPIO & UART0 */
	CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_SetLpsci0Clock(BEE_LPSCI_SRC_CLK);

	/* Connect PTE20 to UART0 TX and PTE21 to UART0 RX*/
	PORT_SetPinMux(BEE_PORT, BEE_PIN_TX, kPORT_MuxAlt4);
	PORT_SetPinMux(BEE_PORT, BEE_PIN_RX, kPORT_MuxAlt4);

	/* Configure GPIO Pin to Output */
	GPIO_PinInit(BEE_GPIO, BEE_PIN_TX, &bee_gpio_config_output);
	GPIO_PinInit(BEE_GPIO, BEE_PIN_RX, &bee_gpio_config_output);

	/*Init UART0 connection to BLT Bee*/
	LPSCI_GetDefaultConfig(&bee_lpsci_config);
	bee_lpsci_config.baudRate_Bps = BEE_LPSCI_BAUD_RATE;
	LPSCI_Init(BEE_LPSCI, &bee_lpsci_config, BEE_LPSCI_CLK_FREQ);

	/* Init DMA for receiving data */
	/* Set multiplexer  for RX*/
	DMAMUX_Init(DMAMUX0);
	DMAMUX_SetSource(DMAMUX0, BEE_DMA_RECEIVE_CHANNEL, BEE_DMA_RECEIVE_SOURCE);
	DMAMUX_EnableChannel(DMAMUX0, BEE_DMA_RECEIVE_CHANNEL);

	/* Configure and Init DMA for RX */
	bee_receiveCallback = callback;
	DMA_Init(DMA0);
	DMA_CreateHandle(&bee_dmaReceiveHandle, DMA0, BEE_DMA_RECEIVE_CHANNEL);
	DMA_SetCallback(&bee_dmaReceiveHandle, bee_dmaReceiveCallback, NULL);
	DMA_PrepareTransfer(&bee_dmaReceiveTransferConfig, (uint32_t *) LPSCI_GetDataRegisterAddress(BEE_LPSCI), sizeof(uint8_t), receiveBuffer, sizeof(receiveBuffer[0]), BEE_CMD_LENGTH, kDMA_PeripheralToMemory);
}

void bee_startReceivingData(void){
	LPSCI_EnableRxDMA(BEE_LPSCI, true);
	LPSCI_EnableRx(BEE_LPSCI, true);
	DMA_SubmitTransfer(&bee_dmaReceiveHandle, &bee_dmaReceiveTransferConfig, kDMA_EnableInterrupt);
	DMA_EnableChannelRequest(DMA0, BEE_DMA_RECEIVE_CHANNEL);
}


void bee_enableSendData(uint16_t * ptrData, uint32_t lengthInByte){
	/* Enable TX */
	ptrDataToSend = (uint8_t *)ptrData;
	bee_lengthDataToSend = lengthInByte;
	LPSCI_EnableTx(BEE_LPSCI, true);
}

void bee_disableSendData(){
	//LPSCI_EnableTx(BEE_LPSCI, false);
}

void bee_sendData(void){
	LPSCI_WriteBlocking(BEE_LPSCI, ptrDataToSend, bee_lengthDataToSend);
}
