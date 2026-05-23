/*
 * bluetooth_bee.h
 *
 *  Created on: 7 févr. 2024
 *      Author: Triet Nguyen (Github : trietngh)
 */
/*
 * Driver for Bluetooth Bee module, it's use to send data to computer and receive data from it.
 * Configuration :
 * 	- UART0
 * 	- TX : PTE20
 * 	- RX : PTE21
 * 	- Baud rate : 115200
 * 	- Parity : None
 * 	- Stop bit : 1
 * 	- Length : 8
 * 	*/

/**
 * Command format (Receive direction):
 *     - CMD_ID : 1 byte
 *     - DataMSB : 1 byte
 *     - DataLSB : 1 byte
 *     - Checksum : 1 byte (XOR of all bytes from CMD_ID to DataLSB)
 */

#ifndef BLUETOOTH_BEE_H_
#define BLUETOOTH_BEE_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define BEE_CMD_LENGTH    4

typedef enum{
    /* Command for changing parameters */
    CMD_ID_ENGINE = 0x01,
    CMD_ID_CAMERA_MODE = 0x02,
    CMD_ID_CAMERA_KP = 0x03,
    CMD_ID_CAMERA_KI = 0x04,
    CMD_ID_CAMERA_KD = 0x05,
    CMD_ID_DIFFERENTIAL_KP = 0x06,
    CMD_ID_DIFFERENTIAL_KI = 0x07,
    CMD_ID_DIFFERENTIAL_KDP = 0x08,
    CMD_ID_SPEED_START = 0x09,
    CMD_ID_SPEED_TARGET = 0x0A,
    CMD_ID_SPEED_TURN = 0x0B,
    /* Command for choosing watch data */
    CMD_ID_CAMERA_NEAR_DATA = 0x0C,
    CMD_ID_CAMERA_NEAR_DATA_DIFF = 0x0D,
    CMD_ID_CAMERA_NEAR_OTHERS = 0x0E,		// RoadMiddle, RoadMiddle_old, BlackLineRight, BlackLineLeft
    CMD_ID_CAMERA_NEAR_NUM_BORDERS = 0x0F,
    CMD_ID_CAMERA_FAR_DATA = 0x10,
    CMD_ID_CAMERA_FAR_DATA_DIFF = 0x11,
    CMD_ID_CAMERA_FAR_OTHERS = 0x12,		// RoadMiddle, RoadMiddle_old, BlackLineRight, BlackLineLeft
    CMD_ID_CAMERA_FAR_NUM_BORDERS = 0x13,
    CMD_ID_CAMERA_COMBINED_CENTER = 0x14,
    CMD_ID_SPEED = 0x15,
    CMD_ID_SERVO_ANGLE = 0x16,
	CMD_ID_STOP_WATCH = 0x017,
} CMD_ID;

extern uint8_t bee_CmdReceive[BEE_CMD_LENGTH];

/**
 * @brief Initialize UART0 to communicate with Bluetooth Bee module
 * @param callback : Function to call when a command is received
 * @param receiveBuffer : Pointer to a buffer to store data received from Bluetooth Bee module
 * @note IN FSL librairy, UART0 is manipulated by LPSCI0
 */
void bee_initCommunication(void (*callback)(void), uint8_t * receiveBuffer);

/**
 * @brief Start receiving data from Bluetooth Bee module to buffer  
 * @note IN FSL librairy, UART0 is manipulated by LPSCI0
 */
void bee_startReceivingData(void);

/**
 * @brief Check if a command is received
 * @param none
 * @return true if a command is received, false otherwise
 */
bool bee_checkCMDReceived(void);

/**
 * @brief Enable to send data to computer via Bluetooth Bee module
 */
void bee_enableSendData(void);

/**
 * @brief Stop sending data to Bluetooth Bee
 * @param none
 */
void bee_disableSendData(void);

/**
 * @brief Send data to computer via Bluetooth Bee module
 * @param ptrData : Pointer to data to send
 * @param lengthInByte : Length of data in bytess
 */
void bee_sendData(uint8_t * ptrData, uint32_t lengthInByte);

#ifdef __cplusplus
}
#endif

#endif /* BLUETOOTH_BEE_H_ */
