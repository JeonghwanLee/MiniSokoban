#pragma once

#include "Common.h"
#include "ModeType.h"
#include "FieldMap.h"

class GameMode
{
public:
	GameMode();
	virtual ~GameMode() = default;

	void SetModeType(ModeType* modeType);
	void SetFieldMaps(FieldMap* fieldMap);

	void GetIntoMode();
	void WaitForKeyInput();
	void Clear();
	bool IsKeyPressed(int key);

	virtual void Initialize() = 0;
	virtual void Draw() = 0;

	virtual bool ActionLeft() = 0;
	virtual bool ActionUp() = 0;
	virtual bool ActionDown() = 0;
	virtual bool ActionRight() = 0;
	virtual bool ActionEnter() = 0;
	virtual bool ActionEscape() = 0;
	virtual bool ActionSpace() = 0;
	virtual bool ActionNum(int level) = 0;
	virtual bool ActionPlayer() = 0;
	virtual bool ActionBox() = 0;
	virtual bool ActionWall() = 0;
	virtual bool ActionGoal() = 0;
	virtual bool ActionWay() = 0;

protected:
	virtual void DrawFieldMap() = 0;
	virtual void DrawObjectDescription() = 0;

	HANDLE mHConsole;
	ModeType* mModeType;
	FieldMap* mFieldMaps;
	FieldMap* mFieldMap;
};
