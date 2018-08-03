#include "Player.h"

// グローバル変数を extern したくないので static
static ObjectPlayer player;

void InitPlayerObject(void)
{
	int i = 0;

	player.flag = TRUE;					// 死んだら FALSE
	player.deg = player.rad = 0;		// アングル / deg, rad
	player.vel = player.spd = { 0,0 };	// とりあえず 0

	player.pos = { GAME_SCREEN_CENTER_X,GAME_SCREEN_CENTER_Y };	// 初期座標

	for (i = 0; i < PLAYER_SHOT_NUM; i++)
	{
		InitShot(&player.shot[i]);
	}

}
void UpdatePlayerObject(void)
{

}
void RenderPlayerObject(void)
{

}