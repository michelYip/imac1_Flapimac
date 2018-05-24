/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __LEVEL__
#define __LEVEL__

#include "unit.h"
#include "projectile.h"
#include "obstacle.h"
#include "bonus.h"
#include "barrier.h"

typedef struct level{
	int height;
	int width;
	int score;
	Unit * player;
	Unit * enemies;
	Obstacle * obstacles;
	Bonus * bonuses;
	Projectile * projectiles;
	Terminal * terminal;
}Level;

/* Load a level from a PPM File */
Level * loadLevel(const char * levelName);

/* Print the level parameter */
void printLevel(Level level);

/* Add score to the current score */
void addScore(Level * level, int score);

/* Substract score to the current score */
void subScore(Level * level, int score);

/* Automatic horizontal scroll */
void scrollLevel(Level * level);

/* Free from memory elements that are not in the screen */
void freeOutOfScreenElements(Level * level);

/* Check the boss position */
int checkBossPosition(Level * level);

/* Free from memory the current level */
void freeLevel(Level * level);

#endif