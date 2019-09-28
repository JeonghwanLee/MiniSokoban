#include "ModeType.h"

ModeType::ModeType()
	: mMode(START_MODE)
{
}

ModeType::~ModeType()
{
}

void ModeType::SetStartMode()
{
	mMode = START_MODE;
}

void ModeType::SetEditorMode()
{
	mMode = EDITOR_MODE;
}

void ModeType::SetPlayMode()
{
	mMode = PLAY_MODE;
}

void ModeType::SetExitMode()
{
	mMode = EXIT_MODE;
}

EModeTypes ModeType::GetGameMode()
{
	return mMode;
}
