#include "Sokoban.h"

Sokoban::Sokoban()
	: mModeType()
	, mGameMode(nullptr)
	, mLevel(1)
{
	for (size_t level = 1; level <= Sokoban::MAX_LEVEL; level++)
	{
		mFieldMaps[level - 1].SetUpFieldMapByLevel(level);
	}
}

Sokoban::~Sokoban()
{
	delete mGameMode;
}

void Sokoban::PlayGame()
{
	while (true)
	{
		// Delete previous game mode object in heap
		if (mGameMode != nullptr) {
			delete mGameMode; 
		}

		switch (mModeType.GetGameMode())
		{
		case EModeTypes::MAIN_MODE:
			mGameMode = new MainMode();
			break;
		case EModeTypes::EDITOR_MODE:
			mGameMode = new EditorMode();
			break;
		case EModeTypes::PLAY_MODE:
			mGameMode = new PlayMode(&mLevel);
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
	mGameMode->SetFieldMaps(mFieldMaps);
	mGameMode->SetModeType(&mModeType);
	mGameMode->Initialize();
	mGameMode->GetIntoMode();
}
