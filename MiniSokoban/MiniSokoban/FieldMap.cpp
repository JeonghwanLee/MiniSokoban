#include "FieldMap.h"
#include "Object.h"

FieldMap::FieldMap()
	: mObjectMap { nullptr }
	, mPlayer(nullptr)
	, mPlayerX(1)
	, mPlayerY(1)
{
	int x, y;
	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		x = i % MAP_WIDTH;
		y = i / MAP_WIDTH;
		if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
		{
			mObjectMap[i] = new Object(EObjectTypes::WALL);
		}
		else if (x == 1 && y == 1)
		{
			mObjectMap[i] = new Object(EObjectTypes::PLAYER);
			mPlayer = mObjectMap[i];
		}
		else
		{
			mObjectMap[i] = nullptr;
		}
	}
}

FieldMap::~FieldMap()
{
	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		if (mObjectMap[i] != nullptr)
		{
			delete mObjectMap[i];
		}
	}
}

FieldMap* FieldMap::CreateCopiedFieldMap()
{
	FieldMap* fieldMap = new FieldMap();
	Object* object;
	int x, y;
	fieldMap->PutObject(mPlayerX, mPlayerY, EObjectTypes::PLAYER);

	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		x = i % MAP_WIDTH;
		y = i / MAP_WIDTH;

		if (x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1)
		{
			object = mObjectMap[i];
			if (object != nullptr && object->GetObjectType() != EObjectTypes::PLAYER) {
				fieldMap->PutObject(x, y, object->GetObjectType());
			}
		}
	}
	return fieldMap;
}

void FieldMap::ResetFieldMapWithWalls()
{
	size_t width = GetMapWidth();
	size_t height = GetMapHeight();

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			PutObject(j, i, EObjectTypes::WALL);
		}
	}
}

void FieldMap::SetUpFieldMapLevels(size_t level)
{
	switch (++level) 
	{
	case 1:
		SetFieldMapLevel1();
		break;
	case 2:
		SetFieldMapLevel2();
		break;
	case 3:
		SetFieldMapLevel3();
		break;
	case 4:
		SetFieldMapLevel4();
		return;
	case 5:
		SetFieldMapLevel5();
		return;
	case 6:
		SetFieldMapLevel6();
		return;
	default:
		assert(false, "Level is out of range.");
		break;
	}
}

void FieldMap::PutObject(int x, int y, EObjectTypes objectType)
{
	if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
	{
		assert(false); // Out of FieldMap
	}
	if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
	{
		return; // Each edge of FieldMap is Wall
	}

	int gridIndex = y * MAP_WIDTH + x;
	if (mObjectMap[gridIndex] != nullptr)
	{
		// Execute nothing when there is the same object in the spot and Not allowed to delete Player.
		if (objectType != mObjectMap[gridIndex]->GetObjectType() && mObjectMap[gridIndex]->GetObjectType() != EObjectTypes::PLAYER)
		{
			delete mObjectMap[gridIndex];
			mObjectMap[gridIndex] = nullptr;
		}
		else {
			return;
		}
	}

	if (objectType == EObjectTypes::PLAYER)
	{
		// A single Player must exist.
		mObjectMap[gridIndex] = mPlayer;
		mObjectMap[mPlayerY * MAP_WIDTH + mPlayerX] = nullptr;
		mPlayerX = x;
		mPlayerY = y;
	}
	else
	{
		if (objectType != EObjectTypes::WAY)
		{
			mObjectMap[gridIndex] = new Object(objectType);
		}
	}
}

void FieldMap::MovePlayerLeft()
{
	if (IsPushable(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX - 1, mPlayerY);
		mPlayerX--;
	}
}

void FieldMap::MovePlayerRight()
{
	if (IsPushable(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX + 1, mPlayerY);
		mPlayerX++;
	}
}

void FieldMap::MovePlayerUp()
{
	if (IsPushable(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX, mPlayerY - 1);
		mPlayerY--;
	}
}

void FieldMap::MovePlayerDown()
{
	if (IsPushable(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX, mPlayerY + 1);
		mPlayerY++;
	}
}

size_t FieldMap::GetMapWidth()
{
	return MAP_WIDTH;
}

size_t FieldMap::GetMapHeight()
{
	return MAP_HEIGHT;
}

Object* FieldMap::GetObject(int x, int y)
{
	return mObjectMap[y * MAP_WIDTH + x];
}

bool FieldMap::IsPushable(int xFrom, int yFrom, int xTo, int yTo)
{
	// Return true when the object is pushed or there is no object to push. 
	if (xFrom < 0 || xFrom > MAP_WIDTH - 1 || yFrom < 0 || yFrom > MAP_HEIGHT - 1)
	{
		assert(false); // Impossible that object is out of map.
	}
	if (xTo < 0 || xTo > MAP_WIDTH - 1 || yTo < 0 || yTo > MAP_HEIGHT - 1)
	{
		return false;
	}

	Object* next = mObjectMap[yFrom * MAP_WIDTH + xFrom];
	Object* nextToNext = mObjectMap[yTo * MAP_WIDTH + xTo];

	if (next != nullptr && next->GetObjectType() == EObjectTypes::PLAYER)
	{
		assert(false); // Impossible to push Player.
	}
	if (next == nullptr)
	{
		return true; // Return true when there is nothing to push.
	}
	else
	{
		if (next->GetObjectType() == EObjectTypes::BOX)
		{
			if (nextToNext == nullptr || nextToNext->GetObjectType() == EObjectTypes::GOAL)
			{
				StandOnTheWayOrGoal(xFrom, yFrom, xTo, yTo);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (next->GetObjectType() == EObjectTypes::WALL)
		{
			return false;
		}
		else if (next->GetObjectType() == EObjectTypes::GOAL)
		{
			if (!next->hasNext())
			{
				return true;
			}
			else
			{
				if (next == nullptr || nextToNext->GetObjectType() == EObjectTypes::GOAL)
				{
					StandOnTheWayOrGoal(xFrom, yFrom, xTo, yTo);
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
}

void FieldMap::StandOnTheWayOrGoal(int xFrom, int yFrom, int xTo, int yTo)
{
	Object* object = mObjectMap[yFrom * MAP_WIDTH + xFrom];
	Object* obstacle = mObjectMap[yTo * MAP_WIDTH + xTo];

	assert(object != nullptr); // Moving object is always not nullptr.
	assert(!(object->GetObjectType() == EObjectTypes::GOAL && !object->hasNext()));
	assert(obstacle == nullptr || obstacle->GetObjectType() == EObjectTypes::GOAL);

	if (object->GetObjectType() == EObjectTypes::GOAL)
	{
		Object* goal = object;
		object = goal->GetNextObject();
		goal->SetNextObject(nullptr);
	}
	else
	{
		mObjectMap[yFrom * MAP_WIDTH + xFrom] = nullptr;
	}

	if (obstacle == nullptr)
	{
		mObjectMap[yTo * MAP_WIDTH + xTo] = object;
	}
	else if (obstacle->GetObjectType() == EObjectTypes::GOAL)
	{
		obstacle->SetNextObject(object);
	}
}

void FieldMap::SetFieldMapLevel1()
{
	assert(GetMapWidth() == 20);
	assert(GetMapHeight() == 20);

	PutObject(11, 17, EObjectTypes::PLAYER);
	ResetFieldMapWithWalls();

	PutObject(5, 18, EObjectTypes::WAY);
	PutObject(6, 18, EObjectTypes::WAY);
	PutObject(7, 18, EObjectTypes::WAY);
	PutObject(8, 18, EObjectTypes::WAY);
	PutObject(9, 18, EObjectTypes::WAY);
	PutObject(5, 17, EObjectTypes::WAY);
	PutObject(9, 17, EObjectTypes::WAY);
	PutObject(14, 17, EObjectTypes::WAY);
	PutObject(15, 17, EObjectTypes::WAY);
	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(1, 16, EObjectTypes::WAY);
	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(3, 16, EObjectTypes::WAY);
	PutObject(4, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(6, 16, EObjectTypes::WAY);
	PutObject(7, 16, EObjectTypes::WAY);
	PutObject(8, 16, EObjectTypes::WAY);
	PutObject(9, 16, EObjectTypes::WAY);
	PutObject(10, 16, EObjectTypes::WAY);
	PutObject(11, 16, EObjectTypes::WAY);
	PutObject(12, 16, EObjectTypes::WAY);
	PutObject(13, 16, EObjectTypes::WAY);
	PutObject(14, 16, EObjectTypes::WAY);
	PutObject(15, 16, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(1, 15, EObjectTypes::WAY);
	PutObject(2, 15, EObjectTypes::WAY);
	PutObject(3, 15, EObjectTypes::WAY);
	PutObject(5, 15, EObjectTypes::WAY);
	PutObject(8, 15, EObjectTypes::WAY);
	PutObject(14, 15, EObjectTypes::WAY);
	PutObject(15, 15, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);
	PutObject(3, 14, EObjectTypes::WAY);
	PutObject(5, 14, EObjectTypes::WAY);
	PutObject(8, 14, EObjectTypes::WAY);
	PutObject(3, 13, EObjectTypes::WAY);
	PutObject(4, 13, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(6, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(8, 13, EObjectTypes::WAY);
	PutObject(5, 12, EObjectTypes::WAY);
	PutObject(6, 12, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::WAY);
	PutObject(6, 11, EObjectTypes::WAY);
	PutObject(7, 11, EObjectTypes::WAY);
	PutObject(5, 10, EObjectTypes::WAY);
	PutObject(6, 10, EObjectTypes::WAY);
	PutObject(7, 10, EObjectTypes::WAY);

	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);

	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::SetFieldMapLevel2()
{
	assert(GetMapWidth() == 20);
	assert(GetMapHeight() == 20);

	PutObject(11, 17, EObjectTypes::PLAYER);
	ResetFieldMapWithWalls();

	PutObject(5, 18, EObjectTypes::WAY);
	PutObject(6, 18, EObjectTypes::WAY);
	PutObject(7, 18, EObjectTypes::WAY);
	PutObject(8, 18, EObjectTypes::WAY);
	PutObject(9, 18, EObjectTypes::WAY);
	PutObject(5, 17, EObjectTypes::WAY);
	PutObject(9, 17, EObjectTypes::WAY);
	PutObject(14, 17, EObjectTypes::WAY);
	PutObject(15, 17, EObjectTypes::WAY);
	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(1, 16, EObjectTypes::WAY);
	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(3, 16, EObjectTypes::WAY);
	PutObject(4, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(6, 16, EObjectTypes::WAY);
	PutObject(7, 16, EObjectTypes::WAY);
	PutObject(8, 16, EObjectTypes::WAY);
	PutObject(9, 16, EObjectTypes::WAY);
	PutObject(10, 16, EObjectTypes::WAY);
	PutObject(11, 16, EObjectTypes::WAY);
	PutObject(12, 16, EObjectTypes::WAY);
	PutObject(13, 16, EObjectTypes::WAY);
	PutObject(14, 16, EObjectTypes::WAY);
	PutObject(15, 16, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(1, 15, EObjectTypes::WAY);
	PutObject(2, 15, EObjectTypes::WAY);
	PutObject(3, 15, EObjectTypes::WAY);
	PutObject(5, 15, EObjectTypes::WAY);
	PutObject(8, 15, EObjectTypes::WAY);
	PutObject(14, 15, EObjectTypes::WAY);
	PutObject(15, 15, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);
	PutObject(3, 14, EObjectTypes::WAY);
	PutObject(5, 14, EObjectTypes::WAY);
	PutObject(8, 14, EObjectTypes::WAY);
	PutObject(3, 13, EObjectTypes::WAY);
	PutObject(4, 13, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(6, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(8, 13, EObjectTypes::WAY);
	PutObject(5, 12, EObjectTypes::WAY);
	PutObject(6, 12, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::WAY);
	PutObject(6, 11, EObjectTypes::WAY);
	PutObject(7, 11, EObjectTypes::WAY);
	PutObject(5, 10, EObjectTypes::WAY);
	PutObject(6, 10, EObjectTypes::WAY);
	PutObject(7, 10, EObjectTypes::WAY);

	PutObject(16, 17, EObjectTypes::GOAL);
	PutObject(17, 17, EObjectTypes::GOAL);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::BOX);
	PutObject(5, 16, EObjectTypes::BOX);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::SetFieldMapLevel3()
{
	assert(GetMapWidth() == 20);
	assert(GetMapHeight() == 20);

	PutObject(11, 17, EObjectTypes::PLAYER);
	ResetFieldMapWithWalls();

	PutObject(5, 18, EObjectTypes::WAY);
	PutObject(6, 18, EObjectTypes::WAY);
	PutObject(7, 18, EObjectTypes::WAY);
	PutObject(8, 18, EObjectTypes::WAY);
	PutObject(9, 18, EObjectTypes::WAY);
	PutObject(5, 17, EObjectTypes::WAY);
	PutObject(9, 17, EObjectTypes::WAY);
	PutObject(14, 17, EObjectTypes::WAY);
	PutObject(15, 17, EObjectTypes::WAY);
	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(1, 16, EObjectTypes::WAY);
	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(3, 16, EObjectTypes::WAY);
	PutObject(4, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(6, 16, EObjectTypes::WAY);
	PutObject(7, 16, EObjectTypes::WAY);
	PutObject(8, 16, EObjectTypes::WAY);
	PutObject(9, 16, EObjectTypes::WAY);
	PutObject(10, 16, EObjectTypes::WAY);
	PutObject(11, 16, EObjectTypes::WAY);
	PutObject(12, 16, EObjectTypes::WAY);
	PutObject(13, 16, EObjectTypes::WAY);
	PutObject(14, 16, EObjectTypes::WAY);
	PutObject(15, 16, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(1, 15, EObjectTypes::WAY);
	PutObject(2, 15, EObjectTypes::WAY);
	PutObject(3, 15, EObjectTypes::WAY);
	PutObject(5, 15, EObjectTypes::WAY);
	PutObject(8, 15, EObjectTypes::WAY);
	PutObject(14, 15, EObjectTypes::WAY);
	PutObject(15, 15, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);
	PutObject(3, 14, EObjectTypes::WAY);
	PutObject(5, 14, EObjectTypes::WAY);
	PutObject(8, 14, EObjectTypes::WAY);
	PutObject(3, 13, EObjectTypes::WAY);
	PutObject(4, 13, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(6, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(8, 13, EObjectTypes::WAY);
	PutObject(5, 12, EObjectTypes::WAY);
	PutObject(6, 12, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::WAY);
	PutObject(6, 11, EObjectTypes::WAY);
	PutObject(7, 11, EObjectTypes::WAY);
	PutObject(5, 10, EObjectTypes::WAY);
	PutObject(6, 10, EObjectTypes::WAY);
	PutObject(7, 10, EObjectTypes::WAY);

	PutObject(16, 17, EObjectTypes::GOAL);
	PutObject(17, 17, EObjectTypes::GOAL);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::BOX);
	PutObject(5, 16, EObjectTypes::BOX);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::SetFieldMapLevel4()
{
	assert(GetMapWidth() == 20);
	assert(GetMapHeight() == 20);

	PutObject(11, 17, EObjectTypes::PLAYER);
	ResetFieldMapWithWalls();

	PutObject(5, 18, EObjectTypes::WAY);
	PutObject(6, 18, EObjectTypes::WAY);
	PutObject(7, 18, EObjectTypes::WAY);
	PutObject(8, 18, EObjectTypes::WAY);
	PutObject(9, 18, EObjectTypes::WAY);
	PutObject(5, 17, EObjectTypes::WAY);
	PutObject(9, 17, EObjectTypes::WAY);
	PutObject(14, 17, EObjectTypes::WAY);
	PutObject(15, 17, EObjectTypes::WAY);
	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(1, 16, EObjectTypes::WAY);
	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(3, 16, EObjectTypes::WAY);
	PutObject(4, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(6, 16, EObjectTypes::WAY);
	PutObject(7, 16, EObjectTypes::WAY);
	PutObject(8, 16, EObjectTypes::WAY);
	PutObject(9, 16, EObjectTypes::WAY);
	PutObject(10, 16, EObjectTypes::WAY);
	PutObject(11, 16, EObjectTypes::WAY);
	PutObject(12, 16, EObjectTypes::WAY);
	PutObject(13, 16, EObjectTypes::WAY);
	PutObject(14, 16, EObjectTypes::WAY);
	PutObject(15, 16, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(1, 15, EObjectTypes::WAY);
	PutObject(2, 15, EObjectTypes::WAY);
	PutObject(3, 15, EObjectTypes::WAY);
	PutObject(5, 15, EObjectTypes::WAY);
	PutObject(8, 15, EObjectTypes::WAY);
	PutObject(14, 15, EObjectTypes::WAY);
	PutObject(15, 15, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);
	PutObject(3, 14, EObjectTypes::WAY);
	PutObject(5, 14, EObjectTypes::WAY);
	PutObject(8, 14, EObjectTypes::WAY);
	PutObject(3, 13, EObjectTypes::WAY);
	PutObject(4, 13, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(6, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(8, 13, EObjectTypes::WAY);
	PutObject(5, 12, EObjectTypes::WAY);
	PutObject(6, 12, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::WAY);
	PutObject(6, 11, EObjectTypes::WAY);
	PutObject(7, 11, EObjectTypes::WAY);
	PutObject(5, 10, EObjectTypes::WAY);
	PutObject(6, 10, EObjectTypes::WAY);
	PutObject(7, 10, EObjectTypes::WAY);

	PutObject(16, 17, EObjectTypes::GOAL);
	PutObject(17, 17, EObjectTypes::GOAL);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::BOX);
	PutObject(5, 16, EObjectTypes::BOX);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::SetFieldMapLevel5()
{
	assert(GetMapWidth() == 20);
	assert(GetMapHeight() == 20);

	PutObject(11, 17, EObjectTypes::PLAYER);
	ResetFieldMapWithWalls();

	PutObject(5, 18, EObjectTypes::WAY);
	PutObject(6, 18, EObjectTypes::WAY);
	PutObject(7, 18, EObjectTypes::WAY);
	PutObject(8, 18, EObjectTypes::WAY);
	PutObject(9, 18, EObjectTypes::WAY);
	PutObject(5, 17, EObjectTypes::WAY);
	PutObject(9, 17, EObjectTypes::WAY);
	PutObject(14, 17, EObjectTypes::WAY);
	PutObject(15, 17, EObjectTypes::WAY);
	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(1, 16, EObjectTypes::WAY);
	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(3, 16, EObjectTypes::WAY);
	PutObject(4, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(6, 16, EObjectTypes::WAY);
	PutObject(7, 16, EObjectTypes::WAY);
	PutObject(8, 16, EObjectTypes::WAY);
	PutObject(9, 16, EObjectTypes::WAY);
	PutObject(10, 16, EObjectTypes::WAY);
	PutObject(11, 16, EObjectTypes::WAY);
	PutObject(12, 16, EObjectTypes::WAY);
	PutObject(13, 16, EObjectTypes::WAY);
	PutObject(14, 16, EObjectTypes::WAY);
	PutObject(15, 16, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(1, 15, EObjectTypes::WAY);
	PutObject(2, 15, EObjectTypes::WAY);
	PutObject(3, 15, EObjectTypes::WAY);
	PutObject(5, 15, EObjectTypes::WAY);
	PutObject(8, 15, EObjectTypes::WAY);
	PutObject(14, 15, EObjectTypes::WAY);
	PutObject(15, 15, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);
	PutObject(3, 14, EObjectTypes::WAY);
	PutObject(5, 14, EObjectTypes::WAY);
	PutObject(8, 14, EObjectTypes::WAY);
	PutObject(3, 13, EObjectTypes::WAY);
	PutObject(4, 13, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(6, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(8, 13, EObjectTypes::WAY);
	PutObject(5, 12, EObjectTypes::WAY);
	PutObject(6, 12, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::WAY);
	PutObject(6, 11, EObjectTypes::WAY);
	PutObject(7, 11, EObjectTypes::WAY);
	PutObject(5, 10, EObjectTypes::WAY);
	PutObject(6, 10, EObjectTypes::WAY);
	PutObject(7, 10, EObjectTypes::WAY);

	PutObject(16, 17, EObjectTypes::GOAL);
	PutObject(17, 17, EObjectTypes::GOAL);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::BOX);
	PutObject(5, 16, EObjectTypes::BOX);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::SetFieldMapLevel6()
{
	assert(GetMapWidth() == 20);
	assert(GetMapHeight() == 20);

	PutObject(11, 17, EObjectTypes::PLAYER);
	ResetFieldMapWithWalls();

	PutObject(5, 18, EObjectTypes::WAY);
	PutObject(6, 18, EObjectTypes::WAY);
	PutObject(7, 18, EObjectTypes::WAY);
	PutObject(8, 18, EObjectTypes::WAY);
	PutObject(9, 18, EObjectTypes::WAY);
	PutObject(5, 17, EObjectTypes::WAY);
	PutObject(9, 17, EObjectTypes::WAY);
	PutObject(14, 17, EObjectTypes::WAY);
	PutObject(15, 17, EObjectTypes::WAY);
	PutObject(16, 17, EObjectTypes::WAY);
	PutObject(17, 17, EObjectTypes::WAY);
	PutObject(1, 16, EObjectTypes::WAY);
	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(3, 16, EObjectTypes::WAY);
	PutObject(4, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(6, 16, EObjectTypes::WAY);
	PutObject(7, 16, EObjectTypes::WAY);
	PutObject(8, 16, EObjectTypes::WAY);
	PutObject(9, 16, EObjectTypes::WAY);
	PutObject(10, 16, EObjectTypes::WAY);
	PutObject(11, 16, EObjectTypes::WAY);
	PutObject(12, 16, EObjectTypes::WAY);
	PutObject(13, 16, EObjectTypes::WAY);
	PutObject(14, 16, EObjectTypes::WAY);
	PutObject(15, 16, EObjectTypes::WAY);
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(1, 15, EObjectTypes::WAY);
	PutObject(2, 15, EObjectTypes::WAY);
	PutObject(3, 15, EObjectTypes::WAY);
	PutObject(5, 15, EObjectTypes::WAY);
	PutObject(8, 15, EObjectTypes::WAY);
	PutObject(14, 15, EObjectTypes::WAY);
	PutObject(15, 15, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::WAY);
	PutObject(17, 15, EObjectTypes::WAY);
	PutObject(3, 14, EObjectTypes::WAY);
	PutObject(5, 14, EObjectTypes::WAY);
	PutObject(8, 14, EObjectTypes::WAY);
	PutObject(3, 13, EObjectTypes::WAY);
	PutObject(4, 13, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(6, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(8, 13, EObjectTypes::WAY);
	PutObject(5, 12, EObjectTypes::WAY);
	PutObject(6, 12, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::WAY);
	PutObject(5, 11, EObjectTypes::WAY);
	PutObject(6, 11, EObjectTypes::WAY);
	PutObject(7, 11, EObjectTypes::WAY);
	PutObject(5, 10, EObjectTypes::WAY);
	PutObject(6, 10, EObjectTypes::WAY);
	PutObject(7, 10, EObjectTypes::WAY);

	PutObject(16, 17, EObjectTypes::GOAL);
	PutObject(17, 17, EObjectTypes::GOAL);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::BOX);
	PutObject(5, 16, EObjectTypes::BOX);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}
