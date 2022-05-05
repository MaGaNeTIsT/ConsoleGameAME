#include "ConioEx.h"


WORD __conioex_h_wAttribute = LIGHTGRAY;

int WhereX(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X - csbi.srWindow.Left + 1;
}

int WhereY(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y - csbi.srWindow.Top + 1;
}

void GotoXY(int x, int y)
{
	COORD c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	c.X = x - 1;
	c.Y = y - 1;
	if (GetConsoleScreenBufferInfo(h, &csbi))
	{
		c.Y += csbi.srWindow.Top;
	}
	SetConsoleCursorPosition(h, c);
}

void ClrEOL(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	COORD	c;
	HANDLE	h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) 
	{
		DWORD num;

		c = csbi.dwCursorPosition;
		FillConsoleOutputAttribute(h, csbi.wAttributes,
			csbi.srWindow.Right - csbi.dwCursorPosition.X + 1, c, &num);
		FillConsoleOutputCharacter(h, ' ',
			csbi.srWindow.Right - csbi.dwCursorPosition.X + 1, c, &num);
	}
}

void ClrScr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD num;
	COORD c = { 0, 0 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) 
	{
		__conioex_h_wAttribute = csbi.wAttributes;
		FillConsoleOutputAttribute(h, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, c, &num);
		FillConsoleOutputCharacter(h, TEXT(' '), csbi.dwSize.X * csbi.dwSize.Y, c, &num);
		GotoXY(csbi.srWindow.Left + 1, csbi.srWindow.Top + 1);
	}
}

void HighVideo(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi))
	{
		SetConsoleTextAttribute(h, csbi.wAttributes | FOREGROUND_INTENSITY);
	}
}

void LowVideo(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi))
	{
		SetConsoleTextAttribute(h, csbi.wAttributes & ~FOREGROUND_INTENSITY);
	}
}

void NormVideo(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGRAY);
}

void TextBackground(int newcolor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(h, &csbi))
	{
		SetConsoleTextAttribute(h, (csbi.wAttributes & ~0x00f0) | ((newcolor & 0x07) << 4));
	}
}

void TextColor(int newcolor)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(h, &csbi))
	{
		SetConsoleTextAttribute(h, (csbi.wAttributes & ~0x0f) | (newcolor & 0x0f));
	}
}

void TextAttr(int newattr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newattr);
}

void SetCursorType(int cur_t)
{
	CONSOLE_CURSOR_INFO	cci;
	static	int nSize = -1;
	
	if (nSize < 0) 
	{
		if (GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci))
		{
			nSize = (int)cci.dwSize;
		}
		else
		{
			nSize = 25;
		}
	}
	cci.dwSize = (cur_t < NORMALCURSOR) ? 100 : nSize;
	cci.bVisible = (cur_t != NOCURSOR);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void InsertLine(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) 
	{
		COORD	c;
		DWORD	len;
		DWORD	num;
		LPCSTR	psz;
		LPWORD	pw;

		c.X = csbi.srWindow.Left;
		len = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		//psz = (LPCSTR)_alloca(len * sizeof(CHAR));
		psz = (LPCSTR)_malloca(len * sizeof(CHAR));
		//pw = (LPWORD)_alloca(len * sizeof(WORD));
		pw = (LPWORD)_malloca(len * sizeof(WORD));
		for (c.Y = csbi.srWindow.Bottom; c.Y > csbi.dwCursorPosition.Y; c.Y--) 
		{
			c.Y--;
			ReadConsoleOutputAttribute(h, pw, len, c, &num);
			ReadConsoleOutputCharacter(h, psz, len, c, &num);
			c.Y++;
			WriteConsoleOutputAttribute(h, pw, len, c, &num);
			WriteConsoleOutputCharacter(h, psz, len, c, &num);
		}
		FillConsoleOutputAttribute(h, csbi.wAttributes, len, c, &num);
		FillConsoleOutputCharacter(h, TEXT(' '), len, c, &num);
	}
}

