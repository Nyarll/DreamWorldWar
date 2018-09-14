#include "Back.h"
#include "GameObjectStruct.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

// <Map Data>
#define MAP_SIZE (2048)
#define MAP_ROTA (1.0)

static Vector2D pos1, pos2;
static SpriteObject asset;		// �e�N�X�`���֌W
static Rect rect1, rect2;		// �e�N�X�`���̍�����W

static Mouse mouse;

void InitBack(void)
{
	srand((unsigned int)time(NULL));

	// �������W�̃Z�b�g
	pos1 = { GAME_SCREEN_CENTER_X,GAME_SCREEN_CENTER_Y };
	pos2 = { GAME_SCREEN_CENTER_X,GAME_SCREEN_CENTER_Y - MAP_SIZE * MAP_ROTA };
	
	// �摜�f�[�^�̓ǂݍ���
	asset.texture = LoadGraph("Resources/Textures/PROTECT/Map.png");

	// �摜�T�C�Y
	asset.height = MAP_SIZE;
	asset.width = MAP_SIZE;

	//�؂���ꏊ�������_���Ō���
	rect1.x = rand() % (MAP_SIZE - (GAME_SCREEN_RIGHT));;
	rect1.y = 0;
	
	rect2.x = rand() % (MAP_SIZE - (GAME_SCREEN_RIGHT));
	rect2.y = 0;
}
void UpdateBack(void)
{
	int move_amount_y = 1.0f;	// Map �� 1 pixel ���ړ�������p

	// ScreenBottom �� Map�̈�ԏオ���B������, �Ăу����_���Ő؂���
	{
		if (pos1.y > (GAME_SCREEN_CENTER_Y + MAP_SIZE * MAP_ROTA))
		{
			pos1.y = pos2.y - MAP_SIZE * MAP_ROTA;
			rect1.x = rand() % (MAP_SIZE - (GAME_SCREEN_RIGHT));
		}
		if (pos1.y < (GAME_SCREEN_CENTER_Y - MAP_SIZE * MAP_ROTA))
		{
			pos1.y = pos2.y + MAP_SIZE * MAP_ROTA;
			rect1.x = rand() % (MAP_SIZE - (GAME_SCREEN_RIGHT));
		}
		if (pos2.y > (GAME_SCREEN_CENTER_Y + MAP_SIZE * MAP_ROTA))
		{
			pos2.y = pos1.y - MAP_SIZE * MAP_ROTA;
			rect2.x = rand() % (MAP_SIZE - (GAME_SCREEN_RIGHT));
		}
		if (pos2.y < (GAME_SCREEN_CENTER_Y - MAP_SIZE * MAP_ROTA))
		{
			pos2.y = pos1.y + MAP_SIZE * MAP_ROTA;
			rect2.x = rand() % (MAP_SIZE - (GAME_SCREEN_RIGHT));
		}
	}
	// �ړ�
	pos1.y += move_amount_y;
	pos2.y += move_amount_y;
}
void RenderBack(int bright)
{
	SetDrawBright(bright, 0, bright);
	DrawRectRotaSprite(&pos1, &rect1, GAME_SCREEN_RIGHT, MAP_ROTA, 0.0, &asset, TRUE);
	DrawRectRotaSprite(&pos2, &rect2, GAME_SCREEN_RIGHT, MAP_ROTA, 0.0, &asset, TRUE);
	SetDrawBright(bright, bright, bright);
}