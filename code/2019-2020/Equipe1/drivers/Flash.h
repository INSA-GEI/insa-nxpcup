/*
 * Flash.h
 *
 *  Created on: Feb 10, 2020
 *      Author: dimercur
 *      
 *  Code is based on driver found on Freescale/NXP website:
 *  	https://community.nxp.com/servlet/JiveServlet/downloadBody/94593-102-1-5584/MKL25_EEPROM_CW103.zip
 *  	
 *  This class implements low level routines for erasing and programming flash.
 *  Code tested on KL25 line of MCU
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "derivative.h"
#include "FlashConst.h"

/* -------------------- Function Pointer ------------------------------- */
typedef UINT32 (*pFLASHCOMMANDSEQUENCE) (PFLASH_SSD_CONFIG PSSDConfig, uint8_t index, uint8_t* pCommandArray);

/* Flash initialization */
typedef UINT32 (*pFLASHINIT) (PFLASH_SSD_CONFIG PSSDConfig);

/* P-Flash get protection */
typedef UINT32 (*pPFLASHGETPROTECTION) (PFLASH_SSD_CONFIG PSSDConfig, UINT32*  protectStatus);

/* P-Flash set protection */
typedef UINT32 (*pPFLASHSETPROTECTION) (PFLASH_SSD_CONFIG  PSSDConfig, UINT32  protectStatus);

/* Flash get interrupt enable */
typedef UINT32 (*pFLASHGETINTERRUPTENABLE) (PFLASH_SSD_CONFIG PSSDConfig, UINT8* interruptState);

/* Flash set interrupt enable */
typedef UINT32 (*pFLASHSETINTERRUPTENABLE) (PFLASH_SSD_CONFIG PSSDConfig, UINT8 interruptState);

/* Flash get security state */
typedef UINT32 (*pFLASHGETSECURITYSTATE) (PFLASH_SSD_CONFIG PSSDConfig, UINT8* securityState);

/* Flash security bypass */
typedef UINT32 (*pFLASHSECURITYBYPASS) (PFLASH_SSD_CONFIG PSSDConfig, UINT8* keyBuffer, \
		pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash erase all Block */
typedef UINT32 (*pFLASHERASEALLBLOCK) (PFLASH_SSD_CONFIG PSSDConfig, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash erase sector */
typedef UINT32 (*pFLASHERASESECTOR) (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash erase suspend */
typedef UINT32 (*pFLASHERASESUSPEND) (PFLASH_SSD_CONFIG PSSDConfig);

/* Flash erase resume */
typedef UINT32 (*pFLASHERASERESUME) (PFLASH_SSD_CONFIG PSSDConfig);

/* Flash checksum */
typedef UINT32 (*pFLASHCHECKSUM) (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32* PSum);

/* Flash verify all block */
typedef UINT32 (*pFLASHVERIFYALLBLOCK) (PFLASH_SSD_CONFIG PSSDConfig, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash verify section*/
typedef UINT32 (*pFLASHVERIFYSECTION) (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT16 Number, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash read once */
typedef UINT32 (*pFLASHREADONCE) (PFLASH_SSD_CONFIG PSSDConfig, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash program once */
typedef UINT32 (*pFLASHPROGRAMONCE) (PFLASH_SSD_CONFIG PSSDConfig, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash program check */
typedef UINT32 (*pFLASHPROGRAMCHECK) (PFLASH_SSD_CONFIG PSSDConfig, UINT32  destination, UINT32 size, UINT8* pExpectedData, UINT32* pFailAddr, UINT8*  pFailData, UINT8   marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

/* Flash read resource */
typedef UINT32 (*pFLASHREADRESOURCE) (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence);                                                                                    

/* Flash program Longword */
typedef UINT32 (*pFLASHPROGRAMLONGWORD) (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

class Flash {
protected:
	/* Internal function. Called by driver APIs only */
	/* Flash command sequence */
	UINT32 FlashCommandSequence(PFLASH_SSD_CONFIG PSSDConfig, UINT8 index, UINT8* pCommandArray);

public:
	Flash();
	virtual ~Flash();

	/* Flash initialisation */
	UINT32 FlashInit(PFLASH_SSD_CONFIG PSSDConfig);

	/* This function  prepares the D/E-Flash block for use
     *                     as D-Flash, E-Flash or a combination of both and 
     *                     initializes the EERAM.
     */
	UINT32 DEFlashPartition(PFLASH_SSD_CONFIG PSSDConfig, UINT8 EEEDataSizeCode, UINT8 DEPartitionCode, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	/* This function retrieves current D-Flash protection status. */
	UINT32 DFlashGetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8* protectStatus);
	
	/* This function sets the D-Flash protection to the intended protection status */
	UINT32 DFlashSetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8 protectStatus);
		
	/* P-Flash get protection */
	UINT32 PFlashGetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT32*  protectStatus);
		
	/* P-Flash set protection */
	UINT32 PFlashSetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT32  protectStatus);                                                

	/* Flash get interrupt enable */
	UINT32 FlashGetInterruptEnable(PFLASH_SSD_CONFIG PSSDConfig, UINT8* interruptState);

	/* Flash set interrupt enable */
	UINT32 FlashSetInterruptEnable(PFLASH_SSD_CONFIG PSSDConfig, UINT8 interruptState);

	/* Flash get security state */
	UINT32 FlashGetSecurityState(PFLASH_SSD_CONFIG PSSDConfig, UINT8* securityState);

	/* Flash security bypass */
	UINT32 FlashSecurityBypass(PFLASH_SSD_CONFIG PSSDConfig, UINT8* keyBuffer, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

	/* Flash erase all Block */
	UINT32 FlashEraseAllBlock(PFLASH_SSD_CONFIG PSSDConfig, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

	/* Flash erase sector */
	UINT32 FlashEraseSector(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

	/* Flash erase suspend */
	UINT32 FlashEraseSuspend(PFLASH_SSD_CONFIG PSSDConfig);

	/* Flash erase resume */
	UINT32 FlashEraseResume(PFLASH_SSD_CONFIG PSSDConfig);                                             

	/* Flash checksum */
	UINT32 FlashCheckSum(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32* PSum);

	/* Flash verify all block */
	UINT32 FlashVerifyAllBlock(PFLASH_SSD_CONFIG PSSDConfig, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

	/* Flash verify section*/
	UINT32 FlashVerifySection(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT16 Number, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);        

	/* Flash read once */
	UINT32 FlashReadOnce(PFLASH_SSD_CONFIG PSSDConfig, UINT8 recordIndex, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

	/* Flash read resource */
	UINT32 FlashReadResource(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence); 

	/* Flash program once */
	UINT32 FlashProgramOnce(PFLASH_SSD_CONFIG PSSDConfig, UINT8 recordIndex, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	/* Flash program check */
	UINT32 FlashProgramCheck(PFLASH_SSD_CONFIG PSSDConfig, UINT32  destination, UINT32  size, UINT8*  pExpectedData, UINT32* pFailAddr, UINT8*  pFailData, UINT8   marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);

	/* Flash program Longword */
	UINT32 FlashProgramLongword(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	/* The Erase Flash Block operation will erase all addresses in a single P-Flash or D-Flash block.*/
	UINT32 FlashEraseBlock (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	/* Program data into Flash*/
	UINT32 FlashProgramPhrase(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	/* Program data into Flash */
	UINT32 FlashProgramSection(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT16 Number, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	/* This function will check to see if an entire 
	*                     P-Flash or D-Flash block has been erased to the
	*                     specifed margin level. 
	*/
	UINT32 FlashVerifyBlock(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence);
	
	
};

#endif /* FLASH_H_ */
