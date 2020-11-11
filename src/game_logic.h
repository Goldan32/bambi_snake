/*
 * game_logic.h
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */

#ifndef SRC_GAME_LOGIC_H_
#define SRC_GAME_LOGIC_H_

#include "kijelzo.h"

uint8_t choice;
uint8_t iter;

void FoodSegment_Place();


/* ################################################################## */


/* Defining the state machine that controls the direction bit*/
typedef enum {RIGHT_STATE, UP_STATE, DOWN_STATE, LEFT_STATE} DirectionState;

typedef enum {RIGHT_TURN, LEFT_TURN } TurnDirection;


/* state machine, that controls the movement of the snake */
typedef struct Direction_StateMachine_Placeholder
{
	uint8_t head; /* The current segments number, that is the head of the snake */
	_Bool input_recieved; /* true, if a button was pushed in this cycle, used to prevent multiple inputs in one cycle */


	_Bool down_or_left; /* the current direction, true if the snake is going down or left atm */
	DirectionState current_state; /* inner state of the state machine */

	/* function that calculates the direction for the next cycle */
	void (*Snake_TurnDirection)(struct Direction_StateMachine_Placeholder* this, TurnDirection turn);



}Direction_StateMachine_Type;

Direction_StateMachine_Type current_direction;






/* MUST BE CALLED AFTER CALCULATING THE NEW DIRECTION WITH THE STATE MACHINE
 * calculates the next state of the display */










/* ################################################################## */







#endif /* SRC_GAME_LOGIC_H_ */
