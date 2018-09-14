#include "SceneManager.h"
#include "PlayScene.h"
#include "Score.h"
#include "Player.h"
#include "Sound.h"


typedef struct MouseCursor_s
{
	Mouse m_pos;
	Vector2D pos;
	SpriteObject asset;
}MouseCursor;

// グローバル変数

static char key[256];
static char key_old[256];

static Scene active_scene;
static Scene next_scene;

static int scene_count;
static int game_startcount = 0;

static HGRP logo_handle;
static HGRP title_handle;

static UINT quit_color;
static UINT go_title_color;
static int bright = 255;
static Flag pause_flag = FALSE;
static Flag go_title_flag = FALSE;
static Flag blackout_flag = FALSE;

static HFNT font;

static 	MouseCursor mouse;	// マウスカーソル

void UpdatePause(void);
void RenderPause(void);

void RenderMouseCursor(void);	// マウスカーソルの描画


// シーンの初期化
void InitScene(void)
{
	active_scene = SCENE_NONE;
	next_scene = SCENE_LOGO;

	scene_count = 0;

	InitPlayScene();
	InitSound();

	if (next_scene != SCENE_NONE)
	{
		active_scene = next_scene;
		next_scene = SCENE_TITLE;
	}

	mouse.asset.texture = LoadGraph("Resources/Textures/PROTECT/MouseCursor.png");
	mouse.asset.width = mouse.asset.height = 14;

	pause_flag = FALSE;
	font = CreateFontToHandle("Algerian", 80, NULL);
	quit_color = COLOR_WHITE;
	go_title_color = COLOR_WHITE;

	title_handle = LoadGraph("Resources/Textures/PROTECT/Title_logo.png");
}

// シーンの更新
void UpdateScene(void)
{
	static int input = 0, input_old = 0;
	GetHitKeyStateAll(key);
	input = CheckHitKeyAll();

	if ((input != 0) && (input_old == 0))
	{
		SetSound(SoundKeyInput);
	}

	if (!pause_flag)
	{
		switch (active_scene)
		{
		case SCENE_LOGO:
			StopSound(SoundMusic);
			if (FALSE == DrawLogo("Resources/Textures/PROTECT/MyLogo_1080_800.png"))
			{
				active_scene = next_scene;
				next_scene = SCENE_PLAY;
			}
			if ((key[KEY_INPUT_SPACE] == 1) && (key_old[KEY_INPUT_SPACE] == 0))
			{
				active_scene = next_scene;
				next_scene = SCENE_PLAY;
			}
			break;

		case SCENE_TITLE:
			StopSound(SoundMusic);
			if ((key[KEY_INPUT_SPACE] == 1) && (key_old[KEY_INPUT_SPACE] == 0))
			{
				InitPlayScene();
				active_scene = next_scene;
				next_scene = SCENE_RESULT;
				game_startcount = 0;
			}
			break;

		case SCENE_PLAY:
			UpdatePlayScene();
			if (game_startcount < 400)
			{
				if (game_startcount == 0)
				{
					SetSound(SoundGameStart);
				}
				game_startcount++;
			}
			else
			{
				StopSound(SoundGameStart);
				SetSound(SoundMusic);
			}

			if ((GetScore() <= 0) || ((GetPlayerNum() == 0) && (GetMaterial() == 0)))
			{
				active_scene = next_scene;
				next_scene = SCENE_TITLE;
			}
			break;

		case SCENE_RESULT:
			StopSound(SoundMusic);
			if ((key[KEY_INPUT_SPACE] == 1) && (key_old[KEY_INPUT_SPACE] == 0))
			{
				active_scene = next_scene;
				next_scene = SCENE_PLAY;
				FinalScore();
			}
			break;
		}
	}
	UpdatePause();
	GetHitKeyStateAll(key_old);
	input_old = CheckHitKeyAll();
}

