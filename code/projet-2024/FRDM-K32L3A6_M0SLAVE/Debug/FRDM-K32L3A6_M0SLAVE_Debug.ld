/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2023
 * Generated linker script file for K32L3A60xxx
 * Created from linkscript.ldt by FMCreateLinkLibraries
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.7.0 [Build 9198] [2023-01-17] on 20 avr. 2023 à 16:11:27
 */

INCLUDE "FRDM-K32L3A6_M0SLAVE_Debug_library.ld"
INCLUDE "FRDM-K32L3A6_M0SLAVE_Debug_memory.ld"

ENTRY(ResetISR)

SECTIONS
{
     .text_Flash2 : ALIGN(8)
    {
       FILL(0xff)
        *(.text_Flash2) /* for compatibility with previous releases */
        *(.text_PROGRAM_FLASH_cm4) /* for compatibility with previous releases */
        *(.text.$Flash2)
        *(.text.$PROGRAM_FLASH_cm4)
        *(.text_Flash2.*) /* for compatibility with previous releases */
        *(.text_PROGRAM_FLASH_cm4.*) /* for compatibility with previous releases */
        *(.text.$Flash2.*)
        *(.text.$PROGRAM_FLASH_cm4.*)
        *(.rodata.$Flash2)
        *(.rodata.$PROGRAM_FLASH_cm4)
        *(.rodata.$Flash2.*)
        *(.rodata.$PROGRAM_FLASH_cm4.*)            } > PROGRAM_FLASH_cm4

    /* MAIN TEXT SECTION */
    .text : ALIGN(8)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
        LONG(LOADADDR(.data_RAM5));
        LONG(    ADDR(.data_RAM5));
        LONG(  SIZEOF(.data_RAM5));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        LONG(    ADDR(.bss_RAM5));
        LONG(  SIZEOF(.bss_RAM5));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

       *(.text*)
       KEEP(*freertos*/tasks.o(.rodata*)) /* FreeRTOS Debug Config */
       *(.rodata .rodata.* .constdata .constdata.*)
       . = ALIGN(8);
    } > PROGRAM_FLASH_cm0plus
    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(8)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > PROGRAM_FLASH_cm0plus

    .ARM.exidx : ALIGN(8)
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > PROGRAM_FLASH_cm0plus
 
    _etext = .;
        
 
    /* USB_RAM */
    .m_usb_data (NOLOAD) :
    {
        *(m_usb_bdt)
        *(m_usb_global)
    } > USB_RAM AT> USB_RAM
    /* DATA section for FLEX_RAM */

    .data_RAM2 : ALIGN(8)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM2 = .) ;
        PROVIDE(__start_data_FLEX_RAM = .) ;
        *(.ramfunc.$RAM2)
        *(.ramfunc.$FLEX_RAM)
        *(.data.$RAM2)
        *(.data.$FLEX_RAM)
        *(.data.$RAM2.*)
        *(.data.$FLEX_RAM.*)
        . = ALIGN(8) ;
        PROVIDE(__end_data_RAM2 = .) ;
        PROVIDE(__end_data_FLEX_RAM = .) ;
     } > FLEX_RAM AT>PROGRAM_FLASH_cm0plus

    /* DATA section for USB_RAM */

    .data_RAM3 : ALIGN(8)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM3 = .) ;
        PROVIDE(__start_data_USB_RAM = .) ;
        *(.ramfunc.$RAM3)
        *(.ramfunc.$USB_RAM)
        *(.data.$RAM3)
        *(.data.$USB_RAM)
        *(.data.$RAM3.*)
        *(.data.$USB_RAM.*)
        . = ALIGN(8) ;
        PROVIDE(__end_data_RAM3 = .) ;
        PROVIDE(__end_data_USB_RAM = .) ;
     } > USB_RAM AT>PROGRAM_FLASH_cm0plus

    /* DATA section for SRAM_DTC_cm4 */

    .data_RAM4 : ALIGN(8)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM4 = .) ;
        PROVIDE(__start_data_SRAM_DTC_cm4 = .) ;
        *(.ramfunc.$RAM4)
        *(.ramfunc.$SRAM_DTC_cm4)
        *(.data.$RAM4)
        *(.data.$SRAM_DTC_cm4)
        *(.data.$RAM4.*)
        *(.data.$SRAM_DTC_cm4.*)
        . = ALIGN(8) ;
        PROVIDE(__end_data_RAM4 = .) ;
        PROVIDE(__end_data_SRAM_DTC_cm4 = .) ;
     } > SRAM_DTC_cm4 AT>PROGRAM_FLASH_cm0plus

    /* DATA section for SRAM_ITC_cm4 */

    .data_RAM5 : ALIGN(8)
    {
        FILL(0xff)
        PROVIDE(__start_data_RAM5 = .) ;
        PROVIDE(__start_data_SRAM_ITC_cm4 = .) ;
        *(.ramfunc.$RAM5)
        *(.ramfunc.$SRAM_ITC_cm4)
        *(.data.$RAM5)
        *(.data.$SRAM_ITC_cm4)
        *(.data.$RAM5.*)
        *(.data.$SRAM_ITC_cm4.*)
        . = ALIGN(8) ;
        PROVIDE(__end_data_RAM5 = .) ;
        PROVIDE(__end_data_SRAM_ITC_cm4 = .) ;
     } > SRAM_ITC_cm4 AT>PROGRAM_FLASH_cm0plus

    /* MAIN DATA SECTION */
    .uninit_RESERVED (NOLOAD) : ALIGN(8)
    {
        _start_uninit_RESERVED = .;
        KEEP(*(.bss.$RESERVED*))
       . = ALIGN(8) ;
        _end_uninit_RESERVED = .;
    } > SRAM_TCM_cm0plus AT> SRAM_TCM_cm0plus

    /* Main DATA section (SRAM_TCM_cm0plus) */
    .data : ALIGN(8)
    {
       FILL(0xff)
       _data = . ;
       PROVIDE(__start_data_RAM = .) ;
       PROVIDE(__start_data_SRAM_TCM_cm0plus = .) ;
       *(vtable)
       *(.ramfunc*)
       KEEP(*(CodeQuickAccess))
       KEEP(*(DataQuickAccess))
       *(RamFunction)
       *(.data*)
       . = ALIGN(8) ;
       _edata = . ;
       PROVIDE(__end_data_RAM = .) ;
       PROVIDE(__end_data_SRAM_TCM_cm0plus = .) ;
    } > SRAM_TCM_cm0plus AT>PROGRAM_FLASH_cm0plus

    /* BSS section for FLEX_RAM */
    .bss_RAM2 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
       PROVIDE(__start_bss_FLEX_RAM = .) ;
       *(.bss.$RAM2)
       *(.bss.$FLEX_RAM)
       *(.bss.$RAM2.*)
       *(.bss.$FLEX_RAM.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM2 = .) ;
       PROVIDE(__end_bss_FLEX_RAM = .) ;
    } > FLEX_RAM AT> FLEX_RAM

    /* BSS section for USB_RAM */
    .bss_RAM3 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
       PROVIDE(__start_bss_USB_RAM = .) ;
       *(.bss.$RAM3)
       *(.bss.$USB_RAM)
       *(.bss.$RAM3.*)
       *(.bss.$USB_RAM.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM3 = .) ;
       PROVIDE(__end_bss_USB_RAM = .) ;
    } > USB_RAM AT> USB_RAM

    /* BSS section for SRAM_DTC_cm4 */
    .bss_RAM4 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
       PROVIDE(__start_bss_SRAM_DTC_cm4 = .) ;
       *(.bss.$RAM4)
       *(.bss.$SRAM_DTC_cm4)
       *(.bss.$RAM4.*)
       *(.bss.$SRAM_DTC_cm4.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM4 = .) ;
       PROVIDE(__end_bss_SRAM_DTC_cm4 = .) ;
    } > SRAM_DTC_cm4 AT> SRAM_DTC_cm4

    /* BSS section for SRAM_ITC_cm4 */
    .bss_RAM5 : ALIGN(8)
    {
       PROVIDE(__start_bss_RAM5 = .) ;
       PROVIDE(__start_bss_SRAM_ITC_cm4 = .) ;
       *(.bss.$RAM5)
       *(.bss.$SRAM_ITC_cm4)
       *(.bss.$RAM5.*)
       *(.bss.$SRAM_ITC_cm4.*)
       . = ALIGN (. != 0 ? 8 : 1) ; /* avoid empty segment */
       PROVIDE(__end_bss_RAM5 = .) ;
       PROVIDE(__end_bss_SRAM_ITC_cm4 = .) ;
    } > SRAM_ITC_cm4 AT> SRAM_ITC_cm4

    /* MAIN BSS SECTION */
    .bss : ALIGN(8)
    {
        _bss = .;
        PROVIDE(__start_bss_RAM = .) ;
        PROVIDE(__start_bss_SRAM_TCM_cm0plus = .) ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(8) ;
        _ebss = .;
        PROVIDE(__end_bss_RAM = .) ;
        PROVIDE(__end_bss_SRAM_TCM_cm0plus = .) ;
        PROVIDE(end = .);
    } > SRAM_TCM_cm0plus AT> SRAM_TCM_cm0plus

    /* NOINIT section for FLEX_RAM */
    .noinit_RAM2 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM2 = .) ;
       PROVIDE(__start_noinit_FLEX_RAM = .) ;
       *(.noinit.$RAM2)
       *(.noinit.$FLEX_RAM)
       *(.noinit.$RAM2.*)
       *(.noinit.$FLEX_RAM.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM2 = .) ;
       PROVIDE(__end_noinit_FLEX_RAM = .) ;
    } > FLEX_RAM AT> FLEX_RAM

    /* NOINIT section for USB_RAM */
    .noinit_RAM3 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM3 = .) ;
       PROVIDE(__start_noinit_USB_RAM = .) ;
       *(.noinit.$RAM3)
       *(.noinit.$USB_RAM)
       *(.noinit.$RAM3.*)
       *(.noinit.$USB_RAM.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM3 = .) ;
       PROVIDE(__end_noinit_USB_RAM = .) ;
    } > USB_RAM AT> USB_RAM

    /* NOINIT section for SRAM_DTC_cm4 */
    .noinit_RAM4 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM4 = .) ;
       PROVIDE(__start_noinit_SRAM_DTC_cm4 = .) ;
       *(.noinit.$RAM4)
       *(.noinit.$SRAM_DTC_cm4)
       *(.noinit.$RAM4.*)
       *(.noinit.$SRAM_DTC_cm4.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM4 = .) ;
       PROVIDE(__end_noinit_SRAM_DTC_cm4 = .) ;
    } > SRAM_DTC_cm4 AT> SRAM_DTC_cm4

    /* NOINIT section for SRAM_ITC_cm4 */
    .noinit_RAM5 (NOLOAD) : ALIGN(8)
    {
       PROVIDE(__start_noinit_RAM5 = .) ;
       PROVIDE(__start_noinit_SRAM_ITC_cm4 = .) ;
       *(.noinit.$RAM5)
       *(.noinit.$SRAM_ITC_cm4)
       *(.noinit.$RAM5.*)
       *(.noinit.$SRAM_ITC_cm4.*)
       . = ALIGN(8) ;
       PROVIDE(__end_noinit_RAM5 = .) ;
       PROVIDE(__end_noinit_SRAM_ITC_cm4 = .) ;
    } > SRAM_ITC_cm4 AT> SRAM_ITC_cm4

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(8)
    {
        _noinit = .;
        PROVIDE(__start_noinit_RAM = .) ;
        PROVIDE(__start_noinit_SRAM_TCM_cm0plus = .) ;
        *(.noinit*)
         . = ALIGN(8) ;
        _end_noinit = .;
       PROVIDE(__end_noinit_RAM = .) ;
       PROVIDE(__end_noinit_SRAM_TCM_cm0plus = .) ;        
    } > SRAM_TCM_cm0plus AT> SRAM_TCM_cm0plus

    /* Reserve and place Heap within memory map */
    _HeapSize = 0x1000;
    .heap (NOLOAD) :  ALIGN(8)
    {
        _pvHeapStart = .;
        . += _HeapSize;
        . = ALIGN(8);
        _pvHeapLimit = .;
    } > SRAM_TCM_cm0plus

     _StackSize = 0x1000;
     /* Reserve space in memory for Stack */
    .heap2stackfill (NOLOAD) :
    {
        . += _StackSize;
    } > SRAM_TCM_cm0plus
    /* Locate actual Stack in memory map */
    .stack ORIGIN(SRAM_TCM_cm0plus) + LENGTH(SRAM_TCM_cm0plus) - _StackSize - 0 (NOLOAD) :  ALIGN(8)
    {
        _vStackBase = .;
        . = ALIGN(8);
        _vStackTop = . + _StackSize;
    } > SRAM_TCM_cm0plus

    /* Provide basic symbols giving location and size of main text
     * block, including initial values of RW data sections. Note that
     * these will need extending to give a complete picture with
     * complex images (e.g multiple Flash banks).
     */
    _image_start = LOADADDR(.text);
    _image_end = LOADADDR(.data) + SIZEOF(.data);
    _image_size = _image_end - _image_start;
}