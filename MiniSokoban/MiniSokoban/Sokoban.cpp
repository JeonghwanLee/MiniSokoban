#include "Sokoban.h"

Sokoban::Sokoban()
	: mModeType()
	, mGameModes{ nullptr }
	, mActiveMode(nullptr)
	, mLevel(1)
{
	for (size_t level = 1; level <= Sokoban::MAX_LEVEL; level++)
	{
		mFieldMaps[level - 1].SetUpFieldMapByLevel(level);
	}
	mGameModes[0] = new MainMode();
	mGameModes[1] = new EditorMode();
	mGameModes[2] = new PlayMode(&mLevel);
}

Sokoban::~Sokoban()
{
	delete[] mGameModes;
}

void Sokoban::PlayGame()
{
	while (true)
	{
		switch (mModeType.GetGameMode())
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
			std::cout << "Terminating Game..." << std::endl;
			return;
		default:
			assert(false);
			break;
		}
		performMode();
	}
}

void Sokoban::performMode()
{
	system("CLS");
	mActiveMode->SetFieldMaps(mFieldMaps);
	mActiveMode->SetModeType(&mModeType);
	mActiveMode->Initialize();
	mActiveMode->GetIntoMode();
}
