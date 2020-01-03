#pragma once

#include "GameMode.h"

class MainMode : public GameMode
{
public:
	MainMode(const std::shared_ptr<ModeType>& modeType);
	MainMode(const MainMode& other) = delete;
	~MainMode() = default;

	virtual void Draw() override;

	virtual void ActionNum(int mode) override;
	virtual void ActionLeft() override;
	virtual void ActionUp() override;
	virtual void ActionDown() override;
	virtual void ActionRight() override;
	virtual void ActionEnter() override;
	virtual void ActionEscape() override;
	virtual void ActionSpace() override;
	virtual void ActionPlayer() override;
	virtual void ActionBox() override;
	virtual void ActionWall() override;
	virtual void ActionGoal() override;
	virtual void ActionWay() override;

	virtual void Initialize() override;

private:
	virtual void drawFieldMap() const override;
	virtual void printObjectDescriptionByObjectType(EObjectTypes objectType) const override;
};