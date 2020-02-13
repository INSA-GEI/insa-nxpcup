/*
 * FlashConst.h
 *
 *  Created on: Feb 10, 2020
 *      Author: dimercur
 *      
 *  Code is based on driver found on Freescale/NXP website:
 *  	https://community.nxp.com/servlet/JiveServlet/downloadBody/94593-102-1-5584/MKL25_EEPROM_CW103.zip
 *  	
 *  This header contains various constants for flash routines
 *  Code tested on KL25 line of MCU
 */

#ifndef FLASHCONST_H_
#define FLASHCONST_H_

#include "derivative.h"

// Base type definition
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef unsigned char BOOL;

typedef signed char INT8;
typedef unsigned char UINT8;
typedef volatile signed char VINT8;
typedef volatile unsigned char VUINT8;

typedef signed short INT16;
typedef unsigned short UINT16;
typedef volatile signed short VINT16;
typedef volatile unsigned short VUINT16;

typedef signed long INT32;
typedef unsigned long UINT32;
typedef volatile signed long VINT32;
typedef volatile unsigned long VUINT32;

// Common definitions and macros
/*------------------------- Configuration Macros -----------------------*/
/* Define derivatives with rule: FTFx_KX_Pblocksize_Dblocksize_EERAMsize_Psectorsize_Dsectorsize */

#define FTFx_KX_256K_256K_4K_2K_2K        1    /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_512K_0K_0K_2K_0K          2    /* Kinetis - ARM Cortex M4 core */
#define FTFx_JX_128K_32K_2K_1K_1K         3    /* ColdFire core */
#define FTFx_FX_256K_32K_2K_1K_1K         4    /* ColdFire core */
#define FTFx_KX_512K_512K_16K_4K_4K       5    /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_1024K_0K_16K_4K_0K        6    /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_32K_0K_0K_1K_0K           7    /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_32K_32K_2K_1K_1K          8    /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_64K_0K_0K_1K_0K           9    /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_64K_32K_2K_1K_1K          10   /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_128K_0K_0K_1K_0K          11   /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_128K_32K_2K_1K_1K         12   /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_64K_32K_2K_2K_1K          13   /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_128K_32K_2K_2K_1K         14   /* Kinetis - ARM Cortex M4 core */
#define FTFx_KX_256K_32K_2K_2K_1K         15   /* Kinetis - ARM Cortex M4 core */
#define FTFx_NX_256K_32K_2K_2K_1K         16   /* Nevis2 - 56800EX 32 bit DSC core */
#define FTFx_NX_128K_32K_2K_2K_1K         17   /* Nevis2 - 56800EX 32 bit DSC core */
#define FTFx_NX_96K_32K_2K_2K_1K          18   /* Nevis2 - 56800EX 32 bit DSC core */
#define FTFx_NX_64K_32K_2K_2K_1K          19   /* Nevis2 - 56800EX 32 bit DSC core */
#define FTFx_LX_128K_0K_0K_1K_0K          20   /* L2K -  ARM Cortex M0 core */
#define FTFx_LX_64K_0K_0K_1K_0K           21   /* L2K -  ARM Cortex M0 core */
#define FTFx_LX_32K_0K_0K_1K_0K           22   /* L2K & L1PT -  ARM Cortex M0 core */
#define FTFx_LX_16K_0K_0K_1K_0K           23   /* L1PT -  ARM Cortex M0 core */
#define FTFx_LX_8K_0K_0K_1K_0K            24   /* L1PT -  ARM Cortex M0 core */
#define FTFx_AX_64K_0K_0K_1K_0K           25   /* Anguilla_Silver - 56800EX 32 bit DSC core */
#define FTFx_AX_48K_0K_0K_1K_0K           26   /* Anguilla_Silver - 56800EX 32 bit DSC core */
#define FTFx_AX_32K_0K_0K_1K_0K           27   /* Anguilla_Silver - 56800EX 32 bit DSC core */
#define FTFx_AX_16K_0K_0K_1K_0K           28   /* Anguilla_Silver - 56800EX 32 bit DSC core */

/* Define compiler */
#define CW                                0   /* CodeWarrior Compiler */
#define IAR                               1   /* IAR Compiler */

