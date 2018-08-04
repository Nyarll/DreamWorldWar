#include "GameObjectStruct.h"

void DrawRotaSprite(const Vector2D* pos, double ExRota, double rad, const Asset* asset, BOOL TransFlag)
{
	Box box;
	if (asset->texture != TEXTURE_LOAD_MISSING)
	{
		DrawRotaGraph(pos->x, pos->y, ExRota, rad, asset->texture, TRUE);
	}
	else
	{
		box.x1 = pos->x - (asset->width / 2) * ExRota;
		box.x2 = pos->x + (asset->width / 2) * ExRota;
		box.y1 = pos->y - (asset->height / 2) * ExRota;
		box.y2 = pos->y + (asset->height / 2) * ExRota;

		// NULL のテクスチャを表示
		DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_FUCHSIA, TRUE);
		DrawBoxAA(box.x1, box.y1, pos->x, pos->y, COLOR_BLACK, TRUE);
		DrawBoxAA(pos->x, pos->y, box.x2, box.y2, COLOR_BLACK, TRUE);
		DrawCircleAA(pos->x, pos->y, (asset->width / 2) * ExRota,100, COLOR_WHITE, FALSE,1);
		DrawLine(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, 1);
		DrawLine(box.x2, box.y1, box.x1, box.y2, COLOR_WHITE, 1);
		DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, FALSE, 1.0f);
	}
}

void DrawRectRotaSprite(const Vector2D* pos,const Rect* rect,int size_x, double ExRota, double rad, const Asset* asset, BOOL TransFlag)
{
	Box box;
	if (asset->texture != TEXTURE_LOAD_MISSING)
	{
		DrawRectRotaGraph(pos->x, pos->y, rect->x, rect->y, size_x, asset->height, ExRota, rad, asset->texture, TransFlag);
	}
	else
	{
		box.x1 = pos->x - (asset->width / 2) * ExRota;
		box.x2 = pos->x + (asset->width / 2) * ExRota;
		box.y1 = pos->y - (asset->height / 2) * ExRota;
		box.y2 = pos->y + (asset->height / 2) * ExRota;

		// NULL のテクスチャを表示
		DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_FUCHSIA, TRUE);
		DrawBoxAA(box.x1, box.y1, pos->x, pos->y, COLOR_BLACK, TRUE);
		DrawBoxAA(pos->x, pos->y, box.x2, box.y2, COLOR_BLACK, TRUE);
		DrawCircleAA(pos->x, pos->y, (asset->width / 2) * ExRota,100, COLOR_WHITE, FALSE, 1);
		DrawLine(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, 1);
		DrawLine(box.x2, box.y1, box.x1, box.y2, COLOR_WHITE, 1);
		DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, FALSE, 1.0f);
	}
}