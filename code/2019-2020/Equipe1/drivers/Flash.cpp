/*
 * Flash.cpp
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

#include "Flash.h"

#if (CPU_CORE == DSC_56800EX)
#define WORD2BYTE(x) ((x)<<1)
#else
#define WORD2BYTE(x) (x)
#endif

Flash::Flash() {
	// Nothing to do 

}

Flash::~Flash() {
	// TODO Auto-generated destructor stub
}

/* Internal function. Called by driver APIs only */
/* Flash command sequence */
UINT32  Flash::FlashCommandSequence (PFLASH_SSD_CONFIG PSSDConfig, UINT8 index, UINT8* pCommandArray)                                             
{
	UINT8  counter;          /* for loop counter variable */
	UINT8  registerValue;    /* store data read from flash register */
	UINT32 returnCode;       /* return code variable */

	/* set the default return as FTFx_OK */
	returnCode = FTFx_OK;

	/* check CCIF bit of the flash status register */

	while(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
	{
		/* wait till CCIF bit is set */
	}

	/* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, \
			(FTFx_SSD_FSTAT_RDCOLERR | FTFx_SSD_FSTAT_ACCERR | FTFx_SSD_FSTAT_FPVIOL));

	/* load FCCOB registers */
	for(counter=0; counter<=index; counter++)
	{
		switch (counter)
		{
		case 0: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB0_OFFSET, pCommandArray[counter]);
		break;
		case 1: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB1_OFFSET, pCommandArray[counter]);
		break;
		case 2: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB2_OFFSET, pCommandArray[counter]);
		break;
		case 3: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB3_OFFSET, pCommandArray[counter]);
		break;
		case 4: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB4_OFFSET, pCommandArray[counter]);
		break;
		case 5: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB5_OFFSET, pCommandArray[counter]);
		break;
		case 6: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB6_OFFSET, pCommandArray[counter]);
		break;
		case 7: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB7_OFFSET, pCommandArray[counter]);
		break;
		case 8: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB8_OFFSET, pCommandArray[counter]);
		break;
		case 9: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB9_OFFSET, pCommandArray[counter]);
		break;
		case 10: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBA_OFFSET, pCommandArray[counter]);
		break;
		case 11: REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBB_OFFSET, pCommandArray[counter]);
		break;
		default: break;
		}
	}

	/* clear CCIF bit */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF);

	/* check CCIF bit */
	while(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
	{
		/* wait till CCIF bit is set */
		/* serve callback function if counter reaches limitation */
		if(NULL_CALLBACK != PSSDConfig->CallBack)
		{
			(PSSDConfig->CallBack)();
		}
		else
		{
			/* do nothing */
		}
	}

	/* Check error bits */
	/*Get flash status register value */
	registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET);

	/* checking access error */
	if(0 != (registerValue & FTFx_SSD_FSTAT_ACCERR))
	{
		/* return an error code FTFx_ERR_ACCERR */
		returnCode = FTFx_ERR_ACCERR;
	}
	/* checking protection error */
	else if(0 != (registerValue & FTFx_SSD_FSTAT_FPVIOL))
	{
		/* return an error code FTFx_ERR_PVIOL */
		returnCode = FTFx_ERR_PVIOL;
	}
	/* checking MGSTAT0 non-correctable error */
	else if(0 != (registerValue & FTFx_SSD_FSTAT_MGSTAT0))
	{
		/* return an error code FTFx_ERR_MGSTAT0 */
		returnCode = FTFx_ERR_MGSTAT0;
	}
	else
	{
		/* do nothing*/
	}

	return(returnCode);
}

/* Flash initialisation */
UINT32 Flash::FlashInit (PFLASH_SSD_CONFIG PSSDConfig)
{
#if (DEBLOCK_SIZE != 0)
	UINT8  EEEDataSetSize;    /* store EEE Data Set Size */
	UINT8  DEPartitionCode;    /* store D/E-Flash Partition Code */
#endif
	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

#if (DEBLOCK_SIZE != 0)    

	while(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
	{
		/* wait till CCIF bit is set */
	}

	/* clear RDCOLERR & ACCERR & FPVIOL flag in flash status register */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, \
			(FTFx_SSD_FSTAT_RDCOLERR | FTFx_SSD_FSTAT_ACCERR | FTFx_SSD_FSTAT_FPVIOL)); 

	/* Write Command Code to FCCOB0 */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB0_OFFSET, FTFx_READ_RESOURCE);
	/* Write address to FCCOB1/2/3 */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB1_OFFSET, ((UINT8)(DFLASH_IFR_READRESOURCE_ADDRESS >> 16)));
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB2_OFFSET, ((UINT8)((DFLASH_IFR_READRESOURCE_ADDRESS >> 8) & 0xFF)));
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB3_OFFSET, ((UINT8)(DFLASH_IFR_READRESOURCE_ADDRESS & 0xFF)));

	/* Write Resource Select Code of 0 to FCCOB8 to select IFR. Without this, */
	/* an access error may occur if the register contains data from a previous command. */
#if (FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE)
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB4_OFFSET, 0);
#else
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB8_OFFSET, 0);
#endif
	/* clear CCIF bit */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF);

	/* check CCIF bit */
	while((REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)) == FALSE)
	{
		/* wait till CCIF bit is set */
	}

	/* Read returned value of FCCOB6/7 or FCCOBA,B to the variables */
#if (FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE)
	EEEDataSetSize = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBA_OFFSET);
	DEPartitionCode = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBB_OFFSET);
#else
	EEEDataSetSize = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB6_OFFSET);
	DEPartitionCode = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB7_OFFSET);
