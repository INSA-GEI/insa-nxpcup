#include "FreescaleIAP.h"
#include "Debug.h"
#include <MKL25Z4.h>


#ifdef TARGET_Freescale

//#define IAPDEBUG

#ifdef TARGET_K64F
//For K64F
#   include "MK64F12.h"
#   define USE_ProgramPhrase 1
#   define FTFA                        FTFE
#   define FTFA_FSTAT_FPVIOL_MASK      FTFE_FSTAT_FPVIOL_MASK 
#   define FTFA_FSTAT_ACCERR_MASK      FTFE_FSTAT_ACCERR_MASK
#   define FTFA_FSTAT_RDCOLERR_MASK    FTFE_FSTAT_RDCOLERR_MASK
#   define FTFA_FSTAT_CCIF_MASK        FTFE_FSTAT_CCIF_MASK
#   define FTFA_FSTAT_MGSTAT0_MASK     FTFE_FSTAT_MGSTAT0_MASK
#else
//Different names used on at least the K20:
# ifndef FTFA_FSTAT_FPVIOL_MASK
#       define FTFA                        FTFL
#       define FTFA_FSTAT_FPVIOL_MASK      FTFL_FSTAT_FPVIOL_MASK 
#       define FTFA_FSTAT_ACCERR_MASK      FTFL_FSTAT_ACCERR_MASK
#       define FTFA_FSTAT_RDCOLERR_MASK    FTFL_FSTAT_RDCOLERR_MASK
#       define FTFA_FSTAT_CCIF_MASK        FTFL_FSTAT_CCIF_MASK
#       define FTFA_FSTAT_MGSTAT0_MASK     FTFL_FSTAT_MGSTAT0_MASK
#   endif
#endif


enum FCMD {
    Read1s = 0x01,
    ProgramCheck = 0x02,
    ReadResource = 0x03,
    ProgramLongword = 0x06,
    ProgramPhrase = 0x07,    
    EraseSector = 0x09,
    Read1sBlock = 0x40,
    ReadOnce = 0x41,
    ProgramOnce = 0x43,
    EraseAll = 0x44,
    VerifyBackdoor = 0x45
    };

inline void run_command(void);
bool check_boundary(int address, unsigned int length);
bool check_align(int address);
IAPCode verify_erased(int address, unsigned int length);
IAPCode check_error(void);
IAPCode program_word(int address, char *data);
    
IAPCode erase_sector(int address) {
    #ifdef IAPDEBUG
	 uart_write( "IAP: Erasing" , 12);
    #endif
    if (check_align(address))
        return AlignError;
    
    //Setup command
    FTFA->FCCOB0 = EraseSector;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;
    
    run_command();
    
    return check_error();
}

IAPCode program_flash(int address, char *data, /*unsigned*/ int length) {
    #ifdef IAPDEBUG
	uart_write( "IAP: Programming flash", 22);
    #endif
    if (check_align(address))
        return AlignError;
        
    IAPCode eraseCheck = verify_erased(address, length);
    if (eraseCheck != Success)
        return eraseCheck;
    
    IAPCode progResult;
#ifdef USE_ProgramPhrase
    for (int i = 0; i < length; i+=8) {
        progResult = program_word(address + i, data + i);
        if (progResult != Success)
            return progResult;
    }
#else
    for (int i = 0; i < length; i+=4) {
        progResult = program_word(address + i, data + i);
        if (progResult != Success)
            return progResult;
    }
#endif    
    return Success;
}

uint32_t flash_size(void) {
    uint32_t retval = (SIM->FCFG2 & 0x7F000000u) >> (24-13);
    if (SIM->FCFG2 & (1<<23))           //Possible second flash bank
        retval += (SIM->FCFG2 & 0x007F0000u) >> (16-13);
    return retval;
}

IAPCode program_word(int address, char *data) {
    #ifdef IAPDEBUG
    #ifdef USE_ProgramPhrase
    #else
    #endif
    
    #endif
    if (check_align(address))
        return AlignError;
#ifdef USE_ProgramPhrase
    FTFA->FCCOB0 = ProgramPhrase;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;
    FTFA->FCCOB4 = data[3];
    FTFA->FCCOB5 = data[2];
    FTFA->FCCOB6 = data[1];
    FTFA->FCCOB7 = data[0];
    FTFA->FCCOB8 = data[7];
    FTFA->FCCOB9 = data[6];
    FTFA->FCCOBA = data[5];
    FTFA->FCCOBB = data[4];
#else
    //Setup command
    FTFA->FCCOB0 = ProgramLongword;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;
    FTFA->FCCOB4 = data[3];
    FTFA->FCCOB5 = data[2];
    FTFA->FCCOB6 = data[1];
    FTFA->FCCOB7 = data[0];
#endif    
    run_command();
    
    return check_error();
}

/* Clear possible flags which are set, run command, wait until done */
inline void run_command(void) {
    //Clear possible old errors, start command, wait until done
    __disable_irq();            //Disable IRQs, preventing IRQ routines from trying to access flash (thanks to https://mbed.org/users/mjr/)
    FTFA->FSTAT = FTFA_FSTAT_FPVIOL_MASK | FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_RDCOLERR_MASK;
    FTFA->FSTAT = FTFA_FSTAT_CCIF_MASK;
    while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));
    __enable_irq();
}    
    
    

/* Check if no flash boundary is violated
   Returns true on violation */
bool check_boundary(int address, unsigned int length) {
    int temp = (address+length - 1) / SECTOR_SIZE;
    address /= SECTOR_SIZE;
    bool retval = (address != temp);
    #ifdef IAPDEBUG
    if (retval)
    	uart_write( "IAP: Boundary violation", 23);
    #endif
    return retval;
}

/* Check if address is correctly aligned
   Returns true on violation */
bool check_align(int address) {
    bool retval = address & 0x03;
    #ifdef IAPDEBUG
    if (retval)
    	uart_write( "IAP: Alignment violation", 24);
    #endif
    return retval;
}

/* Check if an area of flash memory is erased
   Returns error code or Success (in case of fully erased) */
IAPCode verify_erased(int address, unsigned int length) {
    #ifdef IAPDEBUG
	uart_write( "IAP: Verify erased", 18);
    #endif
    
    if (check_align(address))
        return AlignError;
    
    #ifdef USE_ProgramPhrase
    //Check erase is per 16 bytes, we round up
    length = (length + 15) >> 4;
    #else
    //Otherwise per 4 byte (should check if this is true)
    length = (length + 3) >> 2;
    #endif
    
    //Setup command
    FTFA->FCCOB0 = Read1s;
    FTFA->FCCOB1 = (address >> 16) & 0xFF;
    FTFA->FCCOB2 = (address >> 8) & 0xFF;
    FTFA->FCCOB3 = address & 0xFF;
    FTFA->FCCOB4 = (length >> 8) & 0xFF;
    FTFA->FCCOB5 = length & 0xFF;
    FTFA->FCCOB6 = 0;
    
    run_command();
    
    IAPCode retval = check_error();
    if (retval == RuntimeError) {
        #ifdef IAPDEBUG
    	uart_write( "IAP: Flash was not erased", 25);
        #endif
        return EraseError;
    }
    return retval;
        
}

/* Check if an error occured 
   Returns error code or Success*/
IAPCode check_error(void) {
    if (FTFA->FSTAT & FTFA_FSTAT_FPVIOL_MASK) {
        #ifdef IAPDEBUG
    	uart_write( "IAP: Protection violation", 25);
        #endif
        return ProtectionError;
    }
    if (FTFA->FSTAT & FTFA_FSTAT_ACCERR_MASK) {
        #ifdef IAPDEBUG
    	uart_write( "IAP: Flash access error", 23);
        #endif
        return AccessError;
    }
    if (FTFA->FSTAT & FTFA_FSTAT_RDCOLERR_MASK) {
        #ifdef IAPDEBUG
    	uart_write( "IAP: Collision error", 20);
        #endif
        return CollisionError;
    }
    if (FTFA->FSTAT & FTFA_FSTAT_MGSTAT0_MASK) {
        #ifdef IAPDEBUG
    	uart_write( "IAP: Runtime error", 18);
        #endif
        return RuntimeError;
    }
    #ifdef IAPDEBUG
    uart_write( "IAP: No error reported", 22);
    #endif
    return Success;
}


#endif
