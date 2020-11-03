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

/* enumarated type to store the status of a single segment */
typedef enum {SNAKE, FOOD, NOTHING} segment_status;

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

	segment_status role; /* a segment can be FOOD, SNAKE, or NOTHING */
}SingleSegment;

void Decimalpoints_BlinkFiveTimes(void);






#endif /* SRC_KIJELZO_H_ */