void DelLine(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (GetConsoleScreenBufferInfo(h, &csbi)) 
	{
		DWORD	num;
		COORD	c;
		DWORD	len;
		LPCSTR	psz;
		LPWORD	pw;

		c.X = csbi.srWindow.Left;
		len = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		//psz = (LPCSTR)_alloca(len * sizeof(CHAR));
		psz = (LPCSTR)_malloca(len * sizeof(CHAR));
		//pw = (LPWORD)_alloca(len * sizeof(WORD));
		pw = (LPWORD)_malloca(len * sizeof(WORD));
		for (c.Y = csbi.dwCursorPosition.Y; c.Y < csbi.srWindow.Bottom; c.Y++) 
		{
			c.Y++;
			ReadConsoleOutputAttribute(h, pw, len, c, &num);
			ReadConsoleOutputCharacter(h, psz, len, c, &num);
			c.Y--;
			WriteConsoleOutputAttribute(h, pw, len, c, &num);
			WriteConsoleOutputCharacter(h, psz, len, c, &num);
		}
		FillConsoleOutputAttribute(h, __conioex_h_wAttribute, len, c, &num);
		FillConsoleOutputCharacter(h, TEXT(' '), len, c, &num);
	}
}

void SetCaption(char *title)
{
	SetConsoleTitleA(title);
}

int GetCaption(char *title, int len)
{
	return GetConsoleTitleA(title, len);
}

void mSleep(unsigned long msecs)
{
	Sleep(msecs);
}

DWORD __conioex_h_dwKeyMap[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

COORD __conioex_h_crdMouse = { 0, 0 };

void ReInport(void)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		__conioex_h_dwKeyMap[i] = 0;
	}
}

