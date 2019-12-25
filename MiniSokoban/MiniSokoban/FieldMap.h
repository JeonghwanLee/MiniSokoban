#pragma once
#include "Common.h"

class Object;

class FieldMap
{
public:
	FieldMap();
	~FieldMap();

	FieldMap* CreateCopiedFieldMap();

	void ResetFieldMapWithWalls();
	void SetUpFieldMapLevels(size_t level);

	void PutObject(int x, int y, EObjectTypes objectType);
	void MovePlayerLeft();
	void MovePlayerRight();
	void MovePlayerUp();
	void MovePlayerDown();
	
	size_t GetMapWidth();
	size_t GetMapHeight();

	Object* GetObject(int x, int y);

private:
	void SetFieldMapLevel1();
	void SetFieldMapLevel2();
	void SetFieldMapLevel3();
	void SetFieldMapLevel4();
	void SetFieldMapLevel5();
	void SetFieldMapLevel6();
	// yFrom increases as it goes to downwards.
	bool IsPushable(int xFrom, int yFrom, int xTo, int yTo);
	void StandOnTheWayOrGoal(int xFrom, int yFrom, int xTo, int yTo);
	
	enum { MAP_WIDTH = 20, MAP_HEIGHT = 20 };
	Object* mObjectMap[MAP_WIDTH * MAP_HEIGHT];
	Object* mPlayer;
	unsigned int mPlayerX;
	unsigned int mPlayerY;
};
