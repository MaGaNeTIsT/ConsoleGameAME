#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Player.h"
#include "MusicLib.h"
#include "ConioEx.h"
#include "Map.h"
#include "Enemy.h"


PlayerCoordinate* spPlayerCoordinate = NULL;
double fMapBottomCoordinate = 0.0;
double fMapAboveCoordinate = 0.0;
double fMapNextCoordinate = 0;
int iPlayerDeadCount = 0;
int iIfPlayerWallJump = -2;
double fPlayerInitDropX = VALUE_PLAYER_INITX;
double fPlayerInitDropY = VALUE_PLAYER_INITY;

void InitPlayerSpawn(double x, double y)
{
	fPlayerInitDropX = x;
	fPlayerInitDropY = y;
}

void InitPlayerMove(void)
{
	spPlayerCoordinate = (PlayerCoordinate*)malloc(sizeof(PlayerCoordinate));

	spPlayerCoordinate->fDropX = fPlayerInitDropX;

	spPlayerCoordinate->fDropY = fPlayerInitDropY;

	spPlayerCoordinate->fJumpDropY = spPlayerCoordinate->fDropY;

	//spPlayerCoordinate->fMoveDropX = spPlayerCoordinate->fDropX;

	spPlayerCoordinate->fMoveX = 0.0;

	spPlayerCoordinate->fSpeedX = VALUE_PLAYER_SPEEDX;

	spPlayerCoordinate->fJumpHeight = VALUE_PLAYER_JUMPHEIGHT;

	spPlayerCoordinate->bJumpOver = true;

	spPlayerCoordinate->bMove = true;

	spPlayerCoordinate->bJump = false;

	spPlayerCoordinate->bLand = false;

	spPlayerCoordinate->bSpeedUp = false;

	spPlayerCoordinate->bClimb = false;

	spPlayerCoordinate->bWallJump = false;

	spPlayerCoordinate->Touch.fX = 0;

	spPlayerCoordinate->Touch.fY = 0;

	spPlayerCoordinate->iPNC = -2;

	spPlayerCoordinate->iPL = -2;

	spPlayerCoordinate->iPJ = -2;

	spPlayerCoordinate->iPlayerGet = NotTouch;
}

void UninitPlayerMove(void)
{
	free(spPlayerCoordinate);
	spPlayerCoordinate = NULL;
}

