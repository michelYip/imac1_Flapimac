/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/UI.h"

/* Draw the UI */
void drawUI(Level level){
	int i;
	glPushMatrix();
		glTranslatef(level.player->x - UNIT_SIZE*3,0,0);
		glColor3ub(0,0,0);
		glBegin(GL_QUADS);
			glVertex2f(0,-110);
			glVertex2f(WINDOW_WIDTH,-110);
			glVertex2f(WINDOW_WIDTH,0);
			glVertex2f(0,0);
			glVertex2f(0,WINDOW_HEIGHT);
			glVertex2f(WINDOW_WIDTH,WINDOW_HEIGHT);
			glVertex2f(WINDOW_WIDTH,WINDOW_HEIGHT+150);
			glVertex2f(0,WINDOW_HEIGHT+150);
		glEnd();
		glColor3ub(255,255,255);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(level.player->x, -UI_SIZE*3/4, 0);
		for (i = 0; i < level.player->hitpoint; i++){
			glCallList(ID_UI_HEART);
			glTranslatef(UI_SIZE + UI_MARGIN, 0, 0);
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(level.player->x, WINDOW_HEIGHT + UI_SIZE, 0);
		for (i = 0; i < level.player->fire; i++){
			if (i%2)
				glCallList(ID_UI_BULLET_BIRI);
			else
				glCallList(ID_UI_BULLET_LABY);
			glTranslatef(UI_SIZE + UI_MARGIN, 0, 0);
		}
	glPopMatrix();	
}

/* Draw the title screen */
void drawTitleScreen(){
	glCallList(ID_TITLE_SCREEN);
}

/* Draw the level select screen */
void drawLevelSelectScreen(){
	glCallList(ID_LEVEL_SELECT_SCREEN);
}

/* Draw the victory screen */
void drawVictoryScreen(){
	glCallList(ID_VICTORY_SCREEN);
}

/* Draw the game over screen */
void drawGameOverScreen(){
	glCallList(ID_GAME_OVER_SCREEN);
}

/* Draw the game over special screen */
void drawGameOverSpecialScreen(){
	glCallList(ID_YOU_SHALL_NOT_PASS);
}

/* Draw the pause screen */
void drawPauseScreen(Level * level){
	glPushMatrix();
		glTranslatef(level->player->x-UNIT_SIZE*3,0,0);
		glCallList(ID_PAUSE);
	glPopMatrix();
}

/* Draw the credit screen */
void drawCreditScreen(){
	glCallList(ID_CREDITS);
}

/* Draw an arrow */
void drawArrow(int horizontalMargin, int verticalMargin, int choice){
	glPushMatrix();
		glTranslatef(horizontalMargin, verticalMargin+((choice-1)*VERTICAL_MARGIN), 0);
		glCallList(ID_ARROW);
	glPopMatrix();
}

/* Control the input in the menu */
int menuInput(int * choice, int maxChoice){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_KEYUP:
				switch(e.key.keysym.sym){
					case CUSTOM_SDLK_ENTER:
						return *choice;
					case SDLK_UP:
						(*choice)--;
						if (*choice < 1) (*choice) = 1;
						break;
					case SDLK_DOWN:
						(*choice)++;
						if ((*choice) > maxChoice) (*choice) = maxChoice;
						break;
					default:
						break;
				}
			default:
				break;
		}
	}
	return 0;
}

