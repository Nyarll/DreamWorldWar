#pragma once

#include "Define.h"

typedef short Flag;
typedef short State;

typedef struct Color_s
{
	UINT red, green, blue;
};

typedef struct ObjectShot_s
{
	HGRP texture;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;
	State state;
}ObjectShot;

typedef struct ObjectPlayer_s
{
	HGRP texture;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;

	ObjectShot shot[PLAYER_SHOT_NUM];
}ObjectPlayer;

typedef struct ObjectEnemy_s
{
	HGRP texture;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;

	ObjectShot shot[ENEMY_SHOT_NUM];
}ObjectEnemy;

void InitShot(ObjectShot* shot);