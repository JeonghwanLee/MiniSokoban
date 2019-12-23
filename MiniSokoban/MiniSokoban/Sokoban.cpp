#include "Sokoban.h"

Sokoban::Sokoban()
	: mModeType()
	, mFieldMap(new FieldMap())
{
	mFieldMap->SetFieldMapLevel1();
}

Sokoban::~Sokoban()
{
	delete mFieldMap;
}

void Sokoban::PlayGame()
{
	while (true)
	{
		if (mGameMode != nullptr) {
			delete mGameMode; // delete previous game mode object in heap
		}
		switch (mModeType.GetGameMode())
		{
		case START_MODE:
			mGameMode = new StartMode();
			break;
		case EDITOR_MODE:
			mGameMode = new EditorMode();
			mGameMode->SetFieldMap(mFieldMap);
			break;
		case PLAY_MODE:
			mGameMode = new PlayMode();
			mGameMode->SetFieldMap(mFieldMap->CreateCopiedFieldMap());
			break;
		case EXIT_MODE:
			std::cout << "Terminating Game..." << std::endl;
			return;
		default:
			break;
		}
		mGameMode->SetModeType(&mModeType);
		PerformMode(mGameMode);
	}
}

void Sokoban::PerformMode(GameMode* mode) 
{
	mode->Initialize();
	mode->Draw();
	mode->WaitForKeyInput();
}
