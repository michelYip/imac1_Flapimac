/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __BARRIER__
#define __BARRIER__

#include "boundingBox.h"

typedef struct barrier{
	float x, y;
	BoundingBox * boundingBox;
}Barrier;

typedef struct terminal{
	float x, y;
	int state;
	Barrier * upperBarrier;
	Barrier * lowerBarrier;
	BoundingBox * boundingBox;
}Terminal;

/* Initialize the terminal in the level */
Terminal * initTerminal(float levelWidth, float levelHeight, float x, float y);

/* Initalize a barrier */
Barrier * initBarrier(float x, float y);

/* Return the state of the terminal */
int getState(Terminal * terminal);

/* Open the barrier at the end of the level */
void openBarrier(Terminal * terminal);

#endif