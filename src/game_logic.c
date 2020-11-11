/*
 * game_logic.c
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */


#include "game_logic.h"
#include "kijelzo.h"
#include "stdlib.h"

/*
 *Bad solution here
 */

void FoodSegment_Place(){
	bool full = true;
	while(iter==NUM_OF_SEGMENTS-1){
		if(SegmentRoles[iter]==NOTHING){
			full=false;
		}
		else
			iter=iter+1;
	}
	if(!full){
	choice = rand() % NUM_OF_SEGMENTS;
	while(!(SegmentRoles[choice]==NOTHING))
	{
		choice = rand() % NUM_OF_SEGMENTS;
	}
	SegmentRoles[choice] = FOOD;
	}
	else;

}


/* -------------------------------------------------------------- */


void Snake_TurnDirection(Direction_StateMachine_Type* this, TurnDirection turn)
{
	if (this->input_recieved) return; /* If we already calculated the next state, the function returns without modifications to state */
	this->input_recieved = true; /* if we get here, this is the first call instance in this cycle */


	DirectionState next_state;

	if (turn == RIGHT_TURN)
	{
		switch (this->current_state)
		{
			case RIGHT_STATE: next_state = DOWN_STATE; break;
			case UP_STATE: next_state = RIGHT_STATE; break;
			case DOWN_STATE: next_state = LEFT_STATE; break;
			case LEFT_STATE: next_state = UP_STATE; break;
		}
	}

	if (turn == LEFT_TURN)
	{
		switch (this->current_state)
		{
			case RIGHT_STATE: next_state = UP_STATE; break;
			case UP_STATE: next_state = LEFT_STATE; break;
			case DOWN_STATE: next_state = RIGHT_STATE; break;
			case LEFT_STATE: next_state = DOWN_STATE; break;
		}
	}

	this->current_state = next_state;

	this->down_or_left = next_state == (LEFT_STATE || DOWN_STATE) ? true : false;

}






/* -------------------------------------------------------------- */
