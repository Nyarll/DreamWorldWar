#include "GameObjectStruct.h"

#include "PlayScene.h"
#include "Back.h"
#include "Player.h"
#include "Score.h"
#include "Enemy.h"

static Mouse mouse;
int game_time = 0;
int level = 1;

void PlayerEnemyCollision(void);

void InitPlayScene(void)
{
	InitBack();
	InitPlayerObject();
	InitPlayerShot();
	InitScore();
	InitEnemy();
	InitMaterial();
	game_time = 0;
	level = 1;
}
void UpdatePlayScene(void)
{
	int score = GetScore();

	if (game_time > 600)
	{
		level += 1;
		game_time = 0;
	}

	UpdateBack();
	UpdatePlayerObject();
	UpdatePlayerShot();
	UpdateEnemy(level);
	UpdateEnemyShot(level);
	UpdateScore();
	UpdateMaterial();

	PlayerEnemyCollision();

	game_time++;
}
void RenderPlayScene(int bright)
{
	RenderBack(bright);
	RenderEnemy(bright);
	RenderPlayerShot(bright);
	RenderEnemyShot(bright);
	DrawBox(GAME_SCREEN_RIGHT, GAME_SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_BLACK, TRUE);
	RenderPlayerObject(bright);
	RenderScore(bright);
	RenderMaterial(bright);

	DrawPlayerDescription();

	DrawFormatString(GAME_SCREEN_RIGHT, GAME_SCREEN_TOP, COLOR_RED, "%d", game_time);
}

void PlayerEnemyCollision(void)
{
	int e, p, ps, es;
	Vector2D Epos, Ppos, PSpos, ESpos;

	for (e = 0; e < ENEMY_NUM; e++)
	{
		if (GetEnemyFlag(e))
		{
			for (p = 0; p < PLAYER_NUM; p++)
			{
				if (GetPlayerFlag(p))
				{
					Epos = GetEnemyPos(e);
					Ppos = GetPlayerPos(p);

					if (CircleCollision(8, 8, Epos.x, Ppos.x, Epos.y, Ppos.y))	// プレイヤーオブジェクトとエネミーオブジェクトの衝突判定 / 円形
					{
						SetEnemyFlagFalse(e);
						SetPlayerFlagFalse(p);
						AddScore(50);
						PlayerDead();
					}
				}
				for (ps = 0; ps < PLAYER_SHOT_NUM; ps++)
				{
					if (GetPlayerShotFlag(p, ps))
					{
						Epos = GetEnemyPos(e);
						PSpos = GetPlayerShotPos(p, ps);

						if (CircleCollision(8, 4, Epos.x, PSpos.x, Epos.y, PSpos.y))	// プレイヤーの弾オブジェクトとエネミーオブジェクトの衝突判定 / 円形
						{
							SetEnemyFlagFalse(e);
							SetPlayerShotFlagFalse(p, ps);
							AddMaterial(100);
							AddScore(100);
						}
					}
				}
			}
			Epos = GetEnemyPos(e);
			if (Epos.y > GAME_SCREEN_BOTTOM + 17)
			{
				AddScore((-50));
			}
		}

		for (es = 0; es < ENEMY_SHOT_NUM; es++)
		{
			if (GetEnemyShotFlag(e, es))
			{
				ESpos = GetEnemyShotPos(e, es);
				for (p = 0; p < PLAYER_NUM; p++)
				{
					if (GetPlayerFlag(p))
					{
						Ppos = GetPlayerPos(p);
						switch (GetPlayerType(p))
						{
						case 2:
							if (CircleCollision((ENEMY_SHOT_SIZE / 2), 100, ESpos.x, Ppos.x, ESpos.y, Ppos.y))
							{
								SetEnemyShotFlagFalse(e, es);
								PlayerDamage(p, 10);
							}
							break;

						default:
							if (CircleCollision((ENEMY_SHOT_SIZE / 2), 8, ESpos.x, Ppos.x, ESpos.y, Ppos.y))
							{
								SetEnemyShotFlagFalse(e, es);
								SetPlayerFlagFalse(p);
								PlayerDead();
							}
							break;
						}
					}
				}
			}
		}
	}
}

int GetLevel(void)
{
	return level;
}