#pragma once
#include "GameMode.h"

class PlayMode : public GameMode
{
public:
	PlayMode(size_t& currentLevel);
	~PlayMode();

	virtual void Initialize() override;
	void CheckStageClear();
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

private:
	size_t mLevel;
	bool bStageClearFlag;

	virtual void DrawObjectDescription() override;
	virtual void DrawFieldMap() override;
};
