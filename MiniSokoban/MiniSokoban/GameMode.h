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
	void SetCursorOrigin();
	bool IsKeyPressed(int key) const;
	virtual void Initialize() = 0;
	virtual void Draw() = 0;

	virtual void ActionLeft() = 0;
	virtual void ActionUp() = 0;
	virtual void ActionDown() = 0;
	virtual void ActionRight() = 0;
	virtual void ActionEnter() = 0;
	virtual void ActionEscape() = 0;
	virtual void ActionSpace() = 0;
	virtual void ActionNum(int level) = 0;
	virtual void ActionPlayer() = 0;
	virtual void ActionBox() = 0;
	virtual void ActionWall() = 0;
	virtual void ActionGoal() = 0;
	virtual void ActionWay() = 0;

protected:
	virtual void drawFieldMap() const = 0;
	virtual void printObjectDescriptionByObjectType(EObjectTypes objectType) const = 0;

	void drawObjectDescription() const;
	void printObjectByColor(EObjectColors objectColor, bool isCursorOn) const;

	HANDLE mHConsole;
	ModeType* mModeType;
	FieldMap* mFieldMaps;
	FieldMap* mFieldMap;
};
