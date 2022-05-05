#ifndef _MUSIC_H_
#define _MUSIC_H_


typedef struct EMusicInfo {
	char* MusicAddress;

	unsigned long long handle;

	int bIfRepeat;
}MusicInfo;

extern MusicInfo SoundMainMenu;
extern MusicInfo SoundTutor;
extern MusicInfo SoundStage1;
extern MusicInfo SoundRain;

extern MusicInfo SoundMainMap;
extern MusicInfo SoundJump;
extern MusicInfo SoundTeleport;
extern MusicInfo SoundCheckPoint;
extern MusicInfo SoundHurt;
extern MusicInfo SoundClear;


void InitSoundFile(void);
void PlayGameSound(MusicInfo Sound);
void StopGameSound(MusicInfo Sound);
void UninitSoundFile(void);

#endif // !_MUSIC_H_
