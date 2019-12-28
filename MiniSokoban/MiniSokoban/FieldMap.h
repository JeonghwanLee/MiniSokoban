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
	
	Object* GetObjectFromMap(int x, int y) const;

	enum { MAP_WIDTH = 20, MAP_HEIGHT = 20 };

private:
	// yFrom increases as it goes to downwards
	bool isPushable(int xFrom, int yFrom, int xTo, int yTo);
	void moveObjectFromTo(int xFrom, int yFrom, int xTo, int yTo);

	void setFieldMapLevel1();
	void setFieldMapLevel2();
	void setFieldMapLevel3();
	void setFieldMapLevel4();
	void setFieldMapLevel5();
	void setFieldMapLevel6();

	Object* mObjectMap[MAP_WIDTH * MAP_HEIGHT];
	Object* mPlayer;
	unsigned int mPlayerX;
	unsigned int mPlayerY;
	bool mbMoveNextObject;
};
