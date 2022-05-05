#include "Render.h"
#include "GameLogic.h"
#include "ConioEx.h"
#include "InputLib.h"
#include <stdio.h>

void UpdateGameFrameRender(void)
{
	switch (eGameState)
	{
	case EGL_MainMenu:
		FrameMainMenu();
		break;
	case EGL_Tutor:
		FrameTutor();
		break;
	case EGL_OpeningCinematic:
		FrameOpeningCinematic();
		break;
	case EGL_Stage1:
		FrameStage1();
		break;
	case EGL_Cinematic1:
		FrameCinematic1();
		break;
	case EGL_Stage2:
		FrameStage2();
		break;
	case EGL_Cinematic2:
		FrameCinematic2();
		break;
	case EGL_Stage3:
		FrameStage3();
		break;
	case EGL_Cinematic3:
		FrameCinematic3();
		break;
	case EGL_BossStage:
		FrameBossStage();
		break;
	case EGL_EndingCinematic:
		FrameEndingCinematic();
		break;
	default:
		break;
	}
}

void FrameMainMenu(void)
{
	char *cFrameMainMenu = 
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n"
		"                                                                                \n";
	TextAttr(0xb0);
	GotoXY(1, 1);
	printf(cFrameMainMenu);
}
void FrameTutor(void)
{

}
void FrameOpeningCinematic(void)
{

}
void FrameStage1(void)
{

}
void FrameCinematic1(void)
{

}
void FrameStage2(void)
{

}
void FrameCinematic2(void)
{

}
void FrameStage3(void)
{

}
void FrameCinematic3(void)
{

}
void FrameBossStage(void)
{

}
void FrameEndingCinematic(void)
{

}