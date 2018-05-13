/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __OBSTACLES__
#define __OBSTACLES__

#include "boundingBox.h"

typedef struct obstacle{
	int id;
	int hitpoint;
	float x, y;
	BoundingBox * boundingBoxes;
	struct obstacle * next;
} Obstacle, * ObstacleList;

/* Add an obstacle */
void addObstacle(ObstacleList * list, float x, float y);

/* Remove an obstacles from the level */
void removeObstacle(ObstacleList * list, int id);

/* Print the position of the obstacle in parameter */
void printObstacles(ObstacleList list);

#endif