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
#define ELEM_SIZE 70
#define COLLISION_DAMAGE 1

/* HERO STATS */
#define HERO_HP 5
#define HERO_MAX_HEALTH 10
#define HERO_VELOCITY 7
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
#define BOSS_HP 10
#define BOSS_SIZE 300
#define BOSS_RELOAD 700
#define BOSS_FIRE 7

/* PROJECTILES STATS */
#define PROJECTILE_DMG 1
#define PROJECTILE_VELOCITY 5
#define PROJECTILE_SIZE 40

/* OBSTACLES STATS */
#define OBSTACLE_HP 3
#define OBSTACLE_SIZE 40

/* BONUSES STAT */
#define BONUS_SIZE 70

/* LEVEL PARAMETERS */
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 760
#define TERMINAL_SIZE 80
#define BARRIER_WIDTH 100
#define BARRIER_HEIGHT 400
#define SCROLLSPEED 4

/* UI PARAMETERS */
#define UI_SIZE 70
#define UI_MARGIN 20

/* TEXTURES */
#define TEXTURES_SIZE 27
#define TEXTURE_NAME_MAX_SIZE 20
#define ID_BACKGROUND1 1
#define ID_BACKGROUND2 2
#define ID_PLAYER1 3
#define ID_PLAYER2 4
#define ID_ENEMY 5
#define ID_BOSS 6
#define ID_BONUS_HEART 7
#define ID_BONUS_FIRE 8
#define ID_PROJECTILE_PLAYER 9
#define ID_PROJECTILE_ENEMY 10
#define NB_PROJECTILES_ENEMY 5
#define ID_TERMINAL 15
#define ID_BARRIER 16
#define ID_WALL 17
#define NB_ID_WALLS 5
#define ID_UI_HEART 22
#define ID_UI_BULLET 23
#define ID_TITLE_SCREEN 24
#define ID_GAME_OVER_SCREEN 25
#define ID_VICTORY_SCREEN 26
#define ID_ARROW 27

#endif