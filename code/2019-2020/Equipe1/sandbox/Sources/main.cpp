#include "derivative.h" /* include peripheral declarations */
#include "Debug.h"
#include "ImageProcessing.h"
#include "Movement.h"

Movement myMovement;
Img_Proc camera;

int main(){
	
	debug_init();
	myMovement.init();
	camera.init();
	myMovement.set(100,0.0);
	
	for(;;) {	
		}
	
	return 0;
}

void delay_time(int number){
	int cnt;
	for(cnt=0;cnt<number;cnt++);
}

void FTM1_IRQHandler() {//servo interrupt, 100Hz
	//Clear the bit of the interrupt FTM1;
	camera.processAll();
	
	myMovement.set(100,camera.servo_angle);
	
	TPM1_SC |= TPM_SC_TOF_MASK;

}
void FTM2_IRQHandler() {//encoder interrupt 6kHz
	myMovement.encoder.interruptHandler();
	myMovement.regulate();
	
}
