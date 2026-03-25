/*
 * Copyright 2016-2026 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    car_control_frdmmcxn236.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "app.h"

// Definition dans le repertoire board
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif

	PRINTF("Hello World\r\n");

	APP_Init();
	// aucun retour apres ça, la suite est dans APP_Run, appelée par la tache xxxx
	for (;;);
}

