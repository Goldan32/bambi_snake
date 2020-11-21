/*
 * game_logic.h
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */

#ifndef SRC_GAME_LOGIC_H_
#define SRC_GAME_LOGIC_H_

#include "kijelzo.h"

/* ====================== TYPEDEFS/ENUMS ============================= */

/* The states of the direction state machine */
/* Defining the state machine that controls the direction bit */
typedef enum {RIGHT_STATE, UP_STATE, DOWN_STATE, LEFT_STATE} DirectionState;


/* Turn enumeration of the directions the snake can turn to. Including going forward */
typedef enum {RIGHT_TURN, LEFT_TURN, FORWARD_TURN} TurnDirection;


/* Defining the type needed for the state machine that controls the direction bit. Acts like a singleton structure */
typedef struct Direction_StateMachine_Placeholder
{
	_Bool down_or_left; /* the current direction, true if the snake is going down or left at the moment */

	DirectionState current_state; /* inner state of the state machine */

	/* function that calculates the direction for the next cycle */
	void (*Snake_TurnDirection)(struct Direction_StateMachine_Placeholder* this, TurnDirection turn);

}Direction_StateMachine_Type;


/* Structure to store the head, tail, and length of the linked list, that contains the segments of the snake */
typedef struct
{
	uint8_t head;
	uint8_t tail;
	uint8_t length;
}Snake_HeadAndTail;


/* =================================================================== */

/* ========================= GLOBALS ================================= */

Snake_HeadAndTail SnakeEndings;


/* Instantiation of the direction state machine. With this variable, every function can access the direction bit (down_or_left) */
Direction_StateMachine_Type current_direction;


/* contains the number of the segment, that preceds the current element of this array in the snake
 * elements can be 0...NUM_OF_SEGMENTS-1, if the value is NUM_OF_SEGMENTS, or greater than the value is undefined */
uint8_t Snake_BackwardLinkedList[NUM_OF_SEGMENTS];


/* =================================================================== */

/* ========================= FUNCTIONS =============================== */


/* Turns a random NOTHING segment into FOOD segment. Called, when the player eats the previously placed food. */
void FoodSegment_Place();


/* MUST BE CALLED AFTER CALCULATING THE NEW DIRECTION WITH THE STATE MACHINE
 * Calculates the next state of the display */
void Snake_TurnLinkedList(TurnDirection turn);


/* Modifies the values of the array, that contains whether a segment is FOOD, SNAKE, or NOTHING, according to the linked list. */
void LinkedList_ToDraw(segment_status* segments);


/* Takes the next turn direction as arguement, and calculates the next state of the display, and the direction bit */
void Snake_CalculateNextState(TurnDirection turn);


/* Sets the global variables to their starting value. Called once in main before the infinite loop. */
void Snake_StartSetup(void);


/* The function that handles the game after the snake bites into itself. */
void EndOfGame_Function(void);


/* =================================================================== */

#endif /* SRC_GAME_LOGIC_H_ */
