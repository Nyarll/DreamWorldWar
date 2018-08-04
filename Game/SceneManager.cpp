#include "SceneManager.h"
#include "PlayScene.h"

typedef struct MouseCursor_s
{
	Mouse m_pos;
	Vector2D pos;
	Asset asset;
}MouseCursor;

// �O���[�o���ϐ�

static Scene active_scene;
static Scene next_scene;

static int scene_count;

static HGRP logo_handle;

static 	MouseCursor mouse;	// �}�E�X�J�[�\��

void RenderMouseCursor(void);	// �}�E�X�J�[�\���̕`��


// �V�[���̏�����
void InitScene(void)
{
	active_scene = SCENE_NONE;
	next_scene = SCENE_PLAY;

	scene_count = 0;

	InitPlayScene();

	if (next_scene != SCENE_NONE)
	{
		active_scene = next_scene;
		next_scene = SCENE_TITLE;
	}

	mouse.asset.texture = LoadGraph("Resources/Textures/PROTECT/MouseCursor.png");
	mouse.asset.width = mouse.asset.height = 14;
}

// �V�[���̍X�V
void UpdateScene(void)
{
	switch (active_scene)
	{
	case SCENE_LOGO:
		break;

	case SCENE_TITLE:
		break;

	case SCENE_PLAY:
		UpdatePlayScene();
		break;

	case SCENE_RESULT:
		break;
	}
}

// �V�[���̕`��
void RenderScene(void)
{
	static int cnt = 0;
	switch (active_scene)
	{
	case SCENE_LOGO:
		break;

	case SCENE_TITLE:
		if ((cnt % 80) / 40)
		{
			SetFontSize(30);
			DrawFormatString(SCREEN_CENTER_X - 140, SCREEN_CENTER_Y / 2 * 3, COLOR_RED, "Push to SPACE KEY !");
		}
		cnt++;
		break;

	case SCENE_PLAY:
		if (cnt != 0)
		{
			cnt = 0;
		}
		RenderPlayScene();
		break;

	case SCENE_RESULT:
		break;
	}
	RenderMouseCursor();
}


// �V�[���̏I������
void FinalScene(void)
{

}

// �}�E�X�J�[�\���̕`��
void RenderMouseCursor(void)
{
	GetMousePoint(&mouse.m_pos.x, &mouse.m_pos.y);

	mouse.pos.x = (float)mouse.m_pos.x;
	mouse.pos.y = (float)mouse.m_pos.y;

	DrawRotaSprite(&mouse.pos, 2.0, 0.0, &mouse.asset, TRUE);
}