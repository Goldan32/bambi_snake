/*
 * kijelzo.h
 *
 *  Created on: 2020. okt. 2.
 *      Author: Dani
 */

#ifndef SRC_KIJELZO_H_
#define SRC_KIJELZO_H_

#include <stdint.h>

#include "em_lcd.h"
#include "segmentlcd.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

#define NUM_OF_SEGMENTS 37
#define BUTTONS_MASK 0b00000000000000000000000000000011

/*
 *  Each segment is defined by a number from 0 to 37
 *
 *	The number that defines each segment is shown here
 *
 *
 *
 *
 * 	  ----  14 ----		 ----  15 ----		 ----  16 ----		 ----  17 ----		 ----  18 ----		 ----  19 ----		 ----  20 ----
 *   |					|					|					|					|					|					|			  |
 *   29					30					31					32					33					34					35			  36
 *   |					|					|					|					|					|					|			  |
 *    ----  0  ----		 ----  1  ----		 ----  2  ----		 ----  3  ----		 ----  4  ----		 ----  5  ----		 ----  6  ----
 *   |					|					|					|					|					|					|			  |
 *   21					22					23					24					25					26					27			  28
 *   |					|					|					|					|					|					|			  |
 *    ----  7  ----		 ----  8  ----		 ----  9  ----		 ----  10 ----		 ----  11 ----		 ----  12 ----		 ----  13 ----
 *
 *
 *
 */

/* ====================== TYPEDEFS ============================= */

/* enumarated type to store the status of a single segment */
typedef enum {NOTHING, SNAKE, FOOD} segment_status;

/* a structure to logically describe a segment as a "pixel" in the game */
typedef struct
{
	uint8_t id; /* number unique to this segment */

	uint8_t left_zero;
	uint8_t right_zero;
	uint8_t forward_zero; /* left right and forward relative to the cell, when the direction is "zero" */

	uint8_t left_one;
	uint8_t right_one;
	uint8_t forward_one; /* left right and forward relative to the cell, when the direction is "one" */

}SingleSegment_Type;

/* ============================================================== */


/* ====================== GLOBALS =============================== */

/* describes an LCD segment as part of the game map */
SingleSegment_Type SegmentNeighbors[NUM_OF_SEGMENTS];

/* stores the role of each segment: snake, food, or nothing */
segment_status SegmentRoles[NUM_OF_SEGMENTS];


/* ============================================================== */


/* ====================== FUNCTIONS ============================= */

/* the decimal points start to blink and the screen is cleared, signals the end of the game */
void Decimalpoints_BlinkFiveTimes(void);

/* A function that takes an array that contains NUM_OF_SEGMENTS segments status enums
 * then it calls the uppersegments function to set/reset all segments according to the parameter*/
void Screen_DrawAllSegments(segment_status* segments);

/* ============================================================== */


#endif /* SRC_KIJELZO_H_ */
