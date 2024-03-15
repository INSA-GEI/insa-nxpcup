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
 * Message format (Send direction):
 *     - Message ID : See MESSAGE_ID enum
 *     - Data Length MSB : 1 byte
 *     - Data Length LSB : 1 byte
 *     - Data : 0 - 1023 bytes
 */

/**
 * Command format (Receive direction):
 *     - Command ID : See CMD_ID enum
 *     - DataMSB : 1 byte
 *     - DataLSB : 1 byte
 *     - Checksum : 1 byte (XOR of all bytes from Command ID to DataLSB)
 */

#ifndef BLUETOOTH_BEE_H_
#define BLUETOOTH_BEE_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define BEE_BUFFER_SIZE	 30
#define BEE_CMD_LENGTH    4

typedef enum{
    MESSAGE_ID_CAMERA_NEAR_DATA = 0x01,
    MESSAGE_ID_CAMERA_NEAR_BORDER = 0x02,
    MESSAGE_ID_CAMERA_NEAR_CENTER = 0x03,
    MESSAGE_ID_CAMERA_FAR_DATA = 0x04,
    MESSAGE_ID_CAMERA_FAR_BORDER = 0x05,
    MESSAGE_ID_CAMERA_FAR_CENTER = 0x06,
    MESSAGE_ID_CAMERA_COMBINED_CENTER = 0x07,
    MESSAGE_ID_SPEED_LEFT = 0x08,
    MESSAGE_ID_SPEED_RIGHT = 0x09,
    MESSAGE_ID_SERVO_ANGLE = 0x0A,
} MESSAGE_ID;

typedef enum {
    /* CMD for changing parameters*/
    CMD_ID_ENGINE = 0x01,
    CMD_ID_CAMERA_MODE = 0x02,
    CMD_ID_CAMERA_KP = 0x03,
    CMD_ID_CAMERA_KI = 0x04,
    CMD_ID_CAMERA_KD = 0x05,
    CMD_ID_DIFFERENTIAL_KP = 0x06,
    CMD_ID_DIFFERENTIAL_KI = 0x07,
    CMD_ID_DIFFERENTIAL_KD = 0x08,
    CMD_ID_SPEED_START = 0x09,
    CMD_ID_SPEED_LIMIT = 0x0A,
    CMD_ID_SPEED_TURN = 0x0B,
    /* CMD for logging data */
    CMD_ID_CAMERA_NEAR_DATA = 0x0C,
    CMD_ID_CAMERA_NEAR_BORDER = 0x0D,
    CMD_ID_CAMERA_NEAR_CENTER = 0x0E,
    CMD_ID_CAMERA_FAR_DATA = 0x0F,
    CMD_ID_CAMERA_FAR_BORDER = 0x10,
    CMD_ID_CAMERA_FAR_CENTER = 0x11,
    CMD_ID_CAMERA_COMBINED_CENTER = 0x12,
    CMD_ID_SPEED = 0x13,
    CMD_ID_SERVO_ANGLE = 0x14,   
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
 * @brief Enable to send camera data to computer via Bluetooth Bee module
 * @param cameraData : Pointer to camera data
 * @param lengthInByte : Length of camera data in byte
 */
void bee_enableSendCameraData(uint16_t * cameraData, uint32_t lengthInByte);

/**
 * @brief Send camera data to computer via Bluetooth Bee module
 * @param None
 */
void bee_sendCameraData(void);


void bee_initTransferData(void);

#ifdef __cplusplus
}
#endif

#endif /* BLUETOOTH_BEE_H_ */
