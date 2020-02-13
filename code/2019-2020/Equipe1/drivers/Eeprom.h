/*
 * Eeprom.h
 *
 *  Created on: Feb 13, 2020
 *      Author: dimercur
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "derivative.h"
#include "Flash.h"

class Eeprom: public Flash {
public:
	Eeprom();
	virtual ~Eeprom();
	
	UINT32 toto;
	
	/* This function is used to change the function of 
	*                     the EERAM. When not partitioned for EEE, the EERAM 
	*                     is typically used as traditional RAM. When partitioned 
	*                     for EEE, the EERAM is typically used to store EEE data.
	*/
	UINT32 SetEEEEnable(PFLASH_SSD_CONFIG PSSDConfig, UINT8 EEEEnable);
	
	/*This function retrieves current EERAM protection status.*/
	UINT32 EERAMSetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8 protectStatus);
	
	/* This function retrieves current EERAM protection status. */
	UINT32 EERAMGetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8* protectStatus);
	
	/* This function is used to write data to EERAM 
	*                     when it is used as EEPROM emulator     
	*/
	UINT32 EEEWrite(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source);
};

#endif /* EEPROM_H_ */
