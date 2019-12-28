#pragma once

#include "Common.h"
#include "EditorMode.h"
#include "FieldMap.h"
#include "ModeType.h"
#include "Object.h"
#include "PlayMode.h"
#include "MainMode.h"

class Sokoban
{
public:
	Sokoban();
	Sokoban(const Sokoban& other) = delete;
	~Sokoban();

	void PlayGame();

	enum { MAX_LEVEL = 6 };

private:
	void performMode();

	ModeType mModeType;
	GameMode* mGameMode;
	FieldMap mFieldMaps[MAX_LEVEL];
	size_t mLevel;
};

