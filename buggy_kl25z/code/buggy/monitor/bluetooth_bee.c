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

#define BEE_DMA_TRANSFER_SOURCE		3
#define BEE_DMA_TRANSFER_CHANNEL	3

#define BEE_LENGTH_DATA_INFO	5

/* Ring Buffer to store data received from Bluetooth Bee */
uint8_t bee_buffer[BEE_BUFFER_SIZE];	//Unused
/* Buffer to store a command */
uint8_t bee_CmdReceive[BEE_CMD_LENGTH];	//Unused

/* Structure contain data pointer and data size used to store a transfer */
lpsci_transfer_t bee_LPSCITransfer = {bee_CmdReceive, BEE_CMD_LENGTH}; //UNUSED
uint8_t dataInfo[BEE_LENGTH_DATA_INFO];
lpsci_transfer_t bee_transferDataInfo = {dataInfo, BEE_LENGTH_DATA_INFO};
lpsci_transfer_t bee_transferData;
/* Handle for LPSCI Transfer API, it will be initialize in function bee_initReceiveData */
lpsci_handle_t bee_transferHandle;

/* Callback function to call upper layer function */
void (*bee_receiveCallback)(void);

/* Handle for DMA */
dma_handle_t bee_dmaReceiveHandle;
dma_transfer_config_t bee_dmaReceiveTransferConfig;

dma_handle_t bee_dmaTransmitHandle;
dma_transfer_config_t bee_dmaTransmitTransferConfig;

/* Callback function for LPSCI Transfer API, this function will be called when a transfer is completed */
void bee_LPSCITransferCallback(UART0_Type *base, lpsci_handle_t *handle, status_t status, void *userData){
	size_t nbr_bytesReceived;
	/* Call upper layer function */
	if (status == kStatus_LPSCI_RxIdle){
		bee_receiveCallback();
		LPSCI_TransferReceiveNonBlocking(BEE_LPSCI, &bee_transferHandle, &bee_LPSCITransfer, &nbr_bytesReceived);
	}
}

/* Callback function for DMA, this function will be called when a transfer is completed */
void bee_dmaReceiveCallback(dma_handle_t *handle, void *userData){
	bee_receiveCallback();
	DMA_SubmitTransfer(&bee_dmaReceiveHandle, &bee_dmaReceiveTransferConfig, kDMA_EnableInterrupt);
	DMA_EnableChannelRequest(DMA0, BEE_DMA_RECEIVE_CHANNEL);
}

void bee_dmaTransferCallback(dma_handle_t *handle, void *userData){
	DMA_SubmitTransfer(&bee_dmaTransmitHandle, &bee_dmaTransmitTransferConfig, kDMA_EnableInterrupt);
	DMA_EnableChannelRequest(DMA0, BEE_DMA_TRANSFER_CHANNEL);
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
	//LPSCI_TransferCreateHandle(BEE_LPSCI, &bee_transferHandle, bee_LPSCITransferCallback, NULL);
	
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
	DMA_SubmitTransfer(&bee_dmaReceiveHandle, &bee_dmaReceiveTransferConfig, kDMA_EnableInterrupt);
	DMA_EnableChannelRequest(DMA0, BEE_DMA_RECEIVE_CHANNEL);

	/* Init DMA for transmiting data */
	/* Set multiplexer  for TX*/
	DMAMUX_SetSource(DMAMUX0, BEE_DMA_TRANSFER_CHANNEL, BEE_DMA_TRANSFER_SOURCE);
	DMAMUX_EnableChannel(DMAMUX0, BEE_DMA_TRANSFER_CHANNEL);

	/* Configure DMA for TX */
	DMA_CreateHandle(&bee_dmaTransmitHandle, DMA0, BEE_DMA_TRANSFER_CHANNEL);
	DMA_SetCallback(&bee_dmaReceiveHandle, bee_dmaTransferCallback, NULL);


}

