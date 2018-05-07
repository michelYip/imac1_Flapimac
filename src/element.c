/* @uthor : Nathanael ROVERE & Michel YIP */
#include "../include/element.h"

/* Add a projectile for a unit list of projectile */
void addProjectile(Unit * unit){
	Projectile * newP;
	if ((newP = malloc(sizeof(Projectile))) == NULL){
		fprintf(stderr, "error while allocating memory for addProjectile\n");
		exit(EXIT_FAILURE);
	}
	newP -> id = projectileID ++;
	newP -> damage = PROJECTILE_DMG;
	newP -> x = unit->x;
	newP -> y = unit->y;
	newP -> master = unit ->type;
	newP -> speed  = PROJECTILE_SPEED;
	newP -> boundingBoxes = initBoundingBox(unit->x - PROJECTILE_SIZE/2,
										 unit->y - PROJECTILE_SIZE/2, 
										 unit->x + PROJECTILE_SIZE/2, 
										 unit->y + PROJECTILE_SIZE/2);
	if (unit -> projectiles != NULL)
		newP -> next = unit -> projectiles;	
	else
		newP -> next = NULL;
	unit -> projectiles = newP;
}

/* Remove a projectile from the unit list of projectile */
void removeProjectile(Unit * unit, int id){
	Projectile * tmp = unit -> projectiles;
	Projectile * prev;
	if (tmp != NULL && tmp->id == id){
		unit -> projectiles = unit -> projectiles -> next;
		free(tmp);
		return;
	}
	prev = tmp;
	while (tmp->next != NULL && tmp->id == id){
		prev = tmp;
		tmp = tmp -> next;
	}
	if (tmp -> next == NULL && tmp -> id != id){
		printf("Projectile was not in ProjectileList !\n");
		return;
	}
	else if (tmp -> next == NULL && tmp->id == id)
		free(tmp);
	else{
		prev->next = tmp->next;
		free(tmp);
	}
	return;

}

/* Create a unit */
void addUnit(UnitList * list, unitType type, fireType fire, float x, float y){
	Unit * newUnit;
	if ((newUnit = malloc(sizeof(Unit))) == NULL){
		fprintf(stderr,"error while allocating memory for addUnit\n");
		exit(EXIT_FAILURE);
	}
	newUnit -> id = unitID++;
	newUnit -> type = type;
	newUnit -> fire = fire;
	newUnit -> x = x;
	newUnit -> y = y;
	newUnit -> projectiles = NULL;
	newUnit -> boundingBoxes = initBoundingBox(x - UNIT_SIZE/2,
										 	y - UNIT_SIZE/2, 
										 	x + UNIT_SIZE/2, 
										 	y + UNIT_SIZE/2);
	if (type == PLAYER){
		newUnit -> hitpoint = HERO_HP;
		newUnit -> maxSpeed = HERO_MAXSPEED;
		newUnit -> acceleration = HERO_ACCEL;
	} else if (type == ENEMY) {
		newUnit -> hitpoint = ENEMY_HP;
		newUnit -> maxSpeed = ENEMY_MAXSPEED;
		newUnit -> acceleration = ENEMY_ACCEL;
	}
	if ((*list) != NULL)
		newUnit -> next = (*list);	
	else
		newUnit -> next = NULL;
	(*list) = newUnit;
}

/* Remove a unit */
void removeUnit(UnitList * list, int id){

}

/* Print the position of the unit in parameter */
void printUnitPosition(Unit unit){
	printf("id : %d, x : %f, y : %f\n", unit.id, unit.x, unit.y);
}

/* Add an obstacle */
void addObstacle(ObstacleList * list, float x, float y){
	Obstacle * newObstacle;
	if ((newObstacle = malloc(sizeof(Obstacle))) == NULL){
		fprintf(stderr, "error while allocating memory for addObstacle\n");
		exit(EXIT_FAILURE);
	}
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

/* Print the position of the obstacle in parameter */
void printObstacles(ObstacleList list){
	while (list != NULL){
		printf("x : %f, y : %f\n", list->x, list->y);
		list = list->next;
	}
}