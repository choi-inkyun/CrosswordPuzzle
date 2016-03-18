
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

// ���Ͽ��� �ܾ �о���δ�.
bool GameLogicStep1::readFileWord(string fileName)
{
	vector<WordDb*>* mWordList = mGameDataInterface->getWordList();

	mWordList->clear(); // ������ ����ü�� �ʱ�ȭ ��Ų��.

	ifstream inFile;
	inFile.open(fileName.c_str());

	if (!inFile.is_open()) 
	{
		cerr << "���� ���� ����" << endl;
		return false;
	}

	int count = 0;
	char readWordLineString[256];
	char readContentLineString[256];
	while (!inFile.eof()) // ���� ������ �д´�.
	{
		// ���پ� �Է��� �Ǿ� �ִٰ� �����Ͽ� �ڵ��Ѵ�.
		inFile.getline(readWordLineString , 256);
		inFile.getline(readContentLineString , 256);

		++count;
		mWordList->push_back(new WordDb(readWordLineString, readContentLineString, count));
	}

	return true;
}

// �Էµ� �ܾ� �߿��� ���� �ܾ ������ �����Ѵ�.
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

	// �������� ���ڸ� ���ؼ�
	vector<int> randomOrder;
	for (unsigned int i = 0; i < mWordList->size(); ++i) 
	{
		randomOrder.push_back(i);
	}
	random_shuffle(randomOrder.begin(), randomOrder.end());

	// �������� ���� ���ڿ��� �ϳ��� ���鼭 ������ �´�.
	for (unsigned int i = 0; i < random; ++i) 
	{
		mSelectWordList->push_back(mWordList->at(randomOrder[i]));
		mSelectWordList->at(i)->mQuizIndex = i;
	}
	
	ScreenOutput::printSelectWoards(mSelectWordList);

	return true;
}