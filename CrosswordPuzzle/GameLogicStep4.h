
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep4
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep4(GameDataInterface *gameDataInterface);

	bool checkContinue(); // ���� ������ ��� �� ������ �ߺθ� ���´�
};