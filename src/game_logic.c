/*
 * game_logic.c
 *
 *  Created on: 8 Nov 2020
 *      Author: koren
 */


#include "game_logic.h"
#include "kijelzo.h"

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
