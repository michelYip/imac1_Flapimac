/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __RENDER__
#define __RENDER__

#include "level.h"

/* Render the different object in the level */
void renderLevel(Level level);

/* Render the player in the level */
void renderPlayer(Level level);

/* Render the enemies in the level */
void renderEnemies(Level level);

/* Render the obstacles in the level */
void renderObstacles(Level level);

/* Render all the existing projectiles in the level */
void renderProjectiles(Level level);

/* Make the player blink when it's immune to damage */
void isHurt(Unit * player);

#endif