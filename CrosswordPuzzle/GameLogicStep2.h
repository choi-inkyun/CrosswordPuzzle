
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep2
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep2(GameDataInterface *gameDataInterface);

	bool fillQuizBlock(); // ���� ���� �����.
};