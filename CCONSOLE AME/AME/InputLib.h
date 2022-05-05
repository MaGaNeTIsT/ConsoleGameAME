#ifndef _INPUT_H_
#define _INPUT_H_


#define RIGHT_KEY PK_RIGHT
#define LEFT_KEY PK_LEFT
#define JUMP_KEY PK_C
#define UP_KEY PK_UP
#define DOWN_KEY PK_DOWN
#define ENTER_KEY PK_ENTER
#define VALUE_MAP_WIDTH 398


typedef enum EMainMenuSelect {
	Start = 0,
	End
}MainMenuSelect;

extern MainMenuSelect eGameMainMenuSelect;

typedef enum EOpeningCinematicText {
	OCT_Start = 0,
	OCT_Text01,
	OCT_Text02,
	OCT_Text03,
	OCT_Text04,
	OCT_Text05,
	OCT_Text06,
	OCT_Text07,
	OCT_Text08,
	OCT_Text09,
	OCT_Text10,
	OCT_End
}OpeningCinematicText;

extern OpeningCinematicText eOpeningCinematicText;

void UpdateInputOpeningCinematic(void);
void UpdateInputPlayerMove(int(*Map)[VALUE_MAP_WIDTH]);
void UpdateInputMainMenu(void);

#endif // !_INPUT_H_