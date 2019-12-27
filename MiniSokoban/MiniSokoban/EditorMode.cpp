#include "EditorMode.h"
#include "Object.h"

EditorMode::EditorMode()
	: mPutObjectType(EObjectTypes::BOX)
	, mCursorX(0)
	, mCursorY(0)
{
}

EditorMode::~EditorMode()
{
}

void EditorMode::Draw()
{
	Clear();
	if (mFieldMap == nullptr)
	{
		DrawSelectLevel();
	}
	else 
	{
		DrawSelectedLevelMap();
	}
}

bool EditorMode::ActionLeft()
{
	if (mCursorX > 0)
	{
		mCursorX--;
	}
	Draw();
	return false;
}

bool EditorMode::ActionUp()
{
	if (mCursorY > 0)
	{
		mCursorY--;
	}
	Draw();
	return false;
}

bool EditorMode::ActionDown()
{
	if (mCursorY < FieldMap::MAP_HEIGHT - 1)
	{
		mCursorY++;
	}
	Draw();
	return false;
}

bool EditorMode::ActionRight()
{
	if (mCursorX < FieldMap::MAP_WIDTH - 1)
	{
		mCursorX++;
	}
	Draw();
	return false;
}

bool EditorMode::ActionEnter()
{
	mFieldMap->PutObject(mCursorX, mCursorY, mPutObjectType);
	Draw();
	return true;
}

bool EditorMode::ActionEscape()
{
	mModeType->SetStartMode();
	return true;
}

bool EditorMode::ActionSpace()
{
	ResetFieldMap();
	Draw();
	return false;
}

bool EditorMode::ActionNum(int level)
{
	mFieldMap = &mFieldMaps[level - 1];
	system("CLS");
	Draw();
	return false;
}

bool EditorMode::ActionPlayer()
{
	mPutObjectType = EObjectTypes::PLAYER;
	Draw();
	return false;
}

bool EditorMode::ActionBox()
{
	mPutObjectType = EObjectTypes::BOX;
	Draw();
	return false;
}

bool EditorMode::ActionWall()
{
	mPutObjectType = EObjectTypes::WALL;
	Draw();
	return false;
}

bool EditorMode::ActionGoal()
{
	mPutObjectType = EObjectTypes::GOAL;
	Draw();
	return false;
}

bool EditorMode::ActionWay()
{
	mPutObjectType = EObjectTypes::WAY;
	Draw();
	return false;
}

void EditorMode::Initialize()
{
}

void EditorMode::ResetFieldMap()
{
	mFieldMap->ResetFieldMapWithWalls();
}

void EditorMode::DrawSelectLevel()
{
	SetConsoleTextAttribute(mHConsole, BLACK_GREEN);
	std::cout << "Select level of field map you want to edit between 1 and 6." << std::endl;
}

void EditorMode::DrawSelectedLevelMap()
{
	DrawFieldMap();
	std::cout << std::endl;
	DrawObjectDescription();
	SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	std::cout << std::endl;
	std::cout << "Press one of the above keys to select object type to set." << std::endl;
	std::cout << std::endl;
	SetConsoleTextAttribute(mHConsole, BLACK_GREEN);
	std::cout << "ENTER: Set Selected Object    SPACE: Reset Field    ESC: Back to Start Menu" << std::endl;
}

void EditorMode::DrawObjectDescription()
{
	SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
	std::cout << "  ";
	if (mPutObjectType == EObjectTypes::PLAYER)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " Player: p  ";

	SetConsoleTextAttribute(mHConsole, RED_WHITE);
	std::cout << "  ";
	if (mPutObjectType == EObjectTypes::BOX)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " Box: b  ";

	SetConsoleTextAttribute(mHConsole, WHITE_BLACK);
	std::cout << "  ";
	if (mPutObjectType == EObjectTypes::WALL)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " Wall: w  ";

	SetConsoleTextAttribute(mHConsole, YELLOW_WHITE);
	std::cout << "  ";
	if (mPutObjectType == EObjectTypes::GOAL)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " Goal: g  ";

	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << "  ";
	if (mPutObjectType == EObjectTypes::WAY)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " Way: y  ";

	std::cout << std::endl;
}

void EditorMode::DrawFieldMap()
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
			if (mCursorX == j && mCursorY == i)
			{
				std::cout << "[]";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}