/* Endianness */
#define BIG_ENDIAN                        0   /* Big Endian */
#define LITTLE_ENDIAN                     1   /* Little Endian */

/* cpu cores */
#define COLDFIRE                          0   /* ColdFire core */
#define ARM_CM4                           1   /* ARM Cortex M4 core */
#define DSC_56800EX                       2   /* 32 bit DSC core */
#define ARM_CM0PLUS                       3     /* ARM Cortex M0 core */

/* Word size */
#define FTFx_WORD_SIZE                    0x0002     /* 2 bytes */
  
/* Longword size */
#define FTFx_LONGWORD_SIZE                0x0004     /* 4 bytes */

/* Phrase size */
#define FTFx_PHRASE_SIZE                  0x0008     /* 8 bytes */

/* Double-phrase size */
#define FTFx_DPHRASE_SIZE                 0x0010     /* 16 bytes */

/*------------ Return Code Definition for FTFx SSD ---------------------*/
#define FTFx_OK                            0x0000
#define FTFx_ERR_SIZE                      0x0001
#define FTFx_ERR_RANGE                     0x0002
#define FTFx_ERR_ACCERR                    0x0004
#define FTFx_ERR_PVIOL                     0x0008
#define FTFx_ERR_MGSTAT0                   0x0010
#define FTFx_ERR_CHANGEPROT                0x0020
#define FTFx_ERR_EEESIZE                   0x0040
#define FTFx_ERR_EFLASHSIZE                0x0080
#define FTFx_ERR_ADDR                      0x0100
#define FTFx_ERR_NOEEE                     0x0200
#define FTFx_ERR_EFLASHONLY                0x0400
#define FTFx_ERR_DFLASHONLY                0x0800
#define FTFx_ERR_RDCOLERR                  0x1000
#define FTFx_ERR_RAMRDY                    0x2000

/* Flash security status */
#define FLASH_SECURITY_STATE_KEYEN         0x80
#define FLASH_SECURITY_STATE_UNSECURED     0x02

#define FLASH_NOT_SECURE                   0x01
#define FLASH_SECURE_BACKDOOR_ENABLED      0x02
#define FLASH_SECURE_BACKDOOR_DISABLED     0x04

/* macro for flash configuration field offset */
#define FLASH_CNFG_START_ADDRESS           0x400
#define FLASH_CNFG_END_ADDRESS             0x40F

/* EERAM Function Control Code */
#define EEE_ENABLE                         0x00
#define EEE_DISABLE                        0xFF

/*-------------- Read/Write/Set/Clear Operation Macros -----------------*/
#define REG_BIT_SET(address, mask)      (*(VUINT8*)(address) |= (mask))
#define REG_BIT_CLEAR(address, mask)    (*(VUINT8*)(address) &= ~(mask))
#define REG_BIT_TEST(address, mask)     (*(VUINT8 *)(address) & (UINT8)(mask))
#define REG_WRITE(address, value)       (*(VUINT8*)(address) = (value))
#define REG_READ(address)               ((UINT8)(*(VUINT8*)(address)))
#define REG_WRITE32(address, value)     (*(VUINT32*)(address) = (value))
#define REG_READ32(address)             ((UINT32)(*(VUINT32*)(address)))

#define WRITE8(address, value)          (*(VUINT8*)(address) = (value))
#define READ8(address)                  ((UINT8)(*(VUINT8*)(address)))
#define SET8(address, value)            (*(VUINT8*)(address) |= (value))
#define CLEAR8(address, value)          (*(VUINT8*)(address) &= ~(value))
#define TEST8(address, value)           (*(VUINT8*)(address) & (value))

#define WRITE16(address, value)         (*(VUINT16*)(address) = (value))
#define READ16(address)                 ((UINT16)(*(VUINT16*)(address)))
#define SET16(address, value)           (*(VUINT16*)(address) |= (value))
#define CLEAR16(address, value)         (*(VUINT16*)(address) &= ~(value))
#define TEST16(address, value)          (*(VUINT16*)(address) & (value))

#define WRITE32(address, value)         (*(VUINT32*)(address) = (value))
#define READ32(address)                 ((UINT32)(*(VUINT32*)(address)))
#define SET32(address, value)           (*(VUINT32*)(address) |= (value))
#define CLEAR32(address, value)         (*(VUINT32*)(address) &= ~(value))
#define TEST32(address, value)          (*(VUINT32*)(address) & (value))

