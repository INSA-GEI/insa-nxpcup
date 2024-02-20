/*
 * bluetooth_bee.h
 *
 *  Created on: 7 févr. 2024
 *      Author: Triet Nguyen (Github : trietngh)
 */
/*
 * Driver for Bluetooth Bee module, it's use to send debug data to computer.
 * Configuration :
 * 	- UART0
 * 	- TX : PTE20
 * 	- RX : PTE21
 * 	- Baud rate : 9600
 * 	- Parity : None
 * 	- Stop bit : 1
 * 	- Length : 8
 * 	*/

#ifndef BLUETOOTH_BEE_H_
#define BLUETOOTH_BEE_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void bee_init(void);
void bee_sendData(uint16_t * data, uint8_t data_length);

#ifdef __cplusplus
}
#endif

#endif /* BLUETOOTH_BEE_H_ */
