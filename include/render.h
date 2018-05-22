/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __RENDER__
#define __RENDER__

#include "textures.h"

/* Render the different object in the level */
void renderLevel(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Render the player in the level */
void renderPlayer(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Render the enemies in the level */
void renderEnemies(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Render the obstacles in the level */
void renderObstacles(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Render all the existing projectiles in the level */
void renderProjectiles(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Render all the existing bonuses in the level */
void renderBonuses(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Render the terminal of the level */
void renderTerminal(Level level, GLuint textureID[TEXTURES_SIZE]);

/* Make the player blink when it's immune to damage */
void isHurt(Unit * player);

#endif