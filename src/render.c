/* @uthor : Nathanael ROVERE & Michel YIP */
#include "../include/render.h"

/* Render the object in the level */
void renderLevel(Level level){
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
		if (level.player->projectiles != NULL)
			renderProjectiles((*level.player));
		level.player = level.player->next;
	}
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
		if (level.enemies->projectiles != NULL)
			renderProjectiles((*level.enemies));
		level.enemies = level.enemies->next;
	}
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

/* Render all the existing projectiles of the unit in parameter */
void renderProjectiles(Unit unit){
	while (unit.projectiles != NULL){
		glColor3ub(255,255,0);
		glBegin(GL_QUADS);
			glVertex2f(-PROJECTILE_SIZE/2, PROJECTILE_SIZE/2);
			glVertex2f(PROJECTILE_SIZE/2, PROJECTILE_SIZE/2);
			glVertex2f(PROJECTILE_SIZE/2, -PROJECTILE_SIZE/2);
			glVertex2f(-PROJECTILE_SIZE/2, -PROJECTILE_SIZE/2);
		glEnd();
		unit.projectiles = unit.projectiles->next;
	}
}

void scrollLevel(Level * level) {
	glTranslatef(-SCROLLSPEED,0,0);
}