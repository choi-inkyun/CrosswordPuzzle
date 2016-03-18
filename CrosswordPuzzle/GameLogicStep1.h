
#pragma once;

#include "GameDataInterface.h"

using namespace std;

class GameLogicStep1
{
private:
	GameDataInterface *mGameDataInterface;

public:
	GameLogicStep1(GameDataInterface *gameDataInterface);

	bool readFileWord(string fileName); // ���Ͽ��� word �� �д´�.
	bool selectRandomWords(int minCount, int maxCount); // �������� �ܾ �����Ѵ�.

};