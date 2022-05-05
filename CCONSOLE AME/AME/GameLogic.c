#include "GameLogic.h"
#include "Player.h"
#include "Render.h"
#include "InputLib.h"
#include "Map.h"
#include "Enemy.h"
#include "ConioEx.h"
#include "MusicLib.h"
#include <stdio.h>
#include <malloc.h>


GameLogic eGameState = EGL_None;
int iDeadLogic = 0;
double iStageDeadLine = 0;
PrickInfo* Boss = NULL;

void UpdateGameLogic(void)
{
	switch (eGameState)
	{
	case EGL_MainMenu:
		GameMainMenu();
		break;
	case EGL_Tutor:
		GameTutor();
		break;
	case EGL_OpeningCinematic:
		GameOpeningCinematic();
		break;
	case EGL_Stage1:
		GameStage1();
		break;
	case EGL_Cinematic1:
		GameCinematic1();
		break;
	case EGL_Stage2:
		GameStage2();
		break;
	case EGL_Cinematic2:
		GameCinematic2();
		break;
	case EGL_Stage3:
		GameStage3();
		break;
	case EGL_Cinematic3:
		GameCinematic3();
		break;
	case EGL_BossStage:
		GameBossStage();
		break;
	case EGL_EndingCinematic:
		GameEndingCinematic();
		break;
	default:
		break;
	}
}

void EnterGameState(GameLogic eGameState)
{
	OnExitGameState();
	OnEnterGameState(eGameState);
}

void OnEnterGameState(GameLogic eGameState)
{
	switch (eGameState)
	{
	case EGL_MainMenu:
		InitGameMainMenu();
		break;
	case EGL_Tutor:
		InitGameTutor();
		break;
	case EGL_OpeningCinematic:
		InitGameOpeningCinematic();
		break;
	case EGL_Stage1:
		InitGameStage1();
		break;
	case EGL_Cinematic1:
		InitGameCinematic1();
		break;
	case EGL_Stage2:
		InitGameStage2();
		break;
	case EGL_Cinematic2:
		InitGameCinematic2();
		break;
	case EGL_Stage3:
		InitGameStage3();
		break;
	case EGL_Cinematic3:
		InitGameCinematic3();
		break;
	case EGL_BossStage:
		InitGameBossStage();
		break;
	case EGL_EndingCinematic:
		InitGameEndingCinematic();
		break;
	default:
		break;
	}
}

void OnExitGameState(void)
{
	switch (eGameState)
	{
	case EGL_MainMenu:
		ExitGameMainMenu();
		break;
	case EGL_Tutor:
		ExitGameTutor();
		break;
	case EGL_OpeningCinematic:
		ExitGameOpeningCinematic();
		break;
	case EGL_Stage1:
		ExitGameStage1();
		break;
	case EGL_Cinematic1:
		ExitGameCinematic1();
		break;
	case EGL_Stage2:
		ExitGameStage2();
		break;
	case EGL_Cinematic2:
		ExitGameCinematic2();
		break;
	case EGL_Stage3:
		ExitGameStage3();
		break;
	case EGL_Cinematic3:
		ExitGameCinematic3();
		break;
	case EGL_BossStage:
		ExitGameBossStage();
		break;
	case EGL_EndingCinematic:
		ExitGameEndingCinematic();
		break;
	default:
		break;
	}
}

void InitGameMainMenu(void)
{
	eGameState = EGL_MainMenu;
	eGameMainMenuSelect = Start;
	PlayGameSound(SoundMainMenu);
}
void GameMainMenu(void)
{
	//FrameMainMenu();
	RainingSnowing();
	UpdateInputMainMenu();
	DrawMainMenuButton();
}
void ExitGameMainMenu(void)
{
	eGameState = EGL_None;
	TextAttr(0x0f);
	GotoXY(1, 1);
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				printf("\n");
			}
			else {
				printf(" ");
			}
			Sleep(1);
		}
	}
	TextAttr(0xb0);
	eGameMainMenuSelect = Start;
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			free(spRainSnow[i]);
			spRainSnow[i] = NULL;
		}
	}
	iRainSnowRate = 0;
	cRainSnowMap[0] = '\0';

	StopGameSound(SoundMainMenu);
}