/*--------------------- CallBack function period -----------------------*/
#define FLASH_CALLBACK_CS               1          /* Check Sum */

/*-------------------- Callback function prototype ---------------------*/
typedef void (* PCALLBACK)(void);
typedef BOOL (* PFLASH_SWAP_CALLBACK)(UINT8);

/*--------------------Null Callback function defination ----------------*/
#define NULL_CALLBACK                   ((PCALLBACK)0xFFFFFFFF)
#define NULL_SWAP_CALLBACK              ((PFLASH_SWAP_CALLBACK)0xFFFFFFFF)

/*---------------- Flash SSD Configuration Structure -------------------*/
typedef struct _ssd_config
{
    UINT32      ftfxRegBase;        /* FTFx control register base */
    UINT32      PFlashBlockBase;    /* base address of PFlash block */
    UINT32      PFlashBlockSize;    /* size of PFlash block */
    UINT32      DFlashBlockBase;    /* base address of DFlash block */
    UINT32      DFlashBlockSize;    /* size of DFlash block */
    UINT32      EERAMBlockBase;     /* base address of EERAM block */
    UINT32      EERAMBlockSize;     /* size of EERAM block */
    UINT32      EEEBlockSize;       /* size of EEE block */
    BOOL        DebugEnable;        /* background debug mode enable bit */
    PCALLBACK   CallBack;           /* pointer to callback function */
} FLASH_SSD_CONFIG, *PFLASH_SSD_CONFIG;

/* PFlash swap states */
#define FTFx_SWAP_UNINIT            0x00
#define FTFx_SWAP_READY             0x01
#define FTFx_SWAP_INIT              0x01
#define FTFx_SWAP_UPDATE            0x02
#define FTFx_SWAP_UPDATE_ERASED     0x03
#define FTFx_SWAP_COMPLETE          0x04

// Specific constants for KL25 
// FTFx_LX_128K_0K_0K_1K_0K
#define BYTE2WORD(x) (x)

/* Endianness */
#define ENDIANNESS              LITTLE_ENDIAN

/* cpu core */
#define CPU_CORE                ARM_CM0PLUS

/* PFlash sector size */ 
#define FTFx_PSECTOR_SIZE       0x00000400      /* 1 KB size */
/* DFlash sector size */ 
#define FTFx_DSECTOR_SIZE       0x00000000      /* 0 KB size */
#define DEBLOCK_SIZE            0x00000000      /* 0 KB size */
/*destination to read Dflash IFR area*/
#define DFLASH_IFR_READRESOURCE_ADDRESS   0x8000FC 

/* Address offset and size of PFlash IFR and DFlash IFR */
#define PFLASH_IFR_OFFSET                 0x00000000
#define PFLASH_IFR_SIZE                   0x00000100
#define DFLASH_IFR_OFFSET                 0xFFFFFFFF /* reserved */
#define DFLASH_IFR_SIZE                   0xFFFFFFFF /* reserved */    

/* Size for checking alignment of a section */
#define ERSBLK_ALIGN_SIZE       FTFx_LONGWORD_SIZE      /* check align of erase block function */
#define PGMCHK_ALIGN_SIZE       FTFx_LONGWORD_SIZE      /* check align of program check function */
#define PPGMSEC_ALIGN_SIZE      FTFx_LONGWORD_SIZE      /* check align of program section function */
#define DPGMSEC_ALIGN_SIZE      FTFx_LONGWORD_SIZE      /* check align of program section function */
#define RD1BLK_ALIGN_SIZE       FTFx_LONGWORD_SIZE      /* check align of verify block function */
#define PRD1SEC_ALIGN_SIZE      FTFx_LONGWORD_SIZE      /* check align of verify section function */
#define DRD1SEC_ALIGN_SIZE      FTFx_LONGWORD_SIZE      /* check align of verify section function */
#define SWAP_ALIGN_SIZE         FTFx_LONGWORD_SIZE      /* check align of swap function*/
#define RDRSRC_ALIGN_SIZE       FTFx_LONGWORD_SIZE      /* check align of read resource function */
#define RDONCE_INDEX_MAX        0xF                     /* maximum index in read once command */

