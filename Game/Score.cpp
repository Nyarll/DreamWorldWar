#include "Score.h"
#include "PlayScene.h"
#include "GameObjectStruct.h"

#define FIRST_SCORE (2000)

int score;
int high_score;

HFNT font_m;

FILE *fp;

void InitScore(void)
{
	char buf[128];
	int c;

	static Flag skip_flag = FALSE;

	score = FIRST_SCORE;
	font_m = CreateFontToHandle("Algerian", 30, NULL);

	if (high_score == 0)
	{

		memset(buf, 0, sizeof(buf));

		fopen_s(&fp, "Resources/HighScore.dat", "r");

		while (1)
		{
			while (1)
			{
				c = fgetc(fp);

				if (c == '#')	// # の後の行はすべて読み飛ばす
				{
					while ((c = fgetc(fp)) != '\n');
					c = fgetc(fp);
				}

				{
					// 末尾ならループから抜ける
					if (c == EOF)
					{
						break;
					}
					// カンマか改行でないなら文字として読む
					if ((c != ',') && (c != '\n'))
					{
						strcat_s(buf, (const char*)&c);
					}
					// カンマか改行なら抜ける
					else
					{
						break;
					}
				}
			}
			if (c == EOF)
			{
				break;
			}
		}
		high_score = atoi(buf);

		memset(buf, 0, sizeof(buf));
		fclose(fp);
	}
}
void UpdateScore(void)
{

}
void RenderScore(int bright)
{
	SetDrawBright(bright, bright, bright);
	DrawFormatStringToHandle(GAME_SCREEN_RIGHT + 20, GAME_SCREEN_CENTER_Y, COLOR_WHITE, font_m, "Score    : %d", score);
	DrawFormatStringToHandle(GAME_SCREEN_RIGHT + 20, GAME_SCREEN_CENTER_Y - 40, COLOR_WHITE, font_m, "Level : %d", GetLevel());
	DrawFormatStringToHandle(GAME_SCREEN_RIGHT + 20, GAME_SCREEN_CENTER_Y - 120, COLOR_WHITE, font_m, "HighScore(level)\n-> %d", high_score);
}

void FinalScore(void)
{
	int c;

	if (GetLevel() > high_score)
	{
		fopen_s(&fp, "Resources/HighScore.dat", "w");
		fprintf_s(fp, "%d", GetLevel());
		fclose(fp);

		high_score = GetLevel();
	}
}

int GetScore(void)
{
	return score;
}
void AddScore(int add)
{
	score += add;
}

int GetHighScore(void)
{
	return high_score;
}