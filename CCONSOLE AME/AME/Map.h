#ifndef _MAP_H_
#define _MAP_H_


#define MAP_WIDTH 398
#define MAP_HEIGHT 74

#define VALUE_LIMIT_LEFT (1.0)
#define VALUE_LIMIT_RIGHT (398.0)
#define VALUE_LIMIT_TOP (1.0)
#define VALUE_LIMIT_BOTTOM (60.0)

typedef enum EMapBlockProperty{
	Black = 0,
	Land
}MapBlockProperty;

typedef enum EScreenFlashPri {
	Calculate = 0,
	PrintOut
}ScreenFlashPri;

void InitMapBlock(int(*SceneMap)[MAP_WIDTH], int(*LogicMap)[MAP_WIDTH]);

extern ScreenFlashPri eMapPrintLogic;
extern int bTutorLogicMap[MAP_HEIGHT][MAP_WIDTH];
extern int bTutorSceneMap[MAP_HEIGHT][MAP_WIDTH];
extern bStage1LogicMap[MAP_HEIGHT][MAP_WIDTH];
extern bStage1SceneMap[MAP_HEIGHT][MAP_WIDTH];
extern bStage2LogicMap[MAP_HEIGHT][MAP_WIDTH];
extern bStage2SceneMap[MAP_HEIGHT][MAP_WIDTH];
extern bBossStageLogicMap[MAP_HEIGHT][MAP_WIDTH];
extern bBossStageSceneMap[MAP_HEIGHT][MAP_WIDTH];


#endif // !_MAP_H_