#pragma once

#include "GameMode.h"

class PlayMode final : public GameMode
{
public:
	PlayMode();
	PlayMode(const PlayMode& other) = delete;
	~PlayMode();

	virtual void Initialize() override;
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

private:
	virtual void drawFieldMap() const override;
	virtual void printObjectDescriptionByObjectType(EObjectTypes objectType) const override;

	void checkStageClear();
	void drawGameClear();

	FieldMap* mFieldMap;
	size_t mLevel;
	bool mbLevelClearFlag;
};