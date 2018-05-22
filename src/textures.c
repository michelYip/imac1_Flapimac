/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/textures.h"

/* Load the textures */
void loadTextures(SDL_Surface * textures[TEXTURES_SIZE]){
	int i;
	char * texture_name = malloc(sizeof(char)*TEXTURE_NAME_MAX_SIZE);
	for (i = 0; i < TEXTURES_SIZE; i++){
		sprintf(texture_name, "img/%d.png", i);
		if ((textures[i] = IMG_Load(texture_name)) == NULL){
	        fprintf(stderr,"An error occured when loading the image : img/%d.png\n", i);
	        exit(EXIT_FAILURE);
	    }
	}
	free(texture_name);
}

/* Configure the textures and free the memory allocation */
void configTextures(SDL_Surface * textures[TEXTURES_SIZE], GLuint textureID[TEXTURES_SIZE]){
	int i;
	for (i = 0; i < TEXTURES_SIZE; i++){
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			textures[i]->w,
			textures[i]->h,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			textures[i]->pixels
			);
		glBindTexture(GL_TEXTURE_2D, 0);

		SDL_FreeSurface(textures[i]);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/* Draw an unit */
void drawUnit(Unit unit, GLuint textureID[TEXTURES_SIZE]){
	int iTexture;
	if (unit.type == PLAYER){
		iTexture = 2;
	} else{
		iTexture = 3;
	}
	glPushMatrix();
		glTranslatef(unit.x, unit.y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-ELEM_SIZE/2,-ELEM_SIZE/2);
                glTexCoord2f(1,0);
                glVertex2f(ELEM_SIZE/2,-ELEM_SIZE/2);
                glTexCoord2f(1,1);
                glVertex2f(ELEM_SIZE/2,ELEM_SIZE/2);
                glTexCoord2f(0,1);
                glVertex2f(-ELEM_SIZE/2,ELEM_SIZE/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

/* Draw a projectile */
void drawProjectile(Projectile projectile, GLuint textureID[TEXTURES_SIZE]){
	int iTexture;
	if (projectile.master == PLAYER){
		iTexture = 6;
	} else {
		iTexture = 7;
	}
	glPushMatrix();
		glTranslatef(projectile.x, projectile.y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-PROJECTILE_SIZE/2,-PROJECTILE_SIZE/2);
                glTexCoord2f(1,0);
                glVertex2f(PROJECTILE_SIZE/2,-PROJECTILE_SIZE/2);
                glTexCoord2f(1,1);
                glVertex2f(PROJECTILE_SIZE/2,PROJECTILE_SIZE/2);
                glTexCoord2f(0,1);
                glVertex2f(-PROJECTILE_SIZE/2,PROJECTILE_SIZE/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

/* Draw a bonus */
void drawBonus(Bonus bonus, GLuint textureID[TEXTURES_SIZE]){
	int iTexture;
	if (bonus.type == HEART){
		iTexture = 4;
	} else if (bonus.type == FIRE_UPGRADE) {
		iTexture = 5;
	}
	glPushMatrix();
		glTranslatef(bonus.x, bonus.y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-BONUS_SIZE/2,-BONUS_SIZE/2);
                glTexCoord2f(1,0);
                glVertex2f(BONUS_SIZE/2,-BONUS_SIZE/2);
                glTexCoord2f(1,1);
                glVertex2f(BONUS_SIZE/2,BONUS_SIZE/2);
                glTexCoord2f(0,1);
                glVertex2f(-BONUS_SIZE/2,BONUS_SIZE/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

/* Draw an obstacle */
void drawObstacle(Obstacle obstacle, GLuint textureID[TEXTURES_SIZE]){
	int iTexture = 10;
	glPushMatrix();
		glTranslatef(obstacle.x, obstacle.y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-OBSTACLE_SIZE/2,-OBSTACLE_SIZE/2);
                glTexCoord2f(1,0);
                glVertex2f(OBSTACLE_SIZE/2,-OBSTACLE_SIZE/2);
                glTexCoord2f(1,1);
                glVertex2f(OBSTACLE_SIZE/2,OBSTACLE_SIZE/2);
                glTexCoord2f(0,1);
                glVertex2f(-OBSTACLE_SIZE/2,OBSTACLE_SIZE/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

/* Draw a terminal */
void drawTerminal(Terminal terminal, GLuint textureID[TEXTURES_SIZE]){
	int iTexture = 8;
	glPushMatrix();
		glTranslatef(terminal.x, terminal.y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-TERMINAL_SIZE/2,-TERMINAL_SIZE/2);
                glTexCoord2f(1,0);
                glVertex2f(TERMINAL_SIZE/2,-TERMINAL_SIZE/2);
                glTexCoord2f(1,1);
                glVertex2f(TERMINAL_SIZE/2,TERMINAL_SIZE/2);
                glTexCoord2f(0,1);
                glVertex2f(-TERMINAL_SIZE/2,TERMINAL_SIZE/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    iTexture = 9;
	glPushMatrix();
		glTranslatef(terminal.upperBarrier->x, terminal.upperBarrier->y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-BARRIER_WIDTH/2,-BARRIER_HEIGHT/2);
                glTexCoord2f(1,0);
                glVertex2f(BARRIER_WIDTH/2,-BARRIER_HEIGHT/2);
                glTexCoord2f(1,1);
                glVertex2f(BARRIER_WIDTH/2,BARRIER_HEIGHT/2);
                glTexCoord2f(0,1);
                glVertex2f(-BARRIER_WIDTH/2,BARRIER_HEIGHT/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
	glPushMatrix();
		glTranslatef(terminal.lowerBarrier->x, terminal.lowerBarrier->y, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[iTexture]);
		glPushMatrix();
			glBegin(GL_QUADS);
                glTexCoord2f(0,0);
                glVertex2f(-BARRIER_WIDTH/2,-BARRIER_HEIGHT/2);
                glTexCoord2f(1,0);
                glVertex2f(BARRIER_WIDTH/2,-BARRIER_HEIGHT/2);
                glTexCoord2f(1,1);
                glVertex2f(BARRIER_WIDTH/2,BARRIER_HEIGHT/2);
                glTexCoord2f(0,1);
                glVertex2f(-BARRIER_WIDTH/2,BARRIER_HEIGHT/2);
            glEnd();
        glPopMatrix();
    	glDisable(GL_TEXTURE_2D);
    	glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

/* Scroll the background and the level */
void scroll(Level * level, GLuint textureID[TEXTURES_SIZE]){
	scrollLevel(level);
	int background1;
	int background2;
	int i, j = (level->player->x-UNIT_SIZE*3)/WINDOW_WIDTH;
	if (j%2){
		background1 = 1;
		background2 = 0;
	} else {
		background1 = 0;
		background2 = 1;
	}
	for (i = 0;i < 2; i++){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID[background1]);
		glPushMatrix();
			glBegin(GL_QUADS);
	            glTexCoord2f(0,0);
	            glVertex2f(j*WINDOW_WIDTH,0);
	            glTexCoord2f(1,0);
	            glVertex2f((j+1)*WINDOW_WIDTH,0);
	            glTexCoord2f(1,1);
	            glVertex2f((j+1)*WINDOW_WIDTH,WINDOW_HEIGHT);
	            glTexCoord2f(0,1);
	            glVertex2f(j*WINDOW_WIDTH,WINDOW_HEIGHT);
	        glEnd();
	    glPopMatrix();
	    glBindTexture(GL_TEXTURE_2D, textureID[background2]);
		glPushMatrix();
			glBegin(GL_QUADS);
	            glTexCoord2f(0,0);
	            glVertex2f((j+1)*WINDOW_WIDTH,0);
	            glTexCoord2f(1,0);
	            glVertex2f((j+2)*WINDOW_WIDTH,0);
	            glTexCoord2f(1,1);
	            glVertex2f((j+2)*WINDOW_WIDTH,WINDOW_HEIGHT);
	            glTexCoord2f(0,1);
	            glVertex2f((j+1)*WINDOW_WIDTH,WINDOW_HEIGHT);
	        glEnd();
	    glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	 	glBindTexture(GL_TEXTURE_2D, 0);
	 }
}