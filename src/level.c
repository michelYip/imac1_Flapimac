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
	level->bonuses = NULL;
	level->terminal = NULL;
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
   			//Obstacle
   			if (r == 255 && g == 255 && b == 255){
   				addObstacle(&(level->obstacles), (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			//Enemy
   			else if (r == 255 && g == 0 && b == 0){
   				addUnit(&(level->enemies), ENEMY, ENEMY_FIRE, (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			//Player
   			else if (r == 0 && g == 0 && b == 255){
   				addUnit(&(level->player), PLAYER, HERO_FIRE, (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			//Boss
   			else if (r == 125 && g == 125 && b == 125){
   				addUnit(&(level->enemies), BOSS, BOSS_FIRE, (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			else if (r == 0 && g == 255 && b == 0){
   				addBonus(&(level->bonuses), (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
   			}
   			else if (r == 255 && g == 0 && b == 255){
   				level->terminal = initTerminal(level->width, level->height, (float)x*UNIT_SIZE, (float)y*UNIT_SIZE);
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

/* Automatic horizontal scroll */
void scrollLevel(Level * level) {
	if (!checkBossPosition(level)){
		glTranslatef(-SCROLLSPEED,0,0);
	}
}

/* Free from memory elements that are not in the screen */
void freeOutOfScreenElements(Level * level){
	Unit * enemy = level->enemies;
	Projectile * projectile = level->projectiles;
	Obstacle * obstacle = level->obstacles;
	while (enemy != NULL){
		if (enemy->x < level->player->x - UNIT_SIZE * 3){
			removeUnit(&(level->enemies), enemy->id);
			enemy = level->enemies;
		}
		if (enemy == NULL){
			break;
		}
		enemy = enemy->next;
	}
	while (projectile != NULL){
		if (projectile->x < level->player->x - UNIT_SIZE * 3 || projectile->x > level->player->x + WINDOW_WIDTH - UNIT_SIZE * 3){
			removeProjectile(&(level->projectiles), projectile->id);
			projectile = level->projectiles;
		}
		if (projectile == NULL){
			break;
		}
		projectile = projectile->next;
	}
	while (obstacle != NULL){
		if (obstacle->x < level->player->x - OBSTACLE_SIZE * 3){
			removeObstacle(&(level->obstacles), obstacle->id);
			obstacle = level->obstacles;
		}
		if (obstacle == NULL){
			break;
		}
		obstacle = obstacle->next;
	}
}

/* Check the boss position */
int checkBossPosition(Level * level){
	Unit * tmp = level->player;
	Unit * boss = level->enemies;
	while (boss != NULL && boss->type != BOSS) {
		boss = boss->next;
	}
	if (boss == NULL) {
		while (tmp != NULL){
			tmp->x_velocity = SCROLLSPEED;
			tmp = tmp->next;
		}
		return 0;
	}
	else {
		if (boss->x < level->player->x + BOSS_SIZE * 4){
			while (tmp != NULL){
				tmp->x_velocity = 0;
				tmp = tmp->next;
			}
			return 1;
		}
		return 0;
	}
}
