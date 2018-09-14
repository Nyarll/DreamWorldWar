#pragma once

#define ENEMY_NUM 128
#define ENEMY_SIZE 16

#define ENEMY_SHOT_SIZE 4

void InitEnemy(void);
void UpdateEnemy(int level);
void RenderEnemy(int bright);

BOOL GetEnemyFlag(int i);
void SetEnemyFlagFalse(int i);
Vector2D GetEnemyPos(int i);

void InitEnemyShot(void);
void UpdateEnemyShot(int level);
void RenderEnemyShot(int bright);

BOOL GetEnemyShotFlag(int i, int j);
void SetEnemyShotFlagFalse(int i, int j);
Vector2D GetEnemyShotPos(int i, int j);