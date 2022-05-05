#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include <stdio.h>

typedef enum EGameLogic {
	EGL_None = 0,
	EGL_MainMenu,
	EGL_Tutor,
	EGL_OpeningCinematic,
	EGL_Stage1,
	EGL_Cinematic1,
	EGL_Stage2,
	EGL_Cinematic2,
	EGL_Stage3,
	EGL_Cinematic3,
	EGL_BossStage,
	EGL_EndingCinematic
}GameLogic;

extern GameLogic eGameState;
extern int iDeadLogic;
extern double iStageDeadLine;

void UpdateGameLogic(void);
void OnExitGameState(void);
void OnEnterGameState(GameLogic eGameState);
void EnterGameState(GameLogic eGameState);

void InitGameMainMenu(void);
void GameMainMenu(void);
void ExitGameMainMenu(void);

void InitGameTutor(void);
void GameTutor(void);
void ExitGameTutor(void);

void InitGameOpeningCinematic(void);
void GameOpeningCinematic(void);
void ExitGameOpeningCinematic(void);

void InitGameStage1(void);
void GameStage1(void);
void ExitGameStage1(void);

void InitGameCinematic1(void);
void GameCinematic1(void);
void ExitGameCinematic1(void);

void InitGameStage2(void);
void GameStage2(void);
void ExitGameStage2(void);

void InitGameCinematic2(void);
void GameCinematic2(void);
void ExitGameCinematic2(void);

void InitGameStage3(void);
void GameStage3(void);
void ExitGameStage3(void);

void InitGameCinematic3(void);
void GameCinematic3(void);
void ExitGameCinematic3(void);

void InitGameBossStage(void);
void GameBossStage(void);
void ExitGameBossStage(void);

void InitGameEndingCinematic(void);
void GameEndingCinematic(void);
void ExitGameEndingCinematic(void);

#endif // !_GAMELOGIC_H_
