#include "GameObjectStruct.h"

// Null ��`�悷�� / �����\������Ȃ��ꍇ������Â炢���ߎ���
void DrawNullSprite(const Vector2D* pos, const SpriteObject* asset, double ExRota);

// DrawRotaGraph����� 
// (Vector2D* pos, Rota, rad, Asset* asset, TransFlag)
// �O���t�B�b�N�n���h����NULL�Ȃ�NULL��\��
void DrawRotaSprite(const Vector2D* pos, double ExRota, double rad, const SpriteObject* asset, BOOL TransFlag)
{
	Box box;
	if (asset->texture != TEXTURE_LOAD_MISSING)	// �摜���ǂݍ��߂Ă����
	{
		// �ʏ�̕`��
		DrawRotaGraph(pos->x, pos->y, ExRota, rad, asset->texture, TRUE);
	}
	else // �ǂݍ��߂Ă��Ȃ����
	{
		// Null ��\��
		DrawNullSprite(pos, asset, ExRota);
	}
}

// DrawRectRotaGraph����� 
// (Vector2D* pos, Rect* rect, int size_x, double Rota, rad, Asset* asset, TransFlag)
// �O���t�B�b�N�n���h����NULL�Ȃ�NULL��\��
void DrawRectRotaSprite(const Vector2D* pos,const Rect* rect,int size_x, double ExRota, double rad, const SpriteObject* asset, BOOL TransFlag)
{
	Box box;
	if (asset->texture != TEXTURE_LOAD_MISSING)	// �摜���ǂݍ��߂Ă����
	{
		// �ʏ�`��
		DrawRectRotaGraph(pos->x, pos->y, rect->x, rect->y, size_x, asset->height, ExRota, rad, asset->texture, TransFlag);
	}
	else // �ǂݍ��߂Ă��Ȃ����
	{
		// Null ��\��
		DrawNullSprite(pos, asset, ExRota);
	}
}

// DrawBox�Ȃǂ��g�p����Null��\��
// (Vector2D* pos, Asset* asset, Rota)
void DrawNullSprite(const Vector2D* pos, const SpriteObject* asset, double ExRota)
{
	Box box;	// �摜�T�C�Y�Ɠ�����`�f�[�^�i�[�p

	// �摜�T�C�Y�Ɠ�����`�f�[�^���i�[
	box.x1 = pos->x - (asset->width / 2) * ExRota;
	box.x2 = pos->x + (asset->width / 2) * ExRota;
	box.y1 = pos->y - (asset->height / 2) * ExRota;
	box.y2 = pos->y + (asset->height / 2) * ExRota;

	SetDrawBright(255, 255, 255);	// �P�x���ő��
	// NULL �̃e�N�X�`����\��
	DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_FUCHSIA, TRUE);
	DrawBoxAA(box.x1, box.y1, pos->x, pos->y, COLOR_BLACK, TRUE);
	DrawBoxAA(pos->x, pos->y, box.x2, box.y2, COLOR_BLACK, TRUE);
	DrawCircleAA(pos->x, pos->y, (asset->width / 2) * ExRota, 100, COLOR_WHITE, FALSE, 1);
	DrawLine(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, 1);
	DrawLine(box.x2, box.y1, box.x1, box.y2, COLOR_WHITE, 1);
	DrawBoxAA(box.x1, box.y1, box.x2, box.y2, COLOR_WHITE, FALSE, 1.0f);
}