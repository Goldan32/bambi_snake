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
/* enumarated type to store the snakes current direction */
typedef enum {LEFT, RIGHT} game_direction;

/* a structure to logically describe the variables used in the game */
typedef struct
{
	uint8_t score;

	game_status status;
	game_direction direction;


}GameControllerStruct;

GameControllerStruct GameController;

void Game_Init();
void FoodSegment_Place();



#endif /* SRC_GAME_LOGIC_H_ */
