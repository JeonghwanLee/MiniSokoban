#include "MainMode.h"

MainMode::MainMode()
{
}

MainMode::~MainMode()
{
}

void MainMode::Draw()
{
	SetCursorOrigin();
	SetConsoleTextAttribute(mHConsole, static_cast<WORD>(EObjectColors::BLACK_WHITE));
	std::cout << "************  Main  ************" << std::endl;
	std::cout << std::endl;
	std::cout << "        1  Editor Mode          " << std::endl;
	std::cout << std::endl;
	std::cout << "        2  Play Mode            " << std::endl;
	std::cout << std::endl;
	std::cout << "        3  Exit Game            " << std::endl;
	std::cout << std::endl;
	std::cout << "********************************" << std::endl;
	std::cout << std::endl;
}

void MainMode::ActionNum(int mode)
{
	if (mode == 1)
	{
		mModeType->SetEditorMode();
	}
	else if (mode == 2)
	{
		mModeType->SetPlayMode();
	}
	else if (mode == 3)
	{
		mModeType->SetExitMode();
	}
}

void MainMode::ActionLeft()
{
}

void MainMode::ActionUp()
{
}

void MainMode::ActionDown()
{
}

void MainMode::ActionRight()
{
}

void MainMode::ActionEnter()
{
}

void MainMode::ActionEscape()
{
}

void MainMode::ActionSpace()
{
}

void MainMode::ActionPlayer()
{
}

void MainMode::ActionBox()
{
}

void MainMode::ActionWall()
{
}

void MainMode::ActionGoal()
{
}

void MainMode::ActionWay()
{
}

void MainMode::Initialize()
{
}

void MainMode::drawFieldMap() const
{
}

void MainMode::printObjectDescriptionByObjectType(EObjectTypes objectType) const
{
}
