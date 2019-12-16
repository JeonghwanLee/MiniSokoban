#include "GameMode.h"
#include "Sokoban.h"

GameMode::GameMode()
	: mHConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
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
				system("CLS");
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
	COORD origin = { 0, 0 };
	SetConsoleCursorPosition(mHConsole, origin);
	SetConsoleTextAttribute(mHConsole, 1);
}

bool GameMode::Key_pressed(int key)
{
	return (GetAsyncKeyState(key) & (0x8000 != 0));
}
