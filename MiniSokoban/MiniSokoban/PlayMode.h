#pragma once
#include "GameMode.h"

class PlayMode : public GameMode
{
public:
	PlayMode();
	~PlayMode();

	// Inherited from GameMode class
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

	virtual bool ActionNum1() override;
	virtual bool ActionNum2() override;
	virtual bool ActionNum3() override;
	virtual bool ActionNum4() override;
	virtual bool ActionNum5() override;

private:
	bool bStageClearFlag;

	// Inherited from GameMode class
	virtual void DrawObjectDescription() override;
	virtual void DrawFieldMap() override;
};
