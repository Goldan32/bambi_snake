
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
 * This function makes a dinamic array, where all elements are nothing-rolled segment id-s
 * The function choose a random element, and assigns a "FOOD" role, to that particular segment.
 */
void FoodSegment_Place(){

	uint8_t size=0;
	for(uint8_t i=0;i<NUM_OF_SEGMENTS;i++)
	{
		if(SegmentRoles[i] == NOTHING)
		{
			size=size+1;
		}
	}

	uint8_t *nothing_segment_array = (uint8_t*)malloc(size* sizeof(uint8_t));
	uint8_t p=0;
	for(uint8_t i=0;i<NUM_OF_SEGMENTS;i++)
	{
		if(SegmentRoles[i]== NOTHING)
		{
			nothing_segment_array[p] = i;
			p=p+1;
		}

	}

	uint8_t choice=0;
	choice = rand()% size;
	SegmentRoles[nothing_segment_array[choice]] = FOOD;
	SegmentLCD_Number(nothing_segment_array[choice]);
	free(nothing_segment_array);

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

	if (SegmentRoles[SnakeEndings.head] == FOOD)
	{
		SegmentRoles[SnakeEndings.head] = SNAKE;
		SnakeEndings.length++;
		FoodSegment_Place();
		return;
	}
	else
	{
		for (i=SnakeEndings.head;Snake_LinkedList[i]!=SnakeEndings.tail;i=Snake_LinkedList[i]);
		SegmentRoles[Snake_LinkedList[i]] = NOTHING;
		Snake_LinkedList[i] = NUM_OF_SEGMENTS;
		SnakeEndings.tail = i;

		if (SegmentRoles[SnakeEndings.head] == SNAKE)
			{
				EndOfGame_Function();
				return;
			}
		return;
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
}

void Snake_StartSetup(void)
{
	uint8_t i;
	SegmentRoles[0] = SNAKE;
	for (i=1;i<NUM_OF_SEGMENTS;i++)
		SegmentRoles[i] = NOTHING;

	//SegmentRoles[3] = FOOD;
	SegmentRoles[9] = FOOD;

	Screen_DrawAllSegments(SegmentRoles);

}

void EndOfGame_Function(void)
{
	Decimalpoints_BlinkFiveTimes();
	/* waiting for reset */

};


/* -------------------------------------------------------------- */
