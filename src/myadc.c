/*
 * myadc.c
 *
 *  Created on: 2020. nov. 21.
 *      Author: Dani
 */


#include "myadc.h"

void myADC0_Init(void)
{
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_ADC0, true);

	ADC_Reset(ADC0);
	ADC_Init_TypeDef myADC_Init = ADC_INIT_DEFAULT;


	ADC_InitSingle_TypeDef myADC_InitSingle = ADC_INITSINGLE_DEFAULT;
	myADC_InitSingle.input = adcSingleInputCh0;


	ADC_Init(ADC0, &myADC_Init);
	ADC_InitSingle(ADC0, &myADC_InitSingle);


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
