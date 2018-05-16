/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __PHYSICS__
#define __PHYSICS__

#include "level.h"
#include "render.h"
#include "IA.h"

/* Update the level current status */
void updateElementsPosition(Level * level);

/* Check the collision for every object in the level */
void checkCollisions(Level * level);

/* Check the collision for the player with every object in the level */
void checkPlayerCollision(UnitList * unit, Level * level);

/* Check the collision for a projectile with every object in the level */
void checkProjectilesCollision(ProjectileList * projectiles, Level * level);

/* Reduce a unit's hitpoint by the damage dealt in parameter */
int damageUnit(UnitList * unit, int damageDealt);

/* Reduce an obstacle's hitpoint by the damage dealt in parameter */
int damageObstacle(ObstacleList * obstacle, int damageDealt);

/* Check if the player is immune to damage */
int isImmune(Unit * player);

#endif