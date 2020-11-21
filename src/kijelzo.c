/*
 * kijelzo.c
 *
 *  Created on: 2020. okt. 2.
 *      Author: Dani
 */


#include "kijelzo.h"
//#include "my_delay.h"
#include "game_logic.h"
#include "mytimer.h"
#include "bsp_stk_buttons.h"

/* Macros to help iterate through the segments.
 * Basically the values of the segments of the left most digit. */
#define MIDDLE_HORIZONTAL_BASE 0
#define LOWER_HORIZONTAL_BASE 7
#define UPPER_HORIZONTAL_BASE 14
#define LOWER_VERTICAL_BASE 21
#define UPPER_VERTICAL_BASE 29


/* This variable contains the neighbors off all the segments */
SingleSegment_Type SegmentNeighbors[NUM_OF_SEGMENTS]=
{
		{0,30,22,1,21,29,6},		/* middle horizontal row */
		{1,31,23,2,22,30,0},
		{2,32,24,3,23,31,1},
		{3,33,25,4,24,32,2},
		{4,34,26,5,25,33,3},
		{5,35,27,6,26,34,4},
		{6,36,28,0,27,35,5},

		{7,22,30,8,29,21,13},		/* bottom horizontal row */
		{8,23,31,9,30,22,7},
		{9,24,32,10,31,23,8},
		{10,25,33,11,32,24,9},
		{11,26,34,12,33,25,10},
		{12,27,35,13,34,26,11},
		{13,28,36,7,35,27,12},

		{14,22,30,15,29,21,20},		/* top horizontal row */
		{15,23,31,16,30,22,14},
		{16,24,32,17,31,23,15},
		{17,25,33,18,32,24,16},
		{18,26,34,19,33,25,17},
		{19,27,35,20,34,26,18},
		{20,28,36,14,35,27,19},

		{21,6,0,29,7,13,29},		/* bottom vertical row */
		{22,0,1,30,8,7,30},
		{23,1,2,31,9,8,31},
		{24,2,3,32,10,9,32},
		{25,3,4,33,11,10,33},
		{26,4,5,34,12,11,34},
		{27,5,6,35,13,12,35},
		{28,6,0,36,7,13,36},

		{29,20,14,21,0,6,21},		/* top vertical row */
		{30,14,15,22,1,0,22},
		{31,15,16,23,2,1,23},
		{32,16,17,24,3,2,24},
		{33,17,18,25,4,3,25},
		{34,18,19,26,5,4,26},
		{35,19,20,27,6,5,27},
		{36,20,14,28,0,6,28},

};


segment_status SegmentRoles[NUM_OF_SEGMENTS] = {SNAKE, NOTHING};


void Screen_DrawAllSegments(segment_status* segments)
{
	{
		uint8_t i;

		/* A variable with type defined in "segmentlcd_individual.h" passed to function also defined there */
		SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS]={0};


		/* Iterate through all 2 vertical and 3 horizontal rows */

		/* In the middle row, one logical segment is made up of two physical segments */
		for (i=0;i<SEGMENT_LCD_NUM_OF_LOWER_CHARS;i++)
		{
			if (segments[MIDDLE_HORIZONTAL_BASE + i] == NOTHING)
			{
				lowerCharSegments[i].g = 0;
				lowerCharSegments[i].m = 0;
			}
			else
			{
				lowerCharSegments[i].g = 1;
				lowerCharSegments[i].m = 1;
			}

		}

		for (i=0;i<SEGMENT_LCD_NUM_OF_LOWER_CHARS;i++)
		{
			lowerCharSegments[i].d = (segments[LOWER_HORIZONTAL_BASE + i] == NOTHING) ? 0 : 1;
		}

		for (i=0;i<SEGMENT_LCD_NUM_OF_LOWER_CHARS;i++)
		{
			lowerCharSegments[i].a = (segments[UPPER_HORIZONTAL_BASE + i] == NOTHING) ? 0 : 1;
		}

		for (i=0;i<SEGMENT_LCD_NUM_OF_LOWER_CHARS;i++)
		{
			lowerCharSegments[i].e = (segments[LOWER_VERTICAL_BASE + i] == NOTHING) ? 0 : 1;
		}

		for (i=0;i<SEGMENT_LCD_NUM_OF_LOWER_CHARS;i++)
		{
			lowerCharSegments[i].f = (segments[UPPER_VERTICAL_BASE + i] == NOTHING) ? 0 : 1;
		}


		/* Can't iterate through these two using macros, better to have them here */
		lowerCharSegments[6].c = (segments[28] == NOTHING) ? 0 : 1;
		lowerCharSegments[6].b = (segments[36] == NOTHING) ? 0 : 1;


		/* Calling the drawing function from the segmentlcd_individual driver */
		SegmentLCD_LowerSegments(lowerCharSegments);
		}

}


/* This Function uses the segmentlcd_individual driver for blinking the decimal points */
void Decimalpoints_BlinkFiveTimes(void)
{
	uint8_t p;
	SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];
	for (p = 0; p < SEGMENT_LCD_NUM_OF_LOWER_CHARS; p++)
	{
	  lowerCharSegments[p].raw = 0;
	  SegmentLCD_LowerSegments(lowerCharSegments);
    }

	TIMER_Enable(TIMER2, true);
	TIMER_IntClear(TIMER2, _TIMER_IF_MASK);
	TIMER_IntEnable(TIMER2, TIMER_IEN_OF);
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	NVIC_EnableIRQ(TIMER2_IRQn);

	_Bool lcd_on=false;

	while(1)
	{
		/*BSP_ButtonsGet is 0, if*/
		if(!(BSP_ButtonsGet()==0b00000000000000000000000000000011))
		{
			status=RESTARTING;
			SegmentLCD_Symbol(LCD_SYMBOL_DP2, 0);
			SegmentLCD_Symbol(LCD_SYMBOL_DP3, 0);
			SegmentLCD_Symbol(LCD_SYMBOL_DP4, 0);
			SegmentLCD_Symbol(LCD_SYMBOL_DP5, 0);
			return;
		}
		else
		{
			if(mydelayflag)
			{
				mydelayflag=false;
				if(lcd_on)
				{
					SegmentLCD_Symbol(LCD_SYMBOL_DP2, 0);
					SegmentLCD_Symbol(LCD_SYMBOL_DP3, 0);
					SegmentLCD_Symbol(LCD_SYMBOL_DP4, 0);
					SegmentLCD_Symbol(LCD_SYMBOL_DP5, 0);
					lcd_on=false;
				}
				else
				{
					SegmentLCD_Symbol(LCD_SYMBOL_DP2, 1);
					SegmentLCD_Symbol(LCD_SYMBOL_DP3, 1);
					SegmentLCD_Symbol(LCD_SYMBOL_DP4, 1);
					SegmentLCD_Symbol(LCD_SYMBOL_DP5, 1);
					lcd_on=true;
				}
			}
		}
	}
}
