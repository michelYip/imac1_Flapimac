/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __ENUMTYPE__
#define __ENUMTYPE__

typedef enum {
	PLAYER,
	ENEMY,
	BOSS
} unitType;

typedef enum {
	BULLET,
	VOLLEY
} fireType;

typedef enum {
	PLAYABLE,
	UPANDDOWN,
	FOLLOW
} behavior;

#endif