#endif    
	/* Calculate D-Flash size and EEE size */
	switch (DEPartitionCode & 0x0F)
	{
	case 0: PSSDConfig->DFlashBlockSize = DEPART_0000; break;
	case 1: PSSDConfig->DFlashBlockSize = DEPART_0001; break;
	case 2: PSSDConfig->DFlashBlockSize = DEPART_0010; break;
	case 3: PSSDConfig->DFlashBlockSize = DEPART_0011; break;
	case 4: PSSDConfig->DFlashBlockSize = DEPART_0100; break;
	case 5: PSSDConfig->DFlashBlockSize = DEPART_0101; break;
	case 6: PSSDConfig->DFlashBlockSize = DEPART_0110; break;
	case 7: PSSDConfig->DFlashBlockSize = DEPART_0111; break;
	case 8: PSSDConfig->DFlashBlockSize = DEPART_1000; break;
	case 9: PSSDConfig->DFlashBlockSize = DEPART_1001; break;
	case 10: PSSDConfig->DFlashBlockSize = DEPART_1010; break;
	case 11: PSSDConfig->DFlashBlockSize = DEPART_1011; break;
	case 12: PSSDConfig->DFlashBlockSize = DEPART_1100; break;
	case 13: PSSDConfig->DFlashBlockSize = DEPART_1101; break;
	case 14: PSSDConfig->DFlashBlockSize = DEPART_1110; break;
	case 15: PSSDConfig->DFlashBlockSize = DEPART_1111; break;
	default: break;
	}

	switch (EEEDataSetSize & 0x0F)
	{
	case 0: PSSDConfig->EEEBlockSize = EEESIZE_0000; break;
	case 1: PSSDConfig->EEEBlockSize = EEESIZE_0001; break;
	case 2: PSSDConfig->EEEBlockSize = EEESIZE_0010; break;
	case 3: PSSDConfig->EEEBlockSize = EEESIZE_0011; break;
	case 4: PSSDConfig->EEEBlockSize = EEESIZE_0100; break;
	case 5: PSSDConfig->EEEBlockSize = EEESIZE_0101; break;
	case 6: PSSDConfig->EEEBlockSize = EEESIZE_0110; break;
	case 7: PSSDConfig->EEEBlockSize = EEESIZE_0111; break;
	case 8: PSSDConfig->EEEBlockSize = EEESIZE_1000; break;
	case 9: PSSDConfig->EEEBlockSize = EEESIZE_1001; break;
	case 10: PSSDConfig->EEEBlockSize = EEESIZE_1010; break;
	case 11: PSSDConfig->EEEBlockSize = EEESIZE_1011; break;
	case 12: PSSDConfig->EEEBlockSize = EEESIZE_1100; break;
	case 13: PSSDConfig->EEEBlockSize = EEESIZE_1101; break;
	case 14: PSSDConfig->EEEBlockSize = EEESIZE_1110; break;
	case 15: PSSDConfig->EEEBlockSize = EEESIZE_1111; break;
	default: break;
	}        
#else /* DEBLOCK_SIZE == 0 */
	/* If size of D/E-Flash = 0 */
	PSSDConfig->DFlashBlockSize = 0;
	PSSDConfig->EEEBlockSize = 0;
#endif /* of DEBLOCK_SIZE */

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
	}

	return(returnCode);
}

/* P-Flash get protection */
UINT32 Flash::PFlashGetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT32*  protectStatus)
{
	UINT32 registerValue0;
	UINT32 registerValue1;
	UINT32 registerValue2;
	UINT32 registerValue3;

	registerValue0=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT0_OFFSET));
	registerValue1=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT1_OFFSET));
	registerValue2=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT2_OFFSET));
	registerValue3=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT3_OFFSET));

	*protectStatus = ((registerValue0 << 24 ) | \
			(registerValue1 << 16 ) | \
			(registerValue2 << 8 ) | \
			registerValue3); 

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(FTFx_OK);
}

/* P-Flash set protection */
UINT32 Flash::PFlashSetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT32  protectStatus)
{
	UINT32 registerValue;    /* store data read from flash register */
	UINT32 returnCode;       /* return code variable */
	UINT32 temp;
	UINT32 registerValue0;
	UINT32 registerValue1;
	UINT32 registerValue2;
	UINT32 registerValue3;

	/* set the default return as FTFx_OK */
	returnCode = FTFx_OK;
	/* check CCIF bit of the flash status register, it's impossible to write to FPROT if command is in progress */
	if(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
	{
		returnCode = FTFx_ERR_CHANGEPROT;
		goto EXIT;
	}
	/* Read the value of FPPROT registers */
	registerValue0=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT0_OFFSET));
	registerValue1=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT1_OFFSET));
	registerValue2=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT2_OFFSET));
	registerValue3=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT3_OFFSET));

	registerValue = ((registerValue0 << 24 ) | \
			(registerValue1 << 16 ) | \
			(registerValue2 << 8 ) | \
			registerValue3); 

	/* Check if normal mode */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT0_OFFSET, 0xFF);
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT1_OFFSET, 0xFF);
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT2_OFFSET, 0xFF);
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT3_OFFSET, 0xFF);

	/* Read the value of FPPROT registers */
	registerValue0=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT0_OFFSET));
	registerValue1=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT1_OFFSET));
	registerValue2=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT2_OFFSET));
	registerValue3=(UINT32)(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT3_OFFSET));

	if((registerValue0 != 0xFF) || (registerValue1 != 0xFF) || \
			(registerValue2 != 0xFF) || (registerValue3 != 0xFF))
	{
		/* if normal mode */
		temp = protectStatus ^ registerValue;
		if(temp & protectStatus)
		{
			returnCode = FTFx_ERR_CHANGEPROT;    
			goto EXIT;
		}
	}   
	/* if unprotected or special mode */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT0_OFFSET, (UINT8)(protectStatus >> 24));
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT1_OFFSET, (UINT8)(protectStatus >> 16));
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT2_OFFSET, (UINT8)(protectStatus >> 8));
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FPROT3_OFFSET, (UINT8)protectStatus);

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
	}

	return(returnCode);
}

/* Flash get interrupt enable */
UINT32 Flash::FlashGetInterruptEnable(PFLASH_SSD_CONFIG PSSDConfig, UINT8* interruptState)
{
	/* store data read from flash register */
	UINT8  registerValue;

	/* Initial interrupt state value */
	*interruptState = 0;

	/*Get flash configration register value */
	registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET);

	/* Add command complete interrupt enable bit value */
	/* CCIE bit of the FCNFG register */
	*interruptState |= (registerValue & (FTFx_SSD_FCNFG_CCIE | FTFx_SSD_FCNFG_RDCOLLIE));

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(FTFx_OK);
}

/* Flash set interrupt enable */
UINT32 Flash::FlashSetInterruptEnable(PFLASH_SSD_CONFIG PSSDConfig, UINT8 interruptState)
{
	/* store data read from flash register */
	UINT8  registerValue;
	UINT16 i;

	/* Mask off unused bits in interruptState */
	interruptState &= (FTFx_SSD_FCNFG_CCIE | FTFx_SSD_FCNFG_RDCOLLIE);

	/*Get flash configration register value */
	registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET);

	/* Set register value with desired interrupt state */
	registerValue &= ~(FTFx_SSD_FCNFG_CCIE | FTFx_SSD_FCNFG_RDCOLLIE);
	registerValue |= interruptState;
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, registerValue);
	/* wait for setting bits affected */
	for (i = 0x1000; i >0; i++){}
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(FTFx_OK);
}

/* Flash get security state */
UINT32 Flash::FlashGetSecurityState(PFLASH_SSD_CONFIG PSSDConfig, UINT8* securityState)
{
	/* store data read from flash register */
	UINT8  registerValue;

	/*Get flash security register value */
	registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FSEC_OFFSET);

	/* check the status of the flash security bits in the security register */
	if(FLASH_SECURITY_STATE_UNSECURED == (registerValue & FTFx_SSD_FSEC_SEC))
	{
		/* Flash in unsecured state */
		*securityState = FLASH_NOT_SECURE;
	}
	else
	{
		/* Flash in secured state */
		/* check for backdoor key security enable bit */
		if(FLASH_SECURITY_STATE_KEYEN == (registerValue & FTFx_SSD_FSEC_KEYEN))
		{
			/* Backdoor key security enabled */
			*securityState = FLASH_SECURE_BACKDOOR_ENABLED;
		}
		else
		{
			/* Backdoor key security disabled */
			*securityState = FLASH_SECURE_BACKDOOR_DISABLED;
		}
	}

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(FTFx_OK);
}

