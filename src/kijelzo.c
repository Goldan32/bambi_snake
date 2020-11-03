/*
 * kijelzo.c
 *
 *  Created on: 2020. okt. 2.
 *      Author: Dani
 */


#include "kijelzo.h"
#include "my_delay.h"


/*blinks all of the decimal points at once 5 times
 * used at the end of a round*/
void Decimalpoints_BlinkFiveTimes(void)
{
	int i;
	for (i=0;i<5;i++)
	{
		SegmentLCD_Symbol(LCD_SYMBOL_DP2, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP3, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP4, 1);
		SegmentLCD_Symbol(LCD_SYMBOL_DP5, 1);
		myDelay_ms(250);
		SegmentLCD_Symbol(LCD_SYMBOL_DP2, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP3, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP4, 0);
		SegmentLCD_Symbol(LCD_SYMBOL_DP5, 0);
		myDelay_ms(250);
	}
}
