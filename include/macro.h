/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __MACRO__
#define __MACRO__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* STATS PARAMETERS */
#define UNIT_SIZE 40
#define COLLISION_DAMAGE 1

/* HERO STATS */
#define HERO_HP 20
#define HERO_VELOCITY 7
#define HERO_RELOAD 200
#define IMMUNE_TIME 1000
#define BLINK_DURATION 200
#define BLINK_INTERVAL 200

/* ENEMIES STATS */
#define ENEMY_HP 2
#define ENEMY_VELOCITY 2
#define ENEMY_RELOAD 1000

/* BOSS STATS */
#define BOSS_HP 30
#define BOSS_SIZE 300
#define BOSS_RELOAD 750

/* PROJECTILES STATS */
#define PROJECTILE_DMG 1
#define PROJECTILE_VELOCITY 5
#define PROJECTILE_SIZE 20

/* OBSTACLES STATS */
#define OBSTACLE_HP 3
#define OBSTACLE_SIZE 40

/* LEVEL PARAMETERS */
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 760
#define SCROLLSPEED 6

#endif