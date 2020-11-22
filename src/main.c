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
#include "myadc.h"

int main(void)
{

  /* user variable declarations */
  _Bool button1_pressed=false;
  _Bool button2_pressed=false;
  _Bool input_rec=false;
  uint16_t debounce=0;
  
  /* Chip errata */
  CHIP_Init();



  /* user inits */
  SegmentLCD_Init(false);
  //myDelay_Init();
  myTimer1_Init();
  myTimer2_Init();
  BSP_ButtonsInit();
  myADC0_Init();


  /* user setup before infinite loop */
  Snake_StartSetup();

  /* Infinite loop */
  while (1)
  {

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
		  Screen_DrawAllSegments(SegmentRoles);
		  SegmentLCD_Number(SnakeEndings.length);
		  debounce=0;
		  input_rec=false;

	  }
  }

}
