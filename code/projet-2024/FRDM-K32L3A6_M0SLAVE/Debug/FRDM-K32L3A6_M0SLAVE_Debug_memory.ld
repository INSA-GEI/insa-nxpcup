/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2023
 * Generated linker script file for K32L3A60xxx
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.7.0 [Build 9198] [2023-01-17] on 20 avr. 2023 à 16:11:27
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH_cm0plus (rx) : ORIGIN = 0x1000000, LENGTH = 0x40000 /* 256K bytes (alias Flash) */  
  PROGRAM_FLASH_cm4 (rx) : ORIGIN = 0x0, LENGTH = 0x100000 /* 1M bytes (alias Flash2) */  
  SRAM_TCM_cm0plus (rwx) : ORIGIN = 0x9000000, LENGTH = 0x20000 /* 128K bytes (alias RAM) */  
  FLEX_RAM (rwx) : ORIGIN = 0x48000000, LENGTH = 0x1000 /* 4K bytes (alias RAM2) */  
  USB_RAM (rwx) : ORIGIN = 0x48010000, LENGTH = 0x800 /* 2K bytes (alias RAM3) */  
  SRAM_DTC_cm4 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x30000 /* 192K bytes (alias RAM4) */  
  SRAM_ITC_cm4 (rwx) : ORIGIN = 0x8000000, LENGTH = 0x10000 /* 64K bytes (alias RAM5) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH_cm0plus = 0x1000000  ; /* PROGRAM_FLASH_cm0plus */  
  __base_Flash = 0x1000000 ; /* Flash */  
  __top_PROGRAM_FLASH_cm0plus = 0x1000000 + 0x40000 ; /* 256K bytes */  
  __top_Flash = 0x1000000 + 0x40000 ; /* 256K bytes */  
  __base_PROGRAM_FLASH_cm4 = 0x0  ; /* PROGRAM_FLASH_cm4 */  
  __base_Flash2 = 0x0 ; /* Flash2 */  
  __top_PROGRAM_FLASH_cm4 = 0x0 + 0x100000 ; /* 1M bytes */  
  __top_Flash2 = 0x0 + 0x100000 ; /* 1M bytes */  
  __base_SRAM_TCM_cm0plus = 0x9000000  ; /* SRAM_TCM_cm0plus */  
  __base_RAM = 0x9000000 ; /* RAM */  
  __top_SRAM_TCM_cm0plus = 0x9000000 + 0x20000 ; /* 128K bytes */  
  __top_RAM = 0x9000000 + 0x20000 ; /* 128K bytes */  
  __base_FLEX_RAM = 0x48000000  ; /* FLEX_RAM */  
  __base_RAM2 = 0x48000000 ; /* RAM2 */  
  __top_FLEX_RAM = 0x48000000 + 0x1000 ; /* 4K bytes */  
  __top_RAM2 = 0x48000000 + 0x1000 ; /* 4K bytes */  
  __base_USB_RAM = 0x48010000  ; /* USB_RAM */  
  __base_RAM3 = 0x48010000 ; /* RAM3 */  
  __top_USB_RAM = 0x48010000 + 0x800 ; /* 2K bytes */  
  __top_RAM3 = 0x48010000 + 0x800 ; /* 2K bytes */  
  __base_SRAM_DTC_cm4 = 0x20000000  ; /* SRAM_DTC_cm4 */  
  __base_RAM4 = 0x20000000 ; /* RAM4 */  
  __top_SRAM_DTC_cm4 = 0x20000000 + 0x30000 ; /* 192K bytes */  
  __top_RAM4 = 0x20000000 + 0x30000 ; /* 192K bytes */  
  __base_SRAM_ITC_cm4 = 0x8000000  ; /* SRAM_ITC_cm4 */  
  __base_RAM5 = 0x8000000 ; /* RAM5 */  
  __top_SRAM_ITC_cm4 = 0x8000000 + 0x10000 ; /* 64K bytes */  
  __top_RAM5 = 0x8000000 + 0x10000 ; /* 64K bytes */  
