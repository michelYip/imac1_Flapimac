/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __LEVEL__
#define __LEVEL__

#include "element.h"

typedef struct level{
	int height;
	int width;
	Unit * player;
	Unit * enemies;
	Obstacle * obstacles;
}Level;

/* Load a level from a PPM File */
Level * loadLevel(const char * levelName);

/* Print the level parameter */
void printLevel(Level level);



#endif