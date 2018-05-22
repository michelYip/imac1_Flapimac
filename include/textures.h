/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __TEXTURES__
#define __TEXTURES__

#include "level.h"

/* Load the textures */
void loadTextures(SDL_Surface * textures[TEXTURES_SIZE]);

/* Configure the textures and free the memory allocation */
void configTextures(SDL_Surface * textures[TEXTURES_SIZE], GLuint textureID[TEXTURES_SIZE]);

/* Draw an unit */
void drawUnit(Unit unit, GLuint textureID[TEXTURES_SIZE]);

/* Draw a projectile */
void drawProjectile(Projectile projectile, GLuint textureID[TEXTURES_SIZE]);

/* Draw a bonus */
void drawBonus(Bonus bonus, GLuint textureID[TEXTURES_SIZE]);

/* Draw an obstacle */
void drawObstacle(Obstacle obstacle, GLuint textureID[TEXTURES_SIZE]);

/* Draw a terminal */
void drawTerminal(Terminal terminal, GLuint textureID[TEXTURES_SIZE]);

/* Scroll the background and the level */
void scroll(Level * level, GLuint textureID[TEXTURES_SIZE]);

#endif