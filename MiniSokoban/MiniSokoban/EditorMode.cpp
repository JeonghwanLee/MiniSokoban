#include "EditorMode.h"
#include "Object.h"

EditorMode::EditorMode()
	: mPutObjectType(WAY)
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
	DrawFieldMap();
	std::cout << std::endl;
	DrawObjectDescription();
	std::cout << std::endl;
	std::cout << "SPACE: Reset Field" << std::endl;
	std::cout << std::endl;
	SetConsoleTextAttribute(mHConsole, BLACK_GREEN);
	std::cout << "Editor" << std::endl;
	std::cout << "ESC: Start Menu" << std::endl;
	std::cout << std::endl;
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
	if (mCursorY < mFieldMap->GetMapHeight() - 1)
	{
		mCursorY++;
	}
	Draw();
	return false;
}

bool EditorMode::ActionRight()
{
	if (mCursorX < mFieldMap->GetMapWidth() - 1)
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

bool EditorMode::ActionNum1()
{
	mPutObjectType = PLAYER;
	Draw();
	return false;
}

bool EditorMode::ActionNum2()
{
	mPutObjectType = BOX;
	Draw();
	return false;
}

bool EditorMode::ActionNum3()
{
	mPutObjectType = WALL;
	Draw();
	return false;
}

bool EditorMode::ActionNum4()
{
	mPutObjectType = GOAL;
	Draw();
	return false;
}

bool EditorMode::ActionNum5()
{
	mPutObjectType = WAY;
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

void EditorMode::DrawObjectDescription()
{
	SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
	std::cout << "  ";
	if (mPutObjectType == PLAYER)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " 1: Player ";

	SetConsoleTextAttribute(mHConsole, RED_WHITE);
	std::cout << "  ";
	if (mPutObjectType == BOX)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " 2: Box ";

	SetConsoleTextAttribute(mHConsole, WHITE_BLACK);
	std::cout << "  ";
	if (mPutObjectType == WALL)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " 3: Wall ";

	SetConsoleTextAttribute(mHConsole, YELLOW_WHITE);
	std::cout << "  ";
	if (mPutObjectType == GOAL)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " 4: Goal ";

	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << "  ";
	if (mPutObjectType == WAY)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
	}
	else
	{
		SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	}
	std::cout << " 5: Way ";

	std::cout << std::endl;
}

void EditorMode::DrawFieldMap()
{
	size_t width = mFieldMap->GetMapWidth();
	size_t height = mFieldMap->GetMapHeight();
	Object* object;
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			object = mFieldMap->GetObject(j, i);
			if (object == nullptr)
			{
				SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
			}
			else if (object->GetObjectType() == PLAYER)
			{
				SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
			}
			else if (object->GetObjectType() == BOX)
			{
				SetConsoleTextAttribute(mHConsole, RED_WHITE);
			}
			else if (object->GetObjectType() == WALL)
			{
				SetConsoleTextAttribute(mHConsole, WHITE_BLACK);
			}
			else if (object->GetObjectType() == GOAL)
			{
				if (object->hasNext())
				{
					if (object->GetNextObject()->GetObjectType() == PLAYER)
					{
						SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
					}
					else if (object->GetNextObject()->GetObjectType() == BOX)
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
