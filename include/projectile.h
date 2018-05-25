/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __PROJECTILES__
#define __PROJECTILES__

#include "boundingBox.h"
#include "enumType.h"
#include "unit.h"

typedef struct projectile{
	int id;
	int damage;
	float x, y;
	float velocity;
	int idTexture;
	unitType master;
	float orientation;
	BoundingBox * boundingBoxes;
	struct projectile * next;
} Projectile, * ProjectileList;

/* Add a projectile for a unit list of projectile */
void addProjectile(ProjectileList * list, Unit unit, int orientation);

/* Print the list of projectiles in the level */
void printProjectiles(ProjectileList p);

/* Remove a projectile from the unit list of projectile */ 
void removeProjectile(ProjectileList * projectiles, int id);

/* Update the position of the projectile */
void updateProjectilesPosition(ProjectileList * projectiles);

/* Remove all the projectiles */
void freeAllProjectiles(ProjectileList * list);

#endif