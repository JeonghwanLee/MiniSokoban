#pragma once

#include "Common.h"
#include "EditorMode.h"
#include "FieldMap.h"
#include "MainMode.h"
#include "ModeType.h"
#include "Object.h"
#include "PlayMode.h"

class Sokoban
{
public:
	Sokoban();
	Sokoban(const Sokoban& other) = delete;
	~Sokoban();

	void PlayGame();

private:
	void performMode();
	void setActiveModeType();

	enum { MAP_LEVEL = 6 };
	enum { MODE_COUNT = 3 };

	std::shared_ptr<ModeType> mModeType;
	GameMode* mGameModes[MODE_COUNT];
	GameMode* mActiveMode;
	FieldMap mFieldMaps[MAP_LEVEL];
};