void UpdatePlayerMove(int(*Map)[VALUE_MAP_WIDTH])
{
	if (spPlayerCoordinate == NULL)
	{
		TextColor(WHITE);

		GotoXY(10, 1);

		printf("Error::PlayerNotExist");

		return;
	}
	if (Map == NULL)
	{
		TextColor(WHITE);

		GotoXY(10, 1);

		printf("Error::MapNotExist");

		return;
	}
	if (spPlayerCoordinate->bWallJump)
	{
		spPlayerCoordinate->bClimb = false;
		if (iIfPlayerWallJump == -2)
		{
			switch (spPlayerCoordinate->iPNC)
			{
			case LeftLand:
				iIfPlayerWallJump = 0;
				break;
			case RightLand:
				iIfPlayerWallJump = 1;
				break;
			default:
				break;
			}
		}
		switch (iIfPlayerWallJump)
		{
		case 0:
			spPlayerCoordinate->fDropX += spPlayerCoordinate->fSpeedX;
			if (spPlayerCoordinate->iPNC == RightLand)
			{
				if (spPlayerCoordinate->fDropX > fMapNextCoordinate)
				{
					spPlayerCoordinate->fDropX = fMapNextCoordinate;
					spPlayerCoordinate->bWallJump = false;
					spPlayerCoordinate->bJumpOver = true;
				}
			}
			spPlayerCoordinate->iPJ = IfPlayerJumpHurt(Map);
			spPlayerCoordinate->fDropY -= VALUE_JUMPSPEED;
			if ((spPlayerCoordinate->fDropY <= (fMapAboveCoordinate)) && (spPlayerCoordinate->iPJ == UpLand))
			{
				spPlayerCoordinate->fDropY = fMapAboveCoordinate;
				spPlayerCoordinate->bWallJump = false;
				spPlayerCoordinate->bJumpOver = true;
			}
			if (spPlayerCoordinate->fDropY <= (spPlayerCoordinate->fJumpDropY - spPlayerCoordinate->fJumpHeight))
			{
				spPlayerCoordinate->fDropY = spPlayerCoordinate->fJumpDropY - spPlayerCoordinate->fJumpHeight;
				spPlayerCoordinate->bWallJump = false;
				spPlayerCoordinate->bJumpOver = true;
			}
			break;
		case 1:
			spPlayerCoordinate->fDropX -= spPlayerCoordinate->fSpeedX;
			if (spPlayerCoordinate->iPNC == LeftLand)
			{
				if (spPlayerCoordinate->fDropX < fMapNextCoordinate)
				{
					spPlayerCoordinate->fDropX = fMapNextCoordinate;
					spPlayerCoordinate->bWallJump = false;
					spPlayerCoordinate->bJumpOver = true;
				}
			}
			spPlayerCoordinate->iPJ = IfPlayerJumpHurt(Map);
			spPlayerCoordinate->fDropY -= VALUE_JUMPSPEED;
			if ((spPlayerCoordinate->fDropY <= (fMapAboveCoordinate)) && (spPlayerCoordinate->iPJ == UpLand))
			{
				spPlayerCoordinate->fDropY = fMapAboveCoordinate;
				spPlayerCoordinate->bWallJump = false;
				spPlayerCoordinate->bJumpOver = true;
			}
			if (spPlayerCoordinate->fDropY <= (spPlayerCoordinate->fJumpDropY - spPlayerCoordinate->fJumpHeight))
			{
				spPlayerCoordinate->fDropY = spPlayerCoordinate->fJumpDropY - spPlayerCoordinate->fJumpHeight;
				spPlayerCoordinate->bWallJump = false;
				spPlayerCoordinate->bJumpOver = true;
			}
			break;
		default:
			break;
		}
		if (spPlayerCoordinate->fDropX <= VALUE_LIMIT_LEFT)
		{
			spPlayerCoordinate->fDropX = VALUE_LIMIT_LEFT;
		}
		if (spPlayerCoordinate->fDropX >= VALUE_LIMIT_RIGHT)
		{
			spPlayerCoordinate->fDropX = VALUE_LIMIT_RIGHT;
		}
		if (spPlayerCoordinate->fDropY <= VALUE_LIMIT_TOP)
		{
			spPlayerCoordinate->fDropY = VALUE_LIMIT_TOP;
			spPlayerCoordinate->bJumpOver = true;
			spPlayerCoordinate->bWallJump = false;
		}
		if (spPlayerCoordinate->fDropY >= VALUE_LIMIT_BOTTOM)
		{
			iPlayerDeadCount++;
		}
		spPlayerCoordinate->iPNC = IfPlayerNextCrash(Map);
		spPlayerCoordinate->iPJ = IfPlayerJumpHurt(Map);
		spPlayerCoordinate->iPL = IfPlayerLand(Map);
	}
	else {
		//spPlayerCoordinate->fOldDropX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->fDropX += spPlayerCoordinate->fMoveX;
		if (spPlayerCoordinate->fMoveX > (VALUE_RESIST_LAND * spPlayerCoordinate->fSpeedX))
		{
			spPlayerCoordinate->fMoveX -= (spPlayerCoordinate->fMoveX * VALUE_RESIST_LAND);
		}
		if (spPlayerCoordinate->fMoveX < (0.0 - (VALUE_RESIST_LAND * spPlayerCoordinate->fSpeedX)))
		{
			spPlayerCoordinate->fMoveX -= (spPlayerCoordinate->fMoveX * VALUE_RESIST_LAND);
		}
		if ((spPlayerCoordinate->fMoveX > 0) && (spPlayerCoordinate->fMoveX <= (VALUE_RESIST_LAND * spPlayerCoordinate->fSpeedX)))
		{
			spPlayerCoordinate->fMoveX = 0;
		}
		if ((spPlayerCoordinate->fMoveX < 0) && (spPlayerCoordinate->fMoveX >= (0.0 - (VALUE_RESIST_LAND * spPlayerCoordinate->fSpeedX))))
		{
			spPlayerCoordinate->fMoveX = 0;
		}
		switch (spPlayerCoordinate->iPNC)
		{
		case NotCrash:
			fMapNextCoordinate = 0;
			break;
		case LeftLand:
			if ((spPlayerCoordinate->fDropX < fMapNextCoordinate) && (fMapNextCoordinate != 0))
			{
				spPlayerCoordinate->fDropX = fMapNextCoordinate;
			}
			break;
		case RightLand:
			if ((spPlayerCoordinate->fDropX > fMapNextCoordinate) && (fMapNextCoordinate != 0))
			{
				spPlayerCoordinate->fDropX = fMapNextCoordinate;
			}
			break;
		default:
			fMapNextCoordinate = 0;
			break;
		}
		//spPlayerCoordinate->fOldDropY = spPlayerCoordinate->fDropY;
		if (spPlayerCoordinate->bJump && (!spPlayerCoordinate->bJumpOver))
		{
			spPlayerCoordinate->iPJ = -2;
			spPlayerCoordinate->iPJ = IfPlayerJumpHurt(Map);
			spPlayerCoordinate->fDropY += (0.0 - VALUE_JUMPSPEED);
			if (spPlayerCoordinate->iPJ == UpLand)
			{
				if (spPlayerCoordinate->fDropY <= (fMapAboveCoordinate))
				{
					spPlayerCoordinate->fDropY = fMapAboveCoordinate;
					spPlayerCoordinate->bJumpOver = true;
				}
			}
		}
		if (spPlayerCoordinate->fDropY <= (spPlayerCoordinate->fJumpDropY - spPlayerCoordinate->fJumpHeight))
		{
			spPlayerCoordinate->fDropY = spPlayerCoordinate->fJumpDropY - spPlayerCoordinate->fJumpHeight;
			spPlayerCoordinate->bJumpOver = true;
		}
		if (spPlayerCoordinate->bJumpOver)
		{
			spPlayerCoordinate->iPL = -2;
			spPlayerCoordinate->iPL = IfPlayerLand(Map);
			if (spPlayerCoordinate->iPL == NotLand)
			{
				fMapBottomCoordinate = -1.0;
			}
			if (spPlayerCoordinate->bMove)
			{
				if (((spPlayerCoordinate->fDropY + VALUE_PLAYER_LEG) <= fMapBottomCoordinate) && (fMapBottomCoordinate > 0))
				{
					spPlayerCoordinate->bLand = false;
				}
				if (spPlayerCoordinate->iPL == NotLand)
				{
					spPlayerCoordinate->bLand = false;
				}
			}
			if (((!spPlayerCoordinate->bLand) && spPlayerCoordinate->bJumpOver) && (!spPlayerCoordinate->bClimb))
			{
				spPlayerCoordinate->fDropY += VALUE_GRAVITATION;
				if (((spPlayerCoordinate->fDropY + VALUE_PLAYER_LEG) > fMapBottomCoordinate) && (fMapBottomCoordinate > 0))
				{
					spPlayerCoordinate->fDropY = fMapBottomCoordinate - VALUE_PLAYER_LEG;
					spPlayerCoordinate->bLand = true;
					spPlayerCoordinate->bMove = false;
				}
			}
			spPlayerCoordinate->bClimb = false;
		}
		spPlayerCoordinate->iPNC = -2;
		spPlayerCoordinate->iPNC = IfPlayerNextCrash(Map);

		spPlayerCoordinate->iPlayerGet = 0;
		spPlayerCoordinate->iPlayerGet = IfPlayerApproach(Map);

		OnSceneMemberTouch(Map);

		if (spPlayerCoordinate->fDropX <= VALUE_LIMIT_LEFT)
		{
			spPlayerCoordinate->fDropX = VALUE_LIMIT_LEFT;
		}
		if (spPlayerCoordinate->fDropX >= VALUE_LIMIT_RIGHT)
		{
			spPlayerCoordinate->fDropX = VALUE_LIMIT_RIGHT;
		}
		if (spPlayerCoordinate->fDropY <= VALUE_LIMIT_TOP)
		{
			spPlayerCoordinate->fDropY = VALUE_LIMIT_TOP;
			spPlayerCoordinate->bJumpOver = true;
		}
		if (spPlayerCoordinate->fDropY >= VALUE_LIMIT_BOTTOM)
		{
			iPlayerDeadCount++;
		}
		iIfPlayerWallJump = -2;
	}
}

