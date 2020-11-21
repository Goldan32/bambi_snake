/*
 * my_delay.h
 *
 *  Created on: 2020. okt. 2.
 *      Author: Dani
 */

#ifndef SRC_MY_DELAY_H_
#define SRC_MY_DELAY_H_

#include "em_device.h"
#include "em_timer.h"
#include "em_cmu.h"
#include <stdbool.h>

#define RTC_FREQ 32768
#define TIMER_FREQ 48000000

void myDelay_Init(void);
//void myDelay_ms(int ms);

#endif /* SRC_MY_DELAY_H_ */
