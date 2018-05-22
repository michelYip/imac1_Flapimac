/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __MACRO__
#define __MACRO__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* 	STATS PARAMETERS */
#define UNIT_SIZE 40
#define ELEM_SIZE 60
#define COLLISION_DAMAGE 1

/* HERO STATS */
#define HERO_HP 5
#define HERO_MAX_HEALTH 10
#define HERO_VELOCITY 10
#define HERO_RELOAD 300
#define HERO_FIRE 1
#define HERO_MAX_FIRE 7
#define IMMUNE_TIME 1000
#define BLINK_DURATION 200
#define BLINK_INTERVAL 200

/* ENEMIES STATS */
#define ENEMY_HP 2
#define ENEMY_FIRE 1
#define ENEMY_VELOCITY 2
#define ENEMY_RELOAD 1000

/* BOSS STATS */
#define BOSS_HP 100
#define BOSS_SIZE 300
#define BOSS_RELOAD 800
#define BOSS_FIRE 7

/* PROJECTILES STATS */
#define PROJECTILE_DMG 1
#define PROJECTILE_VELOCITY 12
#define PROJECTILE_SIZE 60

/* OBSTACLES STATS */
#define OBSTACLE_HP 3
#define OBSTACLE_SIZE 40

/* BONUSES STAT */
#define BONUS_SIZE 60

/* LEVEL PARAMETERS */
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 760
#define TERMINAL_SIZE 80
#define BARRIER_WIDTH 100
#define BARRIER_HEIGHT 400
#define SCROLLSPEED 6

/* TEXTURES */
#define TEXTURES_SIZE 11
#define TEXTURE_NAME_MAX_SIZE 20

#endif