#include <stdio.h>
#include <malloc.h>

#include "Enemy.h"
#include "Player.h"
#include "Map.h"


PrickInfo* spSceneBox[VALUE_COUNT_BOX];
PrickInfo* spSceneSpawnPoint[VALUE_COUNT_SPAWNPOINT];
PrickInfo* spScenePrick[VALUE_COUNT_PRICK];
PrickInfo* spScenePlatform[VALUE_COUNT_PLATFORM];

void InitSceneMember(void)
{
	for (int i = 0; i < VALUE_COUNT_BOX; i++)
	{
		spSceneBox[i] = NULL;
	}
	for (int i = 0; i < VALUE_COUNT_SPAWNPOINT; i++)
	{
		spSceneSpawnPoint[i] = NULL;
	}
	for (int i = 0; i < VALUE_COUNT_PRICK; i++)
	{
		spScenePrick[i] = NULL;
	}
	for (int i = 0; i < VALUE_COUNT_PLATFORM; i++)
	{
		spScenePlatform[i] = NULL;
	}
}

PrickInfo* CreateSceneMember(PrickType Type, double PostX, double PostY, double LengthX, double LengthY, double SpeedX, double SpeedY, double MaxX, double MaxY, int(*SceneMap)[MAP_WIDTH])
{
	switch (Type)
	{
	case Box:
		for (int i = 0; i < VALUE_COUNT_BOX; i++)
		{
			if (spSceneBox[i] == NULL)
			{
				spSceneBox[i] = (PrickInfo*)malloc(sizeof(PrickInfo));
				spSceneBox[i]->fInitX = PostX;
				spSceneBox[i]->fInitY = PostY;
				spSceneBox[i]->fPostX = spSceneBox[i]->fInitX;
				spSceneBox[i]->fPostY = spSceneBox[i]->fInitY;
				spSceneBox[i]->fOldPostX = spSceneBox[i]->fPostX;
				spSceneBox[i]->fOldPostY = spSceneBox[i]->fPostY;
				spSceneBox[i]->fLengthX = LengthX;
				spSceneBox[i]->fLengthY = LengthY;
				spSceneBox[i]->fSpeedX = SpeedX;
				spSceneBox[i]->fSpeedY = SpeedY;
				spSceneBox[i]->bMove = true;
				spSceneBox[i]->bChange = false;

				spSceneBox[i]->Type = Type;

				DrawSceneMember(spSceneBox[i], SceneMap);

				return spSceneBox[i];
				break;
			}
		}
		break;
	case SpawnPoint:
		for (int i = 0; i < VALUE_COUNT_SPAWNPOINT; i++)
		{
			if (spSceneSpawnPoint[i] == NULL)
			{
				spSceneSpawnPoint[i] = (PrickInfo*)malloc(sizeof(PrickInfo));
				spSceneSpawnPoint[i]->fInitX = PostX;
				spSceneSpawnPoint[i]->fInitY = PostY;
				spSceneSpawnPoint[i]->fPostX = spSceneSpawnPoint[i]->fInitX;
				spSceneSpawnPoint[i]->fPostY = spSceneSpawnPoint[i]->fInitY;
				spSceneSpawnPoint[i]->fOldPostX = spSceneSpawnPoint[i]->fPostX;
				spSceneSpawnPoint[i]->fOldPostY = spSceneSpawnPoint[i]->fPostY;
				spSceneSpawnPoint[i]->fLengthX = LengthX;
				spSceneSpawnPoint[i]->fLengthY = LengthY;
				spSceneSpawnPoint[i]->fSpeedX = SpeedX;
				spSceneSpawnPoint[i]->fSpeedY = SpeedY;
				spSceneSpawnPoint[i]->bMove = true;
				spSceneSpawnPoint[i]->bChange = false;

				spSceneSpawnPoint[i]->Type = Type;

				DrawSceneMember(spSceneSpawnPoint[i], SceneMap);

				return spSceneSpawnPoint[i];
				break;
			}
		}
		break;
	case Prick:
		for (int i = 0; i < VALUE_COUNT_PRICK; i++)
		{
			if (spScenePrick[i] == NULL)
			{
				spScenePrick[i] = (PrickInfo*)malloc(sizeof(PrickInfo));
				spScenePrick[i]->fInitX = PostX;
				spScenePrick[i]->fInitY = PostY;
				spScenePrick[i]->fPostX = spScenePrick[i]->fInitX;
				spScenePrick[i]->fPostY = spScenePrick[i]->fInitY;
				spScenePrick[i]->fOldPostX = spScenePrick[i]->fPostX;
				spScenePrick[i]->fOldPostY = spScenePrick[i]->fPostY;
				spScenePrick[i]->fLengthX = LengthX;
				spScenePrick[i]->fLengthY = LengthY;
				spScenePrick[i]->fSpeedX = SpeedX;
				spScenePrick[i]->fSpeedY = SpeedY;
				spScenePrick[i]->fMaxX = MaxX;
				spScenePrick[i]->fMaxY = MaxY;
				spScenePrick[i]->bMove = true;
				spScenePrick[i]->bChange = false;

				spScenePrick[i]->Type = Type;

				DrawSceneMember(spScenePrick[i], SceneMap);

				return spScenePrick[i];
				break;
			}
		}
		break;
	case Platform:
		for (int i = 0; i < VALUE_COUNT_PLATFORM; i++)
		{
			if (spScenePlatform[i] == NULL)
			{
				spScenePlatform[i] = (PrickInfo*)malloc(sizeof(PrickInfo));
				spScenePlatform[i]->fInitX = PostX;
				spScenePlatform[i]->fInitY = PostY;
				spScenePlatform[i]->fPostX = spScenePlatform[i]->fInitX;
				spScenePlatform[i]->fPostY = spScenePlatform[i]->fInitY;
				spScenePlatform[i]->fOldPostX = spScenePlatform[i]->fPostX;
				spScenePlatform[i]->fOldPostY = spScenePlatform[i]->fPostY;
				spScenePlatform[i]->fLengthX = LengthX;
				spScenePlatform[i]->fLengthY = LengthY;
				spScenePlatform[i]->fSpeedX = SpeedX;
				spScenePlatform[i]->fSpeedY = SpeedY;
				spScenePlatform[i]->fMaxX = MaxX;
				spScenePlatform[i]->fMaxY = MaxY;
				spScenePlatform[i]->bMove = true;
				spScenePlatform[i]->bChange = false;

				spScenePlatform[i]->Type = Type;

				DrawSceneMember(spScenePlatform[i], SceneMap);

				return spScenePlatform[i];
				break;
			}
		}
		break;
	}
}

