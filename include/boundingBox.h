/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __BOUNDING_BOX__
#define __BOUNDING_BOX__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct BoundingBox {
	float x1, y1;
	float x2, y2;
	struct BoundingBox * next;
} BoundingBox, * BoundingBoxList;

/* Initialize a bounding box with the parameter coordinate */
BoundingBoxList initBoundingBox(float x1, float y1, float x2, float y2);

/* Add a bounding box to the list of boxes */
void addBoundingBox(BoundingBoxList * boxes, float x1, float y1, float x2, float y2);

/* Draw a simple square */
void drawSquare();

/* Draw the bounding boxes in parameter */
void drawBoundingBoxes(BoundingBoxList boxes);

/* Check if two bounding boxes are intersecting with each other */
int intersect(BoundingBoxList a, BoundingBoxList b);

/* Move a boundingBox */
void moveBoundingBoxes(BoundingBox * boxes, float x, float y);

#endif