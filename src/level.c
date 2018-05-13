/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/level.h"

/* Load a level from a PPM File */
Level * loadLevel(const char * levelName){
	FILE * fp;
	char buffer[16];
	int c, rgb_comp_color;
	int x, y;
	int r, g, b;
	Level * level;
	if ((level = malloc(sizeof(Level))) == NULL){
		fprintf(stderr, "error while allocating memory for loadLevel\n");
		exit(EXIT_FAILURE);
	}
	level->player = NULL;
	level->enemies=NULL;
	level->obstacles=NULL;
	level->projectiles = NULL;
	//open PPM file for reading
	fp = fopen(levelName, "rb");
	if (!fp){
		fprintf(stderr, "Unable to open file '%s'\n", levelName);
		exit(EXIT_FAILURE);
	}
	//read image format
	if (!fgets(buffer, sizeof(buffer), fp)){
		perror(levelName);
		exit(EXIT_FAILURE);
	}
	//check the image format
	if (buffer[0] != 'P' || buffer[1] != '3'){
		fprintf(stderr, "Invalid image format (must be 'P3')\n");
		exit(EXIT_FAILURE);
	}
	c = getc(fp);
	while (c == '#'){
		while (getc(fp) != '\n');
			c = getc(fp);
	}
	ungetc(c, fp);
	//read image size information
	if (fscanf(fp, "%d %d", &(level->width), &(level->height)) != 2){
		fprintf(stderr, "Invalid image size (error loading '%s')\n", levelName);
		exit(EXIT_FAILURE);
	}
	//read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", levelName);
         exit(1);
    }
    //check rgb component depth
    if (rgb_comp_color != 255) {
         fprintf(stderr, "'%s' does not have 8-bits components\n", levelName);
         exit(1);
    }
    for (y = 0; y < level->height; y++){
    	for (x = 0; x < level->width; x ++){
   			fscanf(fp, "%d", &r);
   			fscanf(fp, "%d", &g);
   			fscanf(fp, "%d", &b);
   			if (r == 255 && g == 255 && b == 255){
   				addObstacle(&(level->obstacles), (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			else if (r == 255 && g == 0 && b == 0){
   				addUnit(&(level->enemies), ENEMY, BULLET, (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			else if (r == 0 && g == 0 && b == 255){
   				addUnit(&(level->player), PLAYER, BULLET, (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
    	}
    }

    return level;
}

/* Print the level parameter */
void printLevel(Level level){
	printf("width : %d, height : %d\n", level.width, level.height);
	printf("PLAYER : \n");
	while(level.player != NULL){
		printUnitPosition(*(level.player));
		level.player = (level.player)->next;
	}
	printf("ENEMIES : \n");
	while(level.enemies != NULL){
		printUnitPosition(*(level.enemies));
		level.enemies = (level.enemies)->next;	
	}
	printf("OBSTACLES : \n");
	printObstacles(level.obstacles);

}

/* Update the level current status */
void updateLevel(Level * level){
	if (level->projectiles != NULL){
		updateProjectilesPosition(&(level->projectiles));
	}
	checkCollisions(level);

}

/* Check the collision for every object in the level */
void checkCollisions(Level * level){
	checkPlayerCollision(&level->player, level);
	checkProjectilesCollision(&level->projectiles, level);
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
			if (player == NULL){
				player = *unit;
				continue;
			}
			if (intersect(player->boundingBoxes, enemies->boundingBoxes)){
				if(damageUnit(&player, COLLISION_DAMAGE)){
					removeUnit(unit, player->id);
				} else {
					knockbackUnit(player, enemies->x, enemies->y, COLLISION_KNOCKBACK);
				}
			}
			enemies = enemies->next;
		}
		while (obstacles != NULL){
			if (player == NULL){
				player = *unit;
				continue;
			}
			if (intersect(player->boundingBoxes, obstacles->boundingBoxes)){
				if(damageUnit(&player, COLLISION_DAMAGE)){
					removeUnit(unit, player->id);
				} else {
					knockbackUnit(player, obstacles->x, obstacles->y, COLLISION_KNOCKBACK);
				}
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
			if (tmp == NULL){
				tmp = *projectiles;
				continue;
			}
			if (tmp->master == ENEMY && intersect(tmp->boundingBoxes, player->boundingBoxes)){
				if(damageUnit(&player, tmp->damage)){
					printf("player is destroyed !\n");
				}
				removeProjectile(projectiles, tmp->id);
			}
			player = player->next;
		}
		while (enemies != NULL){
			if (tmp == NULL){
				tmp = *projectiles;
				continue;
			}
			if (tmp->master == PLAYER && intersect(tmp->boundingBoxes, enemies->boundingBoxes)){
				if(damageUnit(&enemies, tmp->damage)){
					printf("enemy is destroyed !\n");
				}
				removeProjectile(projectiles, tmp->id);
			}
			enemies = enemies->next;
		}
		while (obstacles != NULL){
			if (tmp == NULL){
				tmp = *projectiles;
				continue;
			}
			if (intersect(tmp->boundingBoxes, obstacles->boundingBoxes)){
				removeProjectile(projectiles, tmp->id);
			}
			obstacles = obstacles->next;
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
	(*unit)->hitpoint -= damageDealt;
	if ((*unit)->hitpoint <= 0){
		return 1;
	}
	return 0;
}

/* Push a unit away from the collision */
void knockbackUnit(Unit * unit, float x, float y, float knockbackDistance){
	moveBoundingBoxes(&(unit->boundingBoxes), -(x - unit->x) * knockbackDistance, -(y - unit->y) * knockbackDistance); 
	unit->x += -(x - unit->x) * knockbackDistance;
	unit->y += -(y - unit->y) * knockbackDistance;
}

