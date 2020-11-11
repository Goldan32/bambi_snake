/*
 * mytimer.h
 *
 *  Created on: 9 Nov 2020
 *      Author: koren
 */

#ifndef SRC_MYTIMER_H_
#define SRC_MYTIMER_H_

#include "em_timer.h"
#include "em_cmu.h"
#include "kijelzo.h"



TIMER_Init_TypeDef TIMER1_init;
_Bool timerflag;

void myTimer_Init(void);

void TIMER1_IRQHandler(void);

#endif /* SRC_MYTIMER_H_ */
