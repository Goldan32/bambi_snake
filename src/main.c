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
  uint8_t iter;

  /* Chip errata */
  CHIP_Init();

  /* user inits */
  SegmentLCD_Init(false);
  myDelay_Init();
  myTimer_Init();
  BSP_ButtonsInit();

  /* user setup before infinite loop */
  Snake_StartSetup();

  /* Infinite loop */
  while (1)
  {
	  if (!(BSP_ButtonsGet() & 0b00000000000000000000000000000001))
	  {



		 for (iter = 0; iter < 10 ;iter++)
		 {
			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(RIGHT_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(RIGHT_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);

			 Snake_CalculateNextState(FORWARD_TURN);
			 myDelay_ms(500);
		 }




		/* Snake_CalculateNextState(LEFT_TURN);
		 myDelay_ms(500);

		 Snake_CalculateNextState(LEFT_TURN);
		 myDelay_ms(500); */

	  }
	  /*if(timerflag){
		timerflag=false;
		Screen_DrawAllSegments(SegmentRoles); */
  }




}
