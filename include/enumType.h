/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __ENUMTYPE__
#define __ENUMTYPE__

typedef enum {
	PLAYER,
	ENEMY,
	BOSS
} unitType;

typedef enum {
	PLAYABLE,
	UPANDDOWN,
	FOLLOW
} behavior;

typedef enum {
	HEART,
	FIRE_UPGRADE
} bonusType;

#endif