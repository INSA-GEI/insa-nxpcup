/*
 * afficheur7.h
 *
 *  Created on: Dec 3, 2019
 *      Author: thoma
 */

#ifndef AFFICHEUR7_H_
#define AFFICHEUR7_H_

#define DISP_CLK_PIN (1<<5)
#define DISP_SIN_PIN (1<<6)
#define DISP_LATCH_PIN (1<<10)

//Définition des macros (équivalents à des varaibles statiques binaires)
#define DISP_CLK_OFF		(GPIOC_PSOR |= DISP_CLK_PIN)
#define DISP_CLK_ON		(GPIOC_PCOR |= DISP_CLK_PIN)

#define DISP_SIN_OFF		(GPIOC_PSOR |= DISP_SIN_PIN)
#define DISP_SIN_ON		(GPIOC_PCOR |= DISP_SIN_PIN)

#define DISP_LATCH_OFF		(GPIOC_PSOR |= DISP_LATCH_PIN)
#define DISP_LATCH_ON		(GPIOC_PCOR |= DISP_LATCH_PIN)


void send_data(int data);



#endif /* AFFICHEUR7_H_ */
