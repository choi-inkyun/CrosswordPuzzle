
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep3
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep3(GameDataInterface *gameDataInterface);

	bool startQuizGame(); // ���� ������ �����Ѵ�.
	bool checkQuizAllAnswerSuccess(); // ��� ������ ���߾���� ���θ� �����Ѵ�.
};