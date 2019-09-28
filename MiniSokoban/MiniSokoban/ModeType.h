#pragma once
#include "EModeTypes.h"

class ModeType
{
public:
	ModeType();
	~ModeType();

	void SetStartMode();
	void SetEditorMode();
	void SetPlayMode();
	void SetExitMode();

	EModeTypes GetGameMode();

private:
	EModeTypes mMode;
};

