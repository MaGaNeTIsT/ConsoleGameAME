#ifndef _PLAYER_H_
#define _PLAYER_H_


/////////////////////////////////////////////////////////////////////
////堏摦晹暘
/////////////////////////////////////////////////////////////////////
//#define NULL 0
#define true 1
#define false 0
#define VALUE_MAP_WIDTH 398
#define VALUE_MAP_HEIGHT 74

#define VALUE_PLAYER_LEG (1.0)

#define VALUE_PLAYER_INITX (46.0)
#define VALUE_PLAYER_INITY (15.0)

#define VALUE_PLAYER_SPEEDX (0.6)
#define VALUE_RESIST_LAND (0.4)

#define VALUE_PLAYER_JUMPHEIGHT (5.0)
#define VALUE_JUMPSPEED (0.4)
#define VALUE_GRAVITATION (0.5)

typedef enum EPlayerXCrash {
	NotCrash = 0,
	LeftLand,
	RightLand
}PlayerXCrash;

typedef enum EPlayerYCrash {
	NotLand = 0,
	UpLand,
	DownLand,
}PlayerYCrash;

typedef enum EPlayerSceneMember {
	NotTouch = 0,
	BoxTouch,
	SpawnPointTouch,
	PrickTouch,
	PlatformTouch
}PlayerSceneMember;

typedef struct SCoordinate {
	double fX;
	double fY;
}Coordinate;

typedef struct SPlayerCoordinateInfo {
	double fDropX;
	double fDropY;
	//double fInitDropX;
	//double fInitDropY;
	double fJumpDropY;
	//double fMoveDropX;
	double fMoveX;
	double fSpeedX;
	double fJumpHeight;

	int bJumpOver;
	int bMove;
	int bJump;
	int bLand;
	int bSpeedUp;
	int bClimb;
	int bWallJump;

	Coordinate Touch;

	PlayerXCrash iPNC;
	PlayerYCrash iPL;
	PlayerYCrash iPJ;
	PlayerSceneMember iPlayerGet;
}PlayerCoordinate;

extern PlayerCoordinate* spPlayerCoordinate;
extern double fMapBottomCoordinate;
extern double fMapAboveCoordinate;
extern int iPlayerDeadCount;
extern double fMapNextCoordinate;
extern int iIfPlayerWallJump;
extern double fPlayerInitDropX;
extern double fPlayerInitDropY;

void InitPlayerSpawn(double x, double y);
void InitPlayerMove(void);
void UninitPlayerMove(void);
void UpdatePlayerMove(int(*Map)[VALUE_MAP_WIDTH]);

//////////////////////////////////////////////////////
////return 1::this time under Player's block is black
////return 0::find under player's block
//////////////////////////////////////////////////////
int IfPlayerLand(int(*Map)[VALUE_MAP_WIDTH]);

//////////////////////////////////////////////////////
////return 1::this time above Player's block is black
////return 0::find above player's block
//////////////////////////////////////////////////////
int IfPlayerJumpHurt(int(*Map)[VALUE_MAP_WIDTH]);

//////////////////////////////////////////////////////
////return enum::this time next Player's block is black
////return 0::find next player's block
//////////////////////////////////////////////////////
int IfPlayerNextCrash(int(*Map)[VALUE_MAP_WIDTH]);

//////////////////////////////////////////////////////
////return Player and SceneMember 's relationship
//////////////////////////////////////////////////////
PlayerSceneMember IfPlayerApproach(int(*Map)[VALUE_MAP_WIDTH]);

void OnSceneMemberTouch(int(*Map)[VALUE_MAP_WIDTH]);

#endif // !_PLAYER_H_