int iSceneMemberMoveRate = 0;

void SceneMemberMove(PrickInfo* SceneMember)
{

	//iSceneMemberMoveRate = (iSceneMemberMoveRate + 1) % VALUE_SCENEMEMBER_MOVERATE;
	if (SceneMember == NULL)
	{
		return;
	}

	switch (SceneMember->Type)
	{
	case Prick:
		SceneMember->fOldPostX = SceneMember->fPostX;
		SceneMember->fOldPostY = SceneMember->fPostY;

		SceneMember->fPostX += SceneMember->fSpeedX;
		SceneMember->fPostY += SceneMember->fSpeedY;

		SceneMember->bMove = true;
		break;
	case Platform:
		SceneMember->fOldPostX = SceneMember->fPostX;
		SceneMember->fOldPostY = SceneMember->fPostY;

		SceneMember->fPostX += SceneMember->fSpeedX;
		SceneMember->fPostY += SceneMember->fSpeedY;

		SceneMember->bMove = true;
		break;
	}
}

void DrawSceneMember(PrickInfo* SceneMember, int(*SceneMap)[MAP_WIDTH])
{
	if (SceneMember == NULL)
	{
		return;
	}
	int x, y, ox, oy, lx, ly, type;
	x = ((int)(SceneMember->fPostX));
	y = ((int)(SceneMember->fPostY));
	ox = ((int)(SceneMember->fOldPostX));
	oy = ((int)(SceneMember->fOldPostY));
	lx = ((int)(SceneMember->fLengthX));
	ly = ((int)(SceneMember->fLengthY));
	switch (SceneMember->Type)
	{
	case Box:
		type = 2;
		break;
	case SpawnPoint:
		type = 3;
		break;
	case Prick:
		type = 4;
		break;
	case Platform:
		type = 1;
		break;
	}

	if (SceneMember->bMove == true)
	{
		for (int iy = 0; iy < ly; iy++)
		{
			for (int ix = 0; ix < lx; ix++)
			{
				SceneMap[oy - 1 + iy][ox - 1 + ix] = 0;
			}
		}

		for (int iy = 0; iy < ly; iy++)
		{
			for (int ix = 0; ix < lx; ix++)
			{
				SceneMap[y - 1 + iy][x - 1 + ix] = type;
			}
		}
		SceneMember->bMove == false;
	}
}

