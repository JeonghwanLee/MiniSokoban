#include "Sokoban.h"

Sokoban::Sokoban()
	: mModeType()
	, mGameMode(nullptr)
	, mLevel(1)
{
	for (size_t i = 0; i < Sokoban::MAX_SIZE; i++)
	{
		mFieldMaps[i].SetUpFieldMapLevels(i);
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
		case EModeTypes::START_MODE:
			mGameMode = new StartMode();
			break;
		case EModeTypes::EDITOR_MODE:
			mGameMode = new EditorMode();
			mGameMode->SetFieldMaps(mFieldMaps);
			break;
		case EModeTypes::PLAY_MODE:
			mGameMode = new PlayMode(mLevel);
			mGameMode->SetFieldMaps(mFieldMaps);
			break;
		case EModeTypes::EXIT_MODE:
			std::cout << "Terminating Game..." << std::endl;
			return;
		default:
			assert(false);
			break;
		}

		mGameMode->SetModeType(&mModeType);
		PerformMode(mGameMode);
	}
}

void Sokoban::PerformMode(GameMode* mode) 
{
	system("CLS");
	mode->Initialize();
	mode->GetIntoMode();
}
