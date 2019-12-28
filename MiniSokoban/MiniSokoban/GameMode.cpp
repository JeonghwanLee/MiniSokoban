#include "GameMode.h"
#include "Object.h"

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
		else if (IsKeyPressed(0x31)) // number 1 pressed
		{
			ActionNum(1);
			return;
		}
		else if (IsKeyPressed(0x32)) // number 2 pressed
		{
			ActionNum(2);
			return;
		}
		else if (IsKeyPressed(0x33)) // number 3 pressed
		{
			ActionNum(3);
			return;
		}
		else if (IsKeyPressed(0x34)) // number 4 pressed
		{
			ActionNum(4);
			return;
		}
		else if (IsKeyPressed(0x35)) // number 5 pressed
		{
			ActionNum(5);
			return;
		}
		else if (IsKeyPressed(0x36)) // number 6 pressed
		{
			ActionNum(6);
			return;
		}
		else if (IsKeyPressed(0x50)) // number 'p' pressed
		{
			ActionPlayer();
			return;
		}
		else if (IsKeyPressed(0x42)) // number 'b' pressed
		{
			ActionBox();
			return;
		}
		else if (IsKeyPressed(0x57)) // number 'w' pressed
		{
			ActionWall();
			return;
		}
		else if (IsKeyPressed(0x47)) // number 'g' pressed
		{
			ActionGoal();
			return;
		}
		else if (IsKeyPressed(0x59)) // number 'y' pressed
		{
			ActionWay();
			return;
		}
	}
}

void GameMode::SetCursorOrigin()
{
	COORD origin = { 0, 0 };
	SetConsoleCursorPosition(mHConsole, origin);
}

bool GameMode::IsKeyPressed(int key) const
{
	return (GetAsyncKeyState(key) & (0x8000 != 0));
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
