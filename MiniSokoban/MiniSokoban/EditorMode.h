#pragma once
#include "GameMode.h"

class EditorMode : public GameMode
{
public:
	EditorMode();
	virtual ~EditorMode();

	virtual void Draw() override;
	virtual bool ActionLeft() override;
	virtual bool ActionUp() override;
	virtual bool ActionDown() override;
	virtual bool ActionRight() override;
	virtual bool ActionEnter() override;
	virtual bool ActionEscape() override;
	virtual bool ActionSpace() override;
	virtual bool ActionNum(int level) override;
	virtual bool ActionPlayer() override;
	virtual bool ActionBox() override;
	virtual bool ActionWall() override;
	virtual bool ActionGoal() override;
	virtual bool ActionWay() override;

	virtual void Initialize() override;

private:
	void ResetFieldMap();
	void DrawSelectLevel();
	void DrawSelectedLevelMap();

	virtual void DrawObjectDescription() override;
	virtual void DrawFieldMap() override;

	EObjectTypes mPutObjectType;
	unsigned int mCursorX;
	unsigned int mCursorY;
};
