#include "Player.h"

// Private
void InitPlayerShotObject(void);
void CreatePlayerShot(void);		// Shot を撃つ
int SearchPlayerShot(void);			// Flag が FALSE の Shot を探す

// グローバル変数を extern したくないので static

static ObjectPlayer player;

// Player

void InitPlayerObject(void)
{
	player.flag = TRUE;					// 死んだら FALSE
	player.deg = player.rad = 0;		// アングル / deg, rad
	player.vel = player.spd = { 0,0 };	// とりあえず 0

	player.pos = { GAME_SCREEN_CENTER_X,GAME_SCREEN_CENTER_Y / 2 * 3 };	// 初期座標

	player.asset.texture = LoadGraph("Resources/Textures/PROTECT/Player.png");
	player.asset.width = player.asset.height = 28;

	InitPlayerShotObject();
}
void UpdatePlayerObject(void)
{
	// 初期座標で固定する
	Mouse mouse;
	GetMousePoint(&mouse.x, &mouse.y);

	player.pos.x = mouse.x;
	player.pos.y = mouse.y;

	if (player.pos.x < GAME_SCREEN_LEFT)player.pos.x = GAME_SCREEN_LEFT;
	if (player.pos.x > GAME_SCREEN_RIGHT)player.pos.x = GAME_SCREEN_RIGHT;
	if (player.pos.y < GAME_SCREEN_TOP)player.pos.y = GAME_SCREEN_TOP;
	if (player.pos.y > GAME_SCREEN_BOTTOM)player.pos.y = GAME_SCREEN_BOTTOM;

	UpdatePlayerShotObject();
}
void RenderPlayerObject(void)
{
	RenderPlayerShotObject();

	SetDrawBright(128, 0, 255);
	DrawRotaSprite(&player.pos, 3.0, 0.0, &player.asset, TRUE);
	SetDrawBright(255, 255, 255);
}

// Player Shot
void InitPlayerShotObject(void)
{
	int i = 0;

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		InitShot(&player.shot[i]);
		if (player.shot[i].asset.texture == NULL)
		{
			player.shot[i].asset.texture = LoadGraph("Resources/Textures/PROTECT/.png");
			player.shot[i].asset.height = player.shot[i].asset.width = PLAYER_SHOT_SIZE;
		}
	}
}
void UpdatePlayerShotObject(void)
{
	int sw = GetMouseInput();
	char key[256];
	static int cnt = 0;
	int i = 0;

	GetHitKeyStateAll(key);

	if (sw == MOUSE_INPUT_LEFT)
	{
		if (cnt % 5 == 0)
		{
			CreatePlayerShot();
		}
	}
	else if (key[KEY_INPUT_Z] != 0)
	{
		if (cnt % 5 == 0)
		{
			CreatePlayerShot();
		}
	}
	cnt++;

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		if (player.shot[i].flag)
		{
			player.shot[i].pos.y += player.shot[i].vel.y * player.shot[i].spd.y;

			if (GAME_SCREEN_TOP > player.shot[i].pos.y)
			{
				player.shot[i].flag = FALSE;
			}
		}
	}
}
void RenderPlayerShotObject(void)
{
	int i = 0;

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		if (player.shot[i].flag)
		{
			DrawRotaSprite(&player.shot[i].pos, 1.0, 0.0, &player.shot[i].asset, TRUE);
		}
	}
}

void CreatePlayerShot(void)
{
	int k = SearchPlayerShot();

	if (k != -1)
	{
		player.shot[k].flag = TRUE;
		player.shot[k].pos = player.pos;
		player.shot[k].vel.y = 10.0f;
		player.shot[k].spd.y = -1.0f;
		player.shot[k].state = 0;
	}
}

// Set / Get 

// Player の座標を得る
Vector2D GetPlayerPosition(void)
{
	return player.pos;
}

// Flag が FALSE の Shot を探す / error : -1 を返します
int SearchPlayerShot(void)
{
	int i;

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		if (player.shot[i].flag == FALSE)	// Flag が FALSE の Shot を見つけたら
		{
			return i;	// その Shot の 要素番号を return する
		}
	}
	return -1;	// FALSE の Shot が無ければ -1 を return する
}