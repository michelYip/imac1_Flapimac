/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __ELEMENT__
#define __ELEMENT__

#include "boundingBox.h"

typedef struct element{
	int hitpoint;
	float speed;
	float acceleration;
	BoundingBox * boundingBoxes;
}Element, * ElementList;

#endif