void InitGameTutor(void)
{
	eGameState = EGL_Tutor;
	
	InitMapBlock(bTutorSceneMap,bTutorLogicMap);

	InitPlayerSpawn(VALUE_PLAYER_INITX, VALUE_PLAYER_INITY);

	InitPlayerMove();

	iStageDeadLine = 35.0;

	CreateSceneMember(Platform, 160.0, 23.0, 8, 1, (-0.04), 0, 142.0, 16.0, bTutorSceneMap);
	CreateSceneMember(SpawnPoint, 184.0, 25.0, 2, 1, 184.0, 25.0, 184.0, 25.0, bTutorSceneMap);
	CreateSceneMember(Platform, 220.0, 16.0, 2.0, 10.0, (-0.04), 0, 200.0, 16.0, bTutorSceneMap);
	CreateSceneMember(SpawnPoint, 224.0, 25.0, 2, 1, 224.0, 25.0, 224.0, 25.0, bTutorSceneMap);
	CreateSceneMember(Prick, 254.0, 23.0, 4, 1, 0, 0, 254.0, 23.0, bTutorSceneMap);
	//CreateSceneMember(SpawnPoint, 224.0, 25.0, 2, 1, 224.0, 25.0, 0, 0, bTutorSceneMap);
	CreateSceneMember(Prick, 283.0, 23.0, 2.0, 3.0, 0, (-0.08), 283.0, 15.0, bTutorSceneMap);
	//CreateSceneMember(bTutorSceneMap);
	
	PlayGameSound(SoundTutor);
}
void GameTutor(void)
{
	iDeadLogic = iPlayerDeadCount;

	UpdateInputPlayerMove(bTutorSceneMap);

	UpdateSceneMember(bTutorSceneMap);

	UpdatePlayerMove(bTutorSceneMap);

	InitMap(bTutorSceneMap, spMapFrame);

	DrawPlayerMove();

	if (spPlayerCoordinate->fDropY >= iStageDeadLine)
	{
		iPlayerDeadCount++;
	}

	if (iDeadLogic != iPlayerDeadCount)
	{
		UninitPlayerMove();
		InitPlayerMove();
		DrawPlayerDeadCount();
		PlayGameSound(SoundHurt);
	}

	if ((spPlayerCoordinate->fDropX <= 102.0) && (spPlayerCoordinate->fDropX >= 43.0))
	{
		PrintText("Press C jump", 20, 8);
	}
	if ((spPlayerCoordinate->fDropX <= 128.0) && (spPlayerCoordinate->fDropX >= 104.0))
	{
		PrintText("Hold <- or -> to stay on the wall, then press C reflect jump", 2, 6);
	}
	if ((spPlayerCoordinate->fDropX <= 170.0) && (spPlayerCoordinate->fDropX >= 132.0))
	{
		PrintText("Stand on the moving floor", 35, 8);
	}
	if ((spPlayerCoordinate->fDropX <= 200.0) && (spPlayerCoordinate->fDropX >= 171.0))
	{
		PrintText("Green is check point, when dead you will respawn in there", 2, 8);
	}
	if ((spPlayerCoordinate->fDropX <= 216.0) && (spPlayerCoordinate->fDropX >= 200.0))
	{
		PrintText("When stay on vertical wall, you will slowly drop", 20, 8);
	}
	if ((spPlayerCoordinate->fDropX <= 269.0) && (spPlayerCoordinate->fDropX >= 217.0))
	{
		PrintText("Red is dead spot, when touch them you will return check point", 2, 8);
	}
	if ((spPlayerCoordinate->fDropX <= 303.0) && (spPlayerCoordinate->fDropX >= 274.0))
	{
		PrintText("Press <- or -> and X run", 20, 4);
	}
	if ((spPlayerCoordinate->fDropX <= 356.0) && (spPlayerCoordinate->fDropX >= 306.0))
	{
		PrintText("Blue is final point", 20, 3);
	}

	if (spPlayerCoordinate->fDropY == 22.0)
	{
		if (spPlayerCoordinate->fDropX == 352.0)
		{
			PlayGameSound(SoundClear);
			EnterGameState(EGL_OpeningCinematic);
		}
	}
}
void ExitGameTutor(void)
{
	eGameState = EGL_None;

	TextAttr(0x0f);
	GotoXY(1, 1);
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				printf("\n");
			}
			else {
				printf(" ");
			}
			Sleep(1);
		}
	}
	TextAttr(0xb0);

	DeleteAllSceneMember();

	UninitPlayerMove();

	StopGameSound(SoundTutor);
}


