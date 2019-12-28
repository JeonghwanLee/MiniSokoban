#pragma once

#include "EModeTypes.h"

class ModeType
{
public:
	ModeType();
	~ModeType();

	void SetMainMode();
	void SetEditorMode();
	void SetPlayMode();
	void SetExitMode();

	EModeTypes GetGameMode() const;

private:
	EModeTypes mMode;
};

