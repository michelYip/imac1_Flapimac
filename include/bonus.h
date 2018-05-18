/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __BONUS__
#define __BONUS__

#include "boundingBox.h"
#include "enumType.h"
#include "unit.h"

typedef struct bonus{
	int id;
	float x, y;
	bonusType type;
	BoundingBox * boundingBoxes;
	struct bonus * next;
} Bonus, * BonusList;

/* Add a bonus */
void addBonus(BonusList * list, float x, float y);

/* Print the list of Bonus in the level */
void printBonus(BonusList list);

/* Remove a bonus */ 
void removeBonus(BonusList * list, int id);

/* Apply a bonus to the player */
void applyBonus(Bonus * bonus, Unit * player);

#endif