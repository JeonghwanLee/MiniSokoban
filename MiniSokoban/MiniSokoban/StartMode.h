#pragma once
#include "GameMode.h"

class StartMode : public GameMode
{
public:
	StartMode();
	~StartMode();

	virtual void Draw() override;

	virtual bool ActionNum(int mode) override;

	virtual bool ActionLeft() override;
	virtual bool ActionUp() override;
	virtual bool ActionDown() override;
	virtual bool ActionRight() override;
	virtual bool ActionEnter() override;
	virtual bool ActionEscape() override;
	virtual bool ActionSpace() override;
	virtual bool ActionPlayer() override;
	virtual bool ActionBox() override;
	virtual bool ActionWall() override;
	virtual bool ActionGoal() override;
	virtual bool ActionWay() override;

	virtual void Initialize() override;
	virtual void DrawObjectDescription() override;
	virtual void DrawFieldMap() override;
};

