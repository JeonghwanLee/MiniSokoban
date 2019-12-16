#include "PlayMode.h"
#include "Object.h"

PlayMode::PlayMode()
	: bStageClearFlag(false)
{
}

PlayMode::~PlayMode()
{
}

void PlayMode::CheckStageClear()
{
	size_t width = mFieldMap->GetMapWidth();
	size_t height = mFieldMap->GetMapHeight();

	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			Object* object = mFieldMap->GetObject(j, i);
			if (object == nullptr)
			{
				continue;
			}
			else if (object->GetObjectType() == GOAL)
			{
				if (!object->hasNext())
				{
					return;
				}
				else if (object->GetNextObject()->GetObjectType() != BOX)
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
	std::cout << std::endl;
	SetConsoleTextAttribute(mHConsole, BLACK_GREEN);
	std::cout << "Play" << std::endl;
	std::cout << "ESC: Start Menu" << std::endl;
	std::cout << std::endl;
	if (bStageClearFlag)
	{
		SetConsoleTextAttribute(mHConsole, BLACK_YELLOW);
		std::cout << "**********" << std::endl;
		std::cout << "You Win!" << std::endl;
		std::cout << "**********" << std::endl;
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

bool PlayMode::ActionNum1()
{
	return false;
}

bool PlayMode::ActionNum2()
{
	return false;
}

bool PlayMode::ActionNum3()
{
	return false;
}

bool PlayMode::ActionNum4()
{
	return false;
}

bool PlayMode::ActionNum5()
{
	return false;
}

void PlayMode::DrawObjectDescription()
{
	SetConsoleTextAttribute(mHConsole, GREEN_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " 1: Player ";

	SetConsoleTextAttribute(mHConsole, RED_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " 2: Box ";

	SetConsoleTextAttribute(mHConsole, WHITE_BLACK);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " 3: Wall ";

	SetConsoleTextAttribute(mHConsole, YELLOW_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " 4: Goal ";

	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << "  ";
	SetConsoleTextAttribute(mHConsole, BLACK_WHITE);
	std::cout << " 5: Way ";

	std::cout << std::endl;
}

void PlayMode::DrawFieldMap()
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
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void PlayMode::Initialize()
{
	bStageClearFlag = false;
}