/* Flash security bypass */
UINT32 Flash::FlashSecurityBypass(PFLASH_SSD_CONFIG PSSDConfig, UINT8* keyBuffer, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 pCommandArray[12]; /* command sequence array */
	UINT8 registerValue;    /* registerValue */
	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/*Get flash security register value */
	registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FSEC_OFFSET);

	if (0x02 != (registerValue & 0x03)) 
	{
		/* preparing passing parameter to erase a flash block */
		pCommandArray[0] = FTFx_SECURITY_BY_PASS;
		pCommandArray[4] = keyBuffer[0];
		pCommandArray[5] = keyBuffer[1];
		pCommandArray[6] = keyBuffer[2];
		pCommandArray[7] = keyBuffer[3];
		pCommandArray[8] = keyBuffer[4];
		pCommandArray[9] = keyBuffer[5];
		pCommandArray[10] = keyBuffer[6];
		pCommandArray[11] = keyBuffer[7];

		/* calling flash command sequence function to execute the command */
		returnCode = FlashCommandSequence(PSSDConfig, 11, pCommandArray);
	}

	/* Giving Control to BDM if enabled */
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash erase all Block */
UINT32 Flash::FlashEraseAllBlock(PFLASH_SSD_CONFIG PSSDConfig, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 commandArray[1];     /* command sequence array */
	UINT32 returnCode;         /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* preparing passing parameter to erase all flash blocks */
	/* 1st element for the FCCOB register */
	commandArray[0] = FTFx_ERASE_ALL_BLOCK;

	/* calling flash command sequence function to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 0, commandArray);

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash erase sector */
UINT32 Flash::FlashEraseSector(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 pCommandArray[4]; /* command sequence array */
	UINT32 returnCode;      /* return code variable */
	UINT32 endAddress;      /* storing end address */
	UINT32 sectorSize;        /* size of one sector */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* calculating Flash end address */
	endAddress = destination + BYTE2WORD(size);
	/* check for valid range of the target addresses */
	if((destination < PSSDConfig->PFlashBlockBase) || \
			(endAddress > (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
	{
#if (DEBLOCK_SIZE)    	
		if((destination < PSSDConfig->DFlashBlockBase) || \
				(endAddress > (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
		{
#endif /* End of if(DEBLOCK_SIZE) */ 
			/* return an error code FTFx_ERR_RANGE */
			returnCode = FTFx_ERR_RANGE;
			goto EXIT;
#if (DEBLOCK_SIZE)
		}
		else
		{
			/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
			destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
#else    	
			destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif            
			sectorSize = FTFx_DSECTOR_SIZE;				
		}
#endif /* End of #if(DEBLOCK_SIZE) */        
	}
	else
	{
		/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
		destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
		destination -= PSSDConfig->PFlashBlockBase;
#endif        
		sectorSize = FTFx_PSECTOR_SIZE;
	}

	/* check if the destination is sector aligned or not */
	if (destination & (sectorSize-1))
	{
		/* return an error code FTFx_ERR_ADDR */
		returnCode = FTFx_ERR_ADDR;
		goto EXIT;
	}

	/* check if the size is sector alignment or not */
	if(size & (sectorSize-1))
	{
		/* return an error code FTFx_ERR_SIZE */
		returnCode = FTFx_ERR_SIZE;
		goto EXIT;
	}

	/* check for error return code */
	if(FTFx_OK == returnCode)
	{

		while(size > 0)
		{
			/* preparing passing parameter to erase a flash block */
			pCommandArray[0] = FTFx_ERASE_SECTOR;
			pCommandArray[1] = (UINT8)(destination >> 16);
			pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
			pCommandArray[3] = (UINT8)(destination & 0xFF);

			/* calling flash command sequence function to execute the command */
			returnCode = FlashCommandSequence(PSSDConfig, 3, pCommandArray);

			/* checking the success of command execution */
			if(FTFx_OK != returnCode)
			{
				break;
			}
			else
			{
				/* update size and destination address */
				size -= sectorSize;
				destination += sectorSize;
			}
		}
	}

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash erase suspend */
UINT32 Flash::FlashEraseSuspend(PFLASH_SSD_CONFIG PSSDConfig)
{
	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* check CCIF bit of the flash status register */
	if(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
	{
		/* If the command write sequence in progressing, */
		/* Set ERSSUSP bit in FCNFG register */
		REG_BIT_SET(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, FTFx_SSD_FCNFG_ERSSUSP);
		while(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
		{
			/* wait till CCIF bit is set */
		}
	}
	else
	{
		/* Do nothing */
	}

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash erase resume */
UINT32 Flash::FlashEraseResume(PFLASH_SSD_CONFIG PSSDConfig)
{

	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;
	/* check ERSSUSP bit of the flash configuration register */
	if(TRUE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, FTFx_SSD_FCNFG_ERSSUSP)))
	{
		/* If the ERSSUSP bit is set, */
		/* Clear CCIF bit to resumimg the previous suspended Erasing */
		REG_BIT_CLEAR(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF);
	}
	else
	{
		/* Do nothing */
	}

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash checksum */
UINT32 Flash::FlashCheckSum(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32* PSum)
{
	UINT32 counter;          /* Counter for callback operation */
	UINT32 data;             /* Data read from Flash address */
	UINT32 returnCode;       /* Return code variable */
	UINT32 endAddress;       /* P Flash end address */

	/* initialize counter variable */
	counter = 0;
	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* calculating Flash end address */
	endAddress = WORD2BYTE(destination) + size;

	/* check for valid range of the target addresses */
	if((destination < PSSDConfig->PFlashBlockBase) || \
			(endAddress > (WORD2BYTE(PSSDConfig->PFlashBlockBase) + PSSDConfig->PFlashBlockSize)))
	{
#if(DEBLOCK_SIZE)    	
		if((destination < PSSDConfig->DFlashBlockBase) || \
				(endAddress > (WORD2BYTE(PSSDConfig->DFlashBlockBase) + PSSDConfig->DFlashBlockSize)))
		{
#endif /* End of if(DEBLOCK_SIZE) */         	
			/* return an error code FTFx_ERR_RANGE */
			returnCode = FTFx_ERR_RANGE;
			goto EXIT;
#if(DEBLOCK_SIZE)              
		}
		else
		{
			/* No Error: Do nothing */
		}
#endif /* End of if(DEBLOCK_SIZE) */        
	}
	else
	{
		/* No Error: Do nothing */
	}
#if DSC_56800EX == CPU_CORE
	destination *=2;
	endAddress = destination + size;
#endif	
	if(FTFx_OK == returnCode)
	{       
		*PSum = 0;
		/* doing sum operation */
		while(destination < endAddress)
		{          
			data = READ8(destination);
			*PSum += (UINT32)data;
			destination += 1;
			size -= 1;

			/* Check if need to serve callback function */
			if((++counter) >= FLASH_CALLBACK_CS)
			{
				/* serve callback function if counter reaches limitation */
				if(NULL_CALLBACK != PSSDConfig->CallBack)
				{
					(PSSDConfig->CallBack)();
				}
				else
				{
					/* do nothing */
				}

				/* Reset counter */
				counter = 0;
			}
			else
			{
				/* do nothing */
			}
		}            
	}
	else
	{
		/* error occurred */
	}

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash verify all block */
UINT32 Flash::FlashVerifyAllBlock(PFLASH_SSD_CONFIG PSSDConfig, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 pCommandArray[2]; /* command sequence array */
	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* preparing passing parameter to verify all block command*/
	pCommandArray[0] = FTFx_VERIFY_ALL_BLOCK;
	pCommandArray[1] = marginLevel;

	/* calling flash command sequence function to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 1, pCommandArray);

	/* Giving Control to BDM if enabled */
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash verify section*/
UINT32 Flash::FlashVerifySection(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT16 Number, UINT8 marginLevel, \
		pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 pCommandArray[7]; /* command sequence array */
	UINT32 returnCode;      /* return code variable */

	volatile UINT32 endAddress __attribute__((unused));      /* storing end address. This is the starting point of the next block */

	UINT32 sectionAlign;

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* check for valid range of the destination */
	if((UINT32)(destination - PSSDConfig->PFlashBlockBase) < BYTE2WORD(PSSDConfig->PFlashBlockSize))
	{
		/* calculating Flash end address */
		endAddress = destination + Number * PRD1SEC_ALIGN_SIZE;
	}
#if(DEBLOCK_SIZE)    
	else if((UINT32)(destination - PSSDConfig->DFlashBlockBase) <BYTE2WORD(PSSDConfig->DFlashBlockSize))
	{
		/* calculating Flash end address */
		endAddress = destination + Number * DRD1SEC_ALIGN_SIZE;
	}
#endif /* End of #if(DEBLOCK_SIZE) */    
	else
	{
		/* return an error code FTFx_ERR_RANGE */
		returnCode = FTFx_ERR_RANGE;
		goto EXIT;
	}

	/* check for valid range of end address */
	if((UINT32)(destination - PSSDConfig->PFlashBlockBase) < BYTE2WORD(PSSDConfig->PFlashBlockSize))
	{
		/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
		destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
		destination -= PSSDConfig->PFlashBlockBase;
#endif 
		sectionAlign = PRD1SEC_ALIGN_SIZE;
	}
#if(DEBLOCK_SIZE)   
	else if((UINT32)(destination - PSSDConfig->DFlashBlockBase) < BYTE2WORD(PSSDConfig->DFlashBlockSize))
	{
		/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
		destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
#else    	
		destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif 
		sectionAlign = DRD1SEC_ALIGN_SIZE;
	}    
#endif /* End of #if(DEBLOCK_SIZE */    
	else
	{
		/* return an error code FTFx_ERR_RANGE */
		returnCode = FTFx_ERR_RANGE;
		goto EXIT;
	}

	/* check if the destination is aligned or not */
#if DSC_56800EX == CPU_CORE    
	if (destination &(2*sectionAlign-1))
#else
		if (destination & (sectionAlign-1))
#endif    	
		{
			/* return an error code FTFx_ERR_ADDR */
			returnCode = FTFx_ERR_ADDR;
			goto EXIT;
		}

	/* preparing passing parameter to verify section command */
	pCommandArray[0] = FTFx_VERIFY_SECTION;
	pCommandArray[1] = (UINT8)(destination >> 16);
	pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
	pCommandArray[3] = (UINT8)(destination & 0xFF);
	pCommandArray[4] = (UINT8)(Number >> 8);
	pCommandArray[5] = (UINT8)(Number & 0xFF);
	pCommandArray[6] = marginLevel;

	/* calling flash command sequence function to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 6, pCommandArray);

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif 
	}

	return(returnCode);
}

/* Flash read once */
UINT32 Flash::FlashReadOnce(PFLASH_SSD_CONFIG PSSDConfig, UINT8 recordIndex, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8  pCommandArray[2]; /* command sequence array */
	UINT32 returnCode;       /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* preparing passing parameter for read once command */
	/* 1st element for the FCCOB register */
	pCommandArray[0] = FTFx_READ_ONCE;

	/* 2nd element for the FCCOB register */
	pCommandArray[1] = recordIndex;

	/* calling flash command sequence API to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 1, pCommandArray);

	/* checking for the success of command execution */
	if(FTFx_OK == returnCode)
	{
		/* Read the data from the FCCOB registers into the pDataArray */
		pDataArray[0] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB4_OFFSET);
		pDataArray[1] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB5_OFFSET);
		pDataArray[2] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB6_OFFSET);
		pDataArray[3] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB7_OFFSET);
#if ((FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE) || (FTFx_KX_1024K_0K_16K_4K_0K == FLASH_DERIVATIVE))
		pDataArray[4] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB8_OFFSET);
		pDataArray[5] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB9_OFFSET);
		pDataArray[6] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBA_OFFSET);
		pDataArray[7] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBB_OFFSET);
#endif
	}
	else
	{
		/* do nothing */
	}

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash program once */
UINT32 Flash::FlashProgramOnce(PFLASH_SSD_CONFIG PSSDConfig, UINT8 recordIndex, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
#if ((FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE) || (FTFx_KX_1024K_0K_16K_4K_0K == FLASH_DERIVATIVE))    
	UINT8  pCommandArray[0xC]; /* command sequence array */
#else
	UINT8  pCommandArray[0x8]; /* command sequence array */
#endif 
	UINT32 returnCode;       /* return code variable */
	UINT8  commandArraySize = 0x07;      

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;
	/* set the counter value for 0 */

	/* preparing passing parameter for program once command */
	/* 1st element for the FCCOB register */
	pCommandArray[0] = FTFx_PROGRAM_ONCE;

	/* preparing the rest of the parameters to be passed for the FCCOB registers */
	pCommandArray[1] = recordIndex;
	pCommandArray[2] = 0x00;
	pCommandArray[3] = 0x00;
	pCommandArray[4] = pDataArray[0];
	pCommandArray[5] = pDataArray[1];
	pCommandArray[6] = pDataArray[2];
	pCommandArray[7] = pDataArray[3];
#if ((FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE) || (FTFx_KX_1024K_0K_16K_4K_0K == FLASH_DERIVATIVE))
	pCommandArray[8] = pDataArray[4];
	pCommandArray[9] = pDataArray[5];
	pCommandArray[10] = pDataArray[6];
	pCommandArray[11] = pDataArray[7];
	commandArraySize = 0xB;
#endif

	/* calling flash command sequence API to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, commandArraySize, pCommandArray);


	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif 
	}

	return(returnCode);
}

/* Flash program check */
UINT32 Flash::FlashProgramCheck(PFLASH_SSD_CONFIG PSSDConfig, UINT32  destination, UINT32  size, UINT8*  pExpectedData, UINT32* pFailAddr, UINT8*  pFailData, UINT8   marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 pCommandArray[12]; /* command sequence array */
	UINT32 returnCode;      /* return code variable */
#if DSC_56800EX == CPU_CORE
	UINT8 PFlashFlag;
#endif    

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* check if the destination is Longword aligned or not */
	if ((destination & (PGMCHK_ALIGN_SIZE - 1)))
	{
		/* return an error code FTFx_ERR_ADDR */
		returnCode = FTFx_ERR_ADDR;
		goto EXIT;
	}

	/* check if the size is Longword aligned or not */
#if DSC_56800EX == CPU_CORE    
	if (size & (2*PGMCHK_ALIGN_SIZE - 1))
#else
		if (size & (PGMCHK_ALIGN_SIZE - 1))
#endif    	
		{
			/* return an error code FTFx_ERR_ADDR */
			returnCode = FTFx_ERR_SIZE;
			goto EXIT;
		}

	/* check for valid range of the target addresses */    
	if((destination < PSSDConfig->PFlashBlockBase) || \
			((destination+BYTE2WORD(size)) > (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
	{
#if(DEBLOCK_SIZE)    	
		if((destination < PSSDConfig->DFlashBlockBase) || \
				((destination+BYTE2WORD(size)) > (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
		{
#endif /* End of #if(DEBLOCK_SIZE) */         	
			/* return an error code FTFx_ERR_RANGE */
			returnCode = FTFx_ERR_RANGE;
			goto EXIT;
#if (DEBLOCK_SIZE)            
		}
		else
		{
			/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
			destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
			PFlashFlag = 0;
#else    	
			destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif  
		}
#endif /* End of #if(DEBLOCK_SIZE) */        
	}
	else
	{
		/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
		destination = (2*(destination - PSSDConfig->PFlashBlockBase));
		PFlashFlag = 1;
#else    	
		destination -= PSSDConfig->PFlashBlockBase;
#endif 
	}
	while (size)
	{
		/* check for error return code */
		if(FTFx_OK == returnCode)
		{
			/* preparing passing parameter to program check the flash block */
			pCommandArray[0] = FTFx_PROGRAM_CHECK;
			pCommandArray[1] = (UINT8)(destination >> 16);
			pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
			pCommandArray[3] = (UINT8)(destination & 0xFF);
			pCommandArray[4] = marginLevel;        
#if (ENDIANNESS == BIG_ENDIAN)  /* Big Endian */
			pCommandArray[8] = *pExpectedData;
			pCommandArray[9] = *(pExpectedData+1);
			pCommandArray[10] = *(pExpectedData+2);
			pCommandArray[11] = *(pExpectedData+3);
#else /* Little Endian */
			pCommandArray[8] = *(pExpectedData+3);
			pCommandArray[9] = *(pExpectedData+2);
			pCommandArray[10] = *(pExpectedData+1);
			pCommandArray[11] = *pExpectedData;
#endif
			/* calling flash command sequence function to execute the command */
			returnCode = FlashCommandSequence(PSSDConfig, 11, pCommandArray);

			/* checking for the success of command execution */
			if(FTFx_OK != returnCode)
			{
#if DSC_56800EX == CPU_CORE
				/* Convert to global address in Nevis2 */
				if(PFlashFlag)
				{
					*pFailAddr = (destination >>1) + PSSDConfig->PFlashBlockBase;
				}
#if (DEBLOCK_SIZE) 
				else
				{
					*pFailAddr = (destination>>1) + PSSDConfig->DFlashBlockBase - 0x400000;
				}
#endif
#else            	
				*pFailAddr  =  destination;
#endif
				/* Read fail returned data: if K70, Nevis2, L1PT, L2K are selected */
#if ((FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE) || (FTFx_KX_1024K_0K_16K_4K_0K == FLASH_DERIVATIVE)\
		||(FTFx_NX_256K_32K_2K_2K_1K == FLASH_DERIVATIVE)||(FTFx_NX_128K_32K_2K_2K_1K == FLASH_DERIVATIVE)\
		||(FTFx_NX_96K_32K_2K_2K_1K == FLASH_DERIVATIVE)||(FTFx_NX_64K_32K_2K_2K_1K == FLASH_DERIVATIVE)\
		||(FTFx_LX_128K_0K_0K_1K_0K == FLASH_DERIVATIVE)||(FTFx_LX_96K_0K_0K_1K_0K == FLASH_DERIVATIVE)\
		||(FTFx_LX_64K_0K_0K_1K_0K == FLASH_DERIVATIVE)||(FTFx_LX_32K_0K_0K_1K_0K == FLASH_DERIVATIVE)\
		||(FTFx_LX_8K_0K_0K_1K_0K == FLASH_DERIVATIVE))
				*pFailData = 0x0;
				*(pFailData+1) = 0x0;
				*(pFailData+2) = 0x0;
				*(pFailData+3) = 0x0;
#else /*other derivative */               
#if (ENDIANNESS == BIG_ENDIAN)  /* Big Endian */  
				*pFailData = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB4_OFFSET);
				*(pFailData+1) = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB5_OFFSET);
				*(pFailData+2) = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB6_OFFSET);
				*(pFailData+3) = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB7_OFFSET);    
#else /* Little Endian */
				*(pFailData+3) = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB4_OFFSET);
				*(pFailData+2) = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB5_OFFSET);
				*(pFailData+1) = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB6_OFFSET);
				*pFailData = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB7_OFFSET);
#endif /*of ENDIANNESS */
#endif /* of FLASH_DERIVATIVE */
				goto EXIT;
			}
		}
		size-=FTFx_LONGWORD_SIZE;
		pExpectedData+=FTFx_LONGWORD_SIZE;
		destination+= FTFx_LONGWORD_SIZE;
	}

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif 
	}

	return(returnCode);
}

/* Flash read resource */
UINT32 Flash::FlashReadResource(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT8* pDataArray, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8  pCommandArray[9]; /* command sequence array */
	UINT32 returnCode;       /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* check if the destination is longword aligned or not */
	if (destination & (RDRSRC_ALIGN_SIZE-1))
	{
		/* return an error code FTFx_ERR_ADDR */
		returnCode = FTFx_ERR_ADDR;
		goto EXIT;
	}

	/* check for valid range of the target addresses */    
	if((destination < ( PSSDConfig->PFlashBlockBase + BYTE2WORD(PFLASH_IFR_OFFSET) )) || \
			(destination >= ( PSSDConfig->PFlashBlockBase + BYTE2WORD(PFLASH_IFR_SIZE ))))
	{
#if(DEBLOCK_SIZE)    	
		if((destination < ( PSSDConfig->DFlashBlockBase + BYTE2WORD(DFLASH_IFR_OFFSET) )) || \
				(destination >= ( PSSDConfig->DFlashBlockBase + BYTE2WORD(DFLASH_IFR_SIZE))))
		{

#endif /* End of #if(DEBLOCK_SIZE) */ 
			/* return an error code FTFx_ERR_RANGE */
			returnCode = FTFx_ERR_RANGE;
			goto EXIT;
#if(DEBLOCK_SIZE) 
		}
		else
		{
			/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
			destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
#else    	
			destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif  
		}
#endif /* End of if(DEBLOCK_SIZE) */        
	}
	else
	{
		/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
		destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
		destination -= PSSDConfig->PFlashBlockBase;
#endif 
	}

	/* preparing passing parameter for read resource command */
	/* 1st element for the FCCOB register */
	pCommandArray[0] = FTFx_READ_RESOURCE;
	pCommandArray[1] = (UINT8)(destination >> 16);
	pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
	pCommandArray[3] = (UINT8)(destination & 0xFF);
#if ((FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE) || (FTFx_KX_1024K_0K_16K_4K_0K == FLASH_DERIVATIVE))
	pCommandArray[4] = 0x00;
	/* calling flash command sequence API to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 4, pCommandArray);
#else
	pCommandArray[8] = 0x00;
	/* calling flash command sequence API to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 8, pCommandArray);
#endif    

	/* checking for the success of command execution */
	if(FTFx_OK != returnCode)
	{
		goto EXIT;
	}
	else
	{
		/* do nothing */
	}

	/* Read the data from the FCCOB registers into the pDataArray */
	pDataArray[0] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB4_OFFSET);
	pDataArray[1] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB5_OFFSET);
	pDataArray[2] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB6_OFFSET);
	pDataArray[3] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB7_OFFSET);
