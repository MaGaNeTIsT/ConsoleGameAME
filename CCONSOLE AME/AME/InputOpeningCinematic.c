#include "InputLib.h"
#include "Render.h"
#include "ConioEx.h"
#include "GameLogic.h"
#include <stdio.h>

OpeningCinematicText eOpeningCinematicText = OCT_Start;

void UpdateInputOpeningCinematic(void)
{
	if (Inport(ENTER_KEY))
	{
		ReInport();
		eOpeningCinematicText = (eOpeningCinematicText + 1) % 12;
	}
}

void DrawOpeningCinematic(void)
{
	TextAttr(0xb0);
	if (eGameState == EGL_OpeningCinematic)
	{
		switch (eOpeningCinematicText)
		{
		case OCT_Text01:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf(" ");
			GotoXY(16, 13);
			printf(" ");
			GotoXY(16, 14);
			printf("                                 [Enter]");
			break;
		case OCT_Text02:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf(" ");
			GotoXY(16, 13);
			printf(" ");
			GotoXY(16, 14);
			printf("                                 [Enter]");
			break;
		case OCT_Text03:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text04:
			EnterGameState(EGL_Stage1);
			break;
		}
	}
	if (eGameState == EGL_Cinematic1)
	{
		switch (eOpeningCinematicText)
		{
		case OCT_Text01:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf(" ");
			GotoXY(16, 13);
			printf(" ");
			GotoXY(16, 14);
			printf("                                 [Enter]");
			break;
		case OCT_Text02:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text03:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text04:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text05:
			EnterGameState(EGL_BossStage);
			break;
		}
	}
	if (eGameState == EGL_EndingCinematic)
	{
		switch (eOpeningCinematicText)
		{
		case OCT_Text01:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text02:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text03:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text04:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text05:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text06:
			GotoXY(16, 11);
			printf(" ");
			GotoXY(16, 12);
			printf("                                 [Enter]");
			break;
		case OCT_Text07:
			EnterGameState(EGL_MainMenu);
			break;
		}
	}
}