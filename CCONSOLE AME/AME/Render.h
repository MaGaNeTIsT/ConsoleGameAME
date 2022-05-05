#ifndef _RENDER_H_
#define _RENDER_H_

#include "Player.h"

#define VALUE_SCREEN_HEIGHT 25
#define VALUE_SCREEN_WIDTH 80 

#define RANDOM_COUNT_LINE 15
#define COUNT_LINE_RAINSNOW 15
#define SPEED_RAIN_SNOW (1.8)
#define COUNT_ALL_RAINSNOW 400
#define RAINSNOWRATE 30
typedef struct SRainSnowInfo {
	double fDropX;
	double fDropY;
	//double fOldDropX;
	//double fOldDropY;
	double fSpeedX;
	double fSpeedY;
	int bExist;
	//RainSnowInfo* Next;
}RainSnowInfo;
//extern RainSnowInfo SRainSnowStart;
//extern RainSnowInfo SRainSnowEnd;
typedef enum ERainorSnow {
	Rain = 0,
	Snow
}RainorSnow;
extern RainorSnow eRainorSnow;
extern RainSnowInfo* spRainSnow[COUNT_ALL_RAINSNOW];
extern int iRainSnowRate;
extern int iRainSnowMap[VALUE_SCREEN_HEIGHT][VALUE_SCREEN_WIDTH];
extern char cRainSnowMap[VALUE_SCREEN_HEIGHT*(VALUE_SCREEN_WIDTH + 2)];
extern char* cspRainSnowMap;

void DrawRainSnow(RainSnowInfo* spRainSnow);
void InitRainSnow(void);
void InitMemberRainSnow(void);
void UninitMemberRainSnow(void);
void RainingSnowing(void);
void DrawMainMenuButton(void);

void DrawOpeningCinematic(void);

void DrawPlayerDeadCount(void);
void DrawPlayerMove(void);
void InitMap(int(*Map)[VALUE_MAP_WIDTH], char *gspMapFrame);
//void MapBlockCalculate(int(*Map)[VALUE_MAP_WIDTH], int y, int x, char *gspMapFrame);

extern char cTextMapFrame[((VALUE_SCREEN_HEIGHT + 1)*((2 * VALUE_SCREEN_WIDTH) + 2))];
extern char *spMapFrame;
extern int iMapX, iMapY;

void FrameMainMenu(void);
void FrameTutor(void);
void FrameOpeningCinematic(void);
void FrameStage1(void);
void FrameCinematic1(void);
void FrameStage2(void);
void FrameCinematic2(void);
void FrameStage3(void);
void FrameCinematic3(void);
void FrameBossStage(void);
void FrameEndingCinematic(void);

void UpdateGameFrameRender(void);

void PrintText(char* Text, int x, int y);

#endif // !_RENDER_H_