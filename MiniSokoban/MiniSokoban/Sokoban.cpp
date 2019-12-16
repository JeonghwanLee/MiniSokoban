#include "Sokoban.h"

Sokoban::Sokoban()
	: mStart()
	, mEditor()
	, mPlay()
	, mFieldMap(new FieldMap())
{
	ModeType modeType;
	mStart.SetModeType(&modeType);
	mEditor.SetModeType(&modeType);
	mPlay.SetModeType(&modeType);

	SetFieldMapLevel1(mFieldMap);
	mEditor.SetFieldMap(mFieldMap);

	GetIntoGame(modeType);
}

Sokoban::~Sokoban()
{
	delete mFieldMap;
}

void Sokoban::GetIntoGame(ModeType& modeType) 
{
	while (true)
	{
		switch (modeType.GetGameMode())
		{
		case START_MODE:
			PerformMode(&mStart);
			break;
		case EDITOR_MODE:
			PerformMode(&mEditor);
			break;
		case PLAY_MODE:
			mPlay.SetFieldMap(mFieldMap->CopyAndReturnFieldMap());
			PerformMode(&mPlay);
			break;
		case EXIT_MODE:
			std::cout << "Terminating Game..." << std::endl;
			return;
		default:
			break;
		}
	}
}

void Sokoban::PerformMode(GameMode* mode) 
{
	mode->Initialize();
	mode->Draw();
	mode->WaitForKeyInput();
}

void Sokoban::SetFieldMapLevel1(FieldMap* fieldMap)
{
	assert(fieldMap->GetMapWidth() == 20);
	assert(fieldMap->GetMapHeight() == 20);

	fieldMap->PutObject(11, 17, PLAYER);
	fieldMap->ResetFieldMapWithWalls();

	fieldMap->PutObject(5, 18, WAY);
	fieldMap->PutObject(6, 18, WAY);
	fieldMap->PutObject(7, 18, WAY);
	fieldMap->PutObject(8, 18, WAY);
	fieldMap->PutObject(9, 18, WAY);
	fieldMap->PutObject(5, 17, WAY);
	fieldMap->PutObject(9, 17, WAY);
	fieldMap->PutObject(14, 17, WAY);
	fieldMap->PutObject(15, 17, WAY);
	fieldMap->PutObject(16, 17, WAY);
	fieldMap->PutObject(17, 17, WAY);
	fieldMap->PutObject(1, 16, WAY);
	fieldMap->PutObject(2, 16, WAY);
	fieldMap->PutObject(3, 16, WAY);
	fieldMap->PutObject(4, 16, WAY);
	fieldMap->PutObject(5, 16, WAY);
	fieldMap->PutObject(6, 16, WAY);
	fieldMap->PutObject(7, 16, WAY);
	fieldMap->PutObject(8, 16, WAY);
	fieldMap->PutObject(9, 16, WAY);
	fieldMap->PutObject(10, 16, WAY);
	fieldMap->PutObject(11, 16, WAY);
	fieldMap->PutObject(12, 16, WAY);
	fieldMap->PutObject(13, 16, WAY);
	fieldMap->PutObject(14, 16, WAY);
	fieldMap->PutObject(15, 16, WAY);
	fieldMap->PutObject(16, 16, WAY);
	fieldMap->PutObject(17, 16, WAY);
	fieldMap->PutObject(1, 15, WAY);
	fieldMap->PutObject(2, 15, WAY);
	fieldMap->PutObject(3, 15, WAY);
	fieldMap->PutObject(5, 15, WAY);
	fieldMap->PutObject(8, 15, WAY);
	fieldMap->PutObject(14, 15, WAY);
	fieldMap->PutObject(15, 15, WAY);
	fieldMap->PutObject(16, 15, WAY);
	fieldMap->PutObject(17, 15, WAY);
	fieldMap->PutObject(3, 14, WAY);
	fieldMap->PutObject(5, 14, WAY);
	fieldMap->PutObject(8, 14, WAY);
	fieldMap->PutObject(3, 13, WAY);
	fieldMap->PutObject(4, 13, WAY);
	fieldMap->PutObject(5, 13, WAY);
	fieldMap->PutObject(6, 13, WAY);
	fieldMap->PutObject(7, 13, WAY);
	fieldMap->PutObject(8, 13, WAY);
	fieldMap->PutObject(5, 12, WAY);
	fieldMap->PutObject(6, 12, WAY);
	fieldMap->PutObject(7, 12, WAY);
	fieldMap->PutObject(5, 11, WAY);
	fieldMap->PutObject(6, 11, WAY);
	fieldMap->PutObject(7, 11, WAY);
	fieldMap->PutObject(5, 10, WAY);
	fieldMap->PutObject(6, 10, WAY);
	fieldMap->PutObject(7, 10, WAY);

	fieldMap->PutObject(16, 17, GOAL);
	fieldMap->PutObject(17, 17, GOAL);
	fieldMap->PutObject(16, 16, GOAL);
	fieldMap->PutObject(17, 16, GOAL);
	fieldMap->PutObject(16, 15, GOAL);
	fieldMap->PutObject(17, 15, GOAL);

	fieldMap->PutObject(2, 16, BOX);
	fieldMap->PutObject(5, 16, BOX);
	fieldMap->PutObject(5, 13, BOX);
	fieldMap->PutObject(7, 13, BOX);
	fieldMap->PutObject(7, 12, BOX);
	fieldMap->PutObject(5, 11, BOX);
}
