/*
 * game_logic.c
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */


#include "game_logic.h"
#include "kijelzo.h"
#include "stdlib.h"

/* ----------- macros to help initialize an array -------------------- */
#define NUM_OF_SEGMENTS_2X     NUM_OF_SEGMENTS,  NUM_OF_SEGMENTS
#define NUM_OF_SEGMENTS_4X     NUM_OF_SEGMENTS_2X,  NUM_OF_SEGMENTS_2X
#define NUM_OF_SEGMENTS_8X     NUM_OF_SEGMENTS_4X,  NUM_OF_SEGMENTS_4X
#define NUM_OF_SEGMENTS_16X    NUM_OF_SEGMENTS_8X,  NUM_OF_SEGMENTS_8X
#define NUM_OF_SEGMENTS_32X    NUM_OF_SEGMENTS_16X, NUM_OF_SEGMENTS_16X
/* ------------------------------------------------------------------- */




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


Direction_StateMachine_Type current_direction = { false, RIGHT_STATE, (*Snake_TurnDirection)};

/* every element is set to an undefined value at first */
uint8_t Snake_LinkedList[NUM_OF_SEGMENTS] = {NUM_OF_SEGMENTS_32X,NUM_OF_SEGMENTS_4X, NUM_OF_SEGMENTS};


Snake_HeadAndTail SnakeEndings = {0,0};



void Snake_TurnLinkedList(TurnDirection turn)
{
	uint8_t i;

	if (current_direction.down_or_left)
	{
		if(turn == RIGHT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].right_one] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].right_one;
		}
		if(turn == LEFT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].left_one] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].left_one;
		}
	}
	if (!current_direction.down_or_left)
	{
		if(turn == RIGHT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].right_zero] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].right_zero;
		}
		if(turn == LEFT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].left_zero] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].left_zero;
		}
	}

	for (i=SnakeEndings.head;i!=Snake_LinkedList[SnakeEndings.tail];i=Snake_LinkedList[i]);
	Snake_LinkedList[i] = NUM_OF_SEGMENTS;
	SnakeEndings.tail = i;
}



/* -------------------------------------------------------------- */