//void IfEffectPlayer(PrickInfo* SceneMember)
//{
//	switch (SceneMember->Type)
//	{
//	case Box:
//		//TODO
//		break;
//	case SpawnPoint:
//		//TODO
//		break;
//	case Prick:
//		//TODO
//		break;
//	case Platform:
//		//TODO
//		break;
//	default:
//		break;
//	}
//}

void UninitSceneMember(PrickInfo* SceneMember, int(*SceneMap)[MAP_WIDTH])
{
	if (SceneMember == NULL)
	{
		return;
	}
	int x, y, ox, oy, lx, ly;
	x = ((int)(SceneMember->fPostX));
	y = ((int)(SceneMember->fPostY));
	ox = ((int)(SceneMember->fOldPostX));
	oy = ((int)(SceneMember->fOldPostY));
	lx = ((int)(SceneMember->fLengthX));
	ly = ((int)(SceneMember->fLengthY));

	for (int iy = 0; iy < ly; iy++)
	{
		for (int ix = 0; ix < lx; ix++)
		{
			SceneMap[oy - 1 + iy][ox - 1 + ix] = Black;
		}
	}

	for (int iy = 0; iy < ly; iy++)
	{
		for (int ix = 0; ix < lx; ix++)
		{
			SceneMap[y - 1 + iy][x - 1 + ix] = Black;
		}
	}

	free(SceneMember);
	SceneMember = NULL;
}

void ChangeSceneMemberMove(PrickInfo* SceneMember)
{
	if (SceneMember == NULL)
	{
		return;
	}
	if ((SceneMember->fPostX < SceneMember->fMaxX) && (SceneMember->bChange == false))
	{
		SceneMember->fSpeedX = (-1)*(SceneMember->fSpeedX);
		SceneMember->fSpeedY = (-1)*(SceneMember->fSpeedY);
		SceneMember->bChange = true;
	}
	else if ((SceneMember->fPostY < SceneMember->fMaxY) && (SceneMember->bChange == false))
	{
		SceneMember->fSpeedX = (-1)*(SceneMember->fSpeedX);
		SceneMember->fSpeedY = (-1)*(SceneMember->fSpeedY);
		SceneMember->bChange = true;
	}
	else if ((SceneMember->fPostX > SceneMember->fInitX) && (SceneMember->bChange == true))
	{
		SceneMember->fSpeedX = (-1)*(SceneMember->fSpeedX);
		SceneMember->fSpeedY = (-1)*(SceneMember->fSpeedY);
		SceneMember->bChange = false;
	}
	else if ((SceneMember->fPostY > SceneMember->fInitY) && (SceneMember->bChange == true))
	{
		SceneMember->fSpeedX = (-1)*(SceneMember->fSpeedX);
		SceneMember->fSpeedY = (-1)*(SceneMember->fSpeedY);
		SceneMember->bChange = false;
	}
}

