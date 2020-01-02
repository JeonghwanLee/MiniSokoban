#include "GameMode.h"
#include "Object.h"

GameMode::GameMode()
	: mHConsole(GetStdHandle(STD_OUTPUT_HANDLE))
	, mModeType(nullptr)
	, mFieldMaps(nullptr)
{
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

bool GameMode::IsKeyPressed(int virtualKeyCode) const
{
	// low bit is set. The key of virtualKeyCode has transitioned from released to pressed.
	return GetAsyncKeyState(virtualKeyCode) & 0x0001; 
}

void GameMode::SetCursorOrigin()
{
	COORD origin = { 0, 0 };
	SetConsoleCursorPosition(mHConsole, origin);
}

void GameMode::SetFieldMaps(FieldMap* fieldMaps)
{
	if (mFieldMaps == nullptr)
	{
		mFieldMaps = fieldMaps;
	}
}

void GameMode::SetModeType(ModeType* modeType)
{
	mModeType = modeType;
}

void GameMode::WaitForKeyInput()
{
	while (true)
	{
		if (IsKeyPressed(VK_LEFT))
		{
			ActionLeft();
			return;
		}
		else if (IsKeyPressed(VK_UP))
		{
			ActionUp();
			return;
		}
		else if (IsKeyPressed(VK_DOWN))
		{
			ActionDown();
			return;
		}
		else if (IsKeyPressed(VK_RIGHT))
		{
			ActionRight();
			return;
		}
		else if (IsKeyPressed(VK_RETURN))
		{
			ActionEnter();
			return;
		}
		else if (IsKeyPressed(VK_ESCAPE))
		{
			ActionEscape();
			system("CLS");
			return;
		}
		else if (IsKeyPressed(VK_SPACE))
		{
			ActionSpace();
			return;
		}
		else if (IsKeyPressed(0x31)) 
		{
			ActionNum(1);
			return;
		}
		else if (IsKeyPressed(0x32)) 
		{
			ActionNum(2);
			return;
		}
		else if (IsKeyPressed(0x33)) 
		{
			ActionNum(3);
			return;
		}
		else if (IsKeyPressed(0x34)) 
		{
			ActionNum(4);
			return;
		}
		else if (IsKeyPressed(0x35)) 
		{
			ActionNum(5);
			return;
		}
		else if (IsKeyPressed(0x36)) 
		{
			ActionNum(6);
			return;
		}
		else if (IsKeyPressed(0x50)) // 'p' pressed
		{
			ActionPlayer();
			return;
		}
		else if (IsKeyPressed(0x42)) // 'b' pressed
		{
			ActionBox();
			return;
		}
		else if (IsKeyPressed(0x57)) // 'w' pressed
		{
			ActionWall();
			return;
		}
		else if (IsKeyPressed(0x47)) // 'g' pressed
		{
			ActionGoal();
			return;
		}
		else if (IsKeyPressed(0x59)) // 'y' pressed
		{
			ActionWay();
			return;
		}
	}
}

void GameMode::drawObjectDescription() const
{
	printObjectByColor(EObjectColors::CYANBLUE_WHITE, false);
	printObjectDescriptionByObjectType(EObjectTypes::PLAYER);

	printObjectByColor(EObjectColors::RED_WHITE, false);
	printObjectDescriptionByObjectType(EObjectTypes::BOX);

	printObjectByColor(EObjectColors::WHITE_BLACK, false);
	printObjectDescriptionByObjectType(EObjectTypes::WALL);

	printObjectByColor(EObjectColors::YELLOW_WHITE, false);
	printObjectDescriptionByObjectType(EObjectTypes::GOAL);

	printObjectByColor(EObjectColors::BLACK_WHITE, false);
	printObjectDescriptionByObjectType(EObjectTypes::WAY);

	std::cout << std::endl;
	std::cout << std::endl;
}

void GameMode::printObjectByColor(EObjectColors objectColor, bool isCursorOn) const
{
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(objectColor));

	if (isCursorOn)
	{
		std::cout << "[]";
		return;
	}

	std::cout << "  ";
}