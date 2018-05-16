/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __IA__
#define __IA__

#include "unit.h"
#include "action.h"

/* Manage enemies behavior */
void updateEnemies(Level * level);

/* Update the position of an enemy with UPANDDOWN behavior */
void updateUpAndDown(Unit * enemy);

/* Update the position of an enemy with FOLLOW behavior */
void updateFollow(Unit * enemy, Unit * player);

#endif