#include "InputLib.h"
#include "ConioEx.h"
#include "GameLogic.h"
#include "Render.h"
#include "MusicLib.h"

MainMenuSelect eGameMainMenuSelect = Start;

void UpdateInputMainMenu(void)
{
	if (Inport(UP_KEY))
	{
		ReInport();
		PlayGameSound(SoundMainMap);
		eGameMainMenuSelect = (eGameMainMenuSelect + 1) % 2;
	}
	if (Inport(DOWN_KEY))
	{
		ReInport();
		PlayGameSound(SoundMainMap);
		eGameMainMenuSelect = (eGameMainMenuSelect + 1) % 2;
	}
	if (Inport(ENTER_KEY))
	{
		PlayGameSound(SoundClear);
		if (eGameMainMenuSelect == Start)
		{
			ReInport();
			EnterGameState(EGL_Tutor);
		}
		if (eGameMainMenuSelect == End)
		{
			ReInport();
			_exit(0);
		}
	}
}

void DrawMainMenuButton(void)
{
	if (eRainorSnow == Rain)
	{
		switch (eGameMainMenuSelect)
		{
		case Start:
			TextAttr(0xb0);
			GotoXY(34, 9);
			printf("--> Start");
			GotoXY(34, 15);
			printf("    End");
			break;
		case End:
			TextAttr(0xb0);
			GotoXY(34, 9);
			printf("    Start");
			GotoXY(34, 15);
			printf("--> End");
			break;
		default:
			break;
		}
	}
	if (eRainorSnow == Snow)
	{
		switch (eGameMainMenuSelect)
		{
		case Start:
			TextAttr(0xb0);
			GotoXY(34, 9);
			printf("*** Start");
			GotoXY(34, 15);
			printf("    End");
			break;
		case End:
			TextAttr(0xb0);
			GotoXY(34, 9);
			printf("    Start");
			GotoXY(34, 15);
			printf("*** End");
			break;
		default:
			break;
		}
	}
}