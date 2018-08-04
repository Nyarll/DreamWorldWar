#pragma once

// <System>
#define TEXTURE_LOAD_MISSING (-1)

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
#define GAME_SCREEN_LEFT	(SCREEN_LEFT)
#define GAME_SCREEN_RIGHT	(SCREEN_RIGHT - 540)
#define GAME_SCREEN_TOP		(SCREEN_TOP)
#define GAME_SCREEN_BOTTOM	(SCREEN_BOTTOM)

#define GAME_SCREEN_CENTER_X	(GAME_SCREEN_RIGHT / 2)
#define GAME_SCREEN_CENTER_Y	(GAME_SCREEN_BOTTOM / 2)

// <Player>
#define PLAYER_SPEED 2
#define PLAYER_SHOT_NUM 60

// <Enemy>
#define ENEMY_SHOT_NUM 256