/*
 * game_logic.h
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */

#ifndef SRC_GAME_LOGIC_H_
#define SRC_GAME_LOGIC_H_

#include "kijelzo.h"



/* enumarated type to store the status of the game */
typedef enum {RUNNING, STOP} game_status;
game_status status;


void FoodSegment_Place();

/* ################################################################## */

/* Defining the state machine that controls the direction bit*/
typedef enum {RIGHT_STATE, UP_STATE, DOWN_STATE, LEFT_STATE} DirectionState;

typedef enum {RIGHT_TURN, LEFT_TURN, FORWARD_TURN} TurnDirection;


/* state machine, that controls the movement of the snake */
typedef struct Direction_StateMachine_Placeholder
{

	_Bool down_or_left; /* the current direction, true if the snake is going down or left atm */

	DirectionState current_state; /* inner state of the state machine */

	/* function that calculates the direction for the next cycle */
	void (*Snake_TurnDirection)(struct Direction_StateMachine_Placeholder* this, TurnDirection turn);



}Direction_StateMachine_Type;

Direction_StateMachine_Type current_direction;


/* contains the number of the segment, that preceds the current element of this array in the snake
 * elements can be 0...NUM_OF_SEGMENTS-1, if the value is NUM_OF_SEGMENTS, or greater than the value is undefined */
uint8_t Snake_BackwardLinkedList[NUM_OF_SEGMENTS];

/* structure to store the head and tail of the linked list */
typedef struct
{
	uint8_t head;
	uint8_t tail;
	uint8_t length;
}Snake_HeadAndTail;

Snake_HeadAndTail SnakeEndings;


/* MUST BE CALLED AFTER CALCULATING THE NEW DIRECTION WITH THE STATE MACHINE
 * calculates the next state of the display */
void Snake_TurnLinkedList(TurnDirection turn);

void LinkedList_ToDraw(segment_status* segments);

void Snake_CalculateNextState(TurnDirection turn);

void Snake_StartSetup(void);

void EndOfGame_Function(void);


/* ################################################################## */





#endif /* SRC_GAME_LOGIC_H_ */
