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

/* Automatic horizontal scroll */
void scrollLevel(Level * level);

/* Free from memory elements that are not in the screen */
void freeOutOfScreenElements(Level * level);

/* Check the boss position */
int checkBossPosition(Level * level);

#endif