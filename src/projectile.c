/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/projectile.h"

static int projectileID = 0;

/* Add a projectile for a unit list of projectile */
void addProjectile(ProjectileList * projectiles, Unit unit, int orientation){
	Projectile * newP;
	if ((newP = malloc(sizeof(Projectile))) == NULL){
		fprintf(stderr, "error while allocating memory for addProjectile\n");
		exit(EXIT_FAILURE);
	}
	newP -> id = projectileID++;
	newP -> damage = PROJECTILE_DMG;
	newP -> x = unit.x;
	newP -> y = unit.y;
	newP -> velocity = (unit.type == PLAYER)? PROJECTILE_VELOCITY + unit.x_velocity : PROJECTILE_VELOCITY;
	newP -> idTexture = (unit.type == PLAYER)? ID_PROJECTILE_PLAYER : (rand()%NB_PROJECTILES_ENEMY)+ID_PROJECTILE_ENEMY;
	newP -> master = unit.type;
	newP -> orientation = (unit.type == PLAYER)? 0 + orientation : 180 + orientation;
	newP -> orientation *= M_PI / 180;
	newP -> boundingBoxes = initBoundingBox(unit.x - PROJECTILE_SIZE/2,
										 unit.y - PROJECTILE_SIZE/2, 
										 unit.x + PROJECTILE_SIZE/2, 
										 unit.y + PROJECTILE_SIZE/2);
	if (projectiles != NULL){
		newP -> next = *projectiles;
	}
	else{
		newP -> next = NULL;
	}
	* projectiles = newP;
}

/* Print the list of projectiles in the level */
void printProjectiles(ProjectileList p){
	printf("projectiles : ");
	while (p != NULL){
		printf("%d -> ",p->id);
		p = p->next;
	}
	printf("NULL\n");

}

/* Remove a projectile from the unit list of projectile */
void removeProjectile(ProjectileList * projectiles, int id){
	Projectile * tmp = *projectiles;
	Projectile * prev;
	if (tmp == NULL){
		return;
	}
	if (tmp != NULL && tmp->id == id){
		(*projectiles) = (*projectiles) -> next;
		free(tmp);
		return;
	}
	prev = tmp;
	while (tmp != NULL && tmp->id != id){
		prev = tmp;
		tmp = tmp -> next;
	}
	if (tmp == NULL){
		return;
	}
	prev -> next = tmp -> next;
	free(tmp);
	return;
}

/* Update the position of the projectile */
void updateProjectilesPosition(ProjectileList * projectiles){
	Projectile * tmp = * projectiles;
	while (tmp != NULL){
		tmp->x += cos(tmp->orientation)*tmp->velocity;
		tmp->y += sin(tmp->orientation)*tmp->velocity;		
		moveBoundingBoxes(&(tmp->boundingBoxes), 
						cos(tmp->orientation)*tmp->velocity,
						sin(tmp->orientation)*tmp->velocity);
		tmp = tmp->next;
	}
}


/* Remove all the projectiles */
void freeAllProjectiles(ProjectileList * list){
	while ((*list) != NULL){
		removeProjectile(list, (*list)->id);
	}
}