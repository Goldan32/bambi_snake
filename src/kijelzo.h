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



/* describes an LCD segment as part of the game map */
SingleSegment_Type SegmentNeighbors[NUM_OF_SEGMENTS];

/* stores the role of each segment: snake, food, or nothing */
segment_status SegmentRoles[NUM_OF_SEGMENTS];




/* the decimal points start to blink and the screen is cleared, signals the end of the game */
void Decimalpoints_BlinkFiveTimes(void);

/* A function that takes an array that contains NUM_OF_SEGMENTS segments status enums
 * then it calls the uppersegments function to set/reset all segments according to the parameter*/
void Screen_DrawAllSegments(segment_status* segments);




#endif /* SRC_KIJELZO_H_ */
