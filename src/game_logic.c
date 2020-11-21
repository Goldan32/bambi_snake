
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
	free(nothing_segment_array);

}


/* First parameter is the instance of the state machine. Second parameter is where the snake is turning. */
void Snake_TurnDirection(Direction_StateMachine_Type* this, TurnDirection turn)
{

	DirectionState next_state;

	/* State machine coded in C */
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

	/* The inner state defines the direction bit */
	this->down_or_left = ((next_state == LEFT_STATE ) || (next_state == DOWN_STATE))? true : false;
}


/* Defining the starting values of the direction state machine */
Direction_StateMachine_Type current_direction = { false, RIGHT_STATE, (*Snake_TurnDirection)};


/* Every element is set to an undefined value at first */
uint8_t Snake_LinkedList[NUM_OF_SEGMENTS] = {NUM_OF_SEGMENTS_32X,NUM_OF_SEGMENTS_4X, NUM_OF_SEGMENTS};


/* Head and tail is segment 0, length starts at 1 */
Snake_HeadAndTail SnakeEndings = {0,0,1};




/* For every six possible turn, we determine the next state of the display */
void Snake_TurnLinkedList(TurnDirection turn)
{
	uint8_t i,k=0; /* k: counter, i goes through the linked list */

	if (current_direction.down_or_left) /* Checking the direction bit */
	{
		if(turn == RIGHT_TURN) /* Checking what the input direction was */
		{

			/* SnakeEndings.head contains the number of the segment, that is currently the head of the snake.
			 *
			 * SegmentNeighbors[SnakeEndings.head].right_one contains the number of the segment, that is the right
			 * neighbor of the head, when the direction bit is one.
			 *
			 * The full left value is accessing that segment in the linked list, and setting its value to the current head,
			 * meaning, from now on, it is the first segment in the linked list, as it "points" to the current head */
			Snake_LinkedList[SegmentNeighbors[SnakeEndings.head].right_one] = SnakeEndings.head;

			/* Making the previously selected segment, the new head */
			SnakeEndings.head = SegmentNeighbors[SnakeEndings.head].right_one;

			/* Changing, the direction state machine through its turn function */
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

	/* If the new head was previously food, then we eat it, and don't have to turn off the tail segment. */
	if (SegmentRoles[SnakeEndings.head] == FOOD)
	{
		SegmentRoles[SnakeEndings.head] = SNAKE;
		SnakeEndings.length++;
		FoodSegment_Place();
		return;
	}
	else /* If the next head was not food. */
	{

		/* Finding the tail of the snake with the linked list. */
		for (i=SnakeEndings.head;Snake_LinkedList[i]!=SnakeEndings.tail;i=Snake_LinkedList[i])
		{
			/* Snake can't be longer, than how many segments there are.
			 * If this counter moves past NUM_OF_SEGMENTS, the snake bit into itself, causing an endless loop */
			k++;
			if (k>NUM_OF_SEGMENTS) EndOfGame_Function();
		}
		/* After the for cycle, i is the number of the segment that points to the tail in the linked list. */

		SegmentRoles[Snake_LinkedList[i]] = NOTHING; /* The previous tail is set to NOTHING */
		Snake_LinkedList[i] = NUM_OF_SEGMENTS; /* Its value in the linked list is set to undefined */
		SnakeEndings.tail = i; /* The new tail is set in the global variable */

		/* When the snake bit into its previous tail (no infinite loop from the for cycle) */
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
		if (segments[i] == FOOD) continue; /* We don't want to change where the food is */

		/* iterate through every segment, if its part of the snake (it points to something in the linked list)
		 * then we set it to SNAKE in the argument array (The global variable, SegmentRoles most of the time) */
		if (Snake_LinkedList[i]<NUM_OF_SEGMENTS)
		{
			segments[i] = SNAKE;
		}
		else
		{
			segments[i] = NOTHING;
		}
	}

	/* The tail doesn't point to anything but is part of the snake */
	segments[SnakeEndings.tail] = SNAKE;

}


/* Calls the above 2 functions with correct parameters */
void Snake_CalculateNextState(TurnDirection turn)
{
	Snake_TurnLinkedList(turn);
	LinkedList_ToDraw(SegmentRoles);
}

void Snake_StartSetup(void)
{
	uint8_t i;
	SegmentRoles[0] = SNAKE; /* Starting segment specified in the homework */
	for (i=1;i<NUM_OF_SEGMENTS;i++) /* The rest are NOTHING */
		SegmentRoles[i] = NOTHING;


	/* TODO: Koren ha itt vagy, akkor hívd már meg a random foodot lerakú függvényt a kövi sor helyett,
	 * mert Angiéknak ezért dobta vissza, hogy mindig ugyanaz az elsõ kigyulladó szegmens */
	SegmentRoles[9] = FOOD;

	Screen_DrawAllSegments(SegmentRoles);

}

void EndOfGame_Function(void)
{
	Decimalpoints_BlinkFiveTimes();
	/* waiting for reset */

};

