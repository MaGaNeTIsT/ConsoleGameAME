#ifndef __CONIOEX_H
#define __CONIOEX_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <process.h>
#include <windows.h>
#include <tchar.h>
#include <mmsystem.h>
#include <digitalv.h>
#pragma comment(lib, "winmm.lib")

#ifdef CONIOEX
#define CONIOEX_INST extern 
#else
#define CONIOEX_INST 
#endif

#ifdef __BORLANDC__
#define NOCURSOR		_NOCURSOR
#define SOLIDCURSOR		_SOLIDCURSOR
#define NORMALCURSOR	_NORMALCURSOR
	__inline void SetCursorType(int cur_t) { _setcursortype(cur_t); }
	__inline int _kbhit(void) { return kbhit(); }
#else

#pragma warning(disable:4996)

#define NOCURSOR		0
#define SOLIDCURSOR		1
#define NORMALCURSOR	2

#define _NOCURSOR		NOCURSOR
#define _SOLIDCURSOR	SOLIDCURSOR
#define _NORMALCURSOR	NORMALCURSOR

#ifndef __COLORS
#define __COLORS
	enum COLORS {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY,
		DARKGRAY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};
#endif

	CONIOEX_INST WORD	__conioex_h_wAttribute;

	int WhereX(void);

	int WhereY(void);

	void GotoXY(int x, int y);

	void ClrEOL(void);

	void ClrScr(void);

	void HighVideo(void);

	void LowVideo(void);

	void NormVideo(void);

	void TextBackground(int newcolor);

	void TextColor(int newcolor);

	void TextAttr(int newattr);

	void SetCursorType(int cur_t);

	void InsertLine(void);

	void DelLine(void);

#endif

	__inline void SetCaption(char *title);
	__inline int GetCaption(char *title, int len);
	__inline void mSleep(unsigned long msecs);

#define PK_ENTER				VK_RETURN
#define PK_ESC					VK_ESCAPE
#define PK_F1					VK_F1
#define PK_F2					VK_F2
#define PK_F3					VK_F3
#define PK_F4					VK_F4
#define PK_F5					VK_F5
#define PK_F6					VK_F6
#define PK_F7					VK_F7
#define PK_F8					VK_F8
#define PK_F9					VK_F9
#define PK_F10					VK_F10
#define PK_F11					VK_F11
#define PK_F12					VK_F12
#define PK_SP					VK_SPACE
#define PK_UP					VK_UP
#define PK_DOWN					VK_DOWN
#define PK_RIGHT				VK_RIGHT
#define PK_LEFT					VK_LEFT
#define PK_SHIFT				VK_SHIFT
#define PK_CTRL					VK_CONTROL
#define PK_ALT					VK_MENU
#define PK_BS					VK_BACK
#define PK_PAUSE				VK_PAUSE
#define PK_INS					VK_INSERT
#define PK_DEL					VK_DELETE
#define PK_TAB					VK_TAB
#define PK_NFER					VK_KANA
#define PK_XFER					VK_CONVERT
#define PK_0					0x30
#define PK_1					0x31
#define PK_2					0x32
#define PK_3					0x33
#define PK_4					0x34
#define PK_5					0x35
#define PK_6					0x36
#define PK_7					0x37
#define PK_8					0x38
#define PK_9					0x39
#define PK_NUMPAD0				VK_NUMPAD0
#define PK_NUMPAD1				VK_NUMPAD1
#define PK_NUMPAD2				VK_NUMPAD2
#define PK_NUMPAD3				VK_NUMPAD3
#define PK_NUMPAD4				VK_NUMPAD4
#define PK_NUMPAD5				VK_NUMPAD5
#define PK_NUMPAD6				VK_NUMPAD6
#define PK_NUMPAD7				VK_NUMPAD7
#define PK_NUMPAD8				VK_NUMPAD8
#define PK_NUMPAD9				VK_NUMPAD9
#define PK_A					0x41
#define PK_B					0x42
#define PK_C					0x43
#define PK_D					0x44
#define PK_E					0x45
#define PK_F					0x46
#define PK_G					0x47
#define PK_H					0x48
#define PK_I					0x49
#define PK_J					0x4A
#define PK_K					0x4B
#define PK_L					0x4C
#define PK_M					0x4D
#define PK_N					0x4E
#define PK_O					0x4F
#define PK_P					0x50
#define PK_Q					0x51
#define PK_R					0x52
#define PK_S					0x53
#define PK_T					0x54
#define PK_U					0x55
#define PK_V					0x56
#define PK_W					0x57
#define PK_X					0x58
#define PK_Y					0x59
#define PK_Z					0x5A

#define PK_LT					0x0BC
#define PK_GT					0x0BE
#define PK_SLUSH				0x0BF
#define PK_DOT					VK_DECIMAL
#define PK_DIV					VK_DIVIDE
#define PK_BSLUSH				0x0E2

#define PK_SEMICOLON			0x0BB
#define PK_ADD					VK_ADD
#define PK_COLON				0x0BA
#define PK_MUL					VK_MULTIPLY
#define PK_RBRACE				0x0DD

#define PK_ATMARK				0x0C0
#define PK_LBRACE				0x0DB

#define PK_MINUS				0x0BD
#define PK_SUB					VK_SUBTRACT
#define PK_XOR					0x0DE
#define PK_YEN					0x0DC

#define PK_KANJI				0x0F3
#define PK_CAPS					0x0F0

#define PM_LEFT					VK_LBUTTON
#define PM_MID					VK_MBUTTON
#define PM_RIGHT				VK_RBUTTON
#define PM_CURX					0x0101
#define PM_CURY					0x0102

#define PJ1_XPOS				0x0200
#define PJ1_YPOS				0x0201
#define PJ1_ZPOS				0x0202
#define PJ1_BTNS				0x0203
#define PJ2_XPOS				0x0210
#define PJ2_YPOS				0x0211
#define PJ2_ZPOS				0x0212
#define PJ2_BTNS				0x0213
#define PJ3_XPOS				0x0220
#define PJ3_YPOS				0x0221
#define PJ3_ZPOS				0x0222
#define PJ3_BTNS				0x0223
#define PJ4_XPOS				0x0230
#define PJ4_YPOS				0x0231
#define PJ4_ZPOS				0x0232
#define PJ4_BTNS				0x0233
#define PJ_XPOS					PJ1_XPOS
#define PJ_YPOS					PJ1_YPOS
#define PJ_ZPOS					PJ1_ZPOS
#define PJ_BTNS					PJ1_BTNS

CONIOEX_INST DWORD	__conioex_h_dwKeyMap[8];

CONIOEX_INST COORD	__conioex_h_crdMouse;

void ReInport(void);

int Inport(int port);

	typedef struct {
		int				nDevType;
		MCIDEVICEID		wDeviceID;
		char			szPath[MAX_PATH];
		int				nRepeat;
	} __conioex_h_SoundInfo;

	unsigned long long OpenSound(char *path);

	void CloseSound(unsigned long long hsound);

	void PlaySoundH(unsigned long long hsound, int repeat);

	void StopSound(unsigned long long hsound);

	int CheckSound(unsigned long long hsound);

	void UpdateSound(unsigned long long hsound);

	void SetVolume(unsigned long long hsound, int percent);


#ifdef __cplusplus
}
#endif




#endif
