#include "EditorMode.h"
#include "Object.h"

EditorMode::EditorMode(const std::shared_ptr<ModeType>& modeType)
	: GameMode(modeType)
	, mFieldMap(nullptr)
	, mPutObjectType(EObjectTypes::BOX)
	, mCursorX(0)
	, mCursorY(0)
{
}

void EditorMode::Draw()
{
	SetCursorOrigin();
	if (mFieldMap == nullptr)
	{
		drawSelectLevel();
	}
	else 
	{
		drawSelectedLevelMap();
	}
}

void EditorMode::ActionLeft()
{
	if (mCursorX > 0)
	{
		mCursorX--;
	}
}

void EditorMode::ActionUp()
{
	if (mCursorY > 0)
	{
		mCursorY--;
	}
}

void EditorMode::ActionDown()
{
	if (mCursorY < FieldMap::MAP_HEIGHT - 1)
	{
		mCursorY++;
	}
}

void EditorMode::ActionRight()
{
	if (mCursorX < FieldMap::MAP_WIDTH - 1)
	{
		mCursorX++;
	}
}

void EditorMode::ActionEnter()
{
	mFieldMap->PutObject(mCursorX, mCursorY, mPutObjectType);
}

void EditorMode::ActionEscape()
{
	mFieldMap = nullptr;
	mModeType->SetMainMode();
}

void EditorMode::ActionSpace()
{
}

void EditorMode::ActionNum(int level)
{
	mFieldMap = &mFieldMaps[level - 1];
	system("CLS");
}

void EditorMode::ActionPlayer()
{
	mPutObjectType = EObjectTypes::PLAYER;
}

void EditorMode::ActionBox()
{
	mPutObjectType = EObjectTypes::BOX;
}

void EditorMode::ActionWall()
{
	mPutObjectType = EObjectTypes::WALL;
}

void EditorMode::ActionGoal()
{
	mPutObjectType = EObjectTypes::GOAL;
}

void EditorMode::ActionWay()
{
	mPutObjectType = EObjectTypes::WAY;
}

void EditorMode::Initialize()
{
}

void EditorMode::drawSelectLevel() const
{
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "*********************** Editor Mode *************************" << std::endl;
	std::cout << std::endl;
	std::cout << " Select level of field map you want to edit between 1 and 6. " << std::endl;
	std::cout << std::endl;
	std::cout << "            1      2      3      4      5      6             " << std::endl;
	std::cout << std::endl;
	std::cout << "*************************************************************" << std::endl;
	std::cout << std::endl;
	std::cout << "   ESC: Back to Main" << std::endl;
}

void EditorMode::drawSelectedLevelMap() const
{
	drawFieldMap();
	drawObjectDescription();
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "   Press one of the above keys to select object type to set." << std::endl;
	std::cout << std::endl;
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "   ENTER: Set Selected Object on []    ESC: Save and Back to Main" << std::endl;
}

void EditorMode::drawFieldMap() const
{
	Object* object;
	bool isCursorOn = false;
	for (unsigned int i = 0; i < FieldMap::MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < FieldMap::MAP_WIDTH; j++)
		{
			if (mCursorX == j && mCursorY == i)
			{
				isCursorOn = true;
			}

			object = mFieldMap->GetObjectFromMap(j, i);

			if (object == nullptr)
			{
				printObjectByColor(EObjectColors::BLACK_WHITE, isCursorOn);
			}
			else if (object->GetObjectType() == EObjectTypes::GOAL && object->IsThereObjectOnGoal())
			{
				printObjectByColor(object->GetObjectOnGoal()->GetObjectColor(), isCursorOn);
			}
			else
			{
				printObjectByColor(object->GetObjectColor(), isCursorOn);
			}

			isCursorOn = false;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void EditorMode::printObjectDescriptionByObjectType(EObjectTypes objectType) const
{
	if (mPutObjectType == objectType)
	{
		SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_YELLOW));
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	}

	if (objectType == EObjectTypes::PLAYER)
	{
		std::cout << " Player: p  ";
	}
	else if (objectType == EObjectTypes::BOX)
	{
		std::cout << " Box: b  ";
	}
	else if (objectType == EObjectTypes::GOAL)
	{
		std::cout << " Goal: g  ";
	}
	else if (objectType == EObjectTypes::WALL)
	{
		std::cout << " Wall: w  ";
	}
	else
	{
		std::cout << " Way: y  ";
	}
}