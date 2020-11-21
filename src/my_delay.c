/*
 * my_delay.c
 *
 *  Created on: 2020. okt. 2.
 *      Author: Dani
 */

#include "my_delay.h"


/*initialize clock for the delay function, called at the top of main*/
void myDelay_Init(void)
{
	CMU_ClockEnable(cmuClock_CORELE, true);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
	CMU_ClockEnable(cmuClock_RTC, true);
	CMU_ClockEnable(cmuClock_TIMER0, true);
}


/*delay of "parameter" milliseconds*/
/*void myDelay_ms(int ms)
{
  uint32_t endValue = ms * RTC_FREQ / 1000; // RTC Freq az a mi 14MHz-ünk, 1000 a prescale
  RTC->CNT = 0; // berak egy 0-at

  RTC->CTRL |= RTC_CTRL_EN; //engedélyez

  while ( RTC->CNT < endValue ); // számol addig, amíg elnem éri a maxot

  RTC->CTRL &= ~RTC_CTRL_EN; // // ha vége akkor disable
}*/
