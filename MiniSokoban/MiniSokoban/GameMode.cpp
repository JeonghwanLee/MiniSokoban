#include "GameMode.h"
#include "Sokoban.h"

GameMode::GameMode()
	: mHConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
	mModeType = nullptr;
}

void GameMode::SetModeType(ModeType* modeType)
{
	mModeType = modeType;
}

void GameMode::SetFieldMap(FieldMap* fieldMap)
{
	if (mFieldMap != nullptr)
	{
		delete mFieldMap;
	}
	mFieldMap = fieldMap;
}

void GameMode::WaitForKeyInput()
{
	while (true)
	{
		if (Key_pressed(VK_LEFT))
		{
			if (ActionLeft())
			{
				return;
			}
		}
		else if (Key_pressed(VK_UP))
		{
			if (ActionUp())
			{
				return;
			}
		}
		else if (Key_pressed(VK_DOWN))
		{
			if (ActionDown())
			{
				return;
			}
		}
		else if (Key_pressed(VK_RIGHT))
		{
			if (ActionRight())
			{
				return;
			}
		}
		else if (Key_pressed(VK_RETURN))
		{
			if (ActionEnter())
			{
				return;
			}
		}
		else if (Key_pressed(VK_ESCAPE))
		{
			if (ActionEscape())
			{
				return;
			}
		}
		else if (Key_pressed(VK_SPACE))
		{
			if (ActionSpace())
			{
				return;
			}
		}
		else if (Key_pressed(0x31)) // number 1 pressed
		{
			if (ActionNum1())
			{
				return;
			}
		}
		else if (Key_pressed(0x32)) // number 2 pressed
		{
			if (ActionNum2())
			{
				return;
			}
		}
		else if (Key_pressed(0x33)) // number 3 pressed
		{
			if (ActionNum3())
			{
				return;
			}
		}
		else if (Key_pressed(0x34)) // number 4 pressed
		{
			if (ActionNum4())
			{
				return;
			}
		}
		else if (Key_pressed(0x35)) // number 5 pressed
		{
			if (ActionNum5())
			{
				return;
			}
		}
		Sleep(100);
	}
}

void GameMode::Clear()
{
	SetConsoleTextAttribute(mHConsole, 1);
	system("CLS");
}

void GameMode::PrintAllColors()
{
	for (int i = 0; i < 255; i++)
	{
		SetConsoleTextAttribute(mHConsole, i);
		std::cout << i << " Hello " << std::endl;
	}
}

bool GameMode::Key_pressed(int key)
{
	return (GetAsyncKeyState(key) & (0x8000 != 0));
}
