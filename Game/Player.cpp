#include "GameObjectStruct.h"
#include "Define.h"
#include "Player.h"

#include <math.h>

#define INIT_MATERIAL (1000)
#define PLAYER_HP (300)
#define PLAYER_HPROD (40)

ObjectPlayer player[PLAYER_NUM];	// PlayerObject

int player_num;	// 出現中のプレイヤーの数

HGRP pobj1;
HGRP pobj2;
HGRP pobj3;

HGRP shot_tex;

HGRP set_tex;
State set_state;
State set_type;

Mouse mouse;
int m_input_old;

int material;	// プレイヤーオブジェクトを設置するのに必要になる材料？の量

int SearchPlayerObject(void);		// Flag が FALSE の Player を探す

BOOL SelectPlayerType(void);

void DrawPlayerType0(int count, int i);
void DrawPlayerType1(int count, int i);
void DrawPlayerType2(int count, int i);

int SearchPlayerShot(int i);

// Player Function

void InitPlayerObject(void)
{
	int i, j;

	for (i = 0; i < PLAYER_NUM; i++)
	{
		player[i].flag = FALSE;		// まだ Set されていない

		player[i].pos = { 0,0 };	// とりあえず 0

		player[i].sprite.texture = LoadGraph("Resouces/Textures/PROTECT/.png");
		player[i].sprite.height = player[i].sprite.width = 16;

		player[i].rect = { 0,0 };

		player[i].cnt = 0;

		player[i].HP = 60;

		player[i].deg = 0;
		player[i].rad = 0;

		for (j = 0; j < PLAYER_SHOT_NUM; j++)
		{
			InitShot(&player[i].shot[j]);
		}
	}
	set_type = -1;
	set_tex = -1;
	set_state = -1;
	pobj1 = LoadGraph("Resources/Textures/PROTECT/playerobj1.png");
	pobj2 = LoadGraph("Resources/Textures/PROTECT/playerobj2.png");
	pobj3 = LoadGraph("Resources/Textures/PROTECT/playerobj3.png");

	player_num = 0;
}
void UpdatePlayerObject(void)
{
	int i;
	int k;


	GetMousePoint(&mouse.x, &mouse.y);
	mouse.input = GetMouseInput();

	for (i = 0; i < PLAYER_NUM; i++)
	{
		// TRUE の player だけ
		if (player[i].flag)
		{
			player[i].cnt++;

			if (player[i].type != 2)
			{
				player[i].HP--;		// 毎フレームHPが少しずつ減る
			}

			if (player[i].HP <= 0)	// 0以下になったら死ぬ
			{
				SetPlayerFlagFalse(i);
				player_num -= 1;
			}
		}
	}

	if (SelectPlayerType())
	{
	}
	// 配置
	else if ((mouse.x > GAME_SCREEN_LEFT) && (mouse.x < GAME_SCREEN_RIGHT) &&
		(mouse.y > GAME_SCREEN_TOP) && (mouse.y < GAME_SCREEN_BOTTOM) && (set_type != -1))
	{
		if ((mouse.input == MOUSE_INPUT_RIGHT) && (m_input_old == 0))
		{
			switch (set_type)
			{
			case 0:
				if (material >= USE_MATERIAL_PLAYERTYPE0)
				{
					SetPlayerObject(mouse.x, mouse.y, set_tex, set_state, set_type);
					AddMaterial((-USE_MATERIAL_PLAYERTYPE0));
					player_num += 1;
				}
				break;

			case 1:
				if (material >= USE_MATERIAL_PLAYERTYPE1)
				{
					SetPlayerObject(mouse.x, mouse.y, set_tex, set_state, set_type);
					AddMaterial((-USE_MATERIAL_PLAYERTYPE1));
					player_num += 1;
				}
				break;

			case 2:
				if (material >= USE_MATERIAL_PLAYERTYPE2)
				{
					SetPlayerObject(mouse.x, mouse.y, set_tex, set_state, set_type);
					AddMaterial((-USE_MATERIAL_PLAYERTYPE2));
					player_num += 1;
				}
				break;
			}
		}
	}
	else // 選択解除
	{
		if (((mouse.input == MOUSE_INPUT_LEFT) || (mouse.input == MOUSE_INPUT_RIGHT)) && (m_input_old == 0))
		{
			set_tex = -1;
			set_type = -1;
			set_state = -1;
		}
	}

	m_input_old = GetMouseInput();
}
void RenderPlayerObject(int bright)
{
	int i;
	static Rect rect1 = { 0,0 }, rect2 = { 0,0 }, rect3 = { 0,0 };
	SpriteObject asset;
	Vector2D temp;

	int temp_x;

	static int rect_count = 0;

	SetDrawBright(bright, bright, bright);
	for (i = 0; i < PLAYER_NUM; i++)
	{
		// TRUE の player だけ
		if (player[i].flag)
		{
			switch (player[i].type)
			{
			case 0:
				DrawPlayerType0(rect_count, i);
				DrawRectRotaSprite(&player[i].pos, &player[i].rect, 16, 2.0, 0.0, &player[i].sprite, TRUE);
				// HP バーの表示
				{
					temp_x = (player[i].pos.x - PLAYER_HPROD / 2) + (PLAYER_HPROD * player[i].HP / PLAYER_HP);
					//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);	// 半透明
					DrawBox((player[i].pos.x - PLAYER_HPROD / 2) - 1, (player[i].pos.y + 8), (player[i].pos.x + PLAYER_HPROD / 2) + 1, (player[i].pos.y + 14), 0xff000000, TRUE);
					DrawBox((player[i].pos.x - PLAYER_HPROD / 2), (player[i].pos.y + 9), temp_x, (player[i].pos.y + 13), 0xff00ffff, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				break;

			case 1:
				DrawPlayerType1(rect_count, i);
				DrawRectRotaSprite(&player[i].pos, &player[i].rect, 12, 2.0, 0.0, &player[i].sprite, TRUE);
				// HP バーの表示
				{
					temp_x = (player[i].pos.x - PLAYER_HPROD / 2) + (PLAYER_HPROD * player[i].HP / PLAYER_HP);
					//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);	// 半透明
					DrawBox((player[i].pos.x - PLAYER_HPROD / 2) - 1, (player[i].pos.y + 8), (player[i].pos.x + PLAYER_HPROD / 2) + 1, (player[i].pos.y + 14), 0xff000000, TRUE);
					DrawBox((player[i].pos.x - PLAYER_HPROD / 2), (player[i].pos.y + 9), temp_x, (player[i].pos.y + 13), 0xff00ffff, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				break;

			case 2:
				DrawPlayerType2(rect_count, i);
				DrawRectRotaSprite(&player[i].pos, &player[i].rect, 16, 2.0, 0.0, &player[i].sprite, TRUE);
				// HP バーの表示
				{
					temp_x = (player[i].pos.x - PLAYER_HPROD / 2) + (PLAYER_HPROD * player[i].HP / (PLAYER_HP * 2));
					//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);	// 半透明
					DrawBox((player[i].pos.x - PLAYER_HPROD / 2) - 1, (player[i].pos.y + 8), (player[i].pos.x + PLAYER_HPROD / 2) + 1, (player[i].pos.y + 14), 0xff000000, TRUE);
					DrawBox((player[i].pos.x - PLAYER_HPROD / 2), (player[i].pos.y + 9), temp_x, (player[i].pos.y + 13), 0xff00ffff, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				DrawCircle(player[i].pos.x, player[i].pos.y, 100, 0xff00ffff, FALSE);
				break;
			}

		}
	}

	switch (set_type)
	{
	case -1:
		break;
	case 0:
		DrawBox(GAME_SCREEN_RIGHT + 50 - 16 * 2, SCREEN_TOP + 40 - 16 * 2, GAME_SCREEN_RIGHT + 50 + 16 * 2, SCREEN_TOP + 40 + 16 * 2, COLOR_YELLOW, FALSE);
		break;

	case 1:
		DrawBox(GAME_SCREEN_RIGHT + 50 + 16 * 5 - 16 * 2, SCREEN_TOP + 40 - 16 * 2, GAME_SCREEN_RIGHT + 50 + 16 * 5 + 16 * 2, SCREEN_TOP + 40 + 16 * 2, COLOR_YELLOW, FALSE);
		break;

	case 2:
		DrawBox(GAME_SCREEN_RIGHT + 50 + 16 * 10 - 16 * 2, SCREEN_TOP + 40 - 16 * 2, GAME_SCREEN_RIGHT + 50 + 16 * 10 + 16 * 2, SCREEN_TOP + 40 + 16 * 2, COLOR_YELLOW, FALSE);
		break;
	}

	if (rect_count > 5)
	{
		rect_count = 0;
		rect1.x += 16;
		rect2.x += 12;
		rect3.x += 16;

		if (rect1.x > 32)rect1.x = 0;
		if (rect2.x > 12 * 7)rect2.x = 0;
		if (rect3.x > 16 * 7)rect3.x = 0;
	}


	asset.height = asset.width = 16;
	asset.texture = pobj1;
	temp = { GAME_SCREEN_RIGHT + 50, SCREEN_TOP + 40 };
	DrawRectRotaSprite(&temp, &rect1, 16, 4.0, 0.0, &asset, TRUE);
	asset.height = 12;
	asset.width = 12;
	asset.texture = pobj2;
	temp = { GAME_SCREEN_RIGHT + 50 + 16 * 5, SCREEN_TOP + 40 };
	DrawRectRotaSprite(&temp, &rect2, 12, 4.0, 0.0, &asset, TRUE);
	asset.height = asset.width = 16;
	asset.texture = pobj3;
	temp = { GAME_SCREEN_RIGHT + 50 + 16 * 10, SCREEN_TOP + 40 };
	DrawRectRotaSprite(&temp, &rect1, 16, 4.0, 0.0, &asset, TRUE);

	rect_count++;
}

int SearchPlayerObject(void)
{
	int i;
	for (i = 0; i < PLAYER_NUM; i++)
	{
		if (!player[i].flag)
		{
			return i;
		}
	}
	return -1;
}

BOOL SelectPlayerType(void)
{
	// 選択
	if (BoxCollision(mouse.x, mouse.y, 1, 1, GAME_SCREEN_RIGHT + 50, SCREEN_TOP + 40, 16 * 2, 16 * 2))
	{
		if (mouse.input == MOUSE_INPUT_LEFT)
		{
			set_tex = pobj1;
			set_type = 0;
			set_state = 0;
			return TRUE;
		}
	}
	else if (BoxCollision(mouse.x, mouse.y, 1, 1, GAME_SCREEN_RIGHT + 50 + 16 * 5, SCREEN_TOP + 40, 16 * 2, 16 * 2))
	{
		if (mouse.input == MOUSE_INPUT_LEFT)
		{
			set_tex = pobj2;
			set_type = 1;
			set_state = 1;
			return TRUE;
		}
	}
	else if (BoxCollision(mouse.x, mouse.y, 1, 1, GAME_SCREEN_RIGHT + 50 + 16 * 10, SCREEN_TOP + 40, 16 * 2, 16 * 2))
	{
		if (mouse.input == MOUSE_INPUT_LEFT)
		{
			set_tex = pobj3;
			set_type = 2;
			set_state = 2;
			return TRUE;
		}
	}

	return FALSE;
}

void DrawPlayerDescription(void)
{
	if (BoxCollision(mouse.x, mouse.y, 1, 1, GAME_SCREEN_RIGHT + 50, SCREEN_TOP + 40, 16 * 2, 16 * 2))
	{
		DrawBox(mouse.x - 2, mouse.y - 2, mouse.x + 182, mouse.y + 82, COLOR_RED, FALSE);
		DrawBox(mouse.x - 1, mouse.y - 1, mouse.x + 181, mouse.y + 81, COLOR_RED, FALSE);
		DrawBox(mouse.x, mouse.y, mouse.x + 180, mouse.y + 80, COLOR_BLACK, TRUE);
		DrawFormatString(mouse.x, mouse.y, COLOR_WHITE, "Type : 1\n直線ショット / 1 Way\n前方に対して撃ちだす\n消費マテリアル : ");
		DrawFormatString(mouse.x, mouse.y, COLOR_YELLOW, "\n\n\n                %3d",USE_MATERIAL_PLAYERTYPE0);
	}
	else if (BoxCollision(mouse.x, mouse.y, 1, 1, GAME_SCREEN_RIGHT + 50 + 16 * 5, SCREEN_TOP + 40, 16 * 2, 16 * 2))
	{
		DrawBox(mouse.x - 2, mouse.y - 2, mouse.x + 182, mouse.y + 82, COLOR_RED, FALSE);
		DrawBox(mouse.x - 1, mouse.y - 1, mouse.x + 181, mouse.y + 81, COLOR_RED, FALSE);
		DrawBox(mouse.x, mouse.y, mouse.x + 180, mouse.y + 80, COLOR_BLACK, TRUE);
		DrawFormatString(mouse.x, mouse.y, COLOR_WHITE, "Type : 2\n直線ショット / 2 Way\n前方に対して撃ちだす\n消費マテリアル : ");
		DrawFormatString(mouse.x, mouse.y, COLOR_YELLOW, "\n\n\n                %3d",USE_MATERIAL_PLAYERTYPE1);
	}
	else if (BoxCollision(mouse.x, mouse.y, 1, 1, GAME_SCREEN_RIGHT + 50 + 16 * 10, SCREEN_TOP + 40, 16 * 2, 16 * 2))
	{
		DrawBox(mouse.x - 2, mouse.y - 2, mouse.x + 202, mouse.y + 82, COLOR_RED, FALSE);
		DrawBox(mouse.x - 1, mouse.y - 1, mouse.x + 201, mouse.y + 81, COLOR_RED, FALSE);
		DrawBox(mouse.x, mouse.y, mouse.x + 200, mouse.y + 80, COLOR_BLACK, TRUE);
		DrawFormatString(mouse.x, mouse.y, COLOR_WHITE, "Type : 3\n防御サークル / 周囲\n対敵弾防御シールドを生成\n消費マテリアル : ");
		DrawFormatString(mouse.x, mouse.y, COLOR_YELLOW, "\n\n\n                %3d",USE_MATERIAL_PLAYERTYPE2);
	}
}

BOOL GetPlayerFlag(int i)
{
	return player[i].flag;
}
void SetPlayerFlagFalse(int i)
{
	player[i].flag = FALSE;
}
Vector2D GetPlayerPos(int i)
{
	return player[i].pos;
}
int GetPlayerType(int i)
{
	return player[i].type;
}

static void PlayerType0(int k, int mx, int my, HGRP tex, State state, State type)
{
	player[k].flag = TRUE;	// TRUE にする

							// 座標を Set
	player[k].pos.x = mx;
	player[k].pos.y = my;

	player[k].type = type;
	player[k].state = state;
	player[k].sprite.texture = tex;

	player[k].HP = PLAYER_HP;
}
static void PlayerType1(int k, int mx, int my, HGRP tex, State state, State type)
{
	player[k].flag = TRUE;	// TRUE にする

							// 座標を Set
	player[k].pos.x = mx;
	player[k].pos.y = my;

	player[k].type = type;
	player[k].state = state;
	player[k].sprite.texture = tex;

	player[k].HP = PLAYER_HP;
}
static void PlayerType2(int k, int mx, int my, HGRP tex, State state, State type)
{
	player[k].flag = TRUE;	// TRUE にする

							// 座標を Set
	player[k].pos.x = mx;
	player[k].pos.y = my;

	player[k].type = type;
	player[k].state = state;
	player[k].sprite.texture = tex;

	player[k].HP = PLAYER_HP * 2;
}

void SetPlayerObject(int mx, int my, HGRP tex, State state, State type)
{
	int k = SearchPlayerObject();	// FALSE の PlayerObject を探す

	if (k != (-1))		// FALSE の PlayerObject があったなら
	{
		switch (type)
		{
		case 0:
			PlayerType0(k, mx, my, tex, state, type);
			break;

		case 1:
			PlayerType1(k, mx, my, tex, state, type);
			break;

		case 2:
			PlayerType2(k, mx, my, tex, state, type);
			break;
		}
	}
}

void DrawPlayerType0(int count, int i)
{
	if (count > 5)
	{
		player[i].rect.x += 16;

		if (player[i].rect.x > 32)
		{
			player[i].rect.x = 0;
		}
	}
}
void DrawPlayerType1(int count, int i)
{
	if (count > 5)
	{
		player[i].rect.x += 12;

		if (player[i].rect.x > 12 * 7)
		{
			player[i].rect.x = 0;
		}
	}
}
void DrawPlayerType2(int count, int i)
{
	if (count > 5)
	{
		player[i].rect.x += 16;

		if (player[i].rect.x > 16 * 6)
		{
			player[i].rect.x = 0;
		}
	}
}

void PlayerDamage(int i, int damage)
{
	player[i].HP -= damage;
}

// Player Shot Function

void InitPlayerShot(void)
{
	int i, j;

	shot_tex = LoadGraph("Resources/Textures/PROTECT/player_shot.png");

	for (i = 0; i < PLAYER_NUM; i++)
	{
		for (j = 0; j < PLAYER_SHOT_NUM; j++)
		{
			player[i].shot[j].deg = 0;
			player[i].shot[j].rad = 0;
			player[i].shot[j].state = 0;
			player[i].shot[j].flag = FALSE;

			player[i].shot[j].pos.x = 0;
			player[i].shot[j].pos.y = 0;
			player[i].shot[j].vel.x = 0;
			player[i].shot[j].vel.y = 0;

			player[i].shot[j].spd.x = 0;
			player[i].shot[j].spd.y = 0;

			player[i].shot[j].sprite.texture = shot_tex;
			player[i].shot[j].sprite.height = player[i].shot[j].sprite.width = 12;
		}
	}
}
void UpdatePlayerShot(void)
{
	int i, j, k;

	for (i = 0; i < PLAYER_NUM; i++)
	{
		if (player[i].flag)
		{
			if (player[i].cnt > 10)
			{
				switch (player[i].type)
				{
				case 0:
				{
					if ((k = SearchPlayerShot(i)) != -1)
					{
						player[i].shot[k].flag = TRUE;

						player[i].shot[k].pos = player[i].pos;
						player[i].shot[k].vel.x = 0.0;
						player[i].shot[k].vel.y = 10.0;

						player[i].shot[k].spd.x = 0.0;
						player[i].shot[k].spd.y = -1.0;
					}
				}
				break;

				case 1:
				{
					if ((k = SearchPlayerShot(i)) != -1)
					{
						player[i].shot[k].flag = TRUE;

						player[i].shot[k].pos = player[i].pos;
						player[i].shot[k].rad = DEG_TO_RAD(110);

						player[i].shot[k].vel.x = cos(player[i].shot[k].rad) * 10;
						player[i].shot[k].vel.y = sin(player[i].shot[k].rad) * 10;

						player[i].shot[k].spd.x = 1.0;
						player[i].shot[k].spd.y = -1.0;
					}
					if ((k = SearchPlayerShot(i)) != -1)
					{
						player[i].shot[k].flag = TRUE;

						player[i].shot[k].pos = player[i].pos;
						player[i].shot[k].rad = DEG_TO_RAD(70);

						player[i].shot[k].vel.x = cos(player[i].shot[k].rad) * 10;
						player[i].shot[k].vel.y = sin(player[i].shot[k].rad) * 10;

						player[i].shot[k].spd.x = 1.0;
						player[i].shot[k].spd.y = -1.0;
					}
				}
				break;

				}
				player[i].cnt = 0;
			}
		}
	}

	for (i = 0; i < PLAYER_NUM; i++)
	{
		for (j = 0; j < PLAYER_SHOT_NUM; j++)
		{
			if (player[i].shot[j].flag)
			{
				player[i].shot[j].pos.x += player[i].shot[j].vel.x * player[i].shot[j].spd.x;
				player[i].shot[j].pos.y += player[i].shot[j].vel.y * player[i].shot[j].spd.y;

				if ((player[i].shot[j].pos.y < GAME_SCREEN_TOP - 20)||(player[i].shot[j].pos.x < GAME_SCREEN_LEFT - 20)
					|| (player[i].shot[j].pos.x > GAME_SCREEN_RIGHT + 20))
				{
					player[i].shot[j].flag = FALSE;
				}
			}
		}
	}
}
void RenderPlayerShot(int bright)
{
	int i, j;

	SetDrawBright(bright, bright, bright);
	for (i = 0; i < PLAYER_NUM; i++)
	{
		for (j = 0; j < PLAYER_SHOT_NUM; j++)
		{
			if (player[i].shot[j].flag)
			{
				DrawRotaSprite(&player[i].shot[j].pos, 1.0, 0.0, &player[i].shot[j].sprite, TRUE);
			}
		}
	}
}

int SearchPlayerShot(int i)
{
	int j;

	for (j = 0; j < PLAYER_SHOT_NUM; j++)
	{
		if (player[i].shot[j].flag == FALSE)
		{
			return j;
		}
	}
	return -1;
}

BOOL GetPlayerShotFlag(int i, int s)
{
	return player[i].shot[s].flag;
}
void SetPlayerShotFlagFalse(int i, int s)
{
	player[i].shot[s].flag = FALSE;
}
Vector2D GetPlayerShotPos(int i, int s)
{
	return player[i].shot[s].pos;
}

void PlayerDead(void)
{
	player_num -= 1;
}

// Material

void InitMaterial(void)
{
	material = INIT_MATERIAL;
}
void UpdateMaterial(void)
{

}
void RenderMaterial(int bright)
{
	SetDrawBright(bright, bright, bright);
	DrawFormatStringToHandle(GAME_SCREEN_RIGHT + 20, GAME_SCREEN_CENTER_Y + 40, COLOR_YELLOW, font_m, "Material : %d", material);
}

void AddMaterial(int add)
{
	material += add;
}

int GetPlayerNum(void)
{
	return player_num;
}
int GetMaterial(void)
{
	return material;
}