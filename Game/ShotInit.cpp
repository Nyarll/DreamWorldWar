#include "GameObjectStruct.h"

// ObjectShot �̏�����
void InitShot(ObjectShot* shot)
{
	shot->deg = shot->rad = 0;
	shot->state = shot->flag = FALSE;

	shot->pos = shot->vel = shot->spd = { 0,0 };

	shot->sprite.texture = TEXTURE_LOAD_MISSING;
}