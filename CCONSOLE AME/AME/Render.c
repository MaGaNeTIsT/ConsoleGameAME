#include "Render.h"
#include "ConioEx.h"
#include "Player.h"
#include "Map.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void DrawPlayerMove(void)
{
	TextAttr(0xb0);
	//GotoXY(40, 12);
	//printf("x=%4fy=%4f", spPlayerCoordinate->fDropX, spPlayerCoordinate->fDropY);
	GotoXY(40,13);
	printf("==");
	GotoXY(40,14);
	printf("||");
}

void DrawPlayerDeadCount(void)
{
	GotoXY(10, 26);
	printf("DeathCount:%d", iPlayerDeadCount);
}

char cTextMapFrame[((VALUE_SCREEN_HEIGHT + 1)*((2 * VALUE_SCREEN_WIDTH) + 2))] = "\0";
char *spMapFrame = cTextMapFrame;
int iMapX = 0, iMapY = 0;
ScreenFlashPri eMapPrintLogic = Calculate;

void InitMap(int(*Map)[VALUE_MAP_WIDTH], char *gspMapFrame)
{
	TextAttr(0xb0);
	GotoXY(1, 1);
	iMapX = 0;
	iMapY = 0;
	iMapX = ((int)(spPlayerCoordinate->fDropX)) - 39 - 1;
	iMapY = ((int)(spPlayerCoordinate->fDropY)) - 12 - 1;
	cTextMapFrame[0] = '\0';
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x == VALUE_SCREEN_WIDTH)
			{
				strcat(gspMapFrame, "\n");
				if (y == (VALUE_SCREEN_HEIGHT - 1))
				{
					printf(gspMapFrame);
					cTextMapFrame[0] = '\0';
				}
			}
			else {
				switch (Map[iMapY + y][iMapX + x])
				{
				case -1:
					strcat(gspMapFrame, " ");
					if (x == (VALUE_SCREEN_WIDTH - 1))
					{
						if (y != (VALUE_SCREEN_HEIGHT - 1))
						{
							if (Map[iMapY + y + 1][iMapX] != -1)
							{
								printf(gspMapFrame);
								cTextMapFrame[0] = '\0';
							}
						}
					}
					else {
						if (Map[iMapY + y][iMapX + x + 1] != -1)
						{
							printf(gspMapFrame);
							cTextMapFrame[0] = '\0';
						}
					}
					break;
				case Black:
					strcat(gspMapFrame, " ");
					if (x == (VALUE_SCREEN_WIDTH - 1))
					{
						if (y != (VALUE_SCREEN_HEIGHT - 1))
						{
							if (Map[iMapY + y + 1][iMapX] != Black)
							{
								printf(gspMapFrame);
								cTextMapFrame[0] = '\0';
							}
						}
					}
					else {
						if (Map[iMapY + y][iMapX + x + 1] != Black)
						{
							printf(gspMapFrame);
							cTextMapFrame[0] = '\0';
						}
					}
					break;
				case Land:
					strcat(gspMapFrame, " ");
					if (x == (VALUE_SCREEN_WIDTH - 1))
					{
						if (y != (VALUE_SCREEN_HEIGHT - 1))
						{
							if (Map[iMapY + y + 1][iMapX] != Land)
							{
								TextAttr(0xf0);
								printf(gspMapFrame);
								cTextMapFrame[0] = '\0';
								TextAttr(0xb0);
							}
						}
					}
					else {
						if (Map[iMapY + y][iMapX + x + 1] != Land)
						{
							TextAttr(0xf0);
							printf(gspMapFrame);
							cTextMapFrame[0] = '\0';
							TextAttr(0xb0);
						}
					}
					break;
				case 2:
					strcat(gspMapFrame, " ");
					if (x == (VALUE_SCREEN_WIDTH - 1))
					{
						if (y != (VALUE_SCREEN_HEIGHT - 1))
						{
							if (Map[iMapY + y + 1][iMapX] != 2)
							{
								TextAttr(0x10);
								printf(gspMapFrame);
								cTextMapFrame[0] = '\0';
								TextAttr(0xb0);
							}
						}
					}
					else {
						if (Map[iMapY + y][iMapX + x + 1] != 2)
						{
							TextAttr(0x10);
							printf(gspMapFrame);
							cTextMapFrame[0] = '\0';
							TextAttr(0xb0);
						}
					}
					break;
				case 3:
					strcat(gspMapFrame, "*");
					if (x == (VALUE_SCREEN_WIDTH - 1))
					{
						if (y != (VALUE_SCREEN_HEIGHT - 1))
						{
							if (Map[iMapY + y + 1][iMapX] != 3)
							{
								TextAttr(0x20);
								printf(gspMapFrame);
								cTextMapFrame[0] = '\0';
								TextAttr(0xb0);
							}
						}
					}
					else {
						if (Map[iMapY + y][iMapX + x + 1] != 3)
						{
							TextAttr(0x20);
							printf(gspMapFrame);
							cTextMapFrame[0] = '\0';
							TextAttr(0xb0);
						}
					}
					break;
				case 4:
					strcat(gspMapFrame, "^");
					if (x == (VALUE_SCREEN_WIDTH - 1))
					{
						if (y != (VALUE_SCREEN_HEIGHT - 1))
						{
							if (Map[iMapY + y + 1][iMapX] != 4)
							{
								TextAttr(0x40);
								printf(gspMapFrame);
								cTextMapFrame[0] = '\0';
								TextAttr(0xb0);
							}
						}
					}
					else {
						if (Map[iMapY + y][iMapX + x + 1] != 4)
						{
							TextAttr(0x40);
							printf(gspMapFrame);
							cTextMapFrame[0] = '\0';
							TextAttr(0xb0);
						}
					}
					break;
				}
			}
		}
	}
}


