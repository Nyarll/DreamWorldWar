#include "Enemy.h"
#include "PlayScene.h"
#include "GameObjectStruct.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SHOT_TIMING (180)

static HGRP gh;
static ObjectEnemy enemy[ENEMY_NUM];

static int cnt;
static int temp;

static HGRP shot_gh;

int SearchEnemyObject(void);
BOOL GenerateEnemy(void);

void InitEnemy(void)
{
	int i, j;

	srand((UINT)time(NULL));

	gh = LoadGraph("Resources/Textures/PROTECT/enemy.png");

	for (i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].deg = enemy[i].rad = 0;
		enemy[i].flag = FALSE;
		enemy[i].pos = { 0,0 };
		enemy[i].vel = { 0,0 };
		enemy[i].spd = { 0,0 };
		enemy[i].sprite.height = enemy[i].sprite.width = ENEMY_SIZE;
		enemy[i].sprite.texture = gh;

		enemy[i].cnt = 0;

	}
	InitEnemyShot();
	cnt = 0;
	temp = 1;
}
void UpdateEnemy(int level)
{
	int i;

	if (GetLevel() % 10 == 0)
	{
		temp += 1;
	}

	if (cnt > 60 / (temp))
	{
		cnt = 0;
		GenerateEnemy();
	}

	for (i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag)
		{
			enemy[i].pos.x += enemy[i].vel.x * enemy[i].spd.x;
			enemy[i].pos.y += enemy[i].vel.y * enemy[i].spd.y;

			if ((enemy[i].pos.y > GAME_SCREEN_BOTTOM + 20) || (enemy[i].pos.x < GAME_SCREEN_LEFT - 20) || (enemy[i].pos.x > GAME_SCREEN_RIGHT + 20))
			{
				enemy[i].flag = FALSE;
			}
		}
	}

	cnt++;
}
void RenderEnemy(int bright)
{
	int i;

	for (i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag)
		{
			SetDrawBright(bright, bright, bright);
			DrawRotaSprite(&enemy[i].pos, 2.0, enemy[i].rad, &enemy[i].sprite, TRUE);
		}
	}
}

int SearchEnemyObject(void)
{
	int k;

	for (k = 0; k < ENEMY_NUM; k++)
	{
		if (enemy[k].flag == FALSE)
		{
			return k;
		}
	}
	return -1;
}
BOOL GenerateEnemy(void)
{
	int i;

	if ((i = SearchEnemyObject()) != -1)
	{
		enemy[i].flag = TRUE;
		enemy[i].pos.y = -20;
		enemy[i].pos.x = rand() % (GAME_SCREEN_RIGHT - 32) + 16;

		enemy[i].vel.x = cos(DEG_TO_RAD(rand() % 30 + (270 - 15))) * 2;
		enemy[i].vel.y = sin(DEG_TO_RAD(rand() % 30 + (270 - 15))) * 2;

		enemy[i].spd.x = 1.0;
		enemy[i].spd.y = -1.0;

		enemy[i].rad = DEG_TO_RAD(180);

		return TRUE;
	}
	return FALSE;
}

BOOL GetEnemyFlag(int i)
{
	return enemy[i].flag;
}
void SetEnemyFlagFalse(int i)
{
	enemy[i].flag = FALSE;
}
Vector2D GetEnemyPos(int i)
{
	return enemy[i].pos;
}

// Shot
int SearchEnemyShotObject(int i);
void GenerateEnemyShot(int i);

void InitEnemyShot(void)
{
	int i, j;

	shot_gh = LoadGraph("");

	for (i = 0; i < ENEMY_NUM; i++)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			enemy[i].shot[j].flag = FALSE;
			enemy[i].shot[j].deg = enemy[i].shot[j].rad = 0;
			enemy[i].shot[j].pos = enemy[i].shot[j].vel = enemy[i].shot[j].spd = { 0,0 };
			enemy[i].shot[j].sprite.height = enemy[i].shot[j].sprite.width = ENEMY_SHOT_SIZE;
			enemy[i].shot[j].sprite.texture = shot_gh;
		}
	}
}
void UpdateEnemyShot(int level)
{
	int i, j;

	for (i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag)
		{

			if (enemy[i].cnt > (SHOT_TIMING / level))
			{
				enemy[i].cnt = 0;
				GenerateEnemyShot(i);
			}
			enemy[i].cnt++;
		}
	}

	for (i = 0; i < ENEMY_NUM; i++)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			if (enemy[i].shot[j].flag)
			{
				enemy[i].shot[j].pos.x += enemy[i].shot[j].vel.x * enemy[i].shot[j].spd.x;
				enemy[i].shot[j].pos.y += enemy[i].shot[j].vel.y * enemy[i].shot[j].spd.y;

				if ((GAME_SCREEN_BOTTOM + 20) < enemy[i].shot[j].pos.y)
				{
					enemy[i].shot[j].flag = FALSE;
					enemy[i].shot[j].deg = enemy[i].shot[j].rad = 0;
					enemy[i].shot[j].pos = enemy[i].shot[j].vel = enemy[i].shot[j].spd = { 0,0 };
				}
			}
		}
	}
}
void RenderEnemyShot(int bright)
{
	int i, j;

	for (i = 0; i < ENEMY_NUM; i++)
	{
		for (j = 0; j < ENEMY_SHOT_NUM; j++)
		{
			if (enemy[i].shot[j].flag)
			{
				SetDrawBright(bright, bright, bright);
				DrawRotaSprite(&enemy[i].shot[j].pos, 1.0, enemy[i].shot[j].rad, &enemy[i].shot[j].sprite, TRUE);
			}
		}
	}
}

int SearchEnemyShotObject(int i)
{
	int k;

	if (enemy[i].flag)
	{
		for (k = 0; k < ENEMY_SHOT_NUM; k++)
		{
			if (enemy[i].shot[k].flag == FALSE)
			{
				return k;
			}
		}
	}
	return -1;
}
void GenerateEnemyShot(int i)
{
	int k;

	if ((k = SearchEnemyShotObject(i)) == -1)
	{
		return;
	}
	else
	{
		enemy[i].shot[k].flag = TRUE;
		enemy[i].shot[k].pos = enemy[i].pos;
		enemy[i].shot[k].vel.x = 0;
		enemy[i].shot[k].vel.y = 10;
		enemy[i].shot[k].spd.x = 0;
		enemy[i].shot[k].spd.y = 1;
	}
}

BOOL GetEnemyShotFlag(int i, int j)
{
	return enemy[i].shot[j].flag;
}
void SetEnemyShotFlagFalse(int i, int j)
{
	enemy[i].shot[j].flag = FALSE;
}
Vector2D GetEnemyShotPos(int i, int j)
{
	return enemy[i].shot[j].pos;
}