/*
 * myadc.c
 *
 *  Created on: 2020. nov. 21.
 *      Author: Dani
 */


#include "myadc.h"
#include "mytimer.h"

void myADC0_Init(void)
{
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_ADC0, true);

	ADC_Init_TypeDef ADC0_Init = ADC_INIT_DEFAULT;
	ADC_InitSingle_TypeDef ADC0_InitSingle = ADC_INITSINGLE_DEFAULT;

	ADC0_Init.timebase = ADC_TimebaseCalc(0);
	ADC0_Init.prescale = ADC_PrescaleCalc(7000000,0) ;
	ADC_Init(ADC0, &ADC0_Init);

	ADC0_InitSingle.input = adcSingleInputCh0;
	ADC0_InitSingle.diff = true;
	ADC_InitSingle(ADC0, &ADC0_InitSingle);
}

void myGPIO_Init(void)
{
	CMU_ClockEnable(cmuClock_GPIO, true);
    GPIO_PinModeSet(gpioPortD, 0, gpioModeInput, 0);
}


uint32_t GenerateRandomNumber(void)
{

	myADC0_Init();
	myGPIO_Init();
	ADC_Start(ADC0, adcStartSingle);
	myDelay_ms(100);
	uint32_t retVal = ADC_DataSingleGet(ADC0);
	return retVal;
}
