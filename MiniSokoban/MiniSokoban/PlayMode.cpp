#include "PlayMode.h"
#include "Object.h"

PlayMode::PlayMode(const std::shared_ptr<ModeType>& modeType)
	: GameMode(modeType)
	, mFieldMap(nullptr)
	, mLevel(1)
	, mbLevelClearFlag(false)
{	
}

PlayMode::~PlayMode()
{
	delete mFieldMap;
}

void PlayMode::Initialize()
{
	mbLevelClearFlag = false;
	if (mFieldMap == nullptr)
	{
		mFieldMap = new FieldMap(mFieldMaps[mLevel - 1]);
	}
}

void PlayMode::Draw()
{
	SetCursorOrigin();
	checkStageClear();

	if (mbLevelClearFlag)
	{
		mLevel++;
		if (mLevel > 6)
		{
			drawGameClear();
			return;
		}

		delete mFieldMap;
		mFieldMap = new FieldMap(mFieldMaps[mLevel - 1]);
		mbLevelClearFlag = false;
	}

	drawFieldMap();
	drawObjectDescription();
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "   Level " << mLevel << std::endl;
	std::cout << std::endl;
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "   ESC: Back to Main" << std::endl;
}

void PlayMode::ActionLeft()
{
	mFieldMap->MovePlayerLeft();
}

void PlayMode::ActionUp()
{
	mFieldMap->MovePlayerUp();
}

void PlayMode::ActionDown()
{
	mFieldMap->MovePlayerDown();
}

void PlayMode::ActionRight()
{
	mFieldMap->MovePlayerRight();
}

void PlayMode::ActionEnter()
{
}

void PlayMode::ActionEscape()
{
	mModeType->SetMainMode();
}

void PlayMode::ActionSpace()
{
}

void PlayMode::ActionNum(int level)
{
}

void PlayMode::ActionPlayer()
{
}

void PlayMode::ActionBox()
{
}

void PlayMode::ActionWall()
{
}

void PlayMode::ActionGoal()
{
}

void PlayMode::ActionWay()
{
}

void PlayMode::drawFieldMap() const
{
	Object* object;
	for (unsigned int i = 0; i < FieldMap::MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < FieldMap::MAP_WIDTH; j++)
		{
			object = mFieldMap->GetObjectFromMap(j, i);
			if (object == nullptr)
			{
				printObjectByColor(EObjectColors::BLACK_WHITE, false);
			}
			else if (object->GetObjectType() == EObjectTypes::GOAL && object->IsThereObjectOnGoal())
			{
				printObjectByColor(object->GetObjectOnGoal()->GetObjectColor(), false);
			}
			else
			{
				printObjectByColor(object->GetObjectColor(), false);
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void PlayMode::printObjectDescriptionByObjectType(EObjectTypes objectType) const
{
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	if (objectType == EObjectTypes::PLAYER)
	{
		std::cout << " Player  ";
	}
	else if (objectType == EObjectTypes::BOX)
	{
		std::cout << " Box  ";
	}
	else if (objectType == EObjectTypes::GOAL)
	{
		std::cout << " Goal  ";
	}
	else if (objectType == EObjectTypes::WALL)
	{
		std::cout << " Wall  ";
	}
	else
	{
		std::cout << " Way ";
	}
}

void PlayMode::checkStageClear()
{
	assert(FieldMap::MAP_WIDTH == 20);
	assert(FieldMap::MAP_HEIGHT == 20);
	Object* object;
	for (unsigned int i = 0; i < FieldMap::MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < FieldMap::MAP_WIDTH; j++)
		{
			object = mFieldMap->GetObjectFromMap(j, i);
			if (object == nullptr)
			{
				continue;
			}
			else if (object->GetObjectType() == EObjectTypes::GOAL)
			{
				if (!object->IsThereObjectOnGoal())
				{
					return;
				}
				else if (object->GetObjectOnGoal()->GetObjectType() != EObjectTypes::BOX)
				{
					return;
				}
			}
		}
	}
	mbLevelClearFlag = true;
}

void PlayMode::drawGameClear()
{
	system("CLS");
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "*********************************************" << std::endl;
	std::cout << std::endl;
	std::cout << "  You Win! Press ESC to back to Main.  " << std::endl;
	std::cout << std::endl;
	std::cout << "*********************************************" << std::endl;
	mLevel = 1;
}