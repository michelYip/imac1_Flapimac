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

/* Draw the victory screen */
void drawVictoryScreen(){
	glCallList(ID_VICTORY_SCREEN);
}

/* Draw the game over screen */
void drawGameOverScreen(){
	glCallList(ID_GAME_OVER_SCREEN);
}

/* Draw an arrow */
void drawArrow(){
	glCallList(ID_ARROW);
}