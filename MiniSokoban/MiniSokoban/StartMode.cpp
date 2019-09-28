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

bool StartMode::ActionNum1()
{
	mModeType->SetEditorMode();
	return true;
}

bool StartMode::ActionNum2()
{
	mModeType->SetPlayMode();
	return true;
}

bool StartMode::ActionNum3()
{
	mModeType->SetExitMode();
	return true;
}

bool StartMode::ActionNum4()
{
	return false;
}

bool StartMode::ActionNum5()
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