void InitGameOpeningCinematic(void)
{
	eGameState = EGL_OpeningCinematic;

	eOpeningCinematicText = OCT_Start;

	RainingSnowing();

	PlayGameSound(SoundMainMenu);
}
void GameOpeningCinematic(void)
{
	UpdateInputOpeningCinematic();
	RainingSnowing();
	DrawOpeningCinematic();
}
void ExitGameOpeningCinematic(void)
{
	eGameState = EGL_None;
	TextAttr(0x0f);
	GotoXY(1, 1);
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				printf("\n");
			}
			else {
				printf(" ");
			}
			Sleep(1);
		}
	}
	TextAttr(0xb0);
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			free(spRainSnow[i]);
			spRainSnow[i] = NULL;
		}
	}
	iRainSnowRate = 0;
	cRainSnowMap[0] = '\0';

	StopGameSound(SoundMainMenu);
}


void InitGameStage1(void)
{
	eGameState = EGL_Stage1;

	InitMapBlock(bStage1SceneMap, bStage1LogicMap);

	//(181.0, 38.0);

	InitPlayerSpawn(42.0, 15.0);

	InitPlayerMove();

	iStageDeadLine = 43.0;

	CreateSceneMember(Prick, 53.0, 29.0, 2.0, 1.0, (-0.06), 0, 48.0, 29.0, bStage1SceneMap);
	CreateSceneMember(Prick, 53.0, 23.0, 2.0, 1.0, (-0.04), 0, 48.0, 23.0, bStage1SceneMap);
	CreateSceneMember(Platform, 87.0, 26.0, 10, 1, (-0.05), 0, 58.0, 26.0, bStage1SceneMap);
	CreateSceneMember(Prick, 96.0, 20.0, 2.0, 1.0, (-0.05), 0, 91.0, 20.0, bStage1SceneMap);
	CreateSceneMember(Prick, 105.0, 16.0, 2.0, 1.0, (-0.05), 0, 91.0, 16.0, bStage1SceneMap);
	CreateSceneMember(SpawnPoint, 107.0, 19.0, 2.0, 1.0, 107.0, 19.0, 0, 0, bStage1SceneMap);
	CreateSceneMember(Prick, 121.0, 21.0, 2.0, 1.0, 0, (-0.03), 121.0, 15.0, bStage1SceneMap);
	CreateSceneMember(Prick, 135.0, 21.0, 2.0, 1.0, 0, (-0.05), 135.0, 15.0, bStage1SceneMap);
	CreateSceneMember(Prick, 149.0, 21.0, 2.0, 1.0, 0, (-0.07), 149.0, 15.0, bStage1SceneMap);
	CreateSceneMember(Prick, 163.0, 23.0, 2.0, 1.0, (-0.06), 0, 150.0, 23.0, bStage1SceneMap);
	CreateSceneMember(Prick, 151.0, 32.0, 2.0, 1.0, 0, (-0.03), 151.0, 28.0, bStage1SceneMap);
	CreateSceneMember(SpawnPoint, 133.0, 36.0, 2.0, 1.0, 133.0, 35.0, 133.0, 36.0, bStage1SceneMap);
	CreateSceneMember(Prick, 173.0, 40.0, 2.0, 1.0, (-0.08), 0, 142.0, 40.0, bStage1SceneMap);
	CreateSceneMember(Platform, 165.0, 41.0, 10.0, 1.0, (-0.03), 0, 142.0, 41.0, bStage1SceneMap);
	CreateSceneMember(Prick, 179.0, 31.0, 2.0, 1.0, (-0.05), 0, 165.0, 31.0, bStage1SceneMap);
	CreateSceneMember(Prick, 179.0, 24.0, 2.0, 1.0, (-0.08), 0, 165.0, 24.0, bStage1SceneMap);
	CreateSceneMember(Prick, 186.0, 20.0, 2.0, 1.0, 0, (-0.05), 186.0, 15.0, bStage1SceneMap);
	CreateSceneMember(Box, 185.0, 38.0, 2.0, 1.0, 102.0, 36.0, 185.0, 38.0, bStage1SceneMap);
	CreateSceneMember(Platform, 118.0, 41.0, 2.0, 12.0, (-0.08), 0, 110.0, 41.0, bStage1SceneMap);
	CreateSceneMember(Platform, 105.0, 41.0, 2.0, 8.0, (-0.05), 0, 98.0, 41.0, bStage1SceneMap);
	CreateSceneMember(Platform, 114.0, 59.0, 12.0, 1.0, (-0.09), 0, 101.0, 59.0, bStage1SceneMap);
	CreateSceneMember(Prick, 145.0, 51.0, 2.0, 1.0, (-0.08), 0, 125.0, 51.0, bStage1SceneMap);
	CreateSceneMember(Platform, 128.0, 58.0, 16.0, 1.0, 0, (-0.05), 128.0, 51.0, bStage1SceneMap);
	CreateSceneMember(Prick, 156.0, 53.0, 2.0, 1.0, (-0.08), 0, 138.0, 53.0, bStage1SceneMap);
	CreateSceneMember(Platform, 146.0, 56.0, 20.0, 1.0, 0, (-0.05), 146.0, 47.0, bStage1SceneMap);
	CreateSceneMember(Prick, 184.0, 56.0, 2.0, 1.0, (-0.08), 0, 165.0, 56.0, bStage1SceneMap);
	CreateSceneMember(Platform, 186.0, 57.0, 9.0, 1.0, 0, (-0.05), 186.0, 48.0, bStage1SceneMap);
	//CreateSceneMember(bStage1SceneMap);

	PlayGameSound(SoundStage1);
}
void GameStage1(void)
{
	iDeadLogic = iPlayerDeadCount;

	UpdateInputPlayerMove(bStage1SceneMap);

	UpdateSceneMember(bStage1SceneMap);

	UpdatePlayerMove(bStage1SceneMap);

	InitMap(bStage1SceneMap, spMapFrame);

	DrawPlayerMove();

	if (((int)(spPlayerCoordinate->fDropY)) == 39)
	{
		if ((((int)(spPlayerCoordinate->fDropX)) >= 177) && (((int)(spPlayerCoordinate->fDropX)) <= 192))
		{
			PrintText("Blue check point lead you to a new area", 4, 8);
		}
	}
	if ((((int)(spPlayerCoordinate->fDropX)) >= 177) && (((int)(spPlayerCoordinate->fDropX)) <= 192))
	{
		iStageDeadLine = 63.0;
	}

	if (spPlayerCoordinate->fDropY >= iStageDeadLine)
	{
		iPlayerDeadCount++;
	}

	if (iDeadLogic != iPlayerDeadCount)
	{
		DrawPlayerDeadCount();
		UninitPlayerMove();
		InitPlayerMove();
		PlayGameSound(SoundHurt);
	}

	if (spPlayerCoordinate->fDropY == 48.0)
	{
		if (spPlayerCoordinate->fDropX == 199.0)
		{
			PlayGameSound(SoundClear);
			EnterGameState(EGL_Cinematic1);
		}
	}
}
void ExitGameStage1(void)
{
	eGameState = EGL_None;

	DeleteAllSceneMember();

	UninitPlayerMove();

	StopGameSound(SoundStage1);
}