// シーンの描画
void RenderScene(void)
{
	static int cnt = 0;

	switch (active_scene)
	{
	case SCENE_LOGO:
		break;

	case SCENE_TITLE:
		DrawGraph(0, 0, title_handle, TRUE);
		if ((cnt % 80) / 40)
		{
			SetFontSize(30);
			DrawFormatStringToHandle(SCREEN_CENTER_X - 80 * 6, SCREEN_CENTER_Y / 2 * 3, COLOR_RED, font, "Push to SPACE KEY !");
		}
		cnt++;
		break;

	case SCENE_PLAY:
		if (cnt != 0)
		{
			SetFontSize(16);
			cnt = 0;
		}
		RenderPlayScene(bright);
		break;

	case SCENE_RESULT:
		DrawFormatStringToHandle(SCREEN_CENTER_X - 80 * 6, SCREEN_CENTER_Y - 80, COLOR_WHITE, font, "HighScore level %d",GetHighScore());
		DrawFormatStringToHandle(SCREEN_CENTER_X - 80 * 4, SCREEN_CENTER_Y + 80, COLOR_YELLOW, font, "your Level %d", GetLevel());
		DrawFormatString(SCREEN_CENTER_X - 4 * (sizeof("Push to [SPACE] Key !")), SCREEN_CENTER_Y + 300, 0xff00ffff, "Push to [SPACE] Key !");
		break;
	}

	if (pause_flag)
	{
		RenderPause();
	}

	RenderMouseCursor();
}


// シーンの終了処理
void FinalScene(void)
{

}



void UpdatePause(void)
{
	static int go_title_cnt = 255;

	quit_color = COLOR_WHITE;
	go_title_color = COLOR_WHITE;

	if (go_title_flag == FALSE)
	{
		if ((key[KEY_INPUT_ESCAPE] != 0) && (key_old[KEY_INPUT_ESCAPE] == 0) &&
			(pause_flag == FALSE))
		{
			pause_flag = TRUE;
		}
		else if ((key[KEY_INPUT_ESCAPE] != 0) && (key_old[KEY_INPUT_ESCAPE] == 0) &&
			(pause_flag == TRUE))
		{
			pause_flag = FALSE;
		}

		if (pause_flag)
		{
			if (BoxCollision(SCREEN_CENTER_X, SCREEN_CENTER_Y / 2 + 40, 100, 40, mouse.pos.x, mouse.pos.y, 1, 1))
			{
				quit_color = COLOR_YELLOW;
				if (MOUSE_INPUT_LEFT == GetMouseInput())
				{
					PostQuitMessage(0);
				}
			}

			if (BoxCollision(SCREEN_CENTER_X, (SCREEN_CENTER_Y / 2) + 200, 130, 40, mouse.pos.x, mouse.pos.y, 1, 1))
			{
				go_title_color = COLOR_YELLOW;
				if (MOUSE_INPUT_LEFT == GetMouseInput())
				{
					go_title_flag = TRUE;
				}
			}
		}
	}
	else
	{
		if (blackout_flag)
		{
			go_title_cnt += 5;
			if (go_title_cnt >= 255)
			{
				go_title_cnt = 255;
				pause_flag = FALSE;
				blackout_flag = FALSE;
				go_title_flag = FALSE;
			}
		}
		else
		{
			go_title_cnt -= 5;
			if (go_title_cnt <= 0)
			{
				blackout_flag = TRUE;
				active_scene = SCENE_TITLE;
				next_scene = SCENE_PLAY;
			}
		}
	}
}
void RenderPause(void)
{
	if (go_title_flag)
	{
		if (blackout_flag)
		{
			bright += 5;
		}
		else
		{
			bright -= 5;
		}
		SetDrawBright(bright, bright, bright);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawFormatStringToHandle(SCREEN_CENTER_X - 100, SCREEN_CENTER_Y / 2, quit_color, font, "Quit");
		DrawFormatStringToHandle(SCREEN_CENTER_X - 125, SCREEN_CENTER_Y / 2 + 160, go_title_color, font, "Title");
	}

}


// マウスカーソルの描画
void RenderMouseCursor(void)
{
	GetMousePoint(&mouse.m_pos.x, &mouse.m_pos.y);

	mouse.pos.x = (float)mouse.m_pos.x;
	mouse.pos.y = (float)mouse.m_pos.y;

	if ((mouse.pos.y < SCREEN_TOP) || (mouse.pos.y > SCREEN_BOTTOM) ||
		(mouse.pos.x < SCREEN_LEFT) || (mouse.pos.x > SCREEN_RIGHT))
	{
		SetMouseDispFlag(TRUE);
	}
	else
	{
		SetMouseDispFlag(FALSE);
	}
	/**
	if ((mouse.pos.x < GAME_SCREEN_RIGHT) && (mouse.pos.x > GAME_SCREEN_LEFT) && (!pause_flag))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
	/**/
	DrawRotaSprite(&mouse.pos, 2.0, 0.0, &mouse.asset, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}