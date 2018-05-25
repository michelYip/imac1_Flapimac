/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __UNIT__
#define __UNIT__

#include "boundingBox.h"
#include "enumType.h"

typedef struct unit{
	int id;
	int hitpoint;
	int max_health;
	float x, y;
	float x_velocity, y_velocity;
	int shotTime;
	int fire;
	behavior behavior;
	BoundingBox * boundingBoxes;
	unitType type;
	struct unit * next;
} Unit, * UnitList;

/* Create a unit */
void addUnit(UnitList * list, unitType type, int fire, float x, float y);

/* Remove a unit */
void removeUnit(UnitList * list, int id);

/* Print the position of the unit in parameter */
void printUnitPosition(Unit unit);

/* Remove all enemies */
void freeAllEnemies(UnitList * unit);

#endif