void InitGameCinematic1(void)
{
	eGameState = EGL_Cinematic1;

	eOpeningCinematicText = OCT_Start;

	RainingSnowing();

	PlayGameSound(SoundMainMenu);
}
void GameCinematic1(void)
{
	UpdateInputOpeningCinematic();
	RainingSnowing();
	DrawOpeningCinematic();
}
void ExitGameCinematic1(void)
{
	eGameState = EGL_None;
	TextAttr(0x0f);
	GotoXY(1, 1);
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				printf("\n");
			}
			else {
				printf(" ");
			}
			Sleep(1);
		}
	}
	TextAttr(0xb0);
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			free(spRainSnow[i]);
			spRainSnow[i] = NULL;
		}
	}
	iRainSnowRate = 0;
	cRainSnowMap[0] = '\0';

	StopGameSound(SoundMainMenu);

	PlayGameSound(SoundRain);
}


void InitGameStage2(void)
{
	eGameState = EGL_Stage2;

}
void GameStage2(void)
{

}
void ExitGameStage2(void)
{
	eGameState = EGL_None;

}


void InitGameCinematic2(void)
{
	eGameState = EGL_Cinematic2;

}
void GameCinematic2(void)
{

}
void ExitGameCinematic2(void)
{
	eGameState = EGL_None;

}


