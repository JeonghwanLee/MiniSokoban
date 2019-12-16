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
	void SetFieldMap(FieldMap* fieldMap);

	virtual void Initialize() = 0;
	void WaitForKeyInput();
	virtual void Draw() = 0;
	void Clear();

	bool Key_pressed(int key);

	virtual bool ActionLeft() = 0;
	virtual bool ActionUp() = 0;
	virtual bool ActionDown() = 0;
	virtual bool ActionRight() = 0;
	virtual bool ActionEnter() = 0;
	virtual bool ActionEscape() = 0;
	virtual bool ActionSpace() = 0;
	virtual bool ActionNum1() = 0;
	virtual bool ActionNum2() = 0;
	virtual bool ActionNum3() = 0;
	virtual bool ActionNum4() = 0;
	virtual bool ActionNum5() = 0;

protected:
	virtual void DrawFieldMap() = 0;
	virtual void DrawObjectDescription() = 0;

	HANDLE mHConsole;
	ModeType* mModeType;
	FieldMap* mFieldMap;
};
