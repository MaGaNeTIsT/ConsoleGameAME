#include "MusicLib.h"
#include "ConioEx.h"

MusicInfo SoundMainMenu;
MusicInfo SoundTutor;
MusicInfo SoundStage1;
MusicInfo SoundRain;

MusicInfo SoundMainMap;
MusicInfo SoundJump;
MusicInfo SoundTeleport;
MusicInfo SoundCheckPoint;
MusicInfo SoundHurt;
MusicInfo SoundClear;

void InitSoundFile(void)
{
	SoundMainMenu.MusicAddress = "./MainMenu.mp3";
	SoundMainMenu.handle = OpenSound(SoundMainMenu.MusicAddress);
	SoundMainMenu.bIfRepeat = 1;

	SoundTutor.MusicAddress = "./Tutor.mp3";
	SoundTutor.handle = OpenSound(SoundTutor.MusicAddress);
	SoundTutor.bIfRepeat = 1;

	SoundStage1.MusicAddress = "./Stage1.mp3";
	SoundStage1.handle = OpenSound(SoundStage1.MusicAddress);
	SoundStage1.bIfRepeat = 1;

	SoundRain.MusicAddress = "./Rain.mp3";
	SoundRain.handle = OpenSound(SoundRain.MusicAddress);
	SoundRain.bIfRepeat = 1;
	


	SoundMainMap.MusicAddress = "./MainMap.mp3";
	SoundMainMap.handle = OpenSound(SoundMainMap.MusicAddress);
	SoundMainMap.bIfRepeat = 0;

	SoundJump.MusicAddress = "./Jump.mp3";
	SoundJump.handle = OpenSound(SoundJump.MusicAddress);
	SoundJump.bIfRepeat = 0;

	SoundTeleport.MusicAddress = "./Teleport.mp3";
	SoundTeleport.handle = OpenSound(SoundTeleport.MusicAddress);
	SoundTeleport.bIfRepeat = 0;

	SoundCheckPoint.MusicAddress = "./CheckPoint.mp3";
	SoundCheckPoint.handle = OpenSound(SoundCheckPoint.MusicAddress);
	SoundCheckPoint.bIfRepeat = 0;

	SoundHurt.MusicAddress = "./Hurt.mp3";
	SoundHurt.handle = OpenSound(SoundHurt.MusicAddress);
	SoundHurt.bIfRepeat = 0;

	SoundClear.MusicAddress = "./Clear.mp3";
	SoundClear.handle = OpenSound(SoundClear.MusicAddress);
	SoundClear.bIfRepeat = 0;
}

void PlayGameSound(MusicInfo Sound)
{
	PlaySoundH(Sound.handle, Sound.bIfRepeat);
}

void StopGameSound(MusicInfo Sound)
{
	StopSound(Sound.handle);
}

void UninitSoundFile(void)
{
	CloseSound(SoundMainMenu.handle);
	CloseSound(SoundTutor.handle);
	CloseSound(SoundStage1.handle);
	CloseSound(SoundRain.handle);

	CloseSound(SoundMainMap.handle);
	CloseSound(SoundJump.handle);
	CloseSound(SoundTeleport.handle);
	CloseSound(SoundCheckPoint.handle);
	CloseSound(SoundHurt.handle);
	CloseSound(SoundClear.handle);
}