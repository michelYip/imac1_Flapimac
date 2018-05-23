/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/barrier.h"

/* Initialize the terminal in the level */
Terminal * initTerminal(float levelWidth, float levelHeight, float x, float y){
	Terminal * terminal;
	if ((terminal = malloc(sizeof(Terminal))) == NULL){
		fprintf(stderr, "Error while allocating memory for initTerminal\n");
		exit(EXIT_FAILURE);
	}
	terminal -> x = x;
	terminal -> y = y;
	terminal -> state = 0;
	terminal -> upperBarrier = initBarrier(levelWidth*UNIT_SIZE - TERMINAL_SIZE*2, levelHeight*UNIT_SIZE/4);
	terminal -> lowerBarrier = initBarrier(levelWidth*UNIT_SIZE - TERMINAL_SIZE*2, levelHeight*UNIT_SIZE*3/4);
	terminal -> boundingBox = initBoundingBox(x - TERMINAL_SIZE/2,
										 	y - TERMINAL_SIZE/2, 
										 	x + TERMINAL_SIZE/2, 
										 	y + TERMINAL_SIZE/2);
	return terminal;
}

/* Initalize a barrier */
Barrier * initBarrier(float x, float y){
	Barrier * barrier;
	if ((barrier = malloc(sizeof(Barrier))) == NULL){
		fprintf(stderr, "Error while allocating memory for initBarrier\n");
		exit(EXIT_FAILURE);
	}
	barrier->x = x;
	barrier->y = y;
	barrier->boundingBox = initBoundingBox(x - BARRIER_WIDTH/2,
										 	y - BARRIER_HEIGHT/2, 
										 	x + BARRIER_WIDTH/2, 
										 	y + BARRIER_HEIGHT/2);
	return barrier;
}

/* Return the state of the terminal */
int getState(Terminal * terminal){
	return terminal->state;
}

/* Open the barrier at the end of the level */
void openBarrier(Terminal * terminal){
	moveBoundingBoxes(&(terminal->upperBarrier->boundingBox), 0, -1);
	terminal->upperBarrier->y += -2;
	moveBoundingBoxes(&(terminal->lowerBarrier->boundingBox), 0, 1);
	terminal->lowerBarrier->y += 2;
}

void removeTerminal(Terminal * terminal){
	free(terminal->upperBarrier);
	free(terminal->lowerBarrier);
	free(terminal);
}