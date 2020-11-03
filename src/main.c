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



int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* user inits */
  SegmentLCD_Init(false);
  myDelay_Init();
  BSP_ButtonsInit();



  /* Infinite loop */
  while (1) {
	  if (!(BSP_ButtonsGet() & 0b00000000000000000000000000000011)){

		  blink_decimalpoints();
	  }

/* this is for github */

  }
}
