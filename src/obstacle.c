/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/obstacle.h"

static int obstacleID = 0;

/* Add an obstacle */
void addObstacle(ObstacleList * list, float x, float y){
	Obstacle * newObstacle;
	if ((newObstacle = malloc(sizeof(Obstacle))) == NULL){
		fprintf(stderr, "error while allocating memory for addObstacle\n");
		exit(EXIT_FAILURE);
	}
	newObstacle -> id = obstacleID++;
	newObstacle -> hitpoint = OBSTACLE_HP;
	newObstacle -> x = x;
	newObstacle -> y = y;
	newObstacle -> boundingBoxes = initBoundingBox(x - OBSTACLE_SIZE/2,
										 		y - OBSTACLE_SIZE/2, 
											 	x + OBSTACLE_SIZE/2, 
											 	y + OBSTACLE_SIZE/2);
	if ((*list) != NULL)
		newObstacle -> next = (*list);	
	else
		newObstacle -> next = NULL;
	(*list) = newObstacle;
}

/* Remove an obstacles from the level */
void removeObstacle(ObstacleList * list, int id){
	Obstacle * tmp = *list;
	Obstacle * prev;
	if (tmp == NULL){
		return;
	}
	if (tmp != NULL && tmp->id == id){
		(*list) = (*list)->next;
		free(tmp);
		return;
	}
	prev = tmp;
	while(tmp != NULL && tmp->id != id){
		prev = tmp;
		tmp = tmp -> next;
	}
	if (tmp == NULL){
		return;
	}
	prev->next = tmp->next;
	free(tmp);
	return;
}

/* Print the position of the obstacle in parameter */
void printObstacles(ObstacleList list){
	while (list != NULL){
		printf("x : %f, y : %f\n", list->x, list->y);
		list = list->next;
	}
}