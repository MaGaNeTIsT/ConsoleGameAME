#include "Main.h"

void DispFPS(void);

#define DEBUG

int g_nCountFPS;

void main(void)
{
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	int nCountFrame;


	timeBeginPeriod(1);

	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		nCountFrame = 0;



	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 600, TRUE);

	SetCursorType(NOCURSOR);

	ClrScr();

	InitSoundFile();

	EnterGameState(EGL_MainMenu);



	do
	{
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{
			g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
			dwFPSLastTime = dwCurrentTime;
			nCountFrame = 0;
		}

		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
		{
			dwExecLastTime = dwCurrentTime;



			UpdateGameLogic();



#ifdef DEBUG
			DispFPS();
#endif

			nCountFrame++;
		}
	} while (!Inport(PK_ESC));



	UninitPlayerMove();

	UninitSoundFile();



	timeEndPeriod(1);
}



#ifdef DEBUG
//=============================================================================
// FPS Show
//=============================================================================
void DispFPS(void)
{
	TextColor(WHITE);

	GotoXY(1, 1);
	printf("FPS:%d", g_nCountFPS);
}
#endif