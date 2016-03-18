
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep4
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep4(GameDataInterface *gameDataInterface);

	bool checkContinue(); // 퀴즈 게임을 계속 할 것인지 야부를 묻는다
};