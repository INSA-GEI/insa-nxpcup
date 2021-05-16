#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <MKL25Z4.h>
#include "Debug.h"

#define F_CPU 48000000.0


/**
  * @brief 	Configure systick interrupt with a chosen frequency
  * @param 	float Te = period of the interruption 
  * @retval none
  */
void Timer_init(float);

#endif /* INTERRUPT_H_ */
