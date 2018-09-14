#include "Sound.h"
#include "GameObjectStruct.h"

static ObjectSound sound[SOUND_NUM];

void InitSound(void)
{
	int i;

	sound[SoundGameStart].sound_handle = LoadSoundMem("Resources/Sound/PROTECT/GameStart.wav");
	sound[SoundMusic].sound_handle = LoadSoundMem("Resources/Sound/PROTECT/game_music.wav");
	sound[SoundKeyInput].sound_handle = LoadSoundMem("Resources/Sound/PROTECT/KeyInput.wav");

	for (i = 0; i < SOUND_NUM; i++)
	{
		sound[i].sound_flag = FALSE;
	}
}
void SetSound(SoundName sound_name)
{
	static int bgm_count = 0;
	static int input_count = 0;

	switch (sound_name)
	{
	case SoundGameStart:
	{
		PlaySoundMem(sound[SoundGameStart].sound_handle, DX_PLAYTYPE_BACK);
	}
	break;

	case SoundMusic:
	{
		if (bgm_count <= 0)
		{
			bgm_count = 50;
			StopSoundMem(sound[SoundMusic].sound_handle);
			PlaySoundMem(sound[SoundMusic].sound_handle, DX_PLAYTYPE_LOOP);
		}
		bgm_count--;
	}
	break;

	case SoundKeyInput:
	{
		if (input_count == 0)
		{
			PlaySoundMem(sound[SoundKeyInput].sound_handle, DX_PLAYTYPE_BACK);
		}
		else if (input_count > 30)
		{
			StopSoundMem(sound[SoundMusic].sound_handle);
		}
	}
	break;

	default:
		break;
	}
}
void StopSound(SoundName sound_name)
{
	switch (sound_name)
	{
	case SoundGameStart:
	{
		StopSoundMem(sound[SoundGameStart].sound_handle);
	}
	break;

	case SoundMusic:
	{
		StopSoundMem(sound[SoundMusic].sound_handle);
	}
	break;

	default:
		break;
	}
}