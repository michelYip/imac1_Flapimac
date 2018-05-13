/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __UNIT__
#define __UNIT__

#include "boundingBox.h"
#include "enumType.h"

typedef struct unit{
	int id;
	int hitpoint;
	float x, y;
	float x_velocity, y_velocity;
	fireType fire;
	BoundingBox * boundingBoxes;
	unitType type;
	struct unit * next;
} Unit, * UnitList;

/* Create a unit */
void addUnit(UnitList * list, unitType type, fireType fire, float x, float y);

/* Remove a unit */
void removeUnit(UnitList * list, int id);

/* Print the position of the unit in parameter */
void printUnitPosition(Unit unit);


#endif