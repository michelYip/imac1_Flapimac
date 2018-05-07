/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __ELEMENT__
#define __ELEMENT__

#include "boundingBox.h"

#define PROJECTILE_DMG 4
#define PROJECTILE_VELOCITY 6
#define PROJECTILE_SIZE 20
#define HERO_HP 10
#define HERO_ACCEL 0.1
#define ENEMY_HP 6
#define ENEMY_ACCEL 0.05
#define UNIT_SIZE 40
#define OBSTACLE_HP 15
#define OBSTACLE_SIZE 40

static int unitID = 0;
static int projectileID = 0;

typedef enum {
	PLAYER,
	ENEMY,
	BOSS
} unitType;

typedef enum {
	BULLET,
	MISSILE,
	BOMB
} fireType;

typedef struct projectile{
	int id;
	int damage;
	float x, y;
	float velocity;
	unitType master;
	float orientation;
	BoundingBox * boundingBoxes;
	struct projectile * next;
} Projectile, * ProjectileList;

typedef struct unit{
	int id;
	int hitpoint;
	float x, y;
	float x_velocity, y_velocity;
	fireType fire;
	BoundingBox * boundingBoxes;
	unitType type;
	struct unit * next;
} Unit, * UnitList;

typedef struct obstacle{
	int hitpoint;
	float x, y;
	BoundingBox * boundingBoxes;
	struct obstacle * next;
} Obstacle, * ObstacleList;

/* Add a projectile for a unit list of projectile */
void addProjectile(ProjectileList list, Unit unit);

/* Remove a projectile from the unit list of projectile */ 
void removeProjectile(ProjectileList projectiles, int id);

/* Create a unit */
void addUnit(UnitList * list, unitType type, fireType fire, float x, float y);

/* Remove a unit */
void removeUnit(UnitList * list, int id);

/* Print the position of the unit in parameter */
void printUnitPosition(Unit unit);

/* Add an obstacle */
void addObstacle(ObstacleList * list, float x, float y);

/* Print the position of the obstacle in parameter */
void printObstacles(ObstacleList list);

#endif