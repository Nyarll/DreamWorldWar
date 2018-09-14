#include "GameObjectStruct.h"

// Null を描画する / 何も表示されない場合分かりづらいため実装
void DrawNullSprite(const Vector2D* pos, const SpriteObject* asset, double ExRota);

// DrawRotaGraphを内蔵 
// (Vector2D* pos, Rota, rad, Asset* asset, TransFlag)
// グラフィックハンドルがNULLならNULLを表示
void DrawRotaSprite(const Vector2D* pos, double ExRota, double rad, const SpriteObject* asset, BOOL TransFlag)
{
	Box box;
	if (asset->texture != TEXTURE_LOAD_MISSING)	// 画像が読み込めていれば
	{
		// 通常の描画
		DrawRotaGraph(pos->x, pos->y, ExRota, rad, asset->texture, TRUE);
	}
	else // 読み込めていなければ
	{
		// Null を表示
		DrawNullSprite(pos, asset, ExRota);
	}
}

// DrawRectRotaGraphを内蔵 
// (Vector2D* pos, Rect* rect, int size_x, double Rota, rad, Asset* asset, TransFlag)
// グラフィックハンドルがNULLならNULLを表示
void DrawRectRotaSprite(const Vector2D* pos,const Rect* rect,int size_x, double ExRota, double rad, const SpriteObject* asset, BOOL TransFlag)
{
	Box box;
	if (asset->texture != TEXTURE_LOAD_MISSING)	// 画像が読み込めていれば
	{
		// 通常描画
		DrawRectRotaGraph(pos->x, pos->y, rect->x, rect->y, size_x, asset->height, ExRota, rad, asset->texture, TransFlag);
	}
	else // 読み込めていなければ
	{
		// Null を表示
		DrawNullSprite(pos, asset, ExRota);
	}
}

// DrawBoxなどを使用してNullを表示
// (Vector2D* pos, Asset* asset, Rota)
void DrawNullSprite(const Vector2D* pos, const SpriteObject* asset, double ExRota)
{
	Box box;	// 画像サイズと同じ矩形データ格納用

	// 画像サイズと同じ矩形データを格納
	box.x1 = pos->x - (asset->width / 2) * ExRota;
	box.x2 = pos->x + (asset->width / 2) * ExRota;
	box.y1 = pos->y - (asset->height / 2) * ExRota;
	box.y2 = pos->y + (asset->height / 2) * ExRota;

	SetDrawBright(255, 255, 255);	// 輝度を最大に
	// NULL のテクスチャを表示
	DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_FUCHSIA, TRUE);
	DrawBoxAA(box.x1, box.y1, pos->x, pos->y, COLOR_BLACK, TRUE);
	DrawBoxAA(pos->x, pos->y, box.x2, box.y2, COLOR_BLACK, TRUE);
	DrawCircleAA(pos->x, pos->y, (asset->width / 2) * ExRota, 100, COLOR_WHITE, FALSE, 1);
	DrawLine(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, 1);
	DrawLine(box.x2, box.y1, box.x1, box.y2, COLOR_WHITE, 1);
	DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, FALSE, 1.0f);
}