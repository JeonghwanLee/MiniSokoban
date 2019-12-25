#include "StartMode.h"

StartMode::StartMode()
{
}

StartMode::~StartMode()
{
}

void StartMode::Draw()
{
	Clear();
	SetConsoleTextAttribute(mHConsole, BLACK_GREEN);
	std::cout << "Start Menu" << std::endl;
	std::cout << "1: Editor Mode" << std::endl;
	std::cout << "2: Play Mode" << std::endl;
	std::cout << "3: Exit" << std::endl;
	std::cout << std::endl;
}

bool StartMode::ActionLeft()
{
	return false;
}

bool StartMode::ActionUp()
{
	return false;
}

bool StartMode::ActionDown()
{
	return false;
}

bool StartMode::ActionRight()
{
	return false;
}

bool StartMode::ActionEnter()
{
	return false;
}

bool StartMode::ActionEscape()
{
	return false;
}

bool StartMode::ActionSpace()
{
	return false;
}

bool StartMode::ActionNum(int mode)
{
	if (mode == 1) 
	{
		mModeType->SetEditorMode();
		return true;
	}
	else if (mode == 2)
	{
		mModeType->SetPlayMode();
		return true;
	} 
	else if (mode == 3)
	{
		mModeType->SetExitMode();
		return true;
	}
	return false;
}

bool StartMode::ActionPlayer()
{
	return false;
}

bool StartMode::ActionBox()
{
	return false;
}

bool StartMode::ActionWall()
{
	return false;
}

bool StartMode::ActionGoal()
{
	return false;
}

bool StartMode::ActionWay()
{
	return false;
}

void StartMode::Initialize()
{
}

void StartMode::DrawObjectDescription()
{
}

void StartMode::DrawFieldMap()
{
}
