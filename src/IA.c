/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/IA.h"

/* Manage enemies behavior */
void updateEnemies(Level * level){
	Unit * enemy = level->enemies;
	Obstacle * obstacle;
	while (enemy != NULL){
		obstacle = level->obstacles;
		shoot(&(level->projectiles), enemy);
		while (obstacle != NULL){
			if (intersect(enemy->boundingBoxes, obstacle->boundingBoxes)){
				if (enemy->behavior == UPANDDOWN){
					enemy->y_velocity = -enemy->y_velocity;
				}
				else if (enemy->behavior == FOLLOW){
					enemy->y_velocity = -1;
				}
				break;
			} else {
				if (enemy->behavior == UPANDDOWN) {
					updateUpAndDown(enemy);
				} else if (enemy->behavior == FOLLOW) {
					updateFollow(enemy, level->player);
				}
			}
			obstacle = obstacle->next;
		}
		if (level->obstacles == NULL){
			if (enemy->behavior == UPANDDOWN) {
				updateUpAndDown(enemy);
			} else if (enemy->behavior == FOLLOW) {
				updateFollow(enemy, level->player);
			}
		}
		moveUnit(enemy);
		enemy = enemy->next;
	}
}

/* Update the position of an enemy with UPANDDOWN behavior */
void updateUpAndDown(Unit * enemy){
	int size = (enemy->type == BOSS)? BOSS_SIZE : ELEM_SIZE;
	if (enemy->y_velocity == 0)
		enemy->y_velocity = ENEMY_VELOCITY;
	if (enemy->y_velocity > 0 && enemy->y >= WINDOW_HEIGHT-size){
		enemy->y_velocity = -ENEMY_VELOCITY;
	}
	if (enemy->y_velocity < 0 && enemy->y <= size){
		enemy->y_velocity = ENEMY_VELOCITY;
	}
}

/* Update the position of an enemy with FOLLOW behavior */
void updateFollow(Unit * enemy, Unit * player){
	if (enemy->y < player->y){
		enemy->y_velocity = ENEMY_VELOCITY;
	} else if (enemy->y > player->y){
		enemy->y_velocity = -ENEMY_VELOCITY;
	} else {
		enemy->y_velocity = 0;
	}
}