//void MapBlockCalculate(int(*Map)[VALUE_MAP_WIDTH], int y, int x, char *gspMapFrame)
//{
//	switch (Map[iMapY + y][iMapX + x])
//	{
//	case Black:
//		strcat(gspMapFrame, " ");
//		if (x == (VALUE_SCREEN_WIDTH - 1))
//		{
//			if ((((iMapY + y + 1) < 0) || ((iMapX) < 0)) || (((iMapY + y + 1) > (VALUE_MAP_HEIGHT - 1)) || ((iMapX) > (VALUE_MAP_WIDTH - 1))))
//			{
//				//TextAttr(0xb0);
//				printf(gspMapFrame);
//				cTextMapFrame[0] = '\0';
//			}
//			else
//			{
//				if ((Map[iMapY + y + 1][iMapX]) != Black)
//				{
//					//TextAttr(0xb0);
//					printf(gspMapFrame);
//					cTextMapFrame[0] = '\0';
//				}
//			}
//		}
//		else
//		{
//			if ((((iMapY + y) < 0) || ((iMapX + x + 1) < 0)) || (((iMapY + y) > (VALUE_MAP_HEIGHT - 1)) || ((iMapX + x + 1) > (VALUE_MAP_WIDTH - 1))))
//			{
//				//TextAttr(0xb0);
//				printf(gspMapFrame);
//				cTextMapFrame[0] = '\0';
//			}
//			if ((Map[iMapY + y][iMapX + x + 1]) != Black)
//			{
//				//TextAttr(0xb0);
//				printf(gspMapFrame);
//				cTextMapFrame[0] = '\0';
//			}
//		}
//		break;
//	case Land:
//		strcat(gspMapFrame, " ");
//		if (x == (VALUE_SCREEN_WIDTH - 1))
//		{
//			if ((((iMapY + y + 1) < 0) || ((iMapX) < 0)) || (((iMapY + y + 1) > (VALUE_MAP_HEIGHT - 1)) || ((iMapX) > (VALUE_MAP_WIDTH - 1))))
//			{
//				TextAttr(0xf0);
//				printf(gspMapFrame);
//				cTextMapFrame[0] = '\0';
//				TextAttr(0xb0);
//			}
//			else
//			{
//				if ((Map[iMapY + y + 1][iMapX]) != Land)
//				{
//					TextAttr(0xf0);
//					printf(gspMapFrame);
//					cTextMapFrame[0] = '\0';
//					TextAttr(0xb0);
//				}
//			}
//		}
//		else
//		{
//			if ((((iMapY + y) < 0) || ((iMapX + x + 1) < 0)) || (((iMapY + y) > (VALUE_MAP_HEIGHT - 1)) || ((iMapX + x + 1) > (VALUE_MAP_WIDTH - 1))))
//			{
//				TextAttr(0xf0);
//				printf(gspMapFrame);
//				cTextMapFrame[0] = '\0';
//				TextAttr(0xb0);
//			}
//			if ((Map[iMapY + y][iMapX + x + 1]) != Land)
//			{
//				TextAttr(0xf0);
//				printf(gspMapFrame);
//				cTextMapFrame[0] = '\0';
//				TextAttr(0xb0);
//			}
//		}
//		break;
//	default:
//		break;
//	}
//}

//RainSnowInfo SRainSnowStart;
//RainSnowInfo SRainSnowEnd;
RainSnowInfo* spRainSnow[COUNT_ALL_RAINSNOW];
int iRainSnowRate = 0;
RainorSnow eRainorSnow = Rain;
int iRainSnowMap[VALUE_SCREEN_HEIGHT][VALUE_SCREEN_WIDTH] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};
char cRainSnowMap[VALUE_SCREEN_HEIGHT*(VALUE_SCREEN_WIDTH + 2)] = "\0";
char* cspRainSnowMap = cRainSnowMap;

void InitRainSnow(void)
{
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		spRainSnow[i] = NULL;
	}
}
void InitMemberRainSnow(void)
{
	int iRandom=0;
	int iRainSnowCount[COUNT_LINE_RAINSNOW + RANDOM_COUNT_LINE] = { 0 };
	srand((unsigned)time(NULL));
	iRandom = COUNT_LINE_RAINSNOW + (rand() % RANDOM_COUNT_LINE);
	for (int i = 0; i < iRandom; i++)
	{
		iRainSnowCount[i] = rand() % (VALUE_SCREEN_HEIGHT + VALUE_SCREEN_WIDTH - 1);
	}
	for (int x = 0; x < iRandom; x++)
	{
		for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
		{
			if (spRainSnow[i] == NULL)
			{
				spRainSnow[i] = (RainSnowInfo*)malloc(sizeof(RainSnowInfo));
				spRainSnow[i]->bExist = 1;
				spRainSnow[i]->fDropX = ((double)(iRainSnowCount[x])) + 1.0;
				//spRainSnow[i]->fOldDropX = spRainSnow[i]->fDropX;
				spRainSnow[i]->fDropY = 1.0;
				//spRainSnow[i]->fOldDropY = spRainSnow[i]->fDropY;
				spRainSnow[i]->fSpeedX = -1.0;//(0.0 - (1.0 / ((double)(60 / RAINSNOWRATE))));
				spRainSnow[i]->fSpeedY = SPEED_RAIN_SNOW;//SPEED_RAIN_SNOW / ((double)(60 / RAINSNOWRATE));
				break;
			}
		}
	}
}
void UninitMemberRainSnow(void)
{
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			if ((spRainSnow[i]->fDropX < 1.0) || (spRainSnow[i]->fDropY > ((double)(VALUE_SCREEN_HEIGHT))))
			{
				spRainSnow[i]->bExist = 0;
			}
		}
	}
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			if (spRainSnow[i]->bExist == 0)
			{
				free(spRainSnow[i]);
				spRainSnow[i] = NULL;
			}
		}
	}
}
void RainingSnowing(void)
{
	iRainSnowRate = (iRainSnowRate + 1) % RAINSNOWRATE;
	if (iRainSnowRate == 0)
	{
		for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
		{
			if (spRainSnow[i] != NULL)
			{
				//spRainSnow[i]->fOldDropX = spRainSnow[i]->fDropX;
				spRainSnow[i]->fDropX += spRainSnow[i]->fSpeedX;

				//spRainSnow[i]->fOldDropY = spRainSnow[i]->fDropY;
				spRainSnow[i]->fDropY += spRainSnow[i]->fSpeedY;
			}
		}
		InitMemberRainSnow();
		UninitMemberRainSnow();
		//srand((unsigned)time(NULL));
		//for (int i = 0; i < ((rand() % (RANDOM_COUNT_LINE)) + COUNT_LINE_RAINSNOW); i++)
		//{
		//	InitMemberRainSnow();
		//}
	}
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			iRainSnowMap[y][x] = 0;
		}
	}
	for (int i = 0; i < COUNT_ALL_RAINSNOW; i++)
	{
		if (spRainSnow[i] != NULL)
		{
			DrawRainSnow(spRainSnow[i]);
		}
	}
	for (int y = 0; y < VALUE_SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < (VALUE_SCREEN_WIDTH + 1); x++)
		{
			if (x != VALUE_SCREEN_WIDTH)
			{
				switch (iRainSnowMap[y][x])
				{
				case 0:
					strcat(cspRainSnowMap, " ");
					break;
				case 1:
					switch (eRainorSnow)
					{
					case Rain:
						strcat(cspRainSnowMap, "/");
						break;
					case Snow:
						strcat(cspRainSnowMap, "*");
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
			else {
				if (y != (VALUE_SCREEN_HEIGHT - 1))
				{
					strcat(cspRainSnowMap, "\n");
				}
				else {
					strcat(cspRainSnowMap, "\0");
				}
			}
		}
	}
	TextAttr(0xbf);
	GotoXY(1, 1);
	printf(cspRainSnowMap);
	cRainSnowMap[0] = '\0';
}
void DrawRainSnow(RainSnowInfo* spRainSnow)
{
	if ((spRainSnow->fDropX > 1.0) && (spRainSnow->fDropY > 1.0))
	{
		if ((spRainSnow->fDropX < 80.0) && (spRainSnow->fDropY < 26.0))
		{
			iRainSnowMap[((int)(spRainSnow->fDropY)) - 1][((int)(spRainSnow->fDropX)) - 1] = 1;
		}
	}
}

void PrintText(char* Text, int x, int y)
{
	GotoXY(x, y);
	TextAttr(0xb0);
	printf(Text);
}