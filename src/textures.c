/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/textures.h"

/* Load the textures */
void loadTextures(SDL_Surface * textures[TEXTURES_SIZE]){
	int i;
	char * texture_name = malloc(sizeof(char)*TEXTURE_NAME_MAX_SIZE);
	for (i = 1; i <= TEXTURES_SIZE; i++){
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
	for (i = 1; i <= TEXTURES_SIZE; i++){
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

	glGenLists(TEXTURES_SIZE);
	createDrawBackgroundIDList(textureID);
	createDrawUnitIDList(textureID);
	createDrawBonusIDList(textureID);
	createDrawProjectileIDList(textureID);
	createDrawTerminalIDList(textureID);
	createDrawObstacleIDList(textureID);
	createDrawUIIDList(textureID);
	createDrawMenusScreenIDList(textureID);
}

/* Draw the background */
void drawBackground(Level level){
	int x = (level.player->x-UNIT_SIZE*3)/WINDOW_WIDTH;
	glPushMatrix();
		glTranslatef(x*WINDOW_WIDTH,0,0);
		if (x%2){
			glCallList(ID_BACKGROUND2);
			glTranslatef(WINDOW_WIDTH,0,0);
			glCallList(ID_BACKGROUND1);
		} else {
			glCallList(ID_BACKGROUND1);
			glTranslatef(WINDOW_WIDTH,0,0);
			glCallList(ID_BACKGROUND2);
		}
	glPopMatrix();
}

/* Draw an unit */
void drawUnit(Unit unit){
	glPushMatrix();
		glTranslatef(unit.x, unit.y, 0);
		if (unit.type == PLAYER){
			glCallList(ID_PLAYER1);
		} else if (unit.type == ENEMY){
			glCallList(ID_ENEMY);
		} else if (unit.type == BOSS){
			glCallList(ID_BOSS);
		}
    glPopMatrix();
}

/* Draw a bonus */
void drawBonus(Bonus bonus){
	glPushMatrix();
		glTranslatef(bonus.x, bonus.y, 0);
		if (bonus.type == HEART){
			glCallList(ID_BONUS_HEART);
		} 
		else if (bonus.type == FIRE_UPGRADE){
			glCallList(ID_BONUS_FIRE);
		}
    glPopMatrix();
}

/* Draw a projectile */
void drawProjectile(Projectile projectile){
	glPushMatrix();
		glTranslatef(projectile.x, projectile.y, 0);
		glCallList(projectile.idTexture);
    glPopMatrix();
}

/* Draw a terminal */
void drawTerminal(Terminal terminal){
	glPushMatrix();
		glTranslatef(terminal.x, terminal.y, 0);
		glCallList(ID_TERMINAL);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(terminal.upperBarrier->x, terminal.upperBarrier->y, 0);
		glCallList(ID_BARRIER);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(terminal.lowerBarrier->x, terminal.lowerBarrier->y, 0);
		glCallList(ID_BARRIER);
	glPopMatrix();
}

/* Draw an obstacle */
void drawObstacle(Obstacle obstacle){
	glPushMatrix();
		glTranslatef(obstacle.x, obstacle.y, 0);
		glCallList(obstacle.idTexture);
	glPopMatrix();
}

/* Scroll the background and the level */
void scroll(Level * level, GLuint textureID[TEXTURES_SIZE]){
	scrollLevel(level);
	drawBackground(*level);
}