// Others definitions
/*--------------- FTFx Flash Module Memory Offset Map -----------------*/
#if(ENDIANNESS == BIG_ENDIAN)    /* Big Endian - coldfire CPU */
    /* Flash Status Register (FSTAT)*/
    #define FTFx_SSD_FSTAT_OFFSET               0x00000003
    #define FTFx_SSD_FSTAT_CCIF                 0x80
    #define FTFx_SSD_FSTAT_RDCOLERR             0x40
    #define FTFx_SSD_FSTAT_ACCERR               0x20
    #define FTFx_SSD_FSTAT_FPVIOL               0x10
    #define FTFx_SSD_FSTAT_MGSTAT0              0x01

    /* Flash configuration register (FCNFG)*/
    #define FTFx_SSD_FCNFG_OFFSET               0x00000002
    #define FTFx_SSD_FCNFG_CCIE                 0x80
    #define FTFx_SSD_FCNFG_RDCOLLIE             0x40
    #define FTFx_SSD_FCNFG_ERSAREQ              0x20
    #define FTFx_SSD_FCNFG_ERSSUSP              0x10
    #define FTFx_SSD_FCNFG_RAMRDY               0x02
    #define FTFx_SSD_FCNFG_EEERDY               0x01

    /* Flash security register (FSEC) */
    #define FTFx_SSD_FSEC_OFFSET                0x00000001
    #define FTFx_SSD_FSEC_KEYEN                 0xC0
    #define FTFx_SSD_FSEC_FSLACC                0x0C
    #define FTFx_SSD_FSEC_SEC                   0x03

    /* Flash Option Register (FOPT) */
    #define FTFx_SSD_FOPT_OFFSET                0x00000000

    /* Flash common command object registers (FCCOB0-B) */
    #define FTFx_SSD_FCCOB0_OFFSET              0x00000004
    #define FTFx_SSD_FCCOB1_OFFSET              0x00000005
    #define FTFx_SSD_FCCOB2_OFFSET              0x00000006
    #define FTFx_SSD_FCCOB3_OFFSET              0x00000007
    #define FTFx_SSD_FCCOB4_OFFSET              0x00000008
    #define FTFx_SSD_FCCOB5_OFFSET              0x00000009
    #define FTFx_SSD_FCCOB6_OFFSET              0x0000000A
    #define FTFx_SSD_FCCOB7_OFFSET              0x0000000B
    #define FTFx_SSD_FCCOB8_OFFSET              0x0000000C
    #define FTFx_SSD_FCCOB9_OFFSET              0x0000000D
    #define FTFx_SSD_FCCOBA_OFFSET              0x0000000E
    #define FTFx_SSD_FCCOBB_OFFSET              0x0000000F

    /* P-Flash protection registers (FPROT0-3) */
    #define FTFx_SSD_FPROT0_OFFSET              0x00000010
    #define FTFx_SSD_FPROT1_OFFSET              0x00000011
    #define FTFx_SSD_FPROT2_OFFSET              0x00000012
    #define FTFx_SSD_FPROT3_OFFSET              0x00000013

    /* D-Flash protection registers (FDPROT) */
    #define FTFx_SSD_FDPROT_OFFSET              0x00000014

    /* EERAM Protection Register (FEPROT)  */
    #define FTFx_SSD_FEPROT_OFFSET              0x00000015
   /* Little Endian - kinetis CPU & Big Endian - Nevis2 CPU */
