#pragma once
#pragma warning( disable : 4091 )
#pragma warning( disable : 4244 )

#include "Define.h"

typedef enum Scene_s
{
	SCENE_NONE,
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT
}Scene;

typedef short Flag;
typedef short State;

typedef int HGRP;

typedef struct Color_s
{
	UINT red, green, blue;
}Color;

typedef struct Asset_s
{
	HGRP texture;
	int width, height;
}Asset;

typedef struct Rect_s
{
	int x, y;
}Rect;

typedef struct Mouse_s
{
	int x, y;
}Mouse;

typedef struct ObjectShot_s
{
	Asset asset;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;
	State state;
}ObjectShot;

typedef struct ObjectPlayer_s
{
	Asset asset;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;

	ObjectShot shot[PLAYER_SHOT_NUM];
}ObjectPlayer;

typedef struct ObjectEnemy_s
{
	Asset asset;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;

	ObjectShot shot[ENEMY_SHOT_NUM];
}ObjectEnemy;

void InitShot(ObjectShot* shot);

void DrawRotaSprite(const Vector2D* pos, double ExRota, double rad, const Asset* asset, BOOL TransFlag);
void DrawRectRotaSprite(const Vector2D* pos, const Rect* rect, int size_x, double ExRota, double rad, const Asset* asset, BOOL TransFlag);