#ifndef __ENUMTYPE__
#define __ENUMTYPE__

typedef enum {
	PLAYER,
	ENEMY,
	BOSS
} unitType;

typedef enum {
	BULLET,
	MISSILE,
	BOMB
} fireType;

typedef enum {
	PLAYABLE,
	UPANDDOWN,
	FOLLOW,
	HECTIC
} behavior;

#endif