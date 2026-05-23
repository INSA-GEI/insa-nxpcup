/*
 *    kinetis_sysinit.c - Default init routines for Flycatcher
 *                     		Kinetis ARM systems
 *    Copyright © 2012 Freescale semiConductor Inc. All Rights Reserved.
 */
 
#include "kinetis_sysinit.h"
#include "derivative.h"

/**
 **===========================================================================
 **  External declarations
 **===========================================================================
 */
#if __cplusplus
extern "C" {
#endif
extern uint32_t __vector_table[];
extern unsigned long _estack;
extern void __thumb_startup(void);
#if __cplusplus
}
#endif

/**
 **===========================================================================
 **  Default interrupt handler
 **===========================================================================
 */
void Default_Handler()
{
	__asm("bkpt");
}

/**
 **===========================================================================
 **  Reset handler
 **===========================================================================
 */
void __init_hardware()
{
	SCB_VTOR = (uint32_t)__vector_table; /* Set the interrupt vector table position */
	
	/* Disable the Watchdog because it may reset the core before entering main(). */
	
	WDOG_TOVAL = 0xE803; // setting timeout value
	WDOG_CS2 = WDOG_CS2_CLK_MASK; // setting 1-kHz clock source
	WDOG_CS1 = 0x23; // Watchdog disabled, 
					 // Watchdog interrupts are disabled. Watchdog resets are not delayed, 
					 // Updates allowed. Software can modify the watchdog configuration registers within 128 bus clocks after performing the unlock write sequence,
					 // Watchdog test mode disabled,
					 // Watchdog disabled in chip debug mode,
					 // Watchdog enabled in chip wait mode,
					 // Watchdog enabled in chip stop mode.
}

/* Weak definitions of handlers point to Default_Handler if not implemented */
void NMI_Handler() __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler() __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler() __attribute__ ((weak, alias("Default_Handler")));

void FTMRH_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PMC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void IRQ_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART0_SCI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART1_SCI1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART2_SCI2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ACMP0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTM2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ACMP1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT_CH0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT_CH1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void KBI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void KBI1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ICS_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void WDG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
	
/* The Interrupt Vector Table */
void (* const InterruptVector[])() __attribute__ ((section(".vectortable"))) = {
    /* Processor exceptions */
    (void(*)(void)) &_estack,
    __thumb_startup,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* Interrupts */
	Default_Handler, 		/* Reserved interrupt 16/0 */
	Default_Handler, 		/* Reserved interrupt 17/1 */
	Default_Handler, 		/* Reserved interrupt 18/2 */
	Default_Handler, 		/* Reserved interrupt 19/3 */
	Default_Handler, 		/* Reserved interrupt 20/4 */
    FTMRH_IRQHandler, 		/* Command complete and error interrupt */
    PMC_IRQHandler, 		/* Low-voltage detect, low-voltage warning */
    IRQ_IRQHandler,			/* External interrupt */
    I2C0_IRQHandler,		/* Single interrupt vector for all sources */
    Default_Handler, 		/* Reserved interrupt 25/9 */
    SPI0_IRQHandler,		/* Single interrupt vector for all sources */
    SPI1_IRQHandler,		/* Single interrupt vector for all sources */
    UART0_SCI0_IRQHandler,  /* UART0 Status and Error interrupt */
    UART1_SCI1_IRQHandler,  /* UART1 Status and Error interrupt */
	UART2_SCI2_IRQHandler,  /* UART2 Status and Error interrupt */
    ADC0_IRQHandler,		/* ADC conversion complete interrupt */
    ACMP0_IRQHandler,		/* Analog comparator 0 interrupt */
    FTM0_IRQHandler,		/* Single interrupt vector for all sources */
	FTM1_IRQHandler,		/* Single interrupt vector for all sources */
    FTM2_IRQHandler,		/* Single interrupt vector for all sources */
	RTC_IRQHandler,			/* RTC overflow */
	ACMP1_IRQHandler,		/* Analog comparator 1 interrupt */
	PIT_CH0_IRQHandler,		/* PIT CH0 overflow */
	PIT_CH1_IRQHandler,		/* PIT CH1 overflow */
	KBI0_IRQHandler,		/* Keyboard interrupt0 */
	KBI1_IRQHandler,		/* Keyboard interrupt1 */
	Default_Handler,		/* Reserved interrupt 42/26 */
    ICS_IRQHandler,			/* Clock loss of lock Interrupt */
    WDG_IRQHandler,			/* WDG timeout interrupt */
    Default_Handler,		/* Reserved interrupt 45/29 */
	Default_Handler,		/* Reserved interrupt 46/30 */
	Default_Handler,		/* Reserved interrupt 47/31 */
};