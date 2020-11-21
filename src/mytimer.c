/*
 * mytimer.c
 *
 *  Created on: 9 Nov 2020
 *      Author: koren
 */

#include "mytimer.h"


void TIMER1_IRQHandler(void){
	TIMER_IntClear(TIMER1, _TIMER_IF_MASK);
	timerflag=true;
};

/*
 * Up-count: Counter counts up until it reaches the value in TIMERn_TOP, where it is reset to 0 before
counting up again.
 */
TIMER_Init_TypeDef TIMER1_init = TIMER_INIT_DEFAULT;

void myTimer_Init(void){
	CMU_ClockEnable(cmuClock_TIMER1, true);

	TIMER1_init.enable = true;
	TIMER1_init.debugRun = false;
	TIMER1_init.prescale =   timerPrescale1024 ;
	TIMER1_init.clkSel = timerClkSelHFPerClk;
	TIMER1_init.fallAction = timerInputActionNone;
	TIMER1_init.riseAction = timerInputActionStart ;
	TIMER1_init.mode =timerModeUp ;
	TIMER1_init.dmaClrAct = true;
	TIMER1_init.quadModeX4 = false;
	TIMER1_init.oneShot = false;
	TIMER1_init.sync = false;

	// void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init)
	TIMER_Init(TIMER1, &TIMER1_init);
	// void TIMER_TopBufSet(TIMER_TypeDef *timer, uint32_t val)

	TIMER_TopBufSet(TIMER1, 10000); // With prescale, it takes 0.5 sec to reach top

	// Timer enable
	TIMER_Enable(TIMER1, true);
	// void TIMER_IntClear(TIMER_TypeDef *timer, uint32_t flags)
	TIMER_IntClear(TIMER1, _TIMER_IF_MASK);
	// void TIMER_IntEnable(TIMER_TypeDef *timer, uint32_t flags)
	TIMER_IntEnable(TIMER1, TIMER_IEN_OF);
	// NVIC_ClearPendingIRQ(IRQn_Type IRQn)
	NVIC_ClearPendingIRQ(TIMER1_IRQn);
	// NVIC_EnableIRQ(IRQn_Type IRQn)
	NVIC_EnableIRQ(TIMER1_IRQn);

};
