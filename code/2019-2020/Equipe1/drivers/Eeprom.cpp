/*
 * Eeprom.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: dimercur
 */

#include "Eeprom.h"

Eeprom::Eeprom() {
	// TODO Auto-generated constructor stub

}

Eeprom::~Eeprom() {
	// TODO Auto-generated destructor stub
}

/* This function is used to change the function of 
*                     the EERAM. When not partitioned for EEE, the EERAM 
*                     is typically used as traditional RAM. When partitioned 
*                     for EEE, the EERAM is typically used to store EEE data.
*/
UINT32 Eeprom::SetEEEEnable(PFLASH_SSD_CONFIG PSSDConfig, UINT8 EEEEnable)
{
    UINT8 pCommandArray[2]; /* command sequence array */
    UINT32 returnCode;      /* return code variable */
    
    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;
        
    /* preparing passing parameter to set EEPROM Enabled command */
    pCommandArray[0] = FTFx_SET_EERAM;
    pCommandArray[1] = EEEEnable;
    
    /* calling flash command sequence function to execute the command */
    returnCode = FlashCommandSequence(PSSDConfig, 1, pCommandArray);

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

/*This function retrieves current EERAM protection status.*/
UINT32 Eeprom::EERAMSetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8 protectStatus)
{
    UINT8  registerValue;    /* store data read from flash register */
    UINT32 returnCode;       /* return code variable */
    UINT8  temp;
    
    /* set the default return as FTFx_OK */
    returnCode = FTFx_OK;
    /* check CCIF bit of the flash status register, it's impossible to write to FEPROT if command is in progress */
    if(FALSE == (REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET, FTFx_SSD_FSTAT_CCIF)))
    {
        returnCode = FTFx_ERR_CHANGEPROT;
        goto EXIT;
    }
    /* Check if EERAM is set for EEE */
    if(!(REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, FTFx_SSD_FCNFG_EEERDY)))
    {
        /* EERAM is not set for EEE */
        returnCode = FTFx_ERR_NOEEE;
        goto EXIT;
    }
    else
    {
        /* Do nothing */
    }
    
    /* Read the value of FDPROT register */
    registerValue = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FEPROT_OFFSET);
    
    /* Check if normal mode */
    REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FEPROT_OFFSET, 0xFF);
    
    if(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FEPROT_OFFSET) != 0xFF)
    {
        /* if normal mode */
        temp = (UINT8)(protectStatus ^ registerValue);
        if(!(temp & protectStatus))
        {
            REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FEPROT_OFFSET, protectStatus);
        }
        else
        {
            returnCode = FTFx_ERR_CHANGEPROT;
        }
        goto EXIT;
    }
    /* if unprotected or special mode */
    REG_WRITE(PSSDConfig->ftfxRegBase + FTFx_SSD_FEPROT_OFFSET, protectStatus);
    
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

/* This function retrieves current EERAM protection status. */
UINT32 Eeprom::EERAMGetProtection(PFLASH_SSD_CONFIG PSSDConfig, UINT8* protectStatus)
{
    UINT32 returnCode;      /* return code variable */

    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;
    
    /* Check if EERAM is set for EEE */
    if(REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, FTFx_SSD_FCNFG_EEERDY))
    {
        /* EERAM is set for EEE */
        *protectStatus = REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FEPROT_OFFSET);
    }
    else
    {
        returnCode = FTFx_ERR_NOEEE;
        goto EXIT;
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

/* This function is used to write data to EERAM 
*                     when it is used as EEPROM emulator     
*/
UINT32 Eeprom::EEEWrite(PFLASH_SSD_CONFIG PSSDConfig, UINT32 destination, UINT32 size, UINT32 source)
{
    UINT32 returnCode;           /* Return code variable */
    /* set the default return code as FTFx_OK */
    returnCode = FTFx_OK;
    /* Check if EEE is enabled */
    if(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET) & FTFx_SSD_FCNFG_EEERDY)
    {
        if(destination < PSSDConfig->EERAMBlockBase || \
          ((destination + size) > (PSSDConfig->EERAMBlockBase + BYTE2WORD(PSSDConfig->EEEBlockSize))))
        {
            returnCode = FTFx_ERR_RANGE;
            goto EXIT;
        }
        else
        {
#if DSC_56800EX == CPU_CORE
        	/* Convert word address to byte address in  Nevis2 */
        	destination *=2;
#endif        	
            while(size > 0)
            {    
   
                WRITE8(destination,READ8(source));
                
                while(FALSE == REG_BIT_TEST(PSSDConfig->ftfxRegBase + FTFx_SSD_FCNFG_OFFSET, FTFx_SSD_FCNFG_EEERDY))
				{
				   /* wait till EEERDY bit is set */
				}       
                /* Check for protection violation error */ 
                if(REG_READ(PSSDConfig->ftfxRegBase + FTFx_SSD_FSTAT_OFFSET) & FTFx_SSD_FSTAT_FPVIOL)
                {
                    returnCode = FTFx_ERR_PVIOL;
                    break;
                }
        
                /* update destination address for next iteration */
                destination += 1;
                /* update size for next iteration */
                size -= 1;
               
                /* increment the source adress by 1 */
                source += 1;
            }
        }
    }
    else
    {
        returnCode = FTFx_ERR_NOEEE;
        goto EXIT;
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
