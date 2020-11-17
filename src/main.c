#include "em_device.h"
#include "em_chip.h"

#include "stdbool.h"
#include "em_cmu.h"
#include "em_lcd.h"
#include "segmentlcd.h"

#include "segmentlcd_individual.h"
#include "my_delay.h"
#include "kijelzo.h"
#include "mytimer.h"
#include "game_logic.h"

#include "bsp_stk_buttons.h"
#include "em_timer.h"


volatile bool button_IT_flag = false;

void Button_IRQ(void){

int main(void)
{

  /* user variable declarations */
  uint8_t iter;

  /* Chip errata */
  CHIP_Init();

  /* user inits */
  SegmentLCD_Init(false);
  myDelay_Init();
  myTimer_Init();
  BSP_ButtonsInit();
  Game_Init();

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

  /* Infinite loop */
  while (1) {
	  if (!(BSP_ButtonsGet() & 0b00000000000000000000000000000001)){

		  Decimalpoints_BlinkFiveTimes();
		  myDelay_ms(2000);

		  Screen_DrawAllSegments(SegmentRoles);
	  }
	  if(timerflag){
		timerflag=false;
		Screen_DrawAllSegments(&SegmentRoles[NUM_OF_SEGMENTS]);
	  }



  }
}