int Inport(int port)
{
	DWORD	dwEvent;
	HANDLE	h;

	if ((port & 0xfe00) == 0x0200) 
	{
		int		id = (port & 0x01f0) >> 4;
		int		func = port & 0x0f;
		JOYINFO	ji;

		switch (func) 
		{
		case 0:	case 1:	case 2:	case 3:
			if (joyGetPos(id, &ji) != JOYERR_NOERROR)
			{
				return -1;
			}
				
			switch (func) 
			{
			case 0:
				return ji.wXpos;
			case 1:
				return ji.wYpos;
			case 2:
				return ji.wZpos;
			case 3:
				return ji.wButtons;
			}
			break;
		default:
			break;
		}
		return 0;
	}

	dwEvent = 0;
	h = GetStdHandle(STD_INPUT_HANDLE);
	if (GetNumberOfConsoleInputEvents(h, &dwEvent) && dwEvent) 
	{
		DWORD			dwRead = 0;
		//PINPUT_RECORD	pInpRec = (PINPUT_RECORD)_alloca(dwEvent * sizeof(INPUT_RECORD));
		PINPUT_RECORD	pInpRec = (PINPUT_RECORD)_malloca(dwEvent * sizeof(INPUT_RECORD));

		if (ReadConsoleInput(h, pInpRec, dwEvent, &dwRead) && dwRead) 
		{
			PINPUT_RECORD	pir = pInpRec;
			DWORD			dw;
			for (dw = 0; dw < dwRead; dw++, pir++) 
			{
				switch (pir->EventType) 
				{
				case KEY_EVENT: {
					KEY_EVENT_RECORD*	pker = &pir->Event.KeyEvent;
					if (pker->wVirtualKeyCode > 0x0FF)
						break;
					if (pker->bKeyDown)
						__conioex_h_dwKeyMap[pker->wVirtualKeyCode >> 5] |= (0x01 << (pker->wVirtualKeyCode & 31));
					else
						__conioex_h_dwKeyMap[pker->wVirtualKeyCode >> 5] &= ~(0x01 << (pker->wVirtualKeyCode & 31));
					if (pker->dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
						__conioex_h_dwKeyMap[VK_MENU >> 5] |= (0x01 << (VK_MENU & 31));
					else
						__conioex_h_dwKeyMap[VK_MENU >> 5] &= ~(0x01 << (VK_MENU & 31));
					if (pker->dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED))
						__conioex_h_dwKeyMap[VK_CONTROL >> 5] |= (0x01 << (VK_CONTROL & 31));
					else
						__conioex_h_dwKeyMap[VK_CONTROL >> 5] &= ~(0x01 << (VK_CONTROL & 31));
					if (pker->dwControlKeyState & SHIFT_PRESSED)
						__conioex_h_dwKeyMap[VK_SHIFT >> 5] |= (0x01 << (VK_SHIFT & 31));
					else
						__conioex_h_dwKeyMap[VK_SHIFT >> 5] &= ~(0x01 << (VK_SHIFT & 31));
					break;
				}
				case MOUSE_EVENT: {
					MOUSE_EVENT_RECORD	*pmer = &pir->Event.MouseEvent;
					__conioex_h_crdMouse = pmer->dwMousePosition;
					if (pmer->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						__conioex_h_dwKeyMap[VK_LBUTTON >> 5] |= (0x01 << (VK_LBUTTON & 31));
					else
						__conioex_h_dwKeyMap[VK_LBUTTON >> 5] &= ~(0x01 << (VK_LBUTTON & 31));
					if (pmer->dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED)
						__conioex_h_dwKeyMap[VK_MBUTTON >> 5] |= (0x01 << (VK_MBUTTON & 31));
					else
						__conioex_h_dwKeyMap[VK_MBUTTON >> 5] &= ~(0x01 << (VK_MBUTTON & 31));
					if (pmer->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
						__conioex_h_dwKeyMap[VK_RBUTTON >> 5] |= (0x01 << (VK_RBUTTON & 31));
					else
						__conioex_h_dwKeyMap[VK_RBUTTON >> 5] &= ~(0x01 << (VK_RBUTTON & 31));
					break;
				}
				default:
					break;
				}
			}
		}
	}

	switch (port) 
	{
	case PM_CURX:
		return __conioex_h_crdMouse.X + 1;
	case PM_CURY:
		return __conioex_h_crdMouse.Y + 1;
	default:
		break;
	}
	return (__conioex_h_dwKeyMap[(port & 0x0FF) >> 5] & (0x01 << (port & 31))) != 0;
}

unsigned long long OpenSound(char *path)
{
	const char	szMidiExt[] = ".mid|.midi|.rmi";
	const char	szWaveExt[] = ".wav|.wave";
	const char	szMP3Ext[] = ".mp3";
	char		szExt[_MAX_EXT];
	union {
		MCI_WAVE_OPEN_PARMSA	wop;
		MCI_OPEN_PARMSA			op;
	} m;
	DWORD		dwCmd;
	__conioex_h_SoundInfo	*psi;
	
	psi = (__conioex_h_SoundInfo *)malloc(sizeof(__conioex_h_SoundInfo));
	if (psi == NULL)
	{
		return 0;
	}

	ZeroMemory(psi, sizeof(*psi));
	
	ZeroMemory(&m, sizeof(m));
	_splitpath(path, NULL, NULL, NULL, szExt);
	strlwr(szExt);
	dwCmd = MCI_OPEN_TYPE | MCI_OPEN_ELEMENT;
	if (strstr(szMidiExt, szExt)) 
	{
		psi->nDevType = MCI_DEVTYPE_SEQUENCER;
		lstrcpynA(psi->szPath, path, MAX_PATH);
		m.op.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_SEQUENCER;
		m.op.lpstrElementName = psi->szPath;
		dwCmd |= MCI_OPEN_TYPE_ID;
	}
	else if (strstr(szWaveExt, szExt)) 
	{
		psi->nDevType = MCI_DEVTYPE_WAVEFORM_AUDIO;
		lstrcpynA(psi->szPath, path, MAX_PATH);
		m.wop.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;
		m.wop.lpstrElementName = psi->szPath;
		dwCmd |= MCI_OPEN_TYPE_ID;
		//		m.wop.dwBufferSeconds  = 60;
		//		dwCmd |= MCI_WAVE_OPEN_BUFFER;
	}
	else if (strstr(szMP3Ext, szExt)) 
	{
		psi->nDevType = MCI_DEVTYPE_DIGITAL_VIDEO;
		lstrcpynA(psi->szPath, path, MAX_PATH);
		m.op.lpstrDeviceType = "MPEGVideo";
		m.op.lpstrElementName = psi->szPath;
	}
	else 
	{
		free(psi);
		return 0;
	}
	
	MCIERROR err = mciSendCommand(0, MCI_OPEN, dwCmd, (DWORD_PTR)&m);;
	if(err) 
	{
		free(psi);
		return 0;
	}
	psi->wDeviceID = m.op.wDeviceID;
	return (unsigned long long)psi;
}

void CloseSound(unsigned long long hsound)
{
	__conioex_h_SoundInfo	*psi;

	if (!hsound)
	{
		return;
	}
	psi = (__conioex_h_SoundInfo *)hsound;
	if (psi->wDeviceID) 
	{
		mciSendCommand(psi->wDeviceID, MCI_CLOSE, 0, 0);
		psi->wDeviceID = 0;
	}
	free(psi);
}

void PlaySoundH(unsigned long long hsound, int repeat)
{
	__conioex_h_SoundInfo	*psi;
	DWORD					dwCmd;
	MCI_PLAY_PARMS			mpp;

	if (!hsound)
	{
		return;
	}
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
	{
		return;
	}
	psi->nRepeat = repeat;
	ZeroMemory(&mpp, sizeof(mpp));
	dwCmd = 0;
	if (repeat) 
	{
		switch (psi->nDevType) 
		{
		case MCI_DEVTYPE_DIGITAL_VIDEO:
			dwCmd |= (MCI_FROM | MCI_DGV_PLAY_REPEAT);
			mpp.dwFrom = 0;
			break;
		case MCI_DEVTYPE_SEQUENCER:
		case MCI_DEVTYPE_WAVEFORM_AUDIO:
			break;
		default:
			break;
		}
	}
	mciSendCommand(psi->wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
	mciSendCommand(psi->wDeviceID, MCI_PLAY, dwCmd, (DWORD_PTR)&mpp);
}

void StopSound(unsigned long long hsound)
{
	__conioex_h_SoundInfo	*psi;

	if (!hsound)
	{ 
		return;
	}
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
	{
		return;
	}
	psi->nRepeat = 0;
	mciSendCommand(psi->wDeviceID, MCI_STOP, MCI_WAIT, 0);
	mciSendCommand(psi->wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
}

int CheckSound(unsigned long long hsound)
{
	__conioex_h_SoundInfo	*psi;
	MCI_STATUS_PARMS		msp;

	if (!hsound)
	{
		return 0;
	}
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
	{
		return 0;
	}
	ZeroMemory(&msp, sizeof(msp));
	msp.dwItem = MCI_STATUS_MODE;
	if (mciSendCommand(psi->wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&msp))
	{
		return 0;
	}
	return msp.dwReturn == MCI_MODE_PLAY;
}

void UpdateSound(unsigned long long hsound)
{
	__conioex_h_SoundInfo	*psi;
	MCI_STATUS_PARMS		msp;

	if (!hsound)
	{
		return;
	}

	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID || !psi->nRepeat)
	{
		return;
	}
	switch (psi->nDevType) 
	{
	case MCI_DEVTYPE_DIGITAL_VIDEO:
		break;
	case MCI_DEVTYPE_SEQUENCER:
	case MCI_DEVTYPE_WAVEFORM_AUDIO:
		ZeroMemory(&msp, sizeof(msp));
		msp.dwItem = MCI_STATUS_MODE;
		if (!mciSendCommand(psi->wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&msp))
		{
			if (msp.dwReturn != MCI_MODE_PLAY) 
			{
				if (psi->nRepeat > 0) 
				{
					psi->nRepeat = -1;
					mciSendCommand(psi->wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, 0);
					mciSendCommand(psi->wDeviceID, MCI_PLAY, 0, 0);
				}
			}
			else
			{
				psi->nRepeat = 1;
			}
		}
		break;
	default:
		break;
	}
}

void SetVolume(unsigned long long hsound, int percent)
{
	__conioex_h_SoundInfo	*psi;

	if (!hsound)
	{
		return;
	}
	psi = (__conioex_h_SoundInfo *)hsound;
	if (!psi->wDeviceID)
	{
		return;
	}
	switch (psi->nDevType)
	{
	case MCI_DEVTYPE_DIGITAL_VIDEO: {
		MCI_DGV_SETAUDIO_PARMS	mdsp;

		ZeroMemory(&mdsp, sizeof(mdsp));
		mdsp.dwItem = MCI_DGV_SETAUDIO_VOLUME;
		mdsp.dwValue = percent * 10;
		mciSendCommand(psi->wDeviceID, MCI_SETAUDIO,
			MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD_PTR)&mdsp);
		break;
	}
	case MCI_DEVTYPE_SEQUENCER: {
		DWORD dwVolume;

		dwVolume = 0x0ffff * percent / 100;
		midiOutSetVolume(0, (DWORD)MAKELONG(dwVolume, dwVolume));
		break;
	}
	case MCI_DEVTYPE_WAVEFORM_AUDIO: {
		DWORD dwVolume;

		dwVolume = 0x0ffff * percent / 100;
		waveOutSetVolume(0, (DWORD)MAKELONG(dwVolume, dwVolume));
		break;
	}
	default:
		break;
	}
}

