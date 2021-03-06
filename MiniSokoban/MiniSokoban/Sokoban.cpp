#include "Sokoban.h"

Sokoban::Sokoban()
{
	mModeType = std::make_shared<ModeType>();

	mGameModes[0] = new MainMode(mModeType);
	mGameModes[1] = new EditorMode(mModeType);
	mGameModes[2] = new PlayMode(mModeType);

	for (size_t level = 1; level <= MAP_LEVEL; level++)
	{
		mFieldMaps[level - 1].SetUpFieldMapByLevel(level);
	}
}

Sokoban::~Sokoban()
{
	for (GameMode* gameMode : mGameModes)
	{
		delete gameMode;
		gameMode = nullptr;
	}
}

void Sokoban::PlayGame()
{
	while (true)
	{
		setActiveModeType();

		if (mActiveMode == nullptr)
		{
			std::cout << "Terminating Game..." << std::endl;
			return;
		}

		performMode();
	}
}

void Sokoban::performMode()
{
	system("CLS");
	mActiveMode->SetFieldMaps(mFieldMaps);
	mActiveMode->Initialize();
	mActiveMode->GetIntoMode();
}

void Sokoban::setActiveModeType()
{
	switch (mModeType->GetGameMode())
	{
	case EModeTypes::MAIN_MODE:
		mActiveMode = mGameModes[0];
		break;
	case EModeTypes::EDITOR_MODE:
		mActiveMode = mGameModes[1];
		break;
	case EModeTypes::PLAY_MODE:
		mActiveMode = mGameModes[2];
		break;
	case EModeTypes::EXIT_MODE:
		mActiveMode = nullptr;
		break;
	default:
		assert(false);
		break;
	}
}