#include "FieldMap.h"
#include "Object.h"

FieldMap::FieldMap()
	: mObjectMap{ nullptr }
	, mPlayer(nullptr)
	, mPlayerX(1)
	, mPlayerY(1)
	, bMoveNextObject(false)
{
	int x, y;
	for (int i = 0; i < FieldMap::MAP_WIDTH * FieldMap::MAP_WIDTH; i++)
	{
		x = i % FieldMap::MAP_WIDTH;
		y = i / FieldMap::MAP_WIDTH;
		if (x == 0 || x == FieldMap::MAP_WIDTH - 1 || y == 0 || y == FieldMap::MAP_HEIGHT - 1)
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

FieldMap::FieldMap(const FieldMap& other)
	: mObjectMap{ nullptr }
	, mPlayer(nullptr)
	, mPlayerX(other.mPlayerX)
	, mPlayerY(other.mPlayerY)
{
	for (int i = 0; i < FieldMap::MAP_WIDTH * FieldMap::MAP_WIDTH; i++)
	{
		if (other.mObjectMap[i] != nullptr) {
			mObjectMap[i] = new Object(other.mObjectMap[i]->GetObjectType());
		}
		else
		{
			mObjectMap[i] = nullptr; // WAY
		}
	}
}

FieldMap::~FieldMap()
{
	for (int i = 0; i < FieldMap::MAP_WIDTH * FieldMap::MAP_WIDTH; i++)
	{
		if (mObjectMap[i] != nullptr)
		{
			delete mObjectMap[i];
		}
	}
}

void FieldMap::ResetFieldMapWithWalls()
{
	for (int i = 0; i < FieldMap::MAP_WIDTH * FieldMap::MAP_WIDTH; i++)
	{
		if (mObjectMap[i] != nullptr && mObjectMap[i]->GetObjectType() != EObjectTypes::PLAYER) {
			if (mObjectMap[i]->GetObjectType() == EObjectTypes::GOAL && mObjectMap[i]->hasObjectOnGoal())
			{
				mObjectMap[i]->SetObjectOnGoal(nullptr);
			}
			mObjectMap[i]->SetObjectType(EObjectTypes::WALL);
		}
		else if (mObjectMap[i] == nullptr)
		{
			mObjectMap[i] = new Object(EObjectTypes::WALL);
		}
	}
}

void FieldMap::SetUpFieldMapByLevel(size_t level)
{
	switch (level)
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
	if (x < 0 || x > FieldMap::MAP_WIDTH - 1 || y < 0 || y > FieldMap::MAP_HEIGHT - 1)
	{
		assert(false);
	}
	if (x == 0 || x == FieldMap::MAP_WIDTH - 1 || y == 0 || y == FieldMap::MAP_HEIGHT - 1)
	{
		return;
	}

	if (mObjectMap[y * FieldMap::MAP_WIDTH + x] != nullptr)
	{
		if (objectType != mObjectMap[y * FieldMap::MAP_WIDTH + x]->GetObjectType() && mObjectMap[y * FieldMap::MAP_WIDTH + x]->GetObjectType() != EObjectTypes::PLAYER)
		{
			delete mObjectMap[y * FieldMap::MAP_WIDTH + x];
			mObjectMap[y * FieldMap::MAP_WIDTH + x] = nullptr;
		}
		else {
			return;
		}
	}

	if (objectType == EObjectTypes::PLAYER)
	{
		mObjectMap[y * FieldMap::MAP_WIDTH + x] = mPlayer;
		mObjectMap[mPlayerY * FieldMap::MAP_WIDTH + mPlayerX] = nullptr;
		mPlayerX = x;
		mPlayerY = y;
	}
	else
	{
		if (objectType != EObjectTypes::WAY)
		{
			mObjectMap[y * FieldMap::MAP_WIDTH + x] = new Object(objectType);
		}
	}
}

void FieldMap::MovePlayerLeft()
{
	if (IsPushable(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY))
	{
		if (bMoveNextObject)
		{
			MoveObjectFromTo(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY);
			bMoveNextObject = false;
		}
		MoveObjectFromTo(mPlayerX, mPlayerY, mPlayerX - 1, mPlayerY);
		mPlayerX--;
	}
}

void FieldMap::MovePlayerRight()
{
	if (IsPushable(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY))
	{
		if (bMoveNextObject)
		{
			MoveObjectFromTo(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY);
			bMoveNextObject = false;
		}
		MoveObjectFromTo(mPlayerX, mPlayerY, mPlayerX + 1, mPlayerY);
		mPlayerX++;
	}
}

void FieldMap::MovePlayerUp()
{
	if (IsPushable(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2))
	{
		if (bMoveNextObject)
		{
			MoveObjectFromTo(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2);
			bMoveNextObject = false;
		}
		MoveObjectFromTo(mPlayerX, mPlayerY, mPlayerX, mPlayerY - 1);
		mPlayerY--;
	}
}

void FieldMap::MovePlayerDown()
{
	if (IsPushable(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2))
	{
		if (bMoveNextObject)
		{
			MoveObjectFromTo(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2);
			bMoveNextObject = false;
		}
		MoveObjectFromTo(mPlayerX, mPlayerY, mPlayerX, mPlayerY + 1);
		mPlayerY++;
	}
}

Object* FieldMap::GetObject(int x, int y)
{
	return mObjectMap[y * FieldMap::MAP_WIDTH + x];
}

bool FieldMap::IsPushable(int xFrom, int yFrom, int xTo, int yTo)
{
	if (xFrom < 0 || xFrom > FieldMap::MAP_WIDTH - 1 || yFrom < 0 || yFrom > FieldMap::MAP_HEIGHT - 1)
	{
		assert(false);
	}

	if (xTo < 0 || xTo > FieldMap::MAP_WIDTH - 1 || yTo < 0 || yTo > FieldMap::MAP_HEIGHT - 1)
	{
		return false;
	}

	Object* next = mObjectMap[yFrom * FieldMap::MAP_WIDTH + xFrom];
	Object* nextToNext = mObjectMap[yTo * FieldMap::MAP_WIDTH + xTo];
	EObjectTypes nextObjectType;

	if (next != nullptr && next->GetObjectType() == EObjectTypes::PLAYER)
	{
		assert(false);
	}

	if (next == nullptr)
	{
		return true;
	}
	else
	{
		nextObjectType = next->GetObjectType();
		if (nextObjectType == EObjectTypes::BOX)
		{
			if (nextToNext == nullptr || (nextToNext->GetObjectType() == EObjectTypes::GOAL && !nextToNext->hasObjectOnGoal()))
			{
				bMoveNextObject = true;
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (nextObjectType == EObjectTypes::WALL)
		{
			return false;
		}
		else if (nextObjectType == EObjectTypes::GOAL)
		{
			if (next->hasObjectOnGoal())
			{
				if (nextToNext->GetObjectType() == EObjectTypes::GOAL && !nextToNext->hasObjectOnGoal())
				{
					bMoveNextObject = true;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return true;
			}
		}
	}
}

void FieldMap::MoveObjectFromTo(int xFrom, int yFrom, int xTo, int yTo)
{
	Object* fromObject = mObjectMap[yFrom * FieldMap::MAP_WIDTH + xFrom]; 
	Object* toObject = mObjectMap[yTo * FieldMap::MAP_WIDTH + xTo]; 

	assert(fromObject != nullptr); // Moving object is always not nullptr.
	assert(!(fromObject->GetObjectType() == EObjectTypes::GOAL && !fromObject->hasObjectOnGoal()));
	assert(toObject == nullptr || toObject->GetObjectType() == EObjectTypes::GOAL);

	if (fromObject->GetObjectType() == EObjectTypes::GOAL)
	{
		Object* goal = fromObject;
		fromObject = goal->GetObjectOnGoal();
		goal->SetObjectOnGoal(nullptr);
	}
	else
	{
		mObjectMap[yFrom * FieldMap::MAP_WIDTH + xFrom] = nullptr;
	}

	if (toObject == nullptr)
	{
		mObjectMap[yTo * FieldMap::MAP_WIDTH + xTo] = fromObject;
	}
	else if (toObject->GetObjectType() == EObjectTypes::GOAL)
	{
		toObject->SetObjectOnGoal(fromObject);
	}
}

void FieldMap::SetFieldMapLevel1()
{
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

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
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

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
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

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
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

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
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

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
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

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
