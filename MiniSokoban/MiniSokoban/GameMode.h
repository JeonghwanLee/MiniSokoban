#pragma once

#include "Common.h"
#include "ModeType.h"
#include "FieldMap.h"

class GameMode
{
public:
	GameMode();
	GameMode(const GameMode& other) = delete;
	virtual ~GameMode() = default; 

	void GetIntoMode();
	bool IsKeyPressed(int key) const;
	void SetCursorOrigin();
	void SetFieldMaps(FieldMap* fieldMap);
	void SetModeType(ModeType* modeType);
	void WaitForKeyInput();

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

	virtual void Initialize() = 0;
	virtual void Draw() = 0;

protected:
	void drawObjectDescription() const;
	void printObjectByColor(EObjectColors objectColor, bool isCursorOn) const;

	virtual void drawFieldMap() const = 0;
	virtual void printObjectDescriptionByObjectType(EObjectTypes objectType) const = 0;

	// lifetime is handled by Sokoban
	HANDLE mHConsole;
	ModeType* mModeType;
	FieldMap* mFieldMaps; 
};