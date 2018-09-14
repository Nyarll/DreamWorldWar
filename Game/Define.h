#pragma once

// <System>
#define TEXTURE_LOAD_MISSING (-1)				// �摜�̃��[�h�Ɏ��s

// <���> 
#define SCREEN_WIDTH    (1080)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (800)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

// <�Q�[�����>
#define GAME_SCREEN_LEFT	(SCREEN_LEFT)			// �Q�[����ʂ̍��[
#define GAME_SCREEN_RIGHT	(SCREEN_RIGHT - 400)	// �Q�[����ʂ̉E�[
#define GAME_SCREEN_TOP		(SCREEN_TOP)			// �Q�[����ʂ̏�[
#define GAME_SCREEN_BOTTOM	(SCREEN_BOTTOM)			// �Q�[����ʂ̉��[

#define GAME_SCREEN_CENTER_X	(GAME_SCREEN_RIGHT / 2)		// �Q�[����ʂ̒���(X���W)
#define GAME_SCREEN_CENTER_Y	(GAME_SCREEN_BOTTOM / 2)	// �Q�[����ʂ̒���(Y���W)

// <Player>
#define PLAYER_NUM 128			// Set �ł��� Player �̐�

#define PLAYER_SHOT_NUM 128		// Set ���� Player �̒e��

// <Enemy>
#define ENEMY_SHOT_NUM 256

// <Sound>
typedef enum
{
	SoundGameStart,
	SoundMusic,
	SoundKeyInput,
	SoundNum
}SoundName;

#define SOUND_NUM (SoundNum)