#include "Player.h"

// �O���[�o���ϐ��� extern �������Ȃ��̂� static
static ObjectPlayer player;

void InitPlayerObject(void)
{
	int i = 0;

	player.flag = TRUE;					// ���񂾂� FALSE
	player.deg = player.rad = 0;		// �A���O�� / deg, rad
	player.vel = player.spd = { 0,0 };	// �Ƃ肠���� 0

	player.pos = { GAME_SCREEN_CENTER_X,GAME_SCREEN_CENTER_Y };	// �������W

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