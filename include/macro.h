#ifndef __MACRO__
#define __MACRO__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* STATS PARAMETERS */
#define UNIT_SIZE 40
#define COLLISION_DAMAGE 1
#define COLLISION_KNOCKBACK 1.5
#define PROJECTILE_KNOCKBACK 0.5

/* HERO STATS */
#define HERO_HP 3
#define HERO_VELOCITY 5

/* ENEMIES STATS */
#define ENEMY_HP 2
#define ENEMY_VELOCITY 3

/* PROJECTILES STATS */
#define PROJECTILE_DMG 1
#define PROJECTILE_VELOCITY 7
#define PROJECTILE_SIZE 20

/* OBSTACLES STATS */
#define OBSTACLE_HP 5
#define OBSTACLE_SIZE 40

/* LEVEL PARAMETERS */
#define SCROLLSPEED 2

#endif