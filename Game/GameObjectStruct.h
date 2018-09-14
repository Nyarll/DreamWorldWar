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

typedef struct
{
	HGRP texture;
	int width, height;
}SpriteObject;

typedef struct Rect_s
{
	int x, y;
}Rect;

typedef struct Mouse_s
{
	int x, y;
	int input;
}Mouse;

typedef struct ObjectShot_s
{
	SpriteObject sprite;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;
	State state;
}ObjectShot;

typedef struct
{
	Flag flag;	// 生死
	State state;	// なんらかの状態変化をしたいとき用

	State type;	// 種類

	Vector2D pos;	// 中心座標
	Rect rect;
	SpriteObject sprite;

	double deg, rad;	// 角度

	int cnt;

	int HP;

	ObjectShot shot[PLAYER_SHOT_NUM];
}ObjectPlayer;


typedef struct ObjectEnemy_s
{
	SpriteObject sprite;
	Vector2D pos;
	Vector2D vel;
	Vector2D spd;
	double deg, rad;

	Flag flag;
	int cnt;

	ObjectShot shot[ENEMY_SHOT_NUM];
}ObjectEnemy;

typedef struct ObjectSound_s
{
	int sound_handle;
	Flag sound_flag;
}ObjectSound;

void InitShot(ObjectShot* shot);

void DrawRotaSprite(const Vector2D* pos, double ExRota, double rad, const SpriteObject* sprite, BOOL TransFlag);
void DrawRectRotaSprite(const Vector2D* pos, const Rect* rect, int size_x, double ExRota, double rad, const SpriteObject* sprite, BOOL TransFlag);