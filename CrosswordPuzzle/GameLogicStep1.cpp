
#include "GameLogicStep1.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <time.h>

#include "ScreenOutput.h"

GameLogicStep1::GameLogicStep1(GameDataInterface *gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

// 파일에서 단어를 읽어들인다.
bool GameLogicStep1::readFileWord(string fileName)
{
	vector<WordDb*>* mWordList = mGameDataInterface->getWordList();

	mWordList->clear(); // 데이터 구조체를 초기화 시킨다.

	ifstream inFile;
	inFile.open(fileName.c_str());

	if (!inFile.is_open()) 
	{
		cerr << "파일 오픈 에러" << endl;
		return false;
	}

	int count = 0;
	char readWordLineString[256];
	char readContentLineString[256];
	while (!inFile.eof()) // 파일 끝까지 읽는다.
	{
		// 한줄씩 입력이 되어 있다고 가정하에 코딩한다.
		inFile.getline(readWordLineString , 256);
		inFile.getline(readContentLineString , 256);

		++count;
		mWordList->push_back(new WordDb(readWordLineString, readContentLineString, count));
	}

	return true;
}

// 입력된 단어 중에서 일정 단어를 문제로 선택한다.
bool GameLogicStep1::selectRandomWords(int minCount, int maxCount)
{
	vector<WordDb*>* mWordList = mGameDataInterface->getWordList();
	vector<WordDb*>* mSelectWordList = mGameDataInterface->getSelectWordList();

	srand((unsigned)time(NULL));

	mSelectWordList->clear();

	unsigned random = minCount+ (rand() % (maxCount - minCount + 1));

	if (mWordList->size() == 0) 
	{
		return false;
	}

	// 랜덤으로 숫자를 구해서
	vector<int> randomOrder;
	for (unsigned int i = 0; i < mWordList->size(); ++i) 
	{
		randomOrder.push_back(i);
	}
	random_shuffle(randomOrder.begin(), randomOrder.end());

	// 랜덤으로 구한 숫자에서 하나씩 빼면서 가지고 온다.
	for (unsigned int i = 0; i < random; ++i) 
	{
		mSelectWordList->push_back(mWordList->at(randomOrder[i]));
		mSelectWordList->at(i)->mQuizIndex = i;
	}
	
	ScreenOutput::printSelectWoards(mSelectWordList);

	return true;
}