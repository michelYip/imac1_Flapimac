/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __LEVEL__
#define __LEVEL__

#include "unit.h"
#include "projectile.h"
#include "obstacle.h"

typedef struct level{
	int height;
	int width;
	Unit * player;
	Unit * enemies;
	Obstacle * obstacles;
	Projectile * projectiles;
}Level;

/* Load a level from a PPM File */
Level * loadLevel(const char * levelName);

/* Print the level parameter */
void printLevel(Level level);

/* Update the level current status */
void updateLevel(Level * level);

/* TODO */
/* Check the collision for every object in the level */
void checkCollisions(Level * level);

/* Check the collision for the player with every object in the level */
void checkPlayerCollision(UnitList * unit, Level * level);

/* Check the collision for a projectile with every object in the level */
void checkProjectilesCollision(ProjectileList * projectiles, Level * level);

/* Reduce a unit's hitpoint by the damage dealt in parameter */
int damageUnit(UnitList * unit, int damageDealt);

/* Push a unit away from the collision */
void knockbackUnit(Unit * unit, float x, float y, float knockbackDistance);
#endif