#pragma once


#define USE_MATERIAL_PLAYERTYPE0 (100)
#define USE_MATERIAL_PLAYERTYPE1 (150)
#define USE_MATERIAL_PLAYERTYPE2 (200)

// Public

void InitPlayerObject(void);
void UpdatePlayerObject(void);
void RenderPlayerObject(int bright);

void SetPlayerObject(int mx, int my, HGRP tex, State state, State type);

void DrawPlayerDescription(void);

BOOL GetPlayerFlag(int i);
void SetPlayerFlagFalse(int i);
Vector2D GetPlayerPos(int i);
int GetPlayerType(int i);

void PlayerDamage(int i,int damage);
void PlayerDead(void);

// shot
void InitPlayerShot(void);
void UpdatePlayerShot(void);
void RenderPlayerShot(int bright);

BOOL GetPlayerShotFlag(int i, int s);
void SetPlayerShotFlagFalse(int i, int s);
Vector2D GetPlayerShotPos(int i, int s);

// Material

void InitMaterial(void);
void UpdateMaterial(void);
void RenderMaterial(int bright);

void AddMaterial(int add);

int GetPlayerNum(void);
int GetMaterial(void);

extern HFNT font_m;