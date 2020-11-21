/*
 * mytimer.c
 *
 *  Created on: 9 Nov 2020
 *      Author: koren
 */

#include "mytimer.h"

/* When it reaches the top, it sends an interrupt */
void TIMER1_IRQHandler(void){
	TIMER_IntClear(TIMER1, _TIMER_IF_MASK);
	timerflag=true;
};

void TIMER2_IRQHandler(void){
	TIMER_IntClear(TIMER2, _TIMER_IF_MASK);
	mydelayflag=true;
}
/*
 * Up-count: Counter counts up until it reaches the value in TIMERn_TOP, where it is reset to 0 before
counting up again.
 */
TIMER_Init_TypeDef TIMER1_init = TIMER_INIT_DEFAULT;
TIMER_Init_TypeDef TIMER2_init = TIMER_INIT_DEFAULT;

/*	If HFPERCLK is 14MHz:
 * 			14 MHz / 1024 (prescale) = 13.67 kHz
 * 			----> 0.07314 ms ---> 73.14 us is 1 tick
 * 	for 1 second, 13672 tick needed
 * 	for 0.5 second, 6836 tick needed
 * 	...
 */
void myTimer1_Init(void){

	CMU_ClockEnable(cmuClock_TIMER1, true);

	TIMER1_init.enable = true;
	TIMER1_init.debugRun 	= false;
	TIMER1_init.prescale 	= timerPrescale1024;
	TIMER1_init.clkSel 		= timerClkSelHFPerClk;
	TIMER1_init.fallAction 	= timerInputActionNone;
	TIMER1_init.riseAction 	= timerInputActionStart;
	TIMER1_init.mode 		= timerModeUp;
	TIMER1_init.dmaClrAct 	= true;
	TIMER1_init.quadModeX4 	= false;
	TIMER1_init.oneShot 	= false;
	TIMER1_init.sync 		= false;

	TIMER_Init(TIMER1, &TIMER1_init);

	/* With prescale, it takes 0.5 sec to reach top when buffer is 6836 */
	TIMER_TopBufSet(TIMER1, 16000);

	TIMER_Enable(TIMER1, true);
	TIMER_IntClear(TIMER1, _TIMER_IF_MASK);
	TIMER_IntEnable(TIMER1, TIMER_IEN_OF);
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	NVIC_EnableIRQ(TIMER1_IRQn);

};

void myTimer2_Init(void){

	CMU_ClockEnable(cmuClock_TIMER2, true);

	TIMER2_init.enable 		= true;
	TIMER2_init.debugRun 	= false;
	TIMER2_init.prescale 	= timerPrescale1024;
	TIMER2_init.clkSel 		= timerClkSelHFPerClk;
	TIMER2_init.fallAction 	= timerInputActionNone;
	TIMER2_init.riseAction 	= timerInputActionStart;
	TIMER2_init.mode 		= timerModeUp;
	TIMER2_init.dmaClrAct 	= true;
	TIMER2_init.quadModeX4 	= false;
	TIMER2_init.oneShot 	= false;
	TIMER2_init.sync 		= false;

	TIMER_Init(TIMER2, &TIMER2_init);

	TIMER_TopBufSet(TIMER2, 6836);

};



