/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/render.h"

/* Render the object in the level */
void renderLevel(Level level, GLuint textureID[TEXTURES_SIZE]){
	if (level.player != NULL){
		renderPlayer(level,textureID);
	}
	if (level.enemies != NULL){
		renderEnemies(level,textureID);
	}
	if (level.obstacles != NULL){
		renderObstacles(level,textureID);
	}
	if (level.projectiles != NULL){
		renderProjectiles(level,textureID);
	}
	if (level.bonuses != NULL){
		renderBonuses(level,textureID);
	}
	renderTerminal(level,textureID);
}


/* Render the player in the level */
void renderPlayer(Level level, GLuint textureID[TEXTURES_SIZE]){
	while (level.player != NULL){
		drawUnit(*(level.player));
		level.player = level.player->next;
	}
}

/* Render the enemies in the level */
void renderEnemies(Level level, GLuint textureID[TEXTURES_SIZE]){
	while (level.enemies != NULL){
		if (level.enemies->x < level.player->x + WINDOW_WIDTH)
			drawUnit(*(level.enemies));
		level.enemies = level.enemies->next;
	}
}

/* Render the obstacles in the level */
void renderObstacles(Level level, GLuint textureID[TEXTURES_SIZE]){
	while (level.obstacles != NULL){
		if (level.obstacles->x < level.player->x + WINDOW_WIDTH)
	    	drawObstacle(*(level.obstacles));
		level.obstacles = level.obstacles->next;
	}
}

/* Render all the existing projectiles in the level */
void renderProjectiles(Level level, GLuint textureID[TEXTURES_SIZE]){
	while (level.projectiles != NULL){
		if (level.projectiles->x < level.player->x + WINDOW_WIDTH)
			drawProjectile(*(level.projectiles));
		level.projectiles = level.projectiles->next;
	}
}

/* Render all the existing bonuses in the level */
void renderBonuses(Level level, GLuint textureID[TEXTURES_SIZE]){
	while (level.bonuses != NULL){
		if (level.bonuses->x < level.player->x + WINDOW_WIDTH)
			drawBonus(*(level.bonuses));
		level.bonuses = level.bonuses->next;
	}
}

/* Render the terminal of the level */
void renderTerminal(Level level, GLuint textureID[TEXTURES_SIZE]){
	if (level.terminal != NULL){
		drawTerminal(*(level.terminal));
	}
}

void isHurt(Unit * player){
	glColor3ub(255,0,0);
	glPushMatrix();
		glTranslatef(player->x, player->y, 0);
		glBegin(GL_QUADS);
			glVertex2f(-ELEM_SIZE/2, ELEM_SIZE/2);
			glVertex2f(ELEM_SIZE/2, ELEM_SIZE/2);
			glVertex2f(ELEM_SIZE/2, -ELEM_SIZE/2);
			glVertex2f(-ELEM_SIZE/2, -ELEM_SIZE/2);
		glEnd();
	glPopMatrix();
	glColor3ub(255,255,255);
}