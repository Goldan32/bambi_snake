
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

void Game_Init(){
	GameController.score=1;
	GameController.status=RUNNING;
}

/*
 *Bad solution here
 */
void FoodSegment_Place(){
	uint8_t choice;
	uint8_t iter;
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

	this->down_or_left = ((next_state == LEFT_STATE ) || (next_state == DOWN_STATE))? true : false;

}


Direction_StateMachine_Type current_direction = { false, RIGHT_STATE, (*Snake_TurnDirection)};

/* every element is set to an undefined value at first */
uint8_t Snake_LinkedList[NUM_OF_SEGMENTS] = {NUM_OF_SEGMENTS_32X,NUM_OF_SEGMENTS_4X, NUM_OF_SEGMENTS};


Snake_HeadAndTail SnakeEndings = {0,0,1};



void Snake_TurnLinkedList(TurnDirection turn)
{
	uint8_t i;

	if (current_direction.down_or_left)
	{
		if(turn == RIGHT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].right_one] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].right_one;

			current_direction.Snake_TurnDirection(&current_direction,RIGHT_TURN);
		}
		if(turn == LEFT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].left_one] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].left_one;

			current_direction.Snake_TurnDirection(&current_direction,LEFT_TURN);
		}
		if(turn == FORWARD_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].forward_one] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].forward_one;
		}
	}
	else
	{
		if(turn == RIGHT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].right_zero] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].right_zero;

			current_direction.Snake_TurnDirection(&current_direction,RIGHT_TURN);
		}
		if(turn == LEFT_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].left_zero] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].left_zero;

			current_direction.Snake_TurnDirection(&current_direction,LEFT_TURN);
		}
		if(turn == FORWARD_TURN)
		{
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].forward_zero] = SnakeEndings.head;
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].forward_zero;
		}
	}

	if (SegmentRoles[SnakeEndings.head] == SNAKE)
	{
		/* TODO: Call end of game function */
	}
	if (SegmentRoles[SnakeEndings.head] == FOOD)
	{
		SegmentRoles[SnakeEndings.head] = SNAKE;
		SnakeEndings.length++;
	}
	else
	{
		for (i=SnakeEndings.head;Snake_LinkedList[i]!=SnakeEndings.tail;i=Snake_LinkedList[i]);
		Snake_LinkedList[i] = NUM_OF_SEGMENTS;
		SnakeEndings.tail = i;
	}
}


void LinkedList_ToDraw(segment_status* segments)
{
	uint8_t i;
	for(i=0;i<NUM_OF_SEGMENTS;i++)
	{
		if (segments[i] == FOOD) continue;
		if (Snake_LinkedList[i]<NUM_OF_SEGMENTS)
		{
			segments[i] = SNAKE;
		}
		else
		{
			segments[i] = NOTHING;
		}
	}
	segments[SnakeEndings.tail] = SNAKE;
}


void Snake_CalculateNextState(TurnDirection turn)
{
	Snake_TurnLinkedList(turn);
	LinkedList_ToDraw(SegmentRoles);
	Screen_DrawAllSegments(SegmentRoles);
}

void Snake_StartSetup(void)
{
	uint8_t i;
	SegmentRoles[0] = SNAKE;
	for (i=1;i<NUM_OF_SEGMENTS;i++)
		SegmentRoles[i] = NOTHING;

	SegmentRoles[3] = FOOD;
	SegmentRoles[9] = FOOD;

	Screen_DrawAllSegments(SegmentRoles);

}




/* -------------------------------------------------------------- */
