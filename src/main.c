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


int main(void)
{

  /* user variable declarations */
  _Bool btn0_ret=false;
  _Bool btn1_ret=false;
  _Bool checked=false;

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

  /* Infinite loop */
  while (1)
  {

	  if (!(BSP_ButtonsGet() & 0b00000000000000000000000000000001))
	  {


			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(LEFT_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(FORWARD_TURN);
			  myDelay_ms(500);

			  Snake_CalculateNextState(RIGHT_TURN);
			  myDelay_ms(500);

	  }



	/*  if(timerflag)
	  {
	  		timerflag=false;
	  		if (btn0_ret)
	  		{
	  			Snake_CalculateNextState(LEFT_TURN);
	  		}
	  		else if (btn1_ret)
			{
	  			Snake_CalculateNextState(RIGHT_TURN);
			}
	  		else
			{
				Snake_CalculateNextState(FORWARD_TURN);
			}
	  		checked=false;

	  }
	  if (!checked)
	  {
		  if (!(BSP_ButtonsGet() & 0b00000000000000000000000000000001))
		  {
			  btn0_ret=true;
			  checked=true;
		  }
		  else if(!(BSP_ButtonsGet() & 0b00000000000000000000000000000010))
		  {
			  btn0_ret=true;
			  checked=true;
		  }
		  else
		  {
			  btn0_ret=btn1_ret=false;
		  }

	  }

*/

  }
}
