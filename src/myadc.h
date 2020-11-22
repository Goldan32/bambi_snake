/*
 * myadc.h
 *
 *  Created on: 2020. nov. 21.
 *      Author: Dani
 */

#ifndef SRC_MYADC_H_
#define SRC_MYADC_H_

#include "em_cmu.h"
#include "em_adc.h"
#include "em_gpio.h"

void myADC0_Init(void);

void myGPIO_Init(void);

uint32_t GenerateRandomNumber(void);

#endif /* SRC_MYADC_H_ */
