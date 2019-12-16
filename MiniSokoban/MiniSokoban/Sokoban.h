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

private:
	void GetIntoGame(ModeType& modeType);
	void PerformMode(GameMode* mode);
	void SetFieldMapLevel1(FieldMap* fieldMap);

	StartMode mStart;
	EditorMode mEditor;
	PlayMode mPlay;
	FieldMap* mFieldMap;
};