int IfPlayerLand(int(*Map)[VALUE_MAP_WIDTH])
{
	for (int y = 0; y < VALUE_MAP_HEIGHT; y++)
	{
		switch (Map[y][((int)(spPlayerCoordinate->fDropX)) - 1])
		{
		case Land:
			if ((y + 1) > ((int)(spPlayerCoordinate->fDropY + VALUE_PLAYER_LEG)))
			{
				fMapBottomCoordinate = ((double)(y));
				return DownLand;
			}
			break;
		default:
			break;
		}
		switch (Map[y][(int)(spPlayerCoordinate->fDropX + 1.0) - 1])
		{
		case Land:
			if ((y + 1) > ((int)(spPlayerCoordinate->fDropY + VALUE_PLAYER_LEG)))
			{
				fMapBottomCoordinate = ((double)(y));
				return DownLand;
			}
			break;
		default:
			break;
		}
	}
	return NotLand;
}
int IfPlayerJumpHurt(int(*Map)[VALUE_MAP_WIDTH])
{

	for (int y = VALUE_MAP_HEIGHT - 1; y >= 0; y--)
	{
		switch (Map[y][(int)(spPlayerCoordinate->fDropX) - 1])
		{
		case Land:
			if ((y + 1) < ((int)(spPlayerCoordinate->fDropY)))
			{
				fMapAboveCoordinate = (double)y + 2;
				return UpLand;
			}
			break;
		default:
			break;
		}
		switch (Map[y][(int)(spPlayerCoordinate->fDropX + 1.0) - 1])
		{
		case Land:
			if ((y + 1) < ((int)(spPlayerCoordinate->fDropY)))
			{
				fMapAboveCoordinate = (double)y + 2.0;
				return UpLand;
			}
			break;
		default:
			break;
		}
	}
	return NotLand;
}

