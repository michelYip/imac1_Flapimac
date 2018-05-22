/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __TEXTURES__
#define __TEXTURES__

#include "displayList.h"

/* Load the textures */
void loadTextures(SDL_Surface * textures[TEXTURES_SIZE]);

/* Configure the textures and free the memory allocation */
void configTextures(SDL_Surface * textures[TEXTURES_SIZE], GLuint textureID[TEXTURES_SIZE]);

/* Draw the background */
void drawBackground(Level level);

/* Draw an unit */
void drawUnit(Unit unit);

/* Draw a bonus */
void drawBonus(Bonus bonus);

/* Draw a projectile */
void drawProjectile(Projectile projectile);

/* Draw a terminal */
void drawTerminal(Terminal terminal);

/* Draw an obstacle */
void drawObstacle(Obstacle obstacle);

/* Draw the UI */
void drawUI(Level level);

/* Scroll the background and the level */
void scroll(Level * level, GLuint textureID[TEXTURES_SIZE]);

#endif