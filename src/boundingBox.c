/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/boundingBox.h"

/* Initialize a bounding box with the parameter coordinate */
BoundingBoxList initBoundingBox(float x1, float y1, float x2, float y2){
	BoundingBoxList boxes;
	if ((boxes = malloc(sizeof(BoundingBox))) == NULL){
		fprintf(stderr,"Error : allocating memory of BoundingBox in initBoundingBox()\n");
		exit(EXIT_FAILURE);
	}
	boxes->x1 = x1;
	boxes->y1 = y1;
	boxes->x2 = x2;
	boxes->y2 = y2;
	boxes->next = NULL;

	return boxes;
}

/* Add a bounding box to the list of boxes */
void addBoundingBox(BoundingBoxList * boxes, float x1, float y1, float x2, float y2){
	BoundingBoxList addedBox = initBoundingBox(x1, y1, x2, y2);
	addedBox->next = (*boxes);
	(*boxes) = addedBox;
}

/* Draw a simple square */
void drawSquare(){
	glBegin(GL_LINE_LOOP);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(0.5,-0.5);
		glVertex2f(-.5,-0.5);
	glEnd();
}

/* Draw the bounding boxes in parameter */
void drawBoundingBoxes(BoundingBoxList boxes){
	while (boxes != NULL){
		glPushMatrix();
			glTranslatef((boxes->x1+boxes->x2)/2.0, (boxes->y1+boxes->y2)/2.0, 0);
			glScalef(boxes->x2 - boxes->x1, boxes->y2 - boxes->y1, 0);
			drawSquare();
		glPopMatrix();
		boxes = boxes->next;
	}
}

/* Check if two bounding boxes are intersecting with each other */
int intersect(BoundingBoxList a, BoundingBoxList b){
	float aX, bX, aY, bY, aWidth, bWidth, aHeight, bHeight;
	while (a != NULL){
		while (b != NULL){
			aX = (a->x1+a->x2)/2;
			bX = (b->x1+b->x2)/2;
			aWidth = abs(a->x2 - a->x1);
			bWidth = abs(b->x2 - b->x1);
			aY = (a->y1+a->y2)/2;
			bY = (b->y1+b->y2)/2;
			aHeight = abs(a->y2 - a->y1);
			bHeight = abs(b->y2 - b->y1);
			if (abs(aX - bX) * 2 < (aWidth + bWidth) &&
				abs(aY - bY) * 2 < (aHeight + bHeight)){
				return 1;
			}
			b = b->next;
		}
		a = a->next;
	}
	return 0;
}

/* Move a boundingBox */
void moveBoundingBoxes(BoundingBox * boxes, float x, float y){
	BoundingBox * tmp = boxes;
	while (tmp != NULL){
		tmp->x1 += x;
		tmp->x2 += x;
		tmp->y1 += y;
		tmp->y2 += y;
		tmp = tmp->next;
	}
}