PlatformEffectPlayer IfPlatformEffectPlayer(PrickInfo* SceneMember)
{
	if (SceneMember == NULL)
	{
		return NotEffectPlayer;
	}
	int x, y, lx, ly, px, py;
	x = (int)(SceneMember->fPostX);
	y = (int)(SceneMember->fPostY);
	px = (int)(spPlayerCoordinate->fDropX);
	py = (int)(spPlayerCoordinate->fDropY);
	lx = (int)(SceneMember->fLengthX);
	ly = (int)(SceneMember->fLengthY);
	for (int iy = 0; iy < ly; iy++)
	{
		for (int ix = 0; ix < lx; ix++)
		{
			if ((iy + y - 2) == py)
			{
				if ((ix + x) == px)
				{
					if (spPlayerCoordinate->bLand)
					{
						return EffectPlayerLand;
					}
				}
				if ((ix + x) == (px + 1))
				{
					if (spPlayerCoordinate->bLand)
					{
						return EffectPlayerLand;
					}
				}
			}
			if ((iy + y) == py)
			{
				if ((ix + x - 2) == px)
				{
					if (spPlayerCoordinate->bClimb)
					{
						return EffectPlayerClimb;
					}
				}
				if ((ix + x + 1) == px)
				{
					if (spPlayerCoordinate->bClimb)
					{
						return EffectPlayerClimb;
					}
				}
			}
			if ((iy + y) == (py + 1))
			{
				if ((ix + x - 2) == px)
				{
					if (spPlayerCoordinate->bClimb)
					{
						return EffectPlayerClimb;
					}
				}
				if ((ix + x + 1) == px)
				{
					if (spPlayerCoordinate->bClimb)
					{
						return EffectPlayerClimb;
					}
				}
			}
		}
	}
	return NotEffectPlayer;
}

void UpdateSceneMember(int(*SceneMap)[MAP_WIDTH])
{
	//for (int i = 0; i < VALUE_COUNT_BOX; i++)
	//{
	//	if (spSceneBox[i] != NULL)
	//	{
	//		//TODO
	//	}
	//}
	//for (int i = 0; i < VALUE_COUNT_SPAWNPOINT; i++)
	//{
	//	if (spSceneSpawnPoint[i] != NULL)
	//	{
	//		//TODO
	//	}
	//}

	int iIPEP;
	iIPEP = 0;

	for (int i = 0; i < VALUE_COUNT_PRICK; i++)
	{
		if (spScenePrick[i] != NULL)
		{
			SceneMemberMove(spScenePrick[i]);
			DrawSceneMember(spScenePrick[i], SceneMap);
			ChangeSceneMemberMove(spScenePrick[i]);
		}
	}
	for (int i = 0; i < VALUE_COUNT_PLATFORM; i++)
	{
		if (spScenePlatform[i] != NULL)
		{
			iIPEP = 0;
			iIPEP = IfPlatformEffectPlayer(spScenePlatform[i]);
			switch (iIPEP)
			{
			case EffectPlayerLand:
				spPlayerCoordinate->fDropX += spScenePlatform[i]->fSpeedX;
				spPlayerCoordinate->fDropY = (spScenePlatform[i]->fPostY - 2.00f) + spScenePlatform[i]->fSpeedY;
				spPlayerCoordinate->bMove = true;
				spPlayerCoordinate->bLand = true;
				break;
			case EffectPlayerClimb:
				spPlayerCoordinate->fDropX += spScenePlatform[i]->fSpeedX;
				spPlayerCoordinate->fDropY += spScenePlatform[i]->fSpeedY;
				spPlayerCoordinate->bMove = true;
				spPlayerCoordinate->bClimb = true;
				break;
			}
			SceneMemberMove(spScenePlatform[i]);
			DrawSceneMember(spScenePlatform[i], SceneMap);
			ChangeSceneMemberMove(spScenePlatform[i]);
		}
	}
}

void DeleteAllSceneMember(void)
{
	for (int i = 0; i < VALUE_COUNT_BOX; i++)
	{
		if (spSceneBox[i] != NULL)
		{
			free(spSceneBox[i]);
			spSceneBox[i] = NULL;
		}
	}
	for (int i = 0; i < VALUE_COUNT_SPAWNPOINT; i++)
	{
		if (spSceneSpawnPoint[i] != NULL)
		{
			free(spSceneSpawnPoint[i]);
			spSceneSpawnPoint[i] = NULL;
		}
	}
	for (int i = 0; i < VALUE_COUNT_PRICK; i++)
	{
		if (spScenePrick[i] != NULL)
		{
			free(spScenePrick[i]);
			spScenePrick[i] = NULL;
		}
	}
	for (int i = 0; i < VALUE_COUNT_PLATFORM; i++)
	{
		if (spScenePlatform[i] != NULL)
		{
			free(spScenePlatform[i]);
			spScenePlatform[i] = NULL;
		}
	}
}