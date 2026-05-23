/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "fsl_inputmux.h"
#include "clock_config.h"
#include "board.h"
#include "lcd_impl_flexio.h"
#include "st7796_lcd.h"
#include "fsl_clock.h"
#include "fsl_smartdma.h"
#include "ov7670.h"
#include "string.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
smartdma_camera_param_t smartdmaParam;                  /*!< SMARTDMA function parameters. */
volatile uint8_t g_camera_buffer[320*240*2];
volatile uint8_t g_samrtdma_stack[32];
volatile uint32_t g_camera_complete_flag=0;
static lcd_impl_flexio_t s_lcd_impl;
static st7796_lcd_t s_lcd = {
    .config =
        {
            .direction = ST7796_DIR_0,
            .pix_fmt   = ST7796_RGB565,
            .bgr_mode  = 1,
            .inversion = 0,
            .mirrored  = 1,
        },
    .cb =
        {
            .reset_cb      = lcd_impl_reset,
            .write_cmd_cb  = lcd_impl_write_cmd,
            .write_data_cb = lcd_impl_write_data,
        },
    .user_data = &s_lcd_impl,
};


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SmartDMA_camera_callback(void *param){
		g_camera_complete_flag = 1;
 }
static void SmartDMA_camera_pin_init(void){

	SMARTDMACAMERAPINS_CAM_D7_PORT->PCR[SMARTDMACAMERAPINS_CAM_D7_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D6_PORT->PCR[SMARTDMACAMERAPINS_CAM_D6_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D5_PORT->PCR[SMARTDMACAMERAPINS_CAM_D5_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D4_PORT->PCR[SMARTDMACAMERAPINS_CAM_D4_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D3_PORT->PCR[SMARTDMACAMERAPINS_CAM_D3_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D2_PORT->PCR[SMARTDMACAMERAPINS_CAM_D2_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D1_PORT->PCR[SMARTDMACAMERAPINS_CAM_D1_PIN] = (1<<12)|(7 << 8);
	SMARTDMACAMERAPINS_CAM_D0_PORT->PCR[SMARTDMACAMERAPINS_CAM_D0_PIN] = (1<<12)|(7 << 8);
}

/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    /* attach FRO 12M to FLEXCOMM4 (debug console) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1u);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* init I2C2*/
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    CLOCK_EnableClock(kCLOCK_LPFlexComm2);
    CLOCK_EnableClock(kCLOCK_LPI2c2);
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    SmartDMA_camera_pin_init();
    Ov7670_Init();

    g_camera_complete_flag=0;
	INPUTMUX_Init(INPUTMUX0);
	INPUTMUX_AttachSignal(INPUTMUX0, 0, kINPUTMUX_GpioPort0Pin4ToSmartDma);//P0_10/EZH_CAMERA_VSYNC
	INPUTMUX_AttachSignal(INPUTMUX0, 1, kINPUTMUX_GpioPort0Pin5ToSmartDma);//P0_5/EZH_CAMERA_HSYNC
	INPUTMUX_AttachSignal(INPUTMUX0, 2, kINPUTMUX_GpioPort0Pin7ToSmartDma);//P0_7/EZH_CAMERA_PCLK
	/* Turn off clock to inputmux to save power. Clock is only needed to make changes */
	INPUTMUX_Deinit(INPUTMUX0);

	for(uint32_t i=0;i<320*240;i++){
		g_camera_buffer[2*i]= 0x00;
	}
	lcd_impl_init(&s_lcd_impl);
	st7796_lcd_init(&s_lcd);
	st7796_lcd_load(&s_lcd, (uint8_t *)g_camera_buffer, 0, 	 320-1, 0,   240-1);
	st7796_lcd_load(&s_lcd, (uint8_t *)g_camera_buffer, 0, 	 320-1, 240,   480-1);

	SMARTDMA_InitWithoutFirmware();
	SMARTDMA_InstallFirmware(SMARTDMA_CAMERA_MEM_ADDR,s_smartdmaCameraFirmware,
						 SMARTDMA_CAMERA_FIRMWARE_SIZE);
	SMARTDMA_InstallCallback(SmartDMA_camera_callback, NULL);
	NVIC_EnableIRQ(SMARTDMA_IRQn);
	NVIC_SetPriority(SMARTDMA_IRQn, 3);

	smartdmaParam.smartdma_stack = (uint32_t*)g_samrtdma_stack;
	smartdmaParam.p_buffer  		 = (uint32_t*)g_camera_buffer;
	SMARTDMA_Boot(kEZH_Camera_320240_Whole_Buf, &smartdmaParam, 0x2);

    while (1)
    {
      while(g_camera_complete_flag == 0);
  	  st7796_lcd_load(&s_lcd, (uint8_t *)g_camera_buffer, 0, 320-1, 120, 360-1);
  	  g_camera_complete_flag=0;
    }
}
