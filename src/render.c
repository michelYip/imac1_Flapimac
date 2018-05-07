/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/render.h"

/* Render the object in the level */
void renderLevel(Level level){
	if (level.player != NULL){
		renderPlayer(level);
	}
	if (level.enemies != NULL){
		renderEnemies(level);
	}
	if (level.obstacles != NULL){
		renderObstacles(level);
	}
	if (level.projectiles != NULL){
		renderProjectiles(level);
	}
}


/* Render the player in the level */
void renderPlayer(Level level){
	while (level.player != NULL){
	    glColor3ub(0,0,255);
		glPushMatrix();
			glTranslatef(level.player->x*UNIT_SIZE, level.player->y*UNIT_SIZE, 0);
			glBegin(GL_QUADS);
				glVertex2f(-UNIT_SIZE/2, UNIT_SIZE/2);
				glVertex2f(UNIT_SIZE/2, UNIT_SIZE/2);
				glVertex2f(UNIT_SIZE/2, -UNIT_SIZE/2);
				glVertex2f(-UNIT_SIZE/2, -UNIT_SIZE/2);
			glEnd();
		glPopMatrix();
		level.player = level.player->next;
	}
}

/* Render the enemies in the level */
void renderEnemies(Level level){
	while (level.enemies != NULL){
	    glColor3ub(255,0,0);
		glPushMatrix();
			glTranslatef(level.enemies->x*UNIT_SIZE, level.enemies->y*UNIT_SIZE, 0);
			glBegin(GL_QUADS);
				glVertex2f(-UNIT_SIZE/2, UNIT_SIZE/2);
				glVertex2f(UNIT_SIZE/2, UNIT_SIZE/2);
				glVertex2f(UNIT_SIZE/2, -UNIT_SIZE/2);
				glVertex2f(-UNIT_SIZE/2, -UNIT_SIZE/2);
			glEnd();
		glPopMatrix();
		level.enemies = level.enemies->next;
	}
}

/* Render the obstacles in the level */
void renderObstacles(Level level){
	while (level.obstacles != NULL){
	    glColor3ub(255,255,255);
		glPushMatrix();
			glTranslatef(level.obstacles->x*OBSTACLE_SIZE, level.obstacles->y*OBSTACLE_SIZE, 0);
			glBegin(GL_QUADS);
				glVertex2f(-OBSTACLE_SIZE/2, OBSTACLE_SIZE/2);
				glVertex2f(OBSTACLE_SIZE/2, OBSTACLE_SIZE/2);
				glVertex2f(OBSTACLE_SIZE/2, -OBSTACLE_SIZE/2);
				glVertex2f(-OBSTACLE_SIZE/2, -OBSTACLE_SIZE/2);
			glEnd();
			glPopMatrix();
		level.obstacles = level.obstacles->next;
	}
}

/* Render all the existing projectiles in the level */
void renderProjectiles(Level level){
	while (level.projectiles != NULL){
		glColor3ub(255,255,0);
		glBegin(GL_QUADS);
			glVertex2f(-PROJECTILE_SIZE/2, PROJECTILE_SIZE/2);
			glVertex2f(PROJECTILE_SIZE/2, PROJECTILE_SIZE/2);
			glVertex2f(PROJECTILE_SIZE/2, -PROJECTILE_SIZE/2);
			glVertex2f(-PROJECTILE_SIZE/2, -PROJECTILE_SIZE/2);
		glEnd();
		level.projectiles = level.projectiles->next;
	}
}