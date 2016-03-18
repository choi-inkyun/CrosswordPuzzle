
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep1
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep1(GameDataInterface *gameDataInterface);

	bool readFileWord(string fileName); // 파일에서 word 를 읽는다.
	bool selectRandomWords(int minCount, int maxCount); // 랜덤으로 단어를 선택한다.

};