#if ((FTFx_KX_512K_512K_16K_4K_4K == FLASH_DERIVATIVE) || (FTFx_KX_1024K_0K_16K_4K_0K == FLASH_DERIVATIVE))
	pDataArray[4] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB8_OFFSET);
	pDataArray[5] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOB9_OFFSET);
	pDataArray[6] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBA_OFFSET);
	pDataArray[7] = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCCOBB_OFFSET);
#endif

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* Flash program Longword */
UINT32 Flash::FlashProgramLongword(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
	UINT8 pCommandArray[8]; /* command sequence array */
	UINT32 returnCode;      /* return code variable */
	UINT32 endAddress;      /* storing end address */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* calculating Flash end address */
	endAddress = destination + BYTE2WORD(size);

	/* check if the destination is Longword aligned or not */
	if (destination & (BYTE2WORD(FTFx_LONGWORD_SIZE)-1))
	{
		/* return an error code FTFx_ERR_ADDR */
		returnCode = FTFx_ERR_ADDR;
		goto EXIT;
	}

	/* check if the size is Longword alignment or not */
	if(size & (FTFx_LONGWORD_SIZE-1))
	{
		/* return an error code FTFx_ERR_SIZE */
		returnCode = FTFx_ERR_SIZE;
		goto EXIT;
	}

	/* check for valid range of the target addresses */
	if((destination < PSSDConfig->PFlashBlockBase) || \
			(endAddress > (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
	{
#if(DEBLOCK_SIZE)    	
		if((destination < PSSDConfig->DFlashBlockBase) || \
				(endAddress > (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
		{
#endif /* End of #if(DEBLOCK_SIZE) */  
			/* return an error code FTFx_ERR_RANGE */
			returnCode = FTFx_ERR_RANGE;
			goto EXIT;
#if(DEBLOCK_SIZE)    
		}
		else
		{
			/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
			destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
#else    	
			destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif           
		}        
#endif /* End of #if(DEBLOCK_SIZE) */       
	}
	else
	{
		/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
		destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
		destination -= PSSDConfig->PFlashBlockBase;
#endif 
	}

	/* check for error return code */
	if(FTFx_OK == returnCode)
	{
		while(size > 0)
		{
			/* preparing passing parameter to program the flash block */
			pCommandArray[0] = FTFx_PROGRAM_LONGWORD;
			pCommandArray[1] = (UINT8)(destination >> 16);
			pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
			pCommandArray[3] = (UINT8)(destination & 0xFF);

#if (ENDIANNESS == BIG_ENDIAN)  /* Big Endian */ 
			pCommandArray[4] = READ8(source);
			pCommandArray[5] = READ8(source + 1);
			pCommandArray[6] = READ8(source + 2);
			pCommandArray[7] = READ8(source + 3);
#else /* Little Endian */
			pCommandArray[4] = READ8(source + 3);
			pCommandArray[5] = READ8(source + 2);
			pCommandArray[6] = READ8(source + 1);
			pCommandArray[7] = READ8(source);
#endif

			/* calling flash command sequence function to execute the command */
			returnCode = FlashCommandSequence(PSSDConfig, 7, pCommandArray);

			/* checking for the success of command execution */
			if(FTFx_OK != returnCode)
			{
				break;
			}
			else
			{
				/* update destination address for next iteration */
				destination += FTFx_LONGWORD_SIZE;
				/* update size for next iteration */
				size -= FTFx_LONGWORD_SIZE;
				/* increment the source adress by 1 */
				source += FTFx_LONGWORD_SIZE;
			}
		}
	}

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* This function  prepares the D/E-Flash block for use
 *                     as D-Flash, E-Flash or a combination of both and 
 *                     initializes the EERAM.
 */
UINT32 Flash::DEFlashPartition(PFLASH_SSD_CONFIG PSSDConfig, UINT8 EEEDataSizeCode, UINT8 DEPartitionCode, pFLASHCOMMANDSEQUENCE FlashCommandSequence) {
	UINT8 pCommandArray[6]; /* command sequence array */
	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* preparing passing parameter to program partition command */
	pCommandArray[0] = FTFx_PROGRAM_PARTITION;
	pCommandArray[4] = EEEDataSizeCode;
	pCommandArray[5] = DEPartitionCode;

	/* calling flash command sequence function to execute the command */
	returnCode = FlashCommandSequence(PSSDConfig, 5, pCommandArray);

	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif        
	}

	return(returnCode);
}

/* This function retrieves current D-Flash protection status. */
UINT32 Flash::DFlashGetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8* protectStatus)
{
	UINT32 returnCode;      /* return code variable */

	/* set the default return code as FTFx_OK */
	returnCode = FTFx_OK;

	/* Check if size of DFlash = 0 */
	if(PSSDConfig->DFlashBlockSize == 0)
	{
		returnCode = FTFx_ERR_EFLASHONLY;
		goto EXIT;
	}
	else
	{
		/* Do nothing */
	}

	*protectStatus = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FDPROT_OFFSET);

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* This function sets the D-Flash protection to the intended protection status */
UINT32 Flash::DFlashSetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8 protectStatus)
{
	UINT8  registerValue;    /* store data read from flash register */
	UINT32 returnCode;       /* return code variable */
	UINT8  temp;

	/* set the default return as FTFx_OK */
	returnCode = FTFx_OK;
	/* check CCIF bit of the flash status register, it's impossible to write to DPROT if command is in progress */
	if(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
	{
		returnCode = FTFx_ERR_CHANGEPROT;
		goto EXIT;
	}
	/* Check if size of DFlash = 0 */
	if(PSSDConfig->DFlashBlockSize == 0)
	{
		returnCode = FTFx_ERR_EFLASHONLY;
		goto EXIT;
	}
	else
	{
		/* Do nothing */
	}

	/* Read the value of FDPROT register */
	registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FDPROT_OFFSET);

	/* Check if normal mode */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FDPROT_OFFSET, 0xFF);

	if(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FDPROT_OFFSET) != 0xFF)
	{
		/* if normal mode */
		temp = (UINT8)(protectStatus ^ registerValue);
		if(!(temp & protectStatus))
		{
			REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FDPROT_OFFSET, protectStatus);
		}
		else
		{
			returnCode = FTFx_ERR_CHANGEPROT;
		}
		goto EXIT;
	}
	/* if unprotected or special mode */
	REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FDPROT_OFFSET, protectStatus);

	EXIT:
	/* Enter Debug state if enabled */
	if (TRUE == (PSSDConfig->DebugEnable))
	{
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
		asm
		(
				" BKPT #0 \n "           /* enter Debug state */
		);
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
		asm
		(
				debughlt           /* enter Debug state */
		);
#endif         
	}

	return(returnCode);
}