void bee_startReceivingData(void){
	LPSCI_EnableRxDMA(BEE_LPSCI, true);
	LPSCI_EnableRx(BEE_LPSCI, true);
}


//void bee_initReceiveData(void (*callback)(void)){
//	/* Number of bytes received, not used for now */
//	size_t nbr_bytesReceived;
//	/* Enable RX interrupt */
//	LPSCI_TransferCreateHandle(BEE_LPSCI, &bee_transferHandle, bee_LPSCITransferCallback, NULL);
//	LPSCI_TransferStartRingBuffer(BEE_LPSCI, &bee_transferHandle, bee_buffer, BEE_BUFFER_SIZE);
//	bee_receiveCallback = callback;
//
//	/* Enable RX */
//	LPSCI_EnableRx(BEE_LPSCI, true);
//	LPSCI_TransferReceiveNonBlocking(BEE_LPSCI, &bee_transferHandle, &bee_LPSCITransfer, &nbr_bytesReceived);
//}


void bee_enableSendCameraData(uint16_t * cameraData, uint32_t lengthInByte){
	/* Init DMA for TX */
	DMA_PrepareTransfer(&bee_dmaTransmitTransferConfig, (uint32_t *)cameraData, sizeof(uint16_t), (uint32_t *)LPSCI_GetDataRegisterAddress(BEE_LPSCI), sizeof(uint8_t), lengthInByte, kDMA_MemoryToPeripheral);
	DMA_SetModulo(DMA0, BEE_DMA_TRANSFER_CHANNEL, kDMA_Modulo256Bytes, kDMA_ModuloDisable);

	//DMA_SubmitTransfer(&bee_dmaTransmitHandle, &bee_dmaTransmitTransferConfig, kDMA_EnableInterrupt);
	//DMA_EnableChannelRequest(DMA0, BEE_DMA_TRANSFER_CHANNEL);
	/* Enable TX */
	
	LPSCI_EnableTxDMA(BEE_LPSCI, true);
	LPSCI_EnableTx(BEE_LPSCI, true);
}

void bee_sendCameraData(void){

	DMA_SubmitTransfer(&bee_dmaTransmitHandle, &bee_dmaTransmitTransferConfig, kDMA_NoOptions);
	DMA_EnableCycleSteal(DMA0, BEE_DMA_TRANSFER_CHANNEL, false);
	DMA_EnableChannelRequest(DMA0, BEE_DMA_TRANSFER_CHANNEL);

	

	//dataInfo[0] = 0xFF;
	//dataInfo[1] = 0xFF;
	//dataInfo[2] = id;					/* Message ID */
	//dataInfo[3]	= lengthInByte >> 8;	/* Data Length MSB*/
	//dataInfo[4]	= lengthInByte & 0xFF;	/* Data Length LSB*/


	//bee_transferData.data = data;
	//bee_transferData.dataSize = lengthInByte;

	//LPSCI_TransferSendNonBlocking(BEE_LPSCI, &bee_transferHandle, &bee_transferDataInfo);

	//LPSCI_TransferSendNonBlocking(BEE_LPSCI, &bee_transferHandle, &bee_transferData);
	
	//LPSCI_WriteBlocking(BEE_LPSCI, dataInfo, BEE_LENGTH_DATA_INFO);
	//LPSCI_WriteBlocking(BEE_LPSCI, data, lengthInByte);
	
}

/*
void UART0_IRQHandler(void){
	if((kLPSCI_RxDataRegFullFlag)&LPSCI_GetStatusFlags(BEE_LPSCI)){
		bee_buffer[bee_writePtrBuffer] = LPSCI_ReadByte(BEE_LPSCI);

		if (bee_writePtrBuffer == BEE_BUFFER_SIZE - 1){
			bee_writePtrBuffer = 0;
		}
		else{
			bee_writePtrBuffer++;
		}
		LPSCI_ClearStatusFlags(BEE_LPSCI, kLPSCI_RxDataRegFullFlag);
	}
}
*/
