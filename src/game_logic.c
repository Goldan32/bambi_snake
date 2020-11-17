/*
 * game_logic.c
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */


#include "game_logic.h"
#include "kijelzo.h"
#include "stdlib.h"


void Game_Init(){
	GameController.score=1;
	GameController.status=RUNNING;
	GameController.direction=RIGHT;
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
