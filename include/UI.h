/* @uthor : Nathanael ROVERE & Michel YIP */

#ifndef __UI__
#define __UI__

#include "displayList.h"

/* Draw the UI */
void drawUI(Level level);

/* Draw the score */
void drawScore(Level * level, char * scoreString,TTF_Font * font, SDL_Color fontColor, SDL_Surface * screen);

/* Drawn the title Screen */
void drawTitleScreen();

/* Draw the level select screen */
void drawLevelSelectScreen();

/* Draw the victory screen */
void drawVictoryScreen();

/* Draw the game over screen */
void drawGameOverScreen();

/* Draw the game over special screen */
void drawGameOverSpecialScreen();

/* Draw an arrow */
void drawArrow(int horizontalMargin, int verticalMargin, int choice);

/* Control the input in the menu */
int menuInput(int * choice, int maxChoice);

#endif