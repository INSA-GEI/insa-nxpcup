/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    mtb.c
 * @brief   MTB initialization file.
 * @details Symbols controlling behavior of this code...
 * 			__MTB_DISABLE
 *     		If this symbol is defined, then the buffer array for the MTB
 *     		will not be created.
 *
 * 			__MTB_BUFFER_SIZE
 *     		Symbol specifying the sizer of the buffer array for the MTB.
 *     		This must be a power of 2 in size, and fit into the available
 *   		RAM. The MTB buffer will also be aligned to its 'size' 
 *     		boundary and be placed at the start of a RAM bank (which 
 *     		should ensure minimal or zero padding due to alignment).
 * 
 * 			__MTB_RAM_BANK
 *     		Allows MTB Buffer to be placed into specific RAM bank. When 
 *     		this is not defined, the "default" (first if there are 
 *     		several) RAM bank is used.
 */
 
/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/

// Allow MTB to be removed by setting a define (via command line)
#if !defined (__MTB_DISABLE)

  // Allow for MTB buffer size being set by define set via command line
  // Otherwise provide small default buffer
  #if !defined (__MTB_BUFFER_SIZE)
    #define __MTB_BUFFER_SIZE 128
  #endif
  
  // Check that buffer size requested is >0 bytes in size
  #if (__MTB_BUFFER_SIZE > 0)
    // Pull in MTB related macros
    #include <cr_mtb_buffer.h>

    // Check if MYTB buffer is to be placed in specific RAM bank
    #if defined(__MTB_RAM_BANK)
	    // Place MTB buffer into explicit bank of RAM
	    __CR_MTB_BUFFER_EXT(__MTB_BUFFER_SIZE,__MTB_RAM_BANK);
    #else
	    // Place MTB buffer into 'default' bank of RAM
	    __CR_MTB_BUFFER(__MTB_BUFFER_SIZE);

    #endif  // defined(__MTB_RAM_BANK)

  #endif // (__MTB_BUFFER_SIZE > 0)

#endif // !defined (__MTB_DISABLE)

