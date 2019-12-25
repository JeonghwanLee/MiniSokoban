#include "GameMode.h"
#include "Sokoban.h"

GameMode::GameMode()
	: mHConsole(GetStdHandle(STD_OUTPUT_HANDLE))
	, mModeType(nullptr)
	, mFieldMaps(nullptr)
	, mFieldMap(nullptr)
{
}

void GameMode::SetModeType(ModeType* modeType)
{
	mModeType = modeType;
}

void GameMode::SetFieldMaps(FieldMap* fieldMaps)
{
	mFieldMaps = fieldMaps;
}

void GameMode::GetIntoMode()
{
	EModeTypes currentMode;
	while (true)
	{
		currentMode = mModeType->GetGameMode();
		Draw();
		WaitForKeyInput();
		if (currentMode != mModeType->GetGameMode())
		{
			return;
		}
	}
}

void GameMode::WaitForKeyInput()
{
	while (true)
	{
		if (IsKeyPressed(VK_LEFT))
		{
			if (ActionLeft())
			{
				return;
			}
		}
		else if (IsKeyPressed(VK_UP))
		{
			if (ActionUp())
			{
				return;
			}
		}
		else if (IsKeyPressed(VK_DOWN))
		{
			if (ActionDown())
			{
				return;
			}
		}
		else if (IsKeyPressed(VK_RIGHT))
		{
			if (ActionRight())
			{
				return;
			}
		}
		else if (IsKeyPressed(VK_RETURN))
		{
			if (ActionEnter())
			{
				return;
			}
		}
		else if (IsKeyPressed(VK_ESCAPE))
		{
			if (ActionEscape())
			{ 
				system("CLS");
				return;
			}
		}
		else if (IsKeyPressed(VK_SPACE))
		{
			if (ActionSpace())
			{
				return;
			}
		}
		else if (IsKeyPressed(0x31)) // number 1 pressed
		{
			if (ActionNum(1))
			{
				return;
			}
		}
		else if (IsKeyPressed(0x32)) // number 2 pressed
		{
			if (ActionNum(2))
			{
				return;
			}
		}
		else if (IsKeyPressed(0x33)) // number 3 pressed
		{
			if (ActionNum(3))
			{
				return;
			}
		}
		else if (IsKeyPressed(0x34)) // number 4 pressed
		{
			if (ActionNum(4))
			{
				return;
			}
		}
		else if (IsKeyPressed(0x35)) // number 5 pressed
		{
			if (ActionNum(5))
			{
				return;
			}
		}
		else if (IsKeyPressed(0x36)) // number 6 pressed
		{
			if (ActionNum(6))
			{
				return;
			}
		}
		else if (IsKeyPressed(0x50)) // number 'p' pressed
		{
			if (ActionPlayer())
			{
				return;
			}
		}
		else if (IsKeyPressed(0x42)) // number 'b' pressed
		{
			if (ActionBox())
			{
				return;
			}
		}
		else if (IsKeyPressed(0x57)) // number 'w' pressed
		{
			if (ActionWall())
			{
				return;
			}
		}
		else if (IsKeyPressed(0x47)) // number 'g' pressed
		{
			if (ActionGoal())
			{
				return;
			}
		}
		else if (IsKeyPressed(0x59)) // number 'y' pressed
		{
		if (ActionWay())
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
}

bool GameMode::IsKeyPressed(int key)
{
	return (GetAsyncKeyState(key) & (0x8000 != 0));
}