#else
    /* Flash Status Register (FSTAT)*/
    #define FTFx_SSD_FSTAT_OFFSET               0x00000000
    #define FTFx_SSD_FSTAT_CCIF                 0x80
    #define FTFx_SSD_FSTAT_RDCOLERR             0x40
    #define FTFx_SSD_FSTAT_ACCERR               0x20
    #define FTFx_SSD_FSTAT_FPVIOL               0x10
    #define FTFx_SSD_FSTAT_MGSTAT0              0x01

    /* Flash configuration register (FCNFG)*/
    #define FTFx_SSD_FCNFG_OFFSET               0x00000001
    #define FTFx_SSD_FCNFG_CCIE                 0x80
    #define FTFx_SSD_FCNFG_RDCOLLIE             0x40
    #define FTFx_SSD_FCNFG_ERSAREQ              0x20
    #define FTFx_SSD_FCNFG_ERSSUSP              0x10
    #define FTFx_SSD_FCNFG_RAMRDY               0x02
    #define FTFx_SSD_FCNFG_EEERDY               0x01

    /* Flash security register (FSEC) */
    #define FTFx_SSD_FSEC_OFFSET                0x00000002
    #define FTFx_SSD_FSEC_KEYEN                 0xC0
    #define FTFx_SSD_FSEC_FSLACC                0x0C
    #define FTFx_SSD_FSEC_SEC                   0x03

    /* Flash Option Register (FOPT) */
    #define FTFx_SSD_FOPT_OFFSET                0x00000003

    /* Flash common command object registers (FCCOB0-B) */
    #define FTFx_SSD_FCCOB0_OFFSET              0x00000007
    #define FTFx_SSD_FCCOB1_OFFSET              0x00000006
    #define FTFx_SSD_FCCOB2_OFFSET              0x00000005
    #define FTFx_SSD_FCCOB3_OFFSET              0x00000004
    #define FTFx_SSD_FCCOB4_OFFSET              0x0000000B
    #define FTFx_SSD_FCCOB5_OFFSET              0x0000000A
    #define FTFx_SSD_FCCOB6_OFFSET              0x00000009
    #define FTFx_SSD_FCCOB7_OFFSET              0x00000008
    #define FTFx_SSD_FCCOB8_OFFSET              0x0000000F
    #define FTFx_SSD_FCCOB9_OFFSET              0x0000000E
    #define FTFx_SSD_FCCOBA_OFFSET              0x0000000D
    #define FTFx_SSD_FCCOBB_OFFSET              0x0000000C

    /* P-Flash protection registers (FPROT0-3) */
    #define FTFx_SSD_FPROT0_OFFSET              0x00000013
    #define FTFx_SSD_FPROT1_OFFSET              0x00000012
    #define FTFx_SSD_FPROT2_OFFSET              0x00000011
    #define FTFx_SSD_FPROT3_OFFSET              0x00000010

    /* D-Flash protection registers (FDPROT) */
    #define FTFx_SSD_FDPROT_OFFSET              0x00000017

    /* EERAM Protection Register (FEPROT)  */
    #define FTFx_SSD_FEPROT_OFFSET              0x00000016
#endif

/*------------- Flash hardware algorithm operation commands -------------*/
#define FTFx_VERIFY_BLOCK               0x00
#define FTFx_VERIFY_SECTION             0x01
#define FTFx_PROGRAM_CHECK              0x02
#define FTFx_READ_RESOURCE              0x03
#define FTFx_PROGRAM_LONGWORD           0x06
#define FTFx_PROGRAM_PHRASE             0x07
#define FTFx_ERASE_BLOCK                0x08
#define FTFx_ERASE_SECTOR               0x09
#define FTFx_PROGRAM_SECTION            0x0B
#define FTFx_VERIFY_ALL_BLOCK           0x40
#define FTFx_READ_ONCE                  0x41
#define FTFx_PROGRAM_ONCE               0x43
#define FTFx_ERASE_ALL_BLOCK            0x44
#define FTFx_SECURITY_BY_PASS           0x45
#define FTFx_PFLASH_SWAP                0x46
#define FTFx_PROGRAM_PARTITION          0x80
#define FTFx_SET_EERAM                  0x81

/* Flash margin read settings */
#define FTFx_MARGIN_NORMAL              0x0000
#define FTFx_USER_MARGIN_LEVEL1         0x0001
#define FTFx_USER_MARGIN_LEVEL0         0x0002
#define FTFx_FACTORY_MARGIN_LEVEL0      0x0003
#define FTFx_FACTORY_MARGIN_LEVEL1      0x0004

/* PFlash swap control codes */
#define FTFx_SWAP_SET_INDICATOR_ADDR    0x01
#define FTFx_SWAP_SET_IN_PREPARE        0x02
#define FTFx_SWAP_SET_IN_COMPLETE       0x04
#define FTFx_SWAP_REPORT_STATUS         0x08

#endif /* FLASHCONST_H_ */
