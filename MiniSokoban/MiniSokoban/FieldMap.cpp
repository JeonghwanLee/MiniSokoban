#include "FieldMap.h"
#include "Object.h"

FieldMap::FieldMap()
	: mObjectMap{ nullptr }
	, mPlayerX(1)
	, mPlayerY(1)
	, mbIsNextObjectPushable(false)
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
		}
		else
		{
			mObjectMap[i] = nullptr;
		}
	}
}

FieldMap::FieldMap(const FieldMap& other)
	: mObjectMap{ nullptr }
	, mPlayerX(other.mPlayerX)
	, mPlayerY(other.mPlayerY)
	, mbIsNextObjectPushable(false)
{
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
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
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		if (mObjectMap[i] != nullptr)
		{
			delete mObjectMap[i];
			mObjectMap[i] = nullptr;
		}
	}
}

Object* FieldMap::GetObjectFromMap(int x, int y) const
{
	return mObjectMap[y * MAP_WIDTH + x];
}

void FieldMap::ResetFieldMapWithWalls()
{
	for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{
		if (mObjectMap[i] != nullptr && mObjectMap[i]->GetObjectType() != EObjectTypes::PLAYER) {
			if (mObjectMap[i]->GetObjectType() == EObjectTypes::GOAL && mObjectMap[i]->IsThereObjectOnGoal())
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
		setFieldMapLevel1();
		break;
	case 2:
		setFieldMapLevel2();
		break;
	case 3:
		setFieldMapLevel3();
		break;
	case 4:
		setFieldMapLevel4();
		return;
	case 5:
		setFieldMapLevel5();
		return;
	case 6:
		setFieldMapLevel6();
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
		assert(false);
	}
	if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
	{
		return;
	}

	if (mObjectMap[y * MAP_WIDTH + x] != nullptr)
	{
		if (objectType != mObjectMap[y * MAP_WIDTH + x]->GetObjectType() && mObjectMap[y * MAP_WIDTH + x]->GetObjectType() != EObjectTypes::PLAYER)
		{
			delete mObjectMap[y * MAP_WIDTH + x];
			mObjectMap[y * MAP_WIDTH + x] = nullptr;
		}
		else {
			return;
		}
	}

	if (objectType == EObjectTypes::PLAYER)
	{
		mObjectMap[y * MAP_WIDTH + x] = mObjectMap[mPlayerY * MAP_WIDTH + mPlayerX];
		mObjectMap[mPlayerY * MAP_WIDTH + mPlayerX] = nullptr;
		mPlayerX = x;
		mPlayerY = y;
	}
	else
	{
		if (objectType != EObjectTypes::WAY)
		{
			mObjectMap[y * MAP_WIDTH + x] = new Object(objectType);
		}
	}
}

void FieldMap::MovePlayerLeft()
{
	if (isPushable(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY))
	{
		if (mbIsNextObjectPushable)
		{
			moveObjectFromTo(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY);
			mbIsNextObjectPushable = false;
		}
		moveObjectFromTo(mPlayerX, mPlayerY, mPlayerX - 1, mPlayerY);
		mPlayerX--;
	}
}

void FieldMap::MovePlayerRight()
{
	if (isPushable(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY))
	{
		if (mbIsNextObjectPushable)
		{
			moveObjectFromTo(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY);
			mbIsNextObjectPushable = false;
		}
		moveObjectFromTo(mPlayerX, mPlayerY, mPlayerX + 1, mPlayerY);
		mPlayerX++;
	}
}

void FieldMap::MovePlayerUp()
{
	if (isPushable(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2))
	{
		if (mbIsNextObjectPushable)
		{
			moveObjectFromTo(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2);
			mbIsNextObjectPushable = false;
		}
		moveObjectFromTo(mPlayerX, mPlayerY, mPlayerX, mPlayerY - 1);
		mPlayerY--;
	}
}

void FieldMap::MovePlayerDown()
{
	if (isPushable(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2))
	{
		if (mbIsNextObjectPushable)
		{
			moveObjectFromTo(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2);
			mbIsNextObjectPushable = false;
		}
		moveObjectFromTo(mPlayerX, mPlayerY, mPlayerX, mPlayerY + 1);
		mPlayerY++;
	}
}


bool FieldMap::isPushable(int xFrom, int yFrom, int xTo, int yTo)
{
	if (xFrom < 0 || xFrom > MAP_WIDTH - 1 || yFrom < 0 || yFrom > MAP_HEIGHT - 1)
	{
		assert(false);
	}

	if (xTo < 0 || xTo > MAP_WIDTH - 1 || yTo < 0 || yTo > MAP_HEIGHT - 1)
	{
		return false;
	}

	Object* fromObject = mObjectMap[yFrom * MAP_WIDTH + xFrom];
	Object* toObject = mObjectMap[yTo * MAP_WIDTH + xTo];
	EObjectTypes fromObjectType;

	if (fromObject != nullptr && fromObject->GetObjectType() == EObjectTypes::PLAYER)
	{
		assert(false);
	}

	if (fromObject == nullptr)
	{
		return true;
	}
	else
	{
		fromObjectType = fromObject->GetObjectType();
		if (fromObjectType == EObjectTypes::BOX)
		{
			if (toObject == nullptr || (toObject->GetObjectType() == EObjectTypes::GOAL && !toObject->IsThereObjectOnGoal()))
			{
				mbIsNextObjectPushable = true;
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (fromObjectType == EObjectTypes::WALL)
		{
			return false;
		}
		else if (fromObjectType == EObjectTypes::GOAL)
		{
			if (fromObject->IsThereObjectOnGoal())
			{
				if (toObject == nullptr || (toObject->GetObjectType() == EObjectTypes::GOAL && !toObject->IsThereObjectOnGoal()) )
				{
					mbIsNextObjectPushable = true;
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

void FieldMap::moveObjectFromTo(int xFrom, int yFrom, int xTo, int yTo)
{
	Object* fromObject = mObjectMap[yFrom * MAP_WIDTH + xFrom]; 
	Object* toObject = mObjectMap[yTo * MAP_WIDTH + xTo]; 

	assert(fromObject != nullptr); // Moving object is always not nullptr.
	assert(!(fromObject->GetObjectType() == EObjectTypes::GOAL && !fromObject->IsThereObjectOnGoal()));
	assert(toObject == nullptr || toObject->GetObjectType() == EObjectTypes::GOAL);

	if (fromObject->GetObjectType() == EObjectTypes::GOAL)
	{
		Object* goal = fromObject;
		fromObject = goal->GetObjectOnGoal();
		goal->SetObjectOnGoal(nullptr);
	}
	else
	{
		mObjectMap[yFrom * MAP_WIDTH + xFrom] = nullptr;
	}

	if (toObject == nullptr)
	{
		mObjectMap[yTo * MAP_WIDTH + xTo] = fromObject;
	}
	else if (toObject->GetObjectType() == EObjectTypes::GOAL)
	{
		toObject->SetObjectOnGoal(fromObject);
	}
}

void FieldMap::setFieldMapLevel1()
{
	assert(MAP_WIDTH == 20);
	assert(MAP_HEIGHT == 20);

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

void FieldMap::setFieldMapLevel2()
{
	assert(MAP_WIDTH == 20);
	assert(MAP_HEIGHT == 20);

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
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::WAY);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::WAY);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::setFieldMapLevel3()
{
	assert(MAP_WIDTH == 20);
	assert(MAP_HEIGHT == 20);

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
	PutObject(16, 16, EObjectTypes::WAY);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::WAY);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::setFieldMapLevel4()
{
	assert(MAP_WIDTH == 20);
	assert(MAP_HEIGHT == 20);

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
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::WAY);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::setFieldMapLevel5()
{
	assert(MAP_WIDTH == 20);
	assert(MAP_HEIGHT == 20);

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
	PutObject(17, 17, EObjectTypes::GOAL);
	PutObject(16, 16, EObjectTypes::GOAL);
	PutObject(17, 16, EObjectTypes::GOAL);
	PutObject(16, 15, EObjectTypes::GOAL);
	PutObject(17, 15, EObjectTypes::GOAL);

	PutObject(2, 16, EObjectTypes::WAY);
	PutObject(5, 16, EObjectTypes::BOX);
	PutObject(5, 13, EObjectTypes::BOX);
	PutObject(7, 13, EObjectTypes::BOX);
	PutObject(7, 12, EObjectTypes::BOX);
	PutObject(5, 11, EObjectTypes::BOX);
}

void FieldMap::setFieldMapLevel6()
{
	assert(MAP_WIDTH == 20);
	assert(MAP_HEIGHT == 20);

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