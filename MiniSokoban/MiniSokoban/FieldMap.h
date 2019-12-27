#pragma once
#include "Common.h"

class Object;

class FieldMap
{
public:
	FieldMap();
	FieldMap(const FieldMap& other);
	~FieldMap();

	void ResetFieldMapWithWalls();
	void SetUpFieldMapByLevel(size_t level);

	void PutObject(int x, int y, EObjectTypes objectType);
	void MovePlayerLeft();
	void MovePlayerRight();
	void MovePlayerUp();
	void MovePlayerDown();
	
	Object* GetObject(int x, int y);

	enum { MAP_WIDTH = 20, MAP_HEIGHT = 20 };

private:
	// yFrom increases as it goes to downwards
	bool IsPushable(int xFrom, int yFrom, int xTo, int yTo);
	void MoveObjectFromTo(int xFrom, int yFrom, int xTo, int yTo);

	void SetFieldMapLevel1();
	void SetFieldMapLevel2();
	void SetFieldMapLevel3();
	void SetFieldMapLevel4();
	void SetFieldMapLevel5();
	void SetFieldMapLevel6();

	Object* mObjectMap[MAP_WIDTH * MAP_HEIGHT];
	Object* mPlayer;
	unsigned int mPlayerX;
	unsigned int mPlayerY;
	bool bMoveNextObject;
};
