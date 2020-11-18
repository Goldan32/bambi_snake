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
#include "em_core.h"

int main(void)
{

  /* user variable declarations */

  /* Chip errata */
  CHIP_Init();

  /* user inits */
  SegmentLCD_Init(false);
  myDelay_Init();
  myTimer_Init();
  BSP_ButtonsInit();
  Game_Init();

  /* user setup before infinite loop */
  Snake_StartSetup();
  _Bool button1_pressed;
  _Bool button2_pressed;

  /* Infinite loop */
  while (1)
  {
	  if(!(BSP_ButtonsGet() & 0b00000000000000000000000000000001))
	  {
		  button1_pressed = true;
	  }
	  if(!(BSP_ButtonsGet() & 0b00000000000000000000000000000010))
	  {
		  button2_pressed = true;
	  }
	  if(timerflag)
	  {
	  		timerflag=false;
	  		if (button1_pressed)
	  		{
	  			Snake_CalculateNextState(LEFT_TURN);
	  			button1_pressed=false;
	  		}
	  		else if(button2_pressed)
	  		{
	  			Snake_CalculateNextState(RIGHT_TURN);
	  			button2_pressed=false;
	  		}
	  		else
	  		{
	  			Snake_CalculateNextState(FORWARD_TURN);
	  		}
	  		Screen_DrawAllSegments(SegmentRoles);
	  		SegmentLCD_Number(SnakeEndings.length);
	  }
}
}
