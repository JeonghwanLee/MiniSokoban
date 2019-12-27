#include "PlayMode.h"
#include "Object.h"

PlayMode::PlayMode(size_t& currentLevel)
	: mLevel(currentLevel)
	, bStageClearFlag(false)
{
}

PlayMode::~PlayMode()
{
}

void PlayMode::CheckStageClear()
{
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);

	for (unsigned int i = 0; i < FieldMap::MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < FieldMap::MAP_WIDTH; j++)
		{
			Object* object = mFieldMap->GetObject(j, i);
			if (object == nullptr)
			{
				continue;
			}
			else if (object->GetObjectType() == EObjectTypes::GOAL)
			{
				if (!object->hasNext())
				{
					return;
				}
				else if (object->GetNextObject()->GetObjectType() != EObjectTypes::BOX)
				{
					return;
				}
			}
		}
	}

	bStageClearFlag = true;
}

void PlayMode::Draw()
{
	Clear();
	DrawFieldMap();
	std::cout << std::endl;
	DrawObjectDescription();
	SetConsoleTextAttribute(mHConsole, BLACK_GREEN);
	std::cout << std::endl;
	std::cout << "ESC: Back to Start Menu" << std::endl;
	if (bStageClearFlag)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
		std::cout << std::endl;
		std::cout << "*********************************************" << std::endl;
		std::cout << "  You Win! Press ESC to back to Start Menu.  " << std::endl;
		std::cout << "*********************************************" << std::endl;
	}
}

bool PlayMode::ActionLeft()
{
	if (bStageClearFlag)
	{
		return false;
	}
	mFieldMap->MovePlayerLeft();
	CheckStageClear();
	Draw();
	return false;
}

bool PlayMode::ActionUp()
{
	if (bStageClearFlag)
	{
		return false;
	}
	mFieldMap->MovePlayerUp();
	CheckStageClear();
	Draw();
	return false;
}

bool PlayMode::ActionDown()
{
	if (bStageClearFlag)
	{
		return false;
	}
	mFieldMap->MovePlayerDown();
	CheckStageClear();
	Draw();
	return false;
}

bool PlayMode::ActionRight()
{
	if (bStageClearFlag)
	{
		return false;
	}
	mFieldMap->MovePlayerRight();
	CheckStageClear();
	Draw();
	return false;
}

bool PlayMode::ActionEnter()
{
	return false;
}

bool PlayMode::ActionEscape()
{
	mModeType->SetStartMode();
	return true;
}

bool PlayMode::ActionSpace()
{
	return false;
}

bool PlayMode::ActionNum(int level)
{
	return false;
}

bool PlayMode::ActionPlayer()
{
	return false;
}

bool PlayMode::ActionBox()
{
	return false;
}

bool PlayMode::ActionWall()
{
	return false;
}

bool PlayMode::ActionGoal()
{
	return false;
}

bool PlayMode::ActionWay()
{
	return false;
}

void PlayMode::DrawObjectDescription()
{
	SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " Player  ";

	SetConsoleTextAttribute(mHConsole, RED_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " Box  ";

	SetConsoleTextAttribute(mHConsole, WHITE_BLACK);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " Wall  ";

	SetConsoleTextAttribute(mHConsole, YELLOW_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " Goal  ";

	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " Way ";

	std::cout << std::endl;
}

void PlayMode::DrawFieldMap()
{
	Object* object;
	for (unsigned int i = 0; i < FieldMap::MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < FieldMap::MAP_WIDTH; j++)
		{
			object = mFieldMap->GetObject(j, i);

			if (object == nullptr)
			{
				SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
			}
			else if (object->GetObjectType() == EObjectTypes::PLAYER)
			{
				SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
			}
			else if (object->GetObjectType() == EObjectTypes::BOX)
			{
				SetConsoleTextAttribute(mHConsole, RED_WHITE);
			}
			else if (object->GetObjectType() == EObjectTypes::WALL)
			{
				SetConsoleTextAttribute(mHConsole, WHITE_BLACK);
			}
			else if (object->GetObjectType() == EObjectTypes::GOAL)
			{
				if (object->hasNext())
				{
					if (object->GetNextObject()->GetObjectType() == EObjectTypes::PLAYER)
					{
						SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
					}
					else if (object->GetNextObject()->GetObjectType() == EObjectTypes::BOX)
					{
						SetConsoleTextAttribute(mHConsole, RED_WHITE);
					}
				}
				else
				{
					SetConsoleTextAttribute(mHConsole, YELLOW_WHITE);
				}
			}
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void PlayMode::Initialize()
{
	bStageClearFlag = false;
	mFieldMap = mFieldMaps[mLevel - 1].CreateCopiedFieldMap();
}
