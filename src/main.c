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
#include "time.h"
#include "stdlib.h"

int main(void)
{

  /* user variable declarations */

  
  /* Chip errata */
  CHIP_Init();

  srand(time(NULL));
  /* user inits */
  SegmentLCD_Init(false);
  BSP_ButtonsInit();
  /* user setup before infinite loop */
  Game_Init();
  TIMER_Enable(TIMER1, true);

  /* Infinite loop */
  while (1)
  {
	  if(status==RESTARTING)
	  {
		  Game_Init();
		  myDelay_ms(500);
	  }
	  if(!input_rec)
	  {
		  if(debounce<500)
		  {
			  debounce++;
		  }
		  else
		  {
			  if (!BSP_ButtonGet(0))
			  {
				  button1_pressed=true;
				  input_rec=true;
			  }
			  if (!BSP_ButtonGet(1))
			  {
				  button2_pressed=true;
				  input_rec=true;
			  }
		  }
	  }
	  if(timerflag)
	  {

		  timerflag=false;

		  if (input_rec)
		  {
			  if(button1_pressed)
			  {
				  Snake_CalculateNextState(LEFT_TURN);
				  button1_pressed=false;
			  }
			  else if (button2_pressed)
			  {
				  Snake_CalculateNextState(RIGHT_TURN);
				  button2_pressed=false;
			  }

		  }
		  else
		  {
			  Snake_CalculateNextState(FORWARD_TURN);
		  }
		  if(status==RUNNING)
		  {
		  Screen_DrawAllSegments(SegmentRoles);
		  SegmentLCD_Number(SnakeEndings.length);
		  debounce=0;
		  }
		  input_rec=false;

	  }

  }

}
