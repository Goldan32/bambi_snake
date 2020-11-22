/*
 * mytimer.h
 *
 *  Created on: 9 Nov 2020
 *      Author: koren
 */

#ifndef SRC_MYTIMER_H_
#define SRC_MYTIMER_H_

#include "em_timer.h"
#include "kijelzo.h"
#include "em_cmu.h"

/* With 1024 Prescale, f(timer) = 13.672 kHz */
#define TIMER1_FREQ 13.672;

volatile _Bool timerflag;

void myTimer1_Init(void);

void myTimer2_Init(void);

void TIMER1_IRQHandler(void);

//void myDelay_ms(uint32_t ms);

#endif /* SRC_MYTIMER_H_ */