void InitGameStage3(void)
{
	eGameState = EGL_Stage3;

}
void GameStage3(void)
{

}
void ExitGameStage3(void)
{
	eGameState = EGL_None;

}


void InitGameCinematic3(void)
{
	eGameState = EGL_Cinematic3;

}
void GameCinematic3(void)
{

}
void ExitGameCinematic3(void)
{
	eGameState = EGL_None;

}


void InitGameBossStage(void)
{
	eGameState = EGL_BossStage;

	InitMapBlock(bBossStageSceneMap, bBossStageLogicMap);

	InitPlayerSpawn(317.0, 14.0);

	InitPlayerMove();

	iStageDeadLine = 17.0;

	Boss = NULL;

	CreateSceneMember(Platform, 330.0, 16.0, 12.0, 1.0, (-0.1), 0, 321.0, 16.0, bBossStageSceneMap);
	CreateSceneMember(Box, 344.0, 14.0, 2.0, 1.0, 349.0, 31.0, 344.0, 14.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 332.0, 34.0, 16.0, 1.0, (-0.1), 0, 309.0, 34.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 326.0, 31.0, 16.0, 1.0, (-0.08), 0, 303.0, 31.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 332.0, 28.0, 16.0, 1.0, (-0.06), 0, 309.0, 28.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 326.0, 25.0, 16.0, 1.0, (-0.04), 0, 303.0, 25.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 251.0, 24.0, 2.0, 1.0, (-0.1), 0, 236.0, 24.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 234.0, 29.0, 2.0, 1.0, (-0.07), 0, 218.0, 29.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 201.0, 36.0, 16.0, 1.0, 0, (-0.07), 201.0, 31.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 189.0, 34.0, 20.0, 1.0, (-0.15), 0, 115.0, 34.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 186.0, 33.0, 2.0, 1.0, 0, (-0.13), 186.0, 30.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 172.0, 33.0, 2.0, 1.0, 0, (-0.11), 172.0, 30.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 158.0, 33.0, 2.0, 1.0, 0, (-0.13), 158.0, 30.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 144.0, 33.0, 2.0, 1.0, 0, (-0.11), 144.0, 30.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 130.0, 33.0, 2.0, 1.0, 0, (-0.13), 130.0, 30.0, bBossStageSceneMap);
	CreateSceneMember(Prick, 116.0, 33.0, 2.0, 1.0, 0, (-0.11), 116.0, 30.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 103.0, 16.0, 4.0, 1.0, (-0.08), 0, 87.0, 16.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 42.0, 31.0, 20.0, 1.0, 0, (-0.1), 42.0, 22.0, bBossStageSceneMap);
	CreateSceneMember(Platform, 68.0, 34.0, 16.0, 1.0, (-0.08), 0, 42.0, 34.0, bBossStageSceneMap);
	CreateSceneMember(Box, 82.0, 32.0, 2.0, 1.0, 43.0, 38.0, 82.0, 32.0, bBossStageSceneMap);

}
void GameBossStage(void)
{
	iDeadLogic = iPlayerDeadCount;

	UpdateInputPlayerMove(bBossStageSceneMap);

	UpdateSceneMember(bBossStageSceneMap);

	UpdatePlayerMove(bBossStageSceneMap);

	InitMap(bBossStageSceneMap, spMapFrame);

	DrawPlayerMove();

	if (((int)(spPlayerCoordinate->fDropY)) == 14.0)
	{
		if (((int)(spPlayerCoordinate->fDropX)) == 342.0)
		{
			iStageDeadLine = 39.0;
			if (Boss == NULL)
			{
				Boss = CreateSceneMember(Prick, 357.0, 14.0, 2.0, 23.0, (-0.02), 0, 41.0, 14.0, bBossStageSceneMap);
			}
		}
	}
	if (spPlayerCoordinate->fDropY >= iStageDeadLine)
	{
		iPlayerDeadCount++;
	}

	if ((spPlayerCoordinate->fDropX <= 298.0) && (spPlayerCoordinate->fDropX >= 285.0))
	{
		if (spPlayerCoordinate->fDropY == 21.0)
		{
			Boss->fSpeedX = (-0.5);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 234.0) && (spPlayerCoordinate->fDropX >= 219.0))
	{
		if (spPlayerCoordinate->fDropY == 29.0)
		{
			Boss->fSpeedX = (-0.1);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 110.0) && (spPlayerCoordinate->fDropX >= 92.0))
	{
		if (spPlayerCoordinate->fDropY == 32.0)
		{
			Boss->fSpeedX = (-0.25);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 82.0) && (spPlayerCoordinate->fDropX >= 64.0))
	{
		if (spPlayerCoordinate->fDropY == 19.0)
		{
			Boss->fSpeedX = (-0.02);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 82.0) && (spPlayerCoordinate->fDropX >= 47.0))
	{
		if (spPlayerCoordinate->fDropY == 32.0)
		{
			iStageDeadLine = 61.0;
		}
	}

	if ((spPlayerCoordinate->fDropX <= 115.0) && (spPlayerCoordinate->fDropX >= 42.0))
	{
		if (spPlayerCoordinate->fDropY >= 38.0)
		{
			PrintText(" ", 26, 8);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 192.0) && (spPlayerCoordinate->fDropX >= 117.0))
	{
		if (spPlayerCoordinate->fDropY >= 38.0)
		{
			PrintText(" ", 26,8);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 260.0) && (spPlayerCoordinate->fDropX >= 194.0))
	{
		if (spPlayerCoordinate->fDropY >= 38.0)
		{
			PrintText(" ", 26,8);
		}
	}

	if ((spPlayerCoordinate->fDropX <= 357.0) && (spPlayerCoordinate->fDropX >= 293.0))
	{
		if (spPlayerCoordinate->fDropY >= 38.0)
		{
			PrintText(" ", 26,8);
		}
	}

	if (spPlayerCoordinate->fDropY >= 59.0)
	{
		EnterGameState(EGL_EndingCinematic);
	}

	if (iDeadLogic != iPlayerDeadCount)
	{
		DrawPlayerDeadCount();
		PlayGameSound(SoundHurt);
		EnterGameState(EGL_BossStage);
	}

	//if (spPlayerCoordinate->fDropY == )
	//{
	//	if (spPlayerCoordinate->fDropX == )
	//	{
	//		_exit(0);
	//		//EnterGameState(EGL_Cinematic1);
	//	}
	//}
}
void ExitGameBossStage(void)
{
	eGameState = EGL_None;

	//TextAttr(0x0f);
	//GotoXY(1, 1);
	//for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	//{
	//	for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
	//	{
	//		if (x == VALUE_SCREEN_WIDTH)
	//		{
	//			printf("\n");
	//		}
	//		else {
	//			printf(" ");
	//		}
	//		Sleep(1);
	//	}
	//}
	//TextAttr(0xb0);

	DeleteAllSceneMember();

	UninitPlayerMove();
}


void InitGameEndingCinematic(void)
{
	eGameState = EGL_EndingCinematic;

	eOpeningCinematicText = OCT_Start;

	TextAttr(0x0f);
	GotoXY(1, 1);
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				printf("\n");
			}
			else {
				printf(" ");
			}
			Sleep(1);
		}
	}
	TextAttr(0xb0);

	StopGameSound(SoundRain);

	PlayGameSound(SoundMainMenu);

	RainingSnowing();
}
void GameEndingCinematic(void)
{
	UpdateInputOpeningCinematic();
	RainingSnowing();
	DrawOpeningCinematic();
}
void ExitGameEndingCinematic(void)
{
	eGameState = EGL_None;

	TextAttr(0x0f);
	GotoXY(1, 1);
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				printf("\n");
			}
			else {
				printf(" ");
			}
			Sleep(1);
		}
	}
	TextAttr(0xb0);
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			free(spRainSnow[i]);
			spRainSnow[i] = NULL;
		}
	}
	iRainSnowRate = 0;
	cRainSnowMap[0] = '\0';

	StopGameSound(SoundMainMenu);

	eRainorSnow = Snow;
}