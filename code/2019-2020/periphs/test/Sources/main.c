/****************************************************************************
 * Project developed as a simple Blink the LED's to 
 * demonstrate basic CodeWarrior functionality and capability.
 * Borrowed from Freedom Example Projects: Blinky
 * 
 * Date: 11 Sept 2012
 * Author: M. Ruthenbeck
 * Revision Level 1.0
 */

#include <MKL25Z4.h>
#include "Debug.h"
#include "afficheur7.h"

#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (500000)
#define BLINK_DELAY     FAST_BLINK

void clock_init();
void delay_time(int);
int main (void)
{
	clock_init();
	int i=0;
	debug_init();
	DEBUG_GREEN_OFF;
	while(1){
		
		
		/* ########## TEST AFFICHEUR LCD ########## */
		send_data(1);
		delay_time(SLOW_BLINK);
		send_data(2);
		delay_time(SLOW_BLINK);
		send_data(3);
		delay_time(SLOW_BLINK);
	}
}

void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}


void clock_init(){
	MCG_C2 = (MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK); 	// configure the oscillator settings
	MCG_C1 = (MCG_C1_CLKS(2) | MCG_C1_FRDIV(3));		// divider for 8 MHz clock	
	for (int i = 0 ; i < 24000 ; i++);						// wait for OSCINIT to set
		// now in FBE mode
		MCG_C6 |= MCG_C6_CME0_MASK;		// enable the clock monitor
	MCG_C5 |= MCG_C5_PRDIV0(1); 	// set PLL ref divider to divide by 2
	int temp_reg = MCG_C6; 				// store present C6 value (as CME0 bit was previously set)
	temp_reg &= ~MCG_C6_VDIV0_MASK; // clear VDIV settings
	temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); 	// write new VDIV and enable PLL
	MCG_C6 = temp_reg; 				// update MCG_C6		
	for (int i = 0 ; i < 4000 ; i++); 	// wait for PLLST status bit to set
		// now in PBE mode
		SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV4(1));	// core clock, bus clock div by 2	
	MCG_C1 &= ~MCG_C1_CLKS_MASK;	// switch CLKS mux to select the PLL as MCGCLKOUT	
	for (int i = 0 ; i < 2000 ; i++);	// Wait for clock status bits to update
	// now in PEE mode, core and system clock 48 MHz, bus and flash clock 24 MHz

}