/* The Erase Flash Block operation will erase all addresses in a single P-Flash or D-Flash block.*/
UINT32 Flash::FlashEraseBlock (PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, pFLASHCOMMANDSEQUENCE FlashCommandSequence) {
    UINT8 pCommandArray[4]; /* command sequence array */
    UINT32 returnCode;      /* return code variable */
    
    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;
    
    /* check if the destination is longword aligned or not */
    if (0 != (destination % ERSBLK_ALIGN_SIZE))
    {
        /* return an error code FTFx_ERR_ADDR */
        returnCode = FTFx_ERR_ADDR;
        goto EXIT;
    }
    
    /* check for valid range of the target addresses */    
    if((destination < PSSDConfig->PFlashBlockBase) || \
        (destination >= (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
    {
        if((destination < PSSDConfig->DFlashBlockBase) || \
            (destination >= (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
        {
            /* return an error code FTFx_ERR_RANGE */
            returnCode = FTFx_ERR_RANGE;
            goto EXIT;
        }
        else
        {
        	/* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
        	destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
#else    	
        	destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif         	
        }
    }
    else
    {
        /* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
    	destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
    	destination -= PSSDConfig->PFlashBlockBase;
#endif 
    }
    
    /* preparing passing parameter to erase a flash block */
    pCommandArray[0] = FTFx_ERASE_BLOCK;
    pCommandArray[1] = (UINT8)(destination >> 16);
    pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
    pCommandArray[3] = (UINT8)(destination & 0xFF);

    /* calling flash command sequence function to execute the command */
    returnCode = FlashCommandSequence(PSSDConfig, 3, pCommandArray);
    
EXIT:
    /* Enter Debug state if enabled */
    if (TRUE == (PSSDConfig->DebugEnable))
    {
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
        asm
        (
            " BKPT #0 \n "           /* enter Debug state */
        );
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
        asm
        (
        		debughlt           /* enter Debug state */
        );
#endif         
    }

    return(returnCode);
}

/* Program data into Flash*/
UINT32 Flash::FlashProgramPhrase(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
    UINT8 pCommandArray[12]; /* command sequence array */
    UINT32 returnCode;      /* return code variable */
    UINT32 endAddress;      /* storing end address */
    
    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;
        
    /* calculating Flash end address */
    endAddress = destination + BYTE2WORD(size);
        
    /* check if the destination is Longword aligned or not */
  
    if (0 != (destination % BYTE2WORD(FTFx_PHRASE_SIZE)))	
    {
        /* return an error code FTFx_ERR_ADDR */
        returnCode = FTFx_ERR_ADDR;
        goto EXIT;
    }
        
    /* check if the size is Longword alignment or not */
    if(0 != (size % FTFx_PHRASE_SIZE))
    {
        /* return an error code FTFx_ERR_SIZE */
        returnCode = FTFx_ERR_SIZE;
            goto EXIT;
    }
    
    /* check for valid range of the target addresses */
    if((destination < PSSDConfig->PFlashBlockBase) || \
        (endAddress > (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
    {
        if((destination < PSSDConfig->DFlashBlockBase) || \
            (endAddress > (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
        {
            /* return an error code FTFx_ERR_RANGE */
            returnCode = FTFx_ERR_RANGE;
            goto EXIT;
        }
        else
        {
            /* Convert System memory address to FTFx internal memory address */
	#if DSC_56800EX == CPU_CORE
			destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
	#else    	
			destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
	#endif  
        }
    }
    else
    {
        /* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
    	destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
    	destination -= PSSDConfig->PFlashBlockBase;
#endif   
    }
    
    /* check for error return code */
    if(FTFx_OK == returnCode)
    {
        while(size > 0)
        {
            /* preparing passing parameter to program the flash block */
            pCommandArray[0] = FTFx_PROGRAM_PHRASE;
            pCommandArray[1] = (UINT8)(destination >> 16);
            pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
            pCommandArray[3] = (UINT8)(destination & 0xFF);
        
#if (ENDIANNESS == BIG_ENDIAN)  /* Big Endian */ 
            pCommandArray[4] = READ8(source);
            pCommandArray[5] = READ8(source + 1);
            pCommandArray[6] = READ8(source + 2);
            pCommandArray[7] = READ8(source + 3);
            pCommandArray[8] = READ8(source + 4);
            pCommandArray[9] = READ8(source + 5);
            pCommandArray[10] = READ8(source + 6);
            pCommandArray[11] = READ8(source + 7);
#else /* Little Endian */
            pCommandArray[4] = READ8(source + 3);
            pCommandArray[5] = READ8(source + 2);
            pCommandArray[6] = READ8(source + 1);
            pCommandArray[7] = READ8(source);
            pCommandArray[8] = READ8(source + 7);
            pCommandArray[9] = READ8(source + 6);
            pCommandArray[10] = READ8(source + 5);
            pCommandArray[11] = READ8(source + 4);
#endif
            
            /* calling flash command sequence function to execute the command */
            returnCode = FlashCommandSequence(PSSDConfig, 11, pCommandArray);
    
            /* checking for the success of command execution */
            if(FTFx_OK != returnCode)
            {
                break;
            }
            else
            {
                /* update destination address for next iteration */
                destination += FTFx_PHRASE_SIZE;
                /* update size for next iteration */
                size -= FTFx_PHRASE_SIZE;
                        /* increment the source adress by 1 */
                source += FTFx_PHRASE_SIZE;
            }
        }
    }

EXIT:
    /* Enter Debug state if enabled */
    if (TRUE == (PSSDConfig->DebugEnable))
    {
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
        asm
        (
            " BKPT #0 \n "           /* enter Debug state */
        );
#endif
    }

    return(returnCode);
}

/* Program data into Flash */
UINT32 Flash::FlashProgramSection(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT16 Number, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
    UINT8 pCommandArray[6]; /* command sequence array */
    UINT32 returnCode;      /* return code variable */
    UINT32 endAddress;      /* storing end address */
    UINT32 sectionAlign;    /* storing the aligned size condition of destination*/ 
    
    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;

    /* check RAMRDY bit of the flash configuration register */
    while(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, FTFx_SSD_FCNFG_RAMRDY)))
    {
        /* return an error code FTFx_ERR_RAMRDY */
        returnCode = FTFx_ERR_RAMRDY;
        goto EXIT;
    }
    
    /* check for valid range of the destination */
    if((destination >= PSSDConfig->PFlashBlockBase) && \
        (destination < (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
    {
        /* calculating Flash end address */
        endAddress = destination + Number * PPGMSEC_ALIGN_SIZE;
    }
    else if((destination >= PSSDConfig->DFlashBlockBase) && \
            (destination < (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
    {
        /* calculating Flash end address */
        endAddress = destination + Number * DPGMSEC_ALIGN_SIZE;
    }
    else /* destination does not fall within Pflash or Dflash range */
    {
        /* return an error code FTFx_ERR_RANGE */
        returnCode = FTFx_ERR_RANGE;
        goto EXIT;
    }
    
    /* check for valid range of the target addresses */
    if((endAddress >= PSSDConfig->PFlashBlockBase) && \
        (endAddress <= (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
    {
        /* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
    	destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
    	destination -= PSSDConfig->PFlashBlockBase;
#endif 
        sectionAlign = PPGMSEC_ALIGN_SIZE;
    }
    else if((endAddress >= PSSDConfig->DFlashBlockBase) || \
            (endAddress <= (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
    {
        /* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
    	destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
#else    	
		destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
#endif  
        sectionAlign = DPGMSEC_ALIGN_SIZE;
    }    
    else /* end address does not fall within Pflash or Dflash range */
    {
        /* return an error code FTFx_ERR_RANGE */
        returnCode = FTFx_ERR_RANGE;
        goto EXIT;
    }
        
    /* check alignment of the destination*/
#if DSC_56800EX == CPU_CORE    
    if (0 != (destination % (2*sectionAlign)))
#else
    if (0 != (destination % sectionAlign))
#endif 
    {
        /* return an error code FTFx_ERR_ADDR */
        returnCode = FTFx_ERR_ADDR;
        goto EXIT;
    }
    
    /* check for error return code */
    if(FTFx_OK == returnCode)
    {
        /* preparing passing parameter to program the flash block */
        pCommandArray[0] = FTFx_PROGRAM_SECTION;
        pCommandArray[1] = (UINT8)(destination >> 16);
        pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
        pCommandArray[3] = (UINT8)(destination & 0xFF);
        pCommandArray[4] = (UINT8)(Number >> 8);
        pCommandArray[5] = (UINT8)(Number & 0xFF);
                            
        /* calling flash command sequence function to execute the command */
        returnCode = FlashCommandSequence(PSSDConfig, 5, pCommandArray);

        /* checking for the success of command execution */
        if(FTFx_OK != returnCode)
        {
            goto EXIT;
        }
        else
        {
            /* do nothing */
        }
    }

EXIT:
    /* Enter Debug state if enabled */
    if (TRUE == (PSSDConfig->DebugEnable))
    {
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
        asm
        (
            " BKPT #0 \n "           /* enter Debug state */
        );
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
        asm
        (
        		debughlt           /* enter Debug state */
        );
#endif       
    }

    return(returnCode);
}

/* This function will check to see if an entire 
*                     P-Flash or D-Flash block has been erased to the
*                     specifed margin level. 
*/
UINT32 Flash::FlashVerifyBlock(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT8 marginLevel, pFLASHCOMMANDSEQUENCE FlashCommandSequence)
{
    UINT8 pCommandArray[5]; /* command sequence array */
    UINT32 returnCode;      /* return code variable */
    
    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;
        
    /* check if the destination is longword aligned or not */
    if (0 != (destination % RD1BLK_ALIGN_SIZE))
    {
        /* return an error code FTFx_ERR_ADDR */
        returnCode = FTFx_ERR_ADDR;
        goto EXIT;
    }
    
    /* check for valid range of the target addresses */    
    if((destination < PSSDConfig->PFlashBlockBase) || \
        (destination >= (PSSDConfig->PFlashBlockBase + BYTE2WORD(PSSDConfig->PFlashBlockSize))))
    {
        if((destination < PSSDConfig->DFlashBlockBase) || \
            (destination >= (PSSDConfig->DFlashBlockBase + BYTE2WORD(PSSDConfig->DFlashBlockSize))))
        {
            /* return an error code FTFx_ERR_RANGE */
            returnCode = FTFx_ERR_RANGE;
            goto EXIT;
        }
        else
        {
            /* Convert System memory address to FTFx internal memory address */
	#if DSC_56800EX == CPU_CORE
			destination = (2*(destination - PSSDConfig->DFlashBlockBase)+ 0x800000);
	#else    	
			destination = destination - PSSDConfig->DFlashBlockBase + 0x800000;
	#endif 
        }
    }
    else
    {
        /* Convert System memory address to FTFx internal memory address */
#if DSC_56800EX == CPU_CORE
    	destination = (2*(destination - PSSDConfig->PFlashBlockBase));
#else    	
    	destination -= PSSDConfig->PFlashBlockBase;
#endif 
    }
    
    /* preparing passing parameter to verify block command */
    pCommandArray[0] = FTFx_VERIFY_BLOCK;
    pCommandArray[1] = (UINT8)(destination >> 16);
    pCommandArray[2] = (UINT8)((destination >> 8) & 0xFF);
    pCommandArray[3] = (UINT8)(destination & 0xFF);
    pCommandArray[4] = marginLevel;

    /* calling flash command sequence function to execute the command */
    returnCode = FlashCommandSequence(PSSDConfig, 4, pCommandArray);

EXIT:
    /* Enter Debug state if enabled */
    if (TRUE == (PSSDConfig->DebugEnable))
    {
#if ((CPU_CORE == ARM_CM4) && (COMPILER == IAR))    /* Kx Products */
        asm
        (
            " BKPT #0 \n "           /* enter Debug state */
        );
#endif
#if ((CPU_CORE == DSC_56800EX)&&(COMPILER == CW))     
        asm
        (
        		debughlt           /* enter Debug state */
        );
#endif         
    }

    return(returnCode);
}
