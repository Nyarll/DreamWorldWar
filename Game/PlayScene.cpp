#include "PlayScene.h"
#include "Back.h"
#include "Player.h"

void InitPlayScene(void)
{
	SetMouseDispFlag(FALSE);
	InitBack();
	InitPlayerObject();
}
void UpdatePlayScene(void)
{
	UpdateBack();
	UpdatePlayerObject();
}
void RenderPlayScene(void)
{
	RenderBack();
	RenderPlayerObject();
}