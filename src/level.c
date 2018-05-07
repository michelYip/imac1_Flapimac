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
   				addObstacle(&(level->obstacles), (float)x, (float)y);
   			}
   			else if (r == 255 && g == 0 && b == 0){
   				addUnit(&(level->enemies), ENEMY, BULLET, (float)x, (float)y);
   			}
   			else if (r == 0 && g == 0 && b == 255){
   				addUnit(&(level->player), PLAYER, BULLET, (float)x, (float)y);
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
