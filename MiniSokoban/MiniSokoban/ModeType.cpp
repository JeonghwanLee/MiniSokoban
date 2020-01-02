#include "ModeType.h"

ModeType::ModeType()
	: mMode(EModeTypes::MAIN_MODE)
{
}

void ModeType::SetEditorMode()
{
	mMode = EModeTypes::EDITOR_MODE;
}

void ModeType::SetExitMode()
{
	mMode = EModeTypes::EXIT_MODE;
}

void ModeType::SetMainMode()
{
	mMode = EModeTypes::MAIN_MODE;
}

void ModeType::SetPlayMode()
{
	mMode = EModeTypes::PLAY_MODE;
}

EModeTypes ModeType::GetGameMode() const
{
	return mMode;
}