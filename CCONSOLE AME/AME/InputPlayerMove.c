#include "InputLib.h"
#include "Player.h"
#include "ConioEx.h"
#include "MusicLib.h"


void UpdateInputPlayerMove(int(*Map)[VALUE_MAP_WIDTH])
{
	//ReInport();
	if (Inport(RIGHT_KEY))
	{
		if (!spPlayerCoordinate->bSpeedUp)
		{
			spPlayerCoordinate->bMove = true;
			spPlayerCoordinate->fMoveX += spPlayerCoordinate->fSpeedX;
			if (spPlayerCoordinate->fMoveX > spPlayerCoordinate->fSpeedX)
			{
				spPlayerCoordinate->fMoveX = spPlayerCoordinate->fSpeedX;
			}
		}
		if (spPlayerCoordinate->bSpeedUp)
		{
			spPlayerCoordinate->bMove = true;
			spPlayerCoordinate->fMoveX += 1.3 * spPlayerCoordinate->fSpeedX;
			if (spPlayerCoordinate->fMoveX > (1.3 * spPlayerCoordinate->fSpeedX))
			{
				spPlayerCoordinate->fMoveX = 1.3 * spPlayerCoordinate->fSpeedX;
			}
			spPlayerCoordinate->bSpeedUp = false;
		}
		if ((Map[((int)(spPlayerCoordinate->fDropY)) - 1][((int)(spPlayerCoordinate->fDropX + 2.0)) - 1]) == 1)
		{
			if ((Map[((int)(spPlayerCoordinate->fDropY + 1.0)) - 1][((int)(spPlayerCoordinate->fDropX + 2.0)) - 1]) == 1)
			{
				spPlayerCoordinate->fMoveX = 0;
				spPlayerCoordinate->bClimb = true;
			}
		}
	}
	if (Inport(LEFT_KEY))
	{
		if (!spPlayerCoordinate->bSpeedUp)
		{
			spPlayerCoordinate->bMove = true;
			spPlayerCoordinate->fMoveX -= spPlayerCoordinate->fSpeedX;
			if (spPlayerCoordinate->fMoveX < (0.0 - spPlayerCoordinate->fSpeedX))
			{
				spPlayerCoordinate->fMoveX = (0.0 - spPlayerCoordinate->fSpeedX);
			}
		}
		if (spPlayerCoordinate->bSpeedUp)
		{
			spPlayerCoordinate->bMove = true;
			spPlayerCoordinate->fMoveX -= 1.3 * spPlayerCoordinate->fSpeedX;
			if (spPlayerCoordinate->fMoveX < (1.3 * (0.0 - spPlayerCoordinate->fSpeedX)))
			{
				spPlayerCoordinate->fMoveX = (1.3 * (0.0 - spPlayerCoordinate->fSpeedX));
			}
			spPlayerCoordinate->bSpeedUp = false;
		}
		if ((Map[((int)(spPlayerCoordinate->fDropY)) - 1][((int)(spPlayerCoordinate->fDropX - 1.0)) - 1]) == 1)
		{
			if ((Map[((int)(spPlayerCoordinate->fDropY + 1.0)) - 1][((int)(spPlayerCoordinate->fDropX - 1.0)) - 1]) == 1)
			{
				spPlayerCoordinate->fMoveX = 0;
				spPlayerCoordinate->bClimb = true;
			}
		}
	}
	if (Inport(JUMP_KEY))
	{
		if (((spPlayerCoordinate->bLand && spPlayerCoordinate->bJumpOver) || (spPlayerCoordinate->bClimb)) && (!spPlayerCoordinate->bWallJump))
		{
			spPlayerCoordinate->bMove = true;
			spPlayerCoordinate->bJump = true;
			spPlayerCoordinate->bJumpOver = false;
			spPlayerCoordinate->bLand = false;
			spPlayerCoordinate->fJumpDropY = spPlayerCoordinate->fDropY;
			if (spPlayerCoordinate->bClimb)
			{
				spPlayerCoordinate->bWallJump = true;
			}
		}
		//if ((spPlayerCoordinate->bClimb) && (!spPlayerCoordinate->bLand))
		//{
		//	spPlayerCoordinate->bMove = true;
		//	spPlayerCoordinate->bJump = true;
		//	spPlayerCoordinate->bJumpOver = false;
		//	spPlayerCoordinate->bLand = false;
		//	spPlayerCoordinate->fJumpDropY = spPlayerCoordinate->fDropY;
		//	switch (spPlayerCoordinate->iPNC)
		//	{
		//	case LeftCrash:
		//		if (!spPlayerCoordinate->bSpeedUp)
		//		{
		//			spPlayerCoordinate->bMove = true;
		//			spPlayerCoordinate->fMoveX += spPlayerCoordinate->fSpeedX;
		//			if (spPlayerCoordinate->fMoveX > spPlayerCoordinate->fSpeedX)
		//			{
		//				spPlayerCoordinate->fMoveX = spPlayerCoordinate->fSpeedX;
		//			}
		//		}
		//		if (spPlayerCoordinate->bSpeedUp)
		//		{
		//			spPlayerCoordinate->bMove = true;
		//			spPlayerCoordinate->fMoveX += 2.0* spPlayerCoordinate->fSpeedX;
		//			if (spPlayerCoordinate->fMoveX > (2.0 * spPlayerCoordinate->fSpeedX))
		//			{
		//				spPlayerCoordinate->fMoveX = 2.0 * spPlayerCoordinate->fSpeedX;
		//			}
		//			spPlayerCoordinate->bSpeedUp = false;
		//		}
		//		break;
		//	case RightCrash:
		//		if (!spPlayerCoordinate->bSpeedUp)
		//		{
		//			spPlayerCoordinate->bMove = true;
		//			spPlayerCoordinate->fMoveX -= spPlayerCoordinate->fSpeedX;
		//			if (spPlayerCoordinate->fMoveX < (0.0 - spPlayerCoordinate->fSpeedX))
		//			{
		//				spPlayerCoordinate->fMoveX = (0.0 - spPlayerCoordinate->fSpeedX);
		//			}
		//		}
		//		if (spPlayerCoordinate->bSpeedUp)
		//		{
		//			spPlayerCoordinate->bMove = true;
		//			spPlayerCoordinate->fMoveX -= 2.0 * spPlayerCoordinate->fSpeedX;
		//			if (spPlayerCoordinate->fMoveX < (2.0 * (0.0 - spPlayerCoordinate->fSpeedX)))
		//			{
		//				spPlayerCoordinate->fMoveX = (2.0 * (0.0 - spPlayerCoordinate->fSpeedX));
		//			}
		//			spPlayerCoordinate->bSpeedUp = false;
		//		}
		//		break;
		//	default:
		//		break;
		//	}
		//}
	}
	if (Inport(PK_X))
	{
		spPlayerCoordinate->bSpeedUp = true;
	}
	if (Inport(ENTER_KEY))
	{
		_exit(0);
	}
}