#include <MKL25Z4.h>

#ifndef FREESCALEIAP_H
#define FREESCALEIAP_H

#define TARGET_KLXX 

#define TARGET_Freescale

#ifdef TARGET_Freescale

//#include "mbed.h"

#if defined(TARGET_KLXX)
#define SECTOR_SIZE     51200 //50ko pour stocker tout les cm sur une course de 50m
#elif defined(TARGET_K20D5M) | (TARGET_K22F) | (TARGET_TEENSY3_1)
#define SECTOR_SIZE     2048
#elif defined(TARGET_K64F)
#define SECTOR_SIZE     4096
#else
#warning FreescaleIAP unknown target, using default 1024B
#define SECTOR_SIZE     1024
#endif

enum IAPCode {
    BoundaryError = -99,    //Commands may not span several sectors
    AlignError,             //Data must be aligned on longword (two LSBs zero)
    ProtectionError,        //Flash sector is protected
    AccessError,            //Something went wrong
    CollisionError,         //During writing something tried to flash which was written to
    LengthError,            //The length must be multiples of 4
    RuntimeError,           
    EraseError,             //The flash was not erased before writing to it
    Success = 0
    };

/** Erase a flash sector
 *
 * The size erased depends on the used device
 *
 * @param address address in the sector which needs to be erased
 * @param return Success if no errors were encountered, otherwise one of the error states
 */
IAPCode erase_sector(int address);

/** Program flash
 *
 * Before programming the used area needs to be erased. The erase state is checked
 * before programming, and will return an error if not erased.
 *
 * @param address starting address where the data needs to be programmed (must be longword alligned: two LSBs must be zero)
 * @param data pointer to array with the data to program
 * @param length number of bytes to program (must be a multiple of 4. must be a multiple of 8 when K64F)
 * @param return Success if no errors were encountered, otherwise one of the error states
 */
IAPCode program_flash(int address, char *data, unsigned int length);

/**
 * Returns size of flash memory
 * 
 * This is the first address which is not flash
 *
 * @param return length of flash memory in bytes
 */
uint32_t flash_size(void);

#endif
#endif
