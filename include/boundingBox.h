/* @uthor : Nathanael ROVERE & Michel YIP */

#ifndef __BOUNDING_BOX__
#define __BOUNDING_BOX__

typedef struct boundingBox {
	float x1, y1;
	float x2, y2;
	struct boundingBox * next;
} boundingBox, * boxList;



#endif