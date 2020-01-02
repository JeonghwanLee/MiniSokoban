#pragma once

#include "EModeTypes.h"

class ModeType final
{
public:
	ModeType();
	ModeType(const ModeType& other) = delete;
	~ModeType() = default;

	void SetEditorMode();
	void SetExitMode();
	void SetMainMode();
	void SetPlayMode();

	EModeTypes GetGameMode() const;

private:
	EModeTypes mMode;
};