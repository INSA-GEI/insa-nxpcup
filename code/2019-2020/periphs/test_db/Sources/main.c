/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"

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
    // Select PLL output (CLKS=0)
    // FLL external reference divider (FRDIV=3)
    // External reference clock for FLL (IREFS=0)
    MCG_C1 = MCG_C1_FRDIV(0x03);
    while((MCG_S & MCG_S_CLKST_MASK) != 0x0CU);  // Wait until PLL output
}


#define MAX_OVF 65535
int OVF_cnt1=0;
int OVF_cnt2=0;
int delta1=0;
int delta2=0;
int prev_ccr1=0;
int prev_ccr2=0;


int main(void){
	clock_init();
	debug_init();
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; //Enable the clock of PORTA, PORTB, PORTD
	SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK; //Enable the clock of TPM2 
	
	TPM2_SC = 7;		// prescaler for TPM2 
	TPM2_SC |= TPM_SC_CMOD(1);					// enable TPM2 clock (LPTPM counter increments on every LPTPM counter clock p553)
	TPM2_MOD = 65535;						// value of auto-reload
	
	TPM2_C0SC = 0;
	TPM2_C1SC = 0;
	TPM2_C0SC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM2 channel_0 for ENC_SIG_A1 (p555)
	TPM2_C1SC|=TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK;					// Configuration of TPM1 channel_1 for ENC_SIG_A2 (p555)
	TPM2_SC |= TPM_SC_TOIE_MASK;				// enable overflow interrupt in TPM2
	
	
	PORTB_PCR2 |= PORT_PCR_MUX(3);				// ENC_SIG_A1 PTB2 TPM2_CH0
	PORTB_PCR3 |= PORT_PCR_MUX(3);				// ENC_SIG_A2 PTB3 TPM2_CH1
	
	//Configures the individual port pins for input or output
	GPIOB_PDDR |= (1<<2);
	GPIOB_PDDR |= (1<<3); 
	
	
	// enable interrupts 19 (TPM = FTM2)  in NVIC, no interrupt levels
	NVIC_ICPR |= (1 << 19);			// clear pending interrupt 19
	NVIC_ISER |= (1 << 19);			// enable interrupt 19
		
	for(;;) {	   
	}
	
	return 0;
}

void FTM2_IRQHandler() {//encoder interrupt
	if ((TPM2_SC & TPM_SC_TOF_MASK)) {//Clear the bit flag of the overflow interrupt FTM2
		TPM2_SC |= TPM_SC_TOF_MASK;
		OVF_cnt1++;
		OVF_cnt2++;
		GPIOB_PTOR = DEBUG_RED_Pin;
		
	}
	if ((TPM2_C0SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture1 FTM2
		TPM2_C0SC |= TPM_CnSC_CHF_MASK ;
		int ccr1=TPM2_C0V;
		

		//GPIOB_PTOR = DEBUG_GREEN_Pin;
		
		if(OVF_cnt1<MAX_OVF){
			delta1 = ccr1 - prev_ccr1 + OVF_cnt1*6553;
		}else{
			delta1=-1;
		}
		prev_ccr1 = ccr1;
		OVF_cnt1=0;
		
	}
	if ((TPM2_C1SC & TPM_CnSC_CHF_MASK)) {//Clear the bit flag of the capture2 FTM2
		TPM2_C1SC |= TPM_CnSC_CHF_MASK ;
		int ccr2=TPM2_C1V;
		if(OVF_cnt2<MAX_OVF){
			delta2 = ccr2 - prev_ccr2 + OVF_cnt2*65536;
		}else{
			delta2=-1;
		}

		//GPIOB_PTOR = DEBUG_BLUE_Pin;
		prev_ccr2 = ccr2;
		OVF_cnt2=0;
	}
	//TPM2_SC |= TPM_SC_TOF_MASK;
	//TPM2_C0SC |= TPM_CnSC_CHF_MASK ;
	//TPM2_C1SC |= TPM_CnSC_CHF_MASK ;
}
