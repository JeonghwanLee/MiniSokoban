#pragma once

#include "GameMode.h"

class EditorMode : public GameMode
{
public:
	EditorMode();
	virtual ~EditorMode();

	virtual void Draw() override;
	virtual void ActionLeft() override;
	virtual void ActionUp() override;
	virtual void ActionDown() override;
	virtual void ActionRight() override;
	virtual void ActionEnter() override;
	virtual void ActionEscape() override;
	virtual void ActionSpace() override;
	virtual void ActionNum(int level) override;
	virtual void ActionPlayer() override;
	virtual void ActionBox() override;
	virtual void ActionWall() override;
	virtual void ActionGoal() override;
	virtual void ActionWay() override;

	virtual void Initialize() override;

private:
	void drawSelectLevel() const;
	void drawSelectedLevelMap() const;
	
	virtual void drawFieldMap() const override;
	virtual void printObjectDescriptionByObjectType(EObjectTypes objectType) const override;

	EObjectTypes mPutObjectType;
	unsigned int mCursorX;
	unsigned int mCursorY;
};
