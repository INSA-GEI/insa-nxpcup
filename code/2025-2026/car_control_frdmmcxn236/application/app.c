/*
 * app.c
 *
 *  Created on: 25 mars 2026
 *      Author: dimercur
 */

#include "app.h"

#include "configuration.h"
#include "debug.h"

// include pour ecran et camera
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_inputmux.h"
#include "lcd_impl_flexio.h"
#include "st7796_lcd.h"
#include "fsl_clock.h"
#include "fsl_smartdma.h"
#include "ov7670.h"
#include "string.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Taches applicatives */
#include "app_tasks.h"

/* Taille de l'ecran */
#define WIDTH  320
#define HEIGHT 240
#define SLICE_WIDTH 16

/* Variables liées à la camera et au smartdma */
smartdma_camera_param_t smartdmaParam;                  /*!< SMARTDMA function parameters. */
volatile uint8_t g_smartdma_stack[32];

/* Buffer pour l'image et les bandes */
//volatile uint8_t g_camera_buffer[WIDTH*HEIGHT*2];
//volatile uint8_t middle_slice [HEIGHT*16*2];
uint16_t g_camera_buffer[WIDTH*HEIGHT] __attribute__ ((aligned (4)));		// 32bit aligned

uint16_t middle_slice [SLICE_WIDTH*HEIGHT] __attribute__ ((aligned (4)));	// 32bit aligned
uint16_t bottom_slice [SLICE_WIDTH*HEIGHT] __attribute__ ((aligned (4)));	// 32bit aligned
uint16_t top_slice [SLICE_WIDTH*HEIGHT] __attribute__ ((aligned (4)));	// 32bit aligned

uint16_t middle_slice_Y [SLICE_WIDTH*HEIGHT] __attribute__ ((aligned (4)));	// 32bit aligned
uint16_t bottom_slice_Y [SLICE_WIDTH*HEIGHT] __attribute__ ((aligned (4)));	// 32bit aligned
uint16_t top_slice_Y [SLICE_WIDTH*HEIGHT] __attribute__ ((aligned (4)));	// 32bit aligned

/* Variables liées à l'ecran et au flexio */
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
void SmartDMA_camera_callback(void *param){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	xSemaphoreGiveFromISR(xCameraFrameReceivedSemaphore, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
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

/**
 * Application startup
 * Never call it in a task !!!
 */
void APP_Start(void) {
	/* Init board hardware. */
	/* attach FRO 12M to FLEXCOMM4 (debug console) */
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1u);
	CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

	/* init I2C2*/
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
	CLOCK_EnableClock(kCLOCK_LPFlexComm2);
	CLOCK_EnableClock(kCLOCK_LPI2c2);
	CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u);

	/* Init task, queues and semaphores */
	TASKS_Init();

	/* Init debug support */
	DEBUG_Init();

	// Lancement de freertos, pas de retour après ça !
	vTaskStartScheduler();

	for (;;);
}

/**
 * Application init, to be called in a task
 */
void APP_Init(void) {

	/* Init Camera support */
	SmartDMA_camera_pin_init();
	Ov7670_Init();

	INPUTMUX_Init(INPUTMUX0);
	INPUTMUX_AttachSignal(INPUTMUX0, 0, kINPUTMUX_GpioPort0Pin4ToSmartDma);//P0_10/EZH_CAMERA_VSYNC
	INPUTMUX_AttachSignal(INPUTMUX0, 1, kINPUTMUX_GpioPort0Pin5ToSmartDma);//P0_5/EZH_CAMERA_HSYNC
	INPUTMUX_AttachSignal(INPUTMUX0, 2, kINPUTMUX_GpioPort0Pin7ToSmartDma);//P0_7/EZH_CAMERA_PCLK
	/* Turn off clock to inputmux to save power. Clock is only needed to make changes */
	INPUTMUX_Deinit(INPUTMUX0);

	/* A revoir */
	//for(uint32_t i=0;i<320*240;i++){
	//	g_camera_buffer[2*i]= 0x00;
	//}

	memset(g_camera_buffer, 0, sizeof(g_camera_buffer));

	/* Init LCD support */
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

	smartdmaParam.smartdma_stack = (uint32_t*)g_smartdma_stack;
	smartdmaParam.p_buffer  		 = (uint32_t*)g_camera_buffer;
	SMARTDMA_Boot(kSMARTDMA_FlexIO_CameraWholeFrame, &smartdmaParam, 0x2);

	// All good, let's start
	DEBUG_Print("Rock'n'Roll, baby !");
}

/*!
 * @brief Function responsible for sending image to display and
 * save 3 slices (buffer) of incoming image for line detection.
 *
 * Called by task TASKS_CameraFrameReceived
 */
void APP_CameraFrameReceived(void)
{
	// Attend qu'une image soit reçue
	if (xSemaphoreTake(xCameraFrameReceivedSemaphore, portMAX_DELAY) == pdTRUE)
	{
		DEBUG_EnterSection(T1);

		// Envoi de l'image complete sur l'ecran (à gauche)
		st7796_lcd_load(&s_lcd, (uint8_t *)g_camera_buffer, 0, 320-1, 0, 240-1);

		DEBUG_EnterSection(T3);
		// Recuperation d'une bande de SLICE_WIDTH pixels de haut, en bas de l'ecran
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < SLICE_WIDTH; x++) {
				//output_buffer[y * WIDTH + x] = input_buffer[y * WIDTH + x];
				bottom_slice[y * SLICE_WIDTH + x] = g_camera_buffer[y * WIDTH + x];
			}
		}

		// Recuperation d'une bande de SLICE_WIDTH pixels de haut, au centre de l'ecran
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < SLICE_WIDTH; x++) {
				middle_slice[y * SLICE_WIDTH + x] = g_camera_buffer[y * WIDTH + x+((WIDTH/2)-(SLICE_WIDTH/2))];
			}
		}

		// Recuperation d'une bande de SLICE_WIDTH pixels de haut, en haut de l'ecran
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < SLICE_WIDTH; x++) {
				top_slice[y * SLICE_WIDTH + x] = g_camera_buffer[y * WIDTH + x+(WIDTH-SLICE_WIDTH)];
			}
		}

		xSemaphoreGive(xComputelinesSemaphore);
		DEBUG_LeaveSection(T3);
		DEBUG_LeaveSection(T1);
	}
}

