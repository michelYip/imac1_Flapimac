/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/physics.h"

static Uint32 damagedTime = 0;
static int damaged = 0;

/* Update the level current status */
void updateElementsPosition(Level * level){
	freeOutOfScreenElements(level);
	if (!isImmune(level->player)){
		damaged = 0;
	}
	if (level->projectiles != NULL){
		updateProjectilesPosition(&(level->projectiles));
	}
	if (level->enemies != NULL){
		updateEnemies(level);
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
	Bonus * bonuses;
	Unit * player = *unit;
	while (player != NULL){
		enemies = level->enemies;
		obstacles = level->obstacles;
		bonuses = level->bonuses;
		while (enemies != NULL){
			if (intersect(player->boundingBoxes, enemies->boundingBoxes)){
				if (!isImmune(player)){
					if(damageUnit(&player, COLLISION_DAMAGE)){
						removeUnit(unit, player->id);
						player = *unit;
						if (player == NULL)
							return;
					}
				}
				removeUnit(&(level->enemies), enemies->id);
			}
			enemies = enemies->next;
		}
		while (obstacles != NULL){
			if (intersect(player->boundingBoxes, obstacles->boundingBoxes)){
				if (!isImmune(player)){
					if(damageUnit(&player, COLLISION_DAMAGE)){
						removeUnit(unit, player->id);
						player = *unit;
						if (player == NULL)
							return;
					}
				}
				removeObstacle(&(level->obstacles), obstacles->id);
			}
			obstacles = obstacles->next;
		}
		while (bonuses != NULL){
			if (intersect(player->boundingBoxes, bonuses->boundingBoxes)){
				applyBonus(bonuses, player);
				removeBonus(&(level->bonuses), bonuses->id);
			}
			bonuses = bonuses->next;
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
			if (tmp->master != PLAYER && intersect(tmp->boundingBoxes, player->boundingBoxes)){
				if (!isImmune(player)){
					if(damageUnit(&player, tmp->damage)){
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
			if (tmp->master == PLAYER && intersect(tmp->boundingBoxes, enemies->boundingBoxes)){
				if(damageUnit(&enemies, tmp->damage)){
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
			if (intersect(tmp->boundingBoxes, obstacles->boundingBoxes)){
				if (damageObstacle(&obstacles, tmp->damage)){
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
		if (tmp->master == PLAYER && intersect(tmp->boundingBoxes, level->terminal->boundingBox)){
			level->terminal->state = 1;
			removeProjectile(projectiles, tmp->id);
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
		damagedTime = SDL_GetTicks();
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

/* Check if the player is immune to damage */
int isImmune(Unit * player){
	if (SDL_GetTicks() < damagedTime + IMMUNE_TIME && damaged){
		if (SDL_GetTicks() < damagedTime + BLINK_DURATION){
			isHurt(player);
		} else if (SDL_GetTicks() > damagedTime + 2*BLINK_DURATION && SDL_GetTicks() < damagedTime + 3*BLINK_DURATION){
			isHurt(player);
		} else if (SDL_GetTicks() > damagedTime + 4*BLINK_DURATION && SDL_GetTicks() < damagedTime + 5*BLINK_DURATION){
			isHurt(player);
		}
		return 1;
	}
	return 0;
}
