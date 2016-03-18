
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep3
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep3(GameDataInterface *gameDataInterface);

	bool startQuizGame(); // 퀴즈 게임을 시작한다.
	bool checkQuizAllAnswerSuccess(); // 모두 정답을 맞추어는지 여부를 리턴한다.
};