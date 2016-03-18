
#include "ScreenOutput.h"

#include "GameLogicStep2.h"

GameLogicStep2::GameLogicStep2(GameDataInterface *gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

// 퀴즈 블럭을 생성한다.
bool GameLogicStep2::fillQuizBlock()
{
	vector<WordDb*>* mSelectWordList = mGameDataInterface->getSelectWordList();

	vector<bool> addCheck;
	for (unsigned int i = 0; i < mSelectWordList->size(); ++i) 
	{
		addCheck.push_back(false);
	}

	for (unsigned int i = 0; i < mSelectWordList->size(); ++i) 
	{
		// 단어 수 만큼 quizBlock 에 추가한다.
		mGameDataInterface->insertWordToQuizBlock(mSelectWordList->at(i), i);
	}

	// 전체 판 사이즈를 알아낸 다음에, 그 판 사이즈만큼 출력을 해준다.
	int hozSize = 0;
	int vecSize = 0;
	mGameDataInterface->getBlockTotalSize(&hozSize, &vecSize);
	ScreenOutput::printQuizBlockAnswer(mGameDataInterface->getQuizBlockNumberData() , hozSize, vecSize);

	return true;
}