int IfPlayerNextCrash(int(*Map)[VALUE_MAP_WIDTH])
{
	if ((Map[((int)(spPlayerCoordinate->fDropY)) - 1][((int)(spPlayerCoordinate->fDropX + 2.0)) - 1]) == Land)
	{
		fMapNextCoordinate = (double)((int)(spPlayerCoordinate->fDropX));
		return RightLand;
	}
	if ((Map[((int)(spPlayerCoordinate->fDropY + 1.0)) - 1][((int)(spPlayerCoordinate->fDropX + 2.0)) - 1]) == Land)
	{
		fMapNextCoordinate = (double)((int)(spPlayerCoordinate->fDropX));
		return RightLand;
	}
	if ((Map[((int)(spPlayerCoordinate->fDropY)) - 1][((int)(spPlayerCoordinate->fDropX - 1.0)) - 1]) == Land)
	{
		fMapNextCoordinate = (double)((int)(spPlayerCoordinate->fDropX));
		return LeftLand;
	}
	if ((Map[((int)(spPlayerCoordinate->fDropY + 1.0)) - 1][((int)(spPlayerCoordinate->fDropX - 1.0)) - 1]) == Land)
	{
		fMapNextCoordinate = (double)((int)(spPlayerCoordinate->fDropX));
		return LeftLand;
	}
	return NotCrash;
}

PlayerSceneMember IfPlayerApproach(int(*Map)[VALUE_MAP_WIDTH])
{
	int x, y;
	x = ((int)(spPlayerCoordinate->fDropX)) - 1;
	y = ((int)(spPlayerCoordinate->fDropY)) - 1;
	switch (Map[y][x])
	{
	case Box:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return BoxTouch;
		break;
	case SpawnPoint:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return SpawnPointTouch;
		break;
	case Prick:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return PrickTouch;
		break;
	//case Platform:
	//	spPlayerCoordinate->iPlayerGet = PlatformTouch;
	//	break;
	}
	switch (Map[y][x+1])
	{
	case Box:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return BoxTouch;
		break;
	case SpawnPoint:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return SpawnPointTouch;
		break;
	case Prick:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return PrickTouch;
		break;
		//case Platform:
		//	spPlayerCoordinate->iPlayerGet = PlatformTouch;
		//	break;
	}
	switch (Map[y + ((int)(VALUE_PLAYER_LEG))][x])
	{
	case Box:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return BoxTouch;
		break;
	case SpawnPoint:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return SpawnPointTouch;
		break;
	case Prick:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return PrickTouch;
		break;
		//case Platform:
		//	spPlayerCoordinate->iPlayerGet = PlatformTouch;
		//	break;
	}
	switch (Map[y + ((int)(VALUE_PLAYER_LEG))][x + 1])
	{
	case Box:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return BoxTouch;
		break;
	case SpawnPoint:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return SpawnPointTouch;
		break;
	case Prick:
		spPlayerCoordinate->Touch.fX = spPlayerCoordinate->fDropX;
		spPlayerCoordinate->Touch.fY = spPlayerCoordinate->fDropY;
		return PrickTouch;
		break;
		//case Platform:
		//	spPlayerCoordinate->iPlayerGet = PlatformTouch;
		//	break;
	}
	return NotTouch;
}

void OnSceneMemberTouch(int(*Map)[VALUE_MAP_WIDTH])
{
	switch (spPlayerCoordinate->iPlayerGet)
	{
	case BoxTouch:
		for (int i = 0; i < VALUE_COUNT_BOX; i++)
		{
			if (spSceneBox[i] != NULL)
			{
				for (int y = 0; y < spSceneBox[i]->fLengthY; y++)
				{
					for (int x = 0; x < spSceneBox[i]->fLengthX; x++)
					{
						if ((((int)(spSceneBox[i]->fPostX)) + x) == ((int)(spPlayerCoordinate->Touch.fX)))
						{
							if ((((int)(spSceneBox[i]->fPostY)) + y) == ((int)(spPlayerCoordinate->Touch.fY)))
							{
								InitPlayerSpawn(spSceneBox[i]->fSpeedX, spSceneBox[i]->fSpeedY);
								UninitPlayerMove();
								InitPlayerMove();
								PlayGameSound(SoundTeleport);
								return;
							}
						}
					}
				}
			}
		}
		break;
	case SpawnPointTouch:
		for (int i = 0; i < VALUE_COUNT_SPAWNPOINT; i++)
		{
			if (spSceneSpawnPoint[i] != NULL)
			{
				for (int y = 0; y < spSceneSpawnPoint[i]->fLengthY; y++)
				{
					for (int x = 0; x < spSceneSpawnPoint[i]->fLengthX; x++)
					{
						if ((((int)(spSceneSpawnPoint[i]->fPostX)) + x) == ((int)(spPlayerCoordinate->Touch.fX)))
						{
							if ((((int)(spSceneSpawnPoint[i]->fPostY)) + y) == ((int)(spPlayerCoordinate->Touch.fY)))
							{
								InitPlayerSpawn(spSceneSpawnPoint[i]->fSpeedX, spSceneSpawnPoint[i]->fSpeedY);
								UninitSceneMember(spSceneSpawnPoint[i], Map);
								spSceneSpawnPoint[i] = NULL;
								PlayGameSound(SoundCheckPoint);
								return;
							}
						}
					}
				}
			}
		}
		break;
	case PrickTouch:
		iPlayerDeadCount++;
		return;
		break;
		//case PlatformTouch:
		//	break;
	}

}