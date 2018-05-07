#ifndef __RENDER__
#define __RENDER__

#include "level.h"

#define SCROLLSPEED 5

/* Render the object in the level */
void renderLevel(Level level);

/* Render all the existing projectiles of the unit in parameter */
void renderProjectiles(Unit unit);

#endif