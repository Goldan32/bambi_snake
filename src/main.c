#include "em_device.h"
#include "em_chip.h"

#include "stdbool.h"
#include "em_cmu.h"
#include "em_lcd.h"
#include "segmentlcd.h"

#include "segmentlcd_individual.h"
#include "my_delay.h"
#include "kijelzo.h"

#include "bsp_stk_buttons.h"
#include "em_timer.h"

TIMER_Init_TypeDef TIMER1_init = TIMER_INIT_DEFAULT;


int main(void)
{

  /* user variable declarations */
  uint8_t iter;

  /* Chip errata */
  CHIP_Init();
  CMU_ClockEnable(cmuClock_TIMER1, true);

  /* user inits */
  SegmentLCD_Init(false);
  myDelay_Init();
  BSP_ButtonsInit();

  /*
   * Up-count: Counter counts up until it reaches the value in TIMERn_TOP, where it is reset to 0 before
counting up again.
   */
  TIMER1_init.enable = true;
  TIMER1_init.debugRun = false;
  TIMER1_init.prescale = timerPrescale8 ;
  TIMER1_init.clkSel = timerClkSelHFPerClk;
  TIMER1_init.fallAction = timerInputActionNone;
  TIMER1_init.riseAction = timerInputActionStart ;
  TIMER1_init.mode =timerModeUp ;
  TIMER1_init.dmaClrAct = true;
  TIMER1_init.quadModeX4 = false;
  TIMER1_init.oneShot = false;
  TIMER1_init.sync = false;

  // 62500
// void TIMER_Init(TIMER_TypeDef *timer, const TIMER_Init_TypeDef *init)
  TIMER_Init(TIMER1, &TIMER1_init);
// void TIMER_TopBufSet(TIMER_TypeDef *timer, uint32_t val)
  TIMER_TopBufSet(TIMER1, 62500); // With prescale, it takes 0.5 sec to reach top

  /* user setup before infinite loop */
  for (iter=7;iter<14;iter++)
  {
	  SegmentRoles[iter] = SNAKE;
  }

  SegmentRoles[21] = SNAKE;
  SegmentRoles[29] = SNAKE;
  SegmentRoles[0] = NOTHING;
  SegmentRoles[34] = FOOD;
  SegmentRoles[1] = SNAKE;

// void TIMER_IntClear(TIMER_TypeDef *timer, uint32_t flags)
// void TIMER_IntEnable(TIMER_TypeDef *timer, uint32_t flags)
// uint32_t TIMER_IntGet(TIMER_TypeDef *timer)
// void TIMER_IntSet(TIMER_TypeDef *timer, uint32_t flags)


  TIMER_Enable(TIMER1, true);

  /* Infinite loop */
  while (1) {
	  if (!(BSP_ButtonsGet() & 0b00000000000000000000000000000001)){

		  Decimalpoints_BlinkFiveTimes();
		  myDelay_ms(2000);

		  Screen_DrawAllSegments(SegmentRoles);
	  }



  }
}
