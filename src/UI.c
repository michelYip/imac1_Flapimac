/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/UI.h"

/* Draw the UI */
void drawUI(Level level){
	int i;
	glPushMatrix();
		glTranslatef(level.player->x, UI_SIZE + UI_MARGIN, 0);
		for (i = 0; i < level.player->hitpoint; i++){
			glCallList(ID_UI_HEART);
			glTranslatef(UI_SIZE + UI_MARGIN, 0, 0);
		}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(level.player->x, WINDOW_HEIGHT - UI_SIZE - UI_MARGIN, 0);
		for (i = 0; i < level.player->fire; i++){
			glCallList(ID_UI_BULLET);
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