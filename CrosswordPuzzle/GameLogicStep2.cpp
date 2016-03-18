
#include "ScreenOutput.h"

#include "GameLogicStep2.h"

GameLogicStep2::GameLogicStep2(GameDataInterface *gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

// ���� ���� �����Ѵ�.
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
		// �ܾ� �� ��ŭ quizBlock �� �߰��Ѵ�.
		mGameDataInterface->insertWordToQuizBlock(mSelectWordList->at(i), i);
	}

	// ��ü �� ����� �˾Ƴ� ������, �� �� �����ŭ ����� ���ش�.
	int hozSize = 0;
	int vecSize = 0;
	mGameDataInterface->getBlockTotalSize(&hozSize, &vecSize);
	ScreenOutput::printQuizBlockAnswer(mGameDataInterface->getQuizBlockNumberData() , hozSize, vecSize);

	return true;
}