#pragma once

#include "GameObjectStruct.h"

#define PLAYER_SHOT_SIZE 20

// Public
// ��{�I�Ȋ֐�

void InitPlayerObject(void);
void UpdatePlayerObject(void);
void RenderPlayerObject(void);

void UpdatePlayerShotObject(void);
void RenderPlayerShotObject(void);

// Get / Set 

Vector2D GetPlayerPosition(void);	// Player �̍��W�𓾂