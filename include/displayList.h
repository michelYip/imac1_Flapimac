/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __DISPLAYLIST__
#define __DISPLAYLIST__

#include "level.h"

/* Create en ID List for drawing the background */
void createDrawBackgroundIDList(GLuint textureID[TEXTURES_SIZE]);

/* Create an ID List for drawing an unit */
void createDrawUnitIDList(GLuint textureID[TEXTURES_SIZE]);

/* Create an ID List for drawing a bonus */
void createDrawBonusIDList(GLuint textureID[TEXTURES_SIZE]);

/* Create an ID List for drawing a projectile */
void createDrawProjectileIDList(GLuint textureID[TEXTURES_SIZE]);

/* Create an ID List for drawing a terminal */
void createDrawTerminalIDList(GLuint textureID[TEXTURES_SIZE]);

/* Create an ID List for drawing an obstacle */
void createDrawObstacleIDList(GLuint textureID[TEXTURES_SIZE]);

/* Create an ID List for drawing the UI */
void createDrawUIIDList(GLuint textureID[TEXTURES_SIZE]);

/* Scroll the background and the level */
void scroll(Level * level, GLuint textureID[TEXTURES_SIZE]);

#endif