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

	enum { MAX_SIZE = 6 };

private:
	void PerformMode(GameMode* mode);

	ModeType mModeType;
	GameMode* mGameMode;
	FieldMap mFieldMaps[MAX_SIZE];
	size_t mLevel;
};

