#include "GameObjectStruct.h"

// ObjectShot ‚Ì‰Šú‰»
void InitShot(ObjectShot* shot)
{
	shot->deg = shot->rad = 0;
	shot->state = shot->flag = FALSE;

	shot->pos = shot->vel = shot->spd = { 0,0 };

	shot->texture = NULL;

}