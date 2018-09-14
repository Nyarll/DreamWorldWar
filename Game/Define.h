#pragma once

// <System>
#define TEXTURE_LOAD_MISSING (-1)				// 画像のロードに失敗

// <画面> 
#define SCREEN_WIDTH    (1080)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (800)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

// <ゲーム画面>
#define GAME_SCREEN_LEFT	(SCREEN_LEFT)			// ゲーム画面の左端
#define GAME_SCREEN_RIGHT	(SCREEN_RIGHT - 400)	// ゲーム画面の右端
#define GAME_SCREEN_TOP		(SCREEN_TOP)			// ゲーム画面の上端
#define GAME_SCREEN_BOTTOM	(SCREEN_BOTTOM)			// ゲーム画面の下端

#define GAME_SCREEN_CENTER_X	(GAME_SCREEN_RIGHT / 2)		// ゲーム画面の中央(X座標)
#define GAME_SCREEN_CENTER_Y	(GAME_SCREEN_BOTTOM / 2)	// ゲーム画面の中央(Y座標)

// <Player>
#define PLAYER_NUM 128			// Set できる Player の数

#define PLAYER_SHOT_NUM 128		// Set した Player の弾数

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