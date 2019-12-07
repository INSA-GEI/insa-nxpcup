#include <MKL25Z4.h>
#include "Debug.h"
#include "Motor.h"

#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (1000000)
#define BLINK_DELAY     FAST_BLINK

void clock_init();
void delay_time(int);

int main (void){
	clock_init();
	int i=0;
	debug_init();
	motor_init();
	char str[10];
	while(1){
		/*GPIOB_PTOR = DEBUG_RED_Pin;
		delay_time(FAST_BLINK);
		i=debug_getRotarySW();
		debug_displaySendNb(i);
		int l=uart_read(str,10);
		if(l>0){
			uart_write(str,l);
			uart_writeNb(l,0);
			uart_write("\r\n",2);
		}*/
	}
}

void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}


void clock_init(){
    // Enable clock gate to Port A module to enable pin routing (PORTA=1)
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
    
    // Divide-by-2 for clock 1 and clock 4 (OUTDIV1=1, OUTDIV4=1)   
    SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0x01) | SIM_CLKDIV1_OUTDIV4(0x01);

    // System oscillator drives 32 kHz clock for various peripherals (OSC32KSEL=0)
    SIM_SOPT1 &= ~SIM_SOPT1_OSC32KSEL(0x03);

    // Select PLL as a clock source for various peripherals (PLLFLLSEL=1)
    // Clock source for TPM counter clock is MCGFLLCLK or MCGPLLCLK/2
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
    SIM_SOPT2 = (SIM_SOPT2 & ~(SIM_SOPT2_TPMSRC(0x02))) | SIM_SOPT2_TPMSRC(0x01);
                  
    // PORTA_PCR18: ISF=0,MUX=0 
    // PORTA_PCR19: ISF=0,MUX=0 *           
    PORTA_PCR18 &= ~((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
    PORTA_PCR19 &= ~((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));                                                   
    // Switch to FBE Mode 
    
    // OSC0_CR: ERCLKEN=0,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 
    OSC0_CR = 0;                                                   
    // MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 
    MCG_C2 = (MCG_C2_RANGE0(0x02) | MCG_C2_EREFS0_MASK);
    // MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=0,IREFSTEN=0 
    MCG_C1 = (MCG_C1_CLKS(0x02) | MCG_C1_FRDIV(0x03));
    // MCG_C4: DMX32=0,DRST_DRS=0 
    MCG_C4 &= ~((MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(0x03)));
    // MCG_C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 
    MCG_C5 = MCG_C5_PRDIV0(0x01);                                                   
    // MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 
    MCG_C6 = 0;
    
    // Check that the source of the FLL reference clock is 
    // the external reference clock.
    while((MCG_S & MCG_S_IREFST_MASK) != 0)
        ;

    while((MCG_S & MCG_S_CLKST_MASK) != 8)      // Wait until external reference
        ;
    
    // Switch to PBE mode
    //   Select PLL as MCG source (PLLS=1)
    MCG_C6 = MCG_C6_PLLS_MASK;
    while((MCG_S & MCG_S_LOCK0_MASK) == 0)      // Wait until PLL locked
        ;
    
    // Switch to PEE mode
    //    Select PLL output (CLKS=0)
    //    FLL external reference divider (FRDIV=3)
    //    External reference clock for FLL (IREFS=0)
    MCG_C1 = MCG_C1_FRDIV(0x03);
    while((MCG_S & MCG_S_CLKST_MASK) != 0x0CU);  // Wait until PLL output
}
