#ifndef __RENDER__
#define __RENDER__

#include "action.h"

#define SCROLLSPEED 5

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

#endif