/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/unit.h"

static int unitID = 0;

/* Create a unit */
void addUnit(UnitList * list, unitType type, fireType fire, float x, float y){
	Unit * newUnit;
	if ((newUnit = malloc(sizeof(Unit))) == NULL){
		fprintf(stderr,"error while allocating memory for addUnit\n");
		exit(EXIT_FAILURE);
	}
	newUnit -> id = unitID++;
	newUnit -> type = type;
	newUnit -> fire = fire;
	newUnit -> x = x;
	newUnit -> y = y;
	newUnit -> x_velocity = SCROLLSPEED;
	newUnit -> y_velocity = 0;
	newUnit -> boundingBoxes = initBoundingBox(x - UNIT_SIZE/2,
										 	y - UNIT_SIZE/2, 
										 	x + UNIT_SIZE/2, 
										 	y + UNIT_SIZE/2);
	if (type == PLAYER){
		newUnit -> hitpoint = HERO_HP;
	} else if (type == ENEMY) {
		newUnit -> hitpoint = ENEMY_HP;
	}
	if (list != NULL){
		newUnit -> next = (*list);	
	} else {
		newUnit -> next = NULL;
	}
	(*list) = newUnit;
}

/* Remove a unit */
void removeUnit(UnitList * list, int id){
	Unit * tmp = *list;
	Unit * prev;
	if (tmp == NULL){
		return;
	}
	if (tmp != NULL && tmp->id == id){
		(*list) = (*list)->next;
		free(tmp);
		return;
	}
	prev = tmp;
	while(tmp != NULL && tmp->id != id){
		prev = tmp;
		tmp = tmp -> next;
	}
	if (tmp == NULL){
		return;
	}
	prev->next = tmp->next;
	free(tmp);
	return;
}

/* Print the position of the unit in parameter */
void printUnitPosition(Unit unit){
	printf("id : %d, x : %f, y : %f\n", unit.id, unit.x, unit.y);
}