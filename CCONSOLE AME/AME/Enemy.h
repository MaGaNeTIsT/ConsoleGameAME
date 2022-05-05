#ifndef _ENEMY_H_
#define _ENEMY_H_

#define VALUE_COUNT_BOX 3
#define VALUE_COUNT_SPAWNPOINT 5
#define VALUE_COUNT_PRICK 25
#define VALUE_COUNT_PLATFORM 15

#define VALUE_SCENEMEMBER_MOVERATE 4

#define MAP_WIDTH 398

typedef enum EPrickType {
	Box = 2,
	SpawnPoint,
	Prick,
	Platform
}PrickType;

typedef struct SPrickInfo {
	double fPostX;
	double fPostY;
	double fOldPostX;
	double fOldPostY;
	double fLengthX;
	double fLengthY;
	double fSpeedX;
	double fSpeedY;
	double fMaxX;
	double fMaxY;
	double fInitX;
	double fInitY;
	//double fDamage;

	int bChange;
	int bMove;
	PrickType Type;
}PrickInfo;
extern PrickInfo* spSceneBox[VALUE_COUNT_BOX];
extern PrickInfo* spSceneSpawnPoint[VALUE_COUNT_SPAWNPOINT];
extern PrickInfo* spScenePrick[VALUE_COUNT_PRICK];
extern PrickInfo* spScenePlatform[VALUE_COUNT_PLATFORM];
extern PrickInfo* Boss;

extern int iSceneMemberMoveRate;

typedef enum EIfPlatformEffectPlayer {
	NotEffectPlayer = 0,
	EffectPlayerLand,
	EffectPlayerClimb
}PlatformEffectPlayer;

void InitSceneMember(void);
PrickInfo* CreateSceneMember(PrickType Type, double PostX, double PostY, double LengthX, double LengthY, double SpeedX, double SpeedY, double MaxX, double MaxY, int(*SceneMap)[MAP_WIDTH]);
void SceneMemberMove(PrickInfo* SceneMember);
void DrawSceneMember(PrickInfo* SceneMember, int(*SceneMap)[MAP_WIDTH]);
void UninitSceneMember(PrickInfo* SceneMember, int(*SceneMap)[MAP_WIDTH]);
void ChangeSceneMemberMove(PrickInfo* SceneMember);
PlatformEffectPlayer IfPlatformEffectPlayer(PrickInfo* SceneMember);
void UpdateSceneMember(int(*SceneMap)[MAP_WIDTH]);
void DeleteAllSceneMember(void);

#endif // !_ENEMY_H_