/* @uthor : Nathanael ROVERE & Michel YIP */
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
#define KNOCKBACK 0.5

/* HERO STATS */
#define HERO_HP 5
#define HERO_VELOCITY 6
#define IMMUNE_TIME 1000
#define BLINK_DURATION 200
#define BLINK_INTERVAL 200

/* ENEMIES STATS */
#define ENEMY_HP 2
#define ENEMY_VELOCITY 3
#define TIME_TO_SHOOT 500

/* BOSS STATS */
#define BOSS_HP 30

/* PROJECTILES STATS */
#define PROJECTILE_DMG 1
#define PROJECTILE_VELOCITY 9
#define PROJECTILE_SIZE 20

/* OBSTACLES STATS */
#define OBSTACLE_HP 5
#define OBSTACLE_SIZE 40

/* LEVEL PARAMETERS */
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 760
#define SCROLLSPEED 4

#endif