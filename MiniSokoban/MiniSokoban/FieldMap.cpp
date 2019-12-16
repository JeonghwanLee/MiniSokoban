#include "FieldMap.h"
#include "Object.h"

FieldMap::FieldMap()
{
	mPlayer = nullptr;
	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		int x = i % MAP_WIDTH;
		int y = i / MAP_WIDTH;
		if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
		{
			mObjectMap[i] = new Object(WALL);
		}
		else if (x == 1 && y == 1)
		{
			mObjectMap[i] = new Object(PLAYER);
			mPlayer = mObjectMap[i];
			mPlayerX = x;
			mPlayerY = y;
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
		Object* object = mObjectMap[i];
		if (object != nullptr)
		{
			delete object;
		}
	}
}

FieldMap* FieldMap::CopyAndReturnFieldMap()
{
	FieldMap* fieldMap = new FieldMap();
	fieldMap->PutObject(mPlayerX, mPlayerY, PLAYER);

	for (int i = 0; i < MAP_WIDTH * MAP_WIDTH; i++)
	{
		int x = i % MAP_WIDTH;
		int y = i / MAP_WIDTH;
		if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
		{
			continue; // Each edges of map is Wall object.
		}
		else
		{
			Object* object = mObjectMap[i];
			if (object == nullptr)
			{
				continue;
			}
			else if (object->GetObjectType() == BOX)
			{
				fieldMap->PutObject(x, y, BOX);
			}
			else if (object->GetObjectType() == WALL)
			{
				fieldMap->PutObject(x, y, WALL);
			}
			else if (object->GetObjectType() == GOAL)
			{
				fieldMap->PutObject(x, y, GOAL);
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
			PutObject(j, i, WALL);
		}
	}
}

void FieldMap::PutObject(int x, int y, EObjectTypes objectType)
{
	if (x < 0 || x > MAP_WIDTH - 1 || y < 0 || y > MAP_HEIGHT - 1)
	{
		assert(false); // Out of map
	}
	if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
	{
		return; // Each edges of map is Wall object.
	}

	if (mObjectMap[y*MAP_WIDTH + x] != nullptr)
	{
		if (objectType == mObjectMap[y*MAP_WIDTH + x]->GetObjectType())
		{
			return; // Execute nothing when there is the same object in the spot.
		}
		else if (mObjectMap[y*MAP_WIDTH + x]->GetObjectType() == PLAYER)
		{
			return; // Not allowed to delete Player. When the Player moves to other position, the old one is automatically deleted.
		}
		else
		{
			delete mObjectMap[y*MAP_WIDTH + x];
			mObjectMap[y*MAP_WIDTH + x] = nullptr;
		}
	}

	if (objectType == WAY)
	{
		return;
	}
	else if (objectType == PLAYER)
	{
		// Assume that a single Player must exist.
		mObjectMap[y*MAP_WIDTH + x] = mPlayer;
		mObjectMap[mPlayerY*MAP_WIDTH + mPlayerX] = nullptr;
		mPlayerX = x;
		mPlayerY = y;
	}
	else
	{
		mObjectMap[y*MAP_WIDTH + x] = new Object(objectType);
	}
}

void FieldMap::MovePlayerLeft()
{
	if (Push(mPlayerX - 1, mPlayerY, mPlayerX - 2, mPlayerY))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX - 1, mPlayerY);
		mPlayerX--;
	}
}

void FieldMap::MovePlayerRight()
{
	if (Push(mPlayerX + 1, mPlayerY, mPlayerX + 2, mPlayerY))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX + 1, mPlayerY);
		mPlayerX++;
	}
}

void FieldMap::MovePlayerUp()
{
	if (Push(mPlayerX, mPlayerY - 1, mPlayerX, mPlayerY - 2))
	{
		StandOnTheWayOrGoal(mPlayerX, mPlayerY, mPlayerX, mPlayerY - 1);
		mPlayerY--;
	}
}

void FieldMap::MovePlayerDown()
{
	if (Push(mPlayerX, mPlayerY + 1, mPlayerX, mPlayerY + 2))
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

bool FieldMap::Push(int xFrom, int yFrom, int xTo, int yTo)
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

	Object* object = mObjectMap[yFrom * MAP_WIDTH + xFrom];
	Object* obstacle = mObjectMap[yTo * MAP_WIDTH + xTo];

	if (object != nullptr && object->GetObjectType() == PLAYER)
	{
		assert(false); // Impossible to push Player.
	}
	if (object == nullptr)
	{
		return true; // Return true when there is nothing to push.
	}
	else
	{
		if (object->GetObjectType() == BOX)
		{
			if (obstacle == nullptr || obstacle->GetObjectType() == GOAL)
			{
				StandOnTheWayOrGoal(xFrom, yFrom, xTo, yTo);
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (object->GetObjectType() == WALL)
		{
			return false;
		}
		else if (object->GetObjectType() == GOAL)
		{
			if (!object->hasNext())
			{
				return true;
			}
			else
			{
				if (obstacle == nullptr || obstacle->GetObjectType() == GOAL)
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
	assert(!(object->GetObjectType() == GOAL && !object->hasNext()));
	assert(obstacle == nullptr || obstacle->GetObjectType() == GOAL); 

	if (object->GetObjectType() == GOAL)
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
	else if (obstacle->GetObjectType() == GOAL)
	{
		obstacle->SetNextObject(object);
	}
}
