#include "interrupt.h"

int reload = 0;
const int max_reload = 0xFFFFFA;

void Timer_init(float Te) {
	reload = ((int) (Te*F_CPU))-1;
	if (reload > max_reload) reload = max_reload;
	SYST_CSR |= (1<<2);
	SYST_CSR |= (1<<1);	// Enables systick exception
	SYST_RVR &= 0x0;
	SYST_RVR |= reload;
	SYST_CVR &= 0x0;
	
	SYST_CSR |= (1<<0);	// Enable IT
}
