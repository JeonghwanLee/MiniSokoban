#pragma once
#include "Common.h"
#include "StartMode.h"
#include "EditorMode.h"
#include "PlayMode.h"
#include "ModeType.h"
#include "Object.h"
#include "FieldMap.h"

class Sokoban
{
public:
	Sokoban();
	Sokoban(const Sokoban& other) = delete;
	~Sokoban();

	void PlayGame();

	enum { MAX_LEVEL = 6 };

private:
	void PerformMode();

	ModeType mModeType;
	GameMode* mGameMode;
	FieldMap mFieldMaps[MAX_LEVEL];
	size_t mLevel;
};

