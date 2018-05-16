/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/physics.h"

static Uint32 time = 0;
static int damaged = 0;

/* Update the level current status */
void updateElementsPosition(Level * level){
	if (!isImmune(level->player)){
		damaged = 0;
	}
	if (level->projectiles != NULL){
		updateProjectilesPosition(&(level->projectiles));
	}
	if (level->enemies != NULL){
		updateEnemies(&(level->enemies));
	}
	checkCollisions(level);
}

/* Check the collision for every object in the level */
void checkCollisions(Level * level){
	if (level->player != NULL){
		checkPlayerCollision(&level->player, level);
	}
	if (level->projectiles != NULL){
		checkProjectilesCollision(&level->projectiles, level);
	}
}

/* Check the collision for the player with every object in the level */
void checkPlayerCollision(UnitList * unit, Level * level){
	Unit * enemies;
	Obstacle * obstacles;
	Unit * player = *unit;
	while (player != NULL){
		enemies = level->enemies;
		obstacles = level->obstacles;
		while (enemies != NULL){
			/*if (player == NULL){
				player = *unit;
				continue;
			}*/
			if (intersect(player->boundingBoxes, enemies->boundingBoxes)){
				if (!isImmune(player)){
					if(damageUnit(&player, COLLISION_DAMAGE)){
						removeUnit(unit, player->id);
						player = *unit;
						if (player == NULL)
							return;
					} else {
						knockbackUnit(player, enemies->y);
					}
				}
				removeUnit(&(level->enemies), enemies->id);
			}
			enemies = enemies->next;
		}
		while (obstacles != NULL){
			/*if (player == NULL){
				player = *unit;
				continue;
			}*/
			if (intersect(player->boundingBoxes, obstacles->boundingBoxes)){
				if (!isImmune(player)){
					if(damageUnit(&player, COLLISION_DAMAGE)){
						removeUnit(unit, player->id);
						player = *unit;
						if (player == NULL)
							return;
					} else {
						knockbackUnit(player, obstacles->y);
					}
				}
				removeObstacle(&(level->obstacles), obstacles->id);
			}
			obstacles = obstacles->next;
		}
		if (player == NULL){
			player = *unit;
			continue;
		}
		player = player->next;
	}
}

/* Check the collision for a projectile with every object in the level */
void checkProjectilesCollision(ProjectileList * projectiles, Level * level){
	Unit * player;
	Unit * enemies;
	Obstacle * obstacles;
	Projectile * tmp = *projectiles;
	while (tmp != NULL){
		player = level->player;
		enemies = level->enemies;
		obstacles = level->obstacles;
		while (player != NULL){
			/*if (tmp == NULL){
				tmp = *projectiles;
				continue;
			}*/
			if (tmp->master == ENEMY && intersect(tmp->boundingBoxes, player->boundingBoxes)){
				if (!isImmune(player)){
					if(damageUnit(&player, tmp->damage)){
						printf("player is destroyed !\n");
						removeUnit(&(level->player), player->id);
					}
				}
				removeProjectile(projectiles, tmp->id);
			}
			if (player == NULL){
				player = level->player;
			} else {
				player = player->next;
			}
		}
		while (enemies != NULL){
			/*if (tmp == NULL){
				tmp = *projectiles;
				continue;
			}*/
			if (tmp->master == PLAYER && intersect(tmp->boundingBoxes, enemies->boundingBoxes)){
				if(damageUnit(&enemies, tmp->damage)){
					printf("enemy is destroyed !\n");
					removeUnit(&(level->enemies), enemies->id);
				}
				removeProjectile(projectiles, tmp->id);
			}
			if (enemies == NULL){
				enemies = level -> enemies;
			} else {
				enemies = enemies->next;
			}
		}
		while (obstacles != NULL){
			/*if (tmp == NULL){
				tmp = *projectiles;
				continue;
			}*/
			if (intersect(tmp->boundingBoxes, obstacles->boundingBoxes)){
				if (damageObstacle(&obstacles, tmp->damage)){
					printf("obstacle is destroyed !\n");
					removeObstacle(&(level->obstacles), obstacles->id);
				}
				removeProjectile(projectiles, tmp->id);
			}
			if (obstacles == NULL){
				obstacles = level->obstacles;
			} else {
				obstacles = obstacles->next;
			}
		}
		if (tmp == NULL){
			tmp = *projectiles;
			continue;
		}
		tmp = tmp->next;
	}		
}

/* Reduce a unit's hitpoint by the damage dealt in parameter */
int damageUnit(UnitList * unit, int damageDealt){
	damaged = 1;
	(*unit)->hitpoint -= damageDealt;
	if ((*unit)->type == PLAYER){
		time = SDL_GetTicks();
	}
	if ((*unit)->hitpoint <= 0){
		return 1;
	}
	return 0;
}

/* Reduce an obstacle's hitpoint by the damage dealt in parameter */
int damageObstacle(ObstacleList * obstacle, int damageDealt){
	(*obstacle)->hitpoint -= damageDealt;
	if ((*obstacle)->hitpoint <= 0){
		return 1;
	}
	return 0;
}

/* Push a unit away from the collision */
void knockbackUnit(Unit * unit, float y){
	moveBoundingBoxes(&(unit->boundingBoxes), 0, -(y - unit->y) * KNOCKBACK); 
	unit->y += -(y - unit->y) * KNOCKBACK;
}

/* Check if the player is immune to damage */
int isImmune(Unit * player){
	if (SDL_GetTicks() < time + IMMUNE_TIME && damaged){
		if (SDL_GetTicks() < time + BLINK_DURATION){
			isHurt(player);
		} else if (SDL_GetTicks() > time + 2*BLINK_DURATION && SDL_GetTicks() < time + 3*BLINK_DURATION){
			isHurt(player);
		} else if (SDL_GetTicks() > time + 4*BLINK_DURATION && SDL_GetTicks() < time + 5*BLINK_DURATION){
			isHurt(player);
		}
		return 1;
	}
	return 0;
}