#include <stdint.h>

void APP_rotate_and_luma (
    uint16_t *src,
    uint16_t *dst,
    int width,
    int height
) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            uint16_t pixel = src[y * width + x];

            // Extraction RGB565
            uint16_t r = (pixel >> 11) & 0x1F;
            uint16_t g = (pixel >> 5)  & 0x3F;
            uint16_t b =  pixel        & 0x1F;

            // Mise à l’échelle vers 8 bits
            r = (r << 3) | (r >> 2);
            g = (g << 2) | (g >> 4);
            b = (b << 3) | (b >> 2);

            // Luminance
            uint16_t Y = (77 * r + 150 * g + 29 * b) >> 8;

            // Stockée sur 16 bits (simple extension)
            uint16_t Y16 = Y << 8; // ou Y * 257 pour full scale

            // Rotation 90° horaire
            dst[x * height + (height - 1 - y)] = Y16;
        }
    }
}

#include <stdint.h>

void APP_binarize_per_line(
    uint16_t *img,
    int width,
    int height
) {
    for (int y = 0; y < height; y++) {

        uint16_t min = 0xFFFF;
        uint16_t max = 0x0000;

        // 1. trouver min / max
        for (int x = 0; x < width; x++) {
            uint16_t v = img[y * width + x];
            if (v < min) min = v;
            if (v > max) max = v;
        }

        // 2. seuil
        uint16_t threshold = (min + max) >> 1;

        // 3. seuillage
        for (int x = 0; x < width; x++) {
            uint16_t *p = &img[y * width + x];
            *p = (*p >= threshold) ? 0xFFFF : 0x0000;
        }
    }
}

void APP_rotate_back (
    uint16_t *src,
    uint16_t *dst,
    int width,
    int height
) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            uint16_t pixel = src[y * width + x];

            // Rotation 90° horaire
            dst[x * height + (height - 1 - y)] = pixel;
        }
    }
}

/*!
 * @brief Function responsible for searching for line in image slices.
 *
 * Called by task TASKS_Computelines
 */
void APP_Computelines (void)
{

	if (xSemaphoreTake(xComputelinesSemaphore, portMAX_DELAY) == pdTRUE)
	{
		DEBUG_EnterSection(T2);
		DEBUG_EnterSection(T3);

		APP_rotate_and_luma(top_slice, top_slice_Y, SLICE_WIDTH, HEIGHT);
		APP_rotate_and_luma(middle_slice, middle_slice_Y, SLICE_WIDTH, HEIGHT);
		APP_rotate_and_luma(bottom_slice, bottom_slice_Y, SLICE_WIDTH, HEIGHT);

		APP_binarize_per_line(top_slice_Y, SLICE_WIDTH, HEIGHT);
		APP_binarize_per_line(middle_slice_Y, SLICE_WIDTH, HEIGHT);
		APP_binarize_per_line(bottom_slice_Y, SLICE_WIDTH, HEIGHT);

		APP_rotate_back(top_slice_Y, top_slice, SLICE_WIDTH, HEIGHT);
		APP_rotate_back(middle_slice_Y, middle_slice, SLICE_WIDTH, HEIGHT);
		APP_rotate_back(bottom_slice_Y, bottom_slice, SLICE_WIDTH, HEIGHT);
		DEBUG_LeaveSection(T3);

		// Envoi de la bande du bas sur l'ecran
		st7796_lcd_load(&s_lcd, (uint8_t *)bottom_slice, 0 , SLICE_WIDTH-1, 240, 480-1);
		st7796_lcd_load(&s_lcd, (uint8_t *)bottom_slice, SLICE_WIDTH , 2*SLICE_WIDTH-1, 240, 480-1);

		// Envoi de la bande du milieu sur l'ecran
		st7796_lcd_load(&s_lcd, (uint8_t *)middle_slice, WIDTH/2-8 , WIDTH/2+8-1, 240, 480-1);
		st7796_lcd_load(&s_lcd, (uint8_t *)middle_slice, WIDTH/2-8-SLICE_WIDTH , WIDTH/2+8-1-SLICE_WIDTH, 240, 480-1);

		// Envoi de la bande du haut sur l'ecran
		st7796_lcd_load(&s_lcd, (uint8_t *)top_slice, WIDTH-SLICE_WIDTH , WIDTH-1, 240, 480-1);
		st7796_lcd_load(&s_lcd, (uint8_t *)top_slice, WIDTH-2*SLICE_WIDTH , WIDTH-SLICE_WIDTH-1, 240, 480-1);

		DEBUG_LeaveSection(T2);
	}
}

/*!
 * @brief Function responsible for motor control
 *
 * Called by task TASKS_MotorsControlLoop
 */
void APP_CarControl (void) {
	// Todo
}

