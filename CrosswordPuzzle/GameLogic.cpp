
#include "GameLogic.h"

#include <fstream>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>

#include "ScreenOutput.h"

GameLogic::GameLogic()
: GameLogicStep1(this), GameLogicStep2(this), GameLogicStep3(this), GameLogicStep4(this) // 인자를 넣어서 초기화
{
}

void GameLogic::init() 
{
	ScreenOutput::setGameDataInterface((GameDataInterface*)this);
}

// Block 의 가로 세로 사이즈를 얻어온다.
void GameLogic::getBlockTotalSize(int *hozSize, int *vecSize) 
{
	map<int, map<int, QuizBlockData*>>::iterator iter = mQuizBlockData.begin();
	for (; iter != mQuizBlockData.end(); ++iter)
	{
		if (iter->first > *vecSize) {
			*vecSize = iter->first;
		}

		map<int, QuizBlockData*>::iterator iter2 = iter->second.begin();
		for (; iter2 != iter->second.end(); ++iter2)
		{
			if (iter2->first > *hozSize) {
				*hozSize = iter2->first;
			}
		}
	}

	// 가로 세로 줄 수
	++(*vecSize);
	++(*hozSize);
}

void GameLogic::insertWordToQuizBlock(WordDb* wordDb, int quizIndex) 
{
	int hozSize = 0;
	int vecSize = 0;
	getBlockTotalSize(&hozSize, &vecSize);

	string word = wordDb->mWord;
	for (unsigned int w = 0; w < word.size(); ++w) 
	{ 
		// 한개 단어에 대해서 전체 퀴즈 판에서 동일한 단어가 있는지를 검사한다.
		for (int j = 0; j < vecSize; ++j) 
		{
			for(int k = 0; k < hozSize; ++k) 
			{
				if (mQuizBlockData[j][k] != NULL && mQuizBlockData[j][k]->mText == word.at(w) != 0) 
				{
					if ((j != 0 && mQuizBlockData[j-1][k] != NULL) || mQuizBlockData[j+1][k] != NULL)
					{
						// 가로로 체크
						// 가로로 배치할 공간이 있는지 여부 체크
						int checkIndex = k - w;
						if (checkIndex < 0) {
							break;
						}

						// 단어가 배치될 양쪽 맨 끝에 다음에 단어가 있는 경우 넣지 않는다. 단어가 이어지면서 헤깔릴 수 있기 때문이다.
						int index = k - w - 1;
						if (index > -1 && mQuizBlockData[j][index] != NULL || mQuizBlockData[j][k - w + word.size()] != NULL) {
							break;
						}

						bool success = true;
						// 중복되는 단어가 이미 배치되어 있는 경우, 그 단어를 가로 세로로 해서 낱말을 배치할 수 있는지 검사하고 가능하면 넣는다.
						for (unsigned int z = 0; z < word.size(); ++z) 
						{
							// 들어가야 할 장소에 단어가 있는지 검색한다.
							index = k - w + z;
							if (mQuizBlockData[j][index] != NULL && index != k) 
							{
								success = false;
								break;
							}
	
							// 들어가야 할 장소 주변에 단어가 있는지 검색한다. 단어가 겹치면 뜻이 되기 때문에 보기 안좋아지므로
							if (((j > 0 && mQuizBlockData[j-1][index] != NULL) || mQuizBlockData[j+1][index] != NULL) && index != k)
							{
								success = false;
								break;
							}

						}

						// 단어를 추가할 수 있는 곳을 찾았다면 추가해준다.
						if (success == true)
						{
							insertWordToQuizBlock(wordDb, j, k - w, false, quizIndex);
							return;
						}
					} 
					else if ((k != 0 && mQuizBlockData[j][k-1] != NULL) || mQuizBlockData[j][k+1] != NULL)
					{
						// 세로로 체크
						// 세로로 배치할 공간이 있는지 여부 체크
						int checkIndex = j - w;
						if (checkIndex < 0) {
							break;
						}

						// 단어가 배치될 양쪽 맨 끝에 다음에 단어가 있는 경우 넣지 않는다. 단어가 이어지면서 헤깔릴 수 있기 때문이다.
						int index = j - w - 1;
						if (index > -1 && mQuizBlockData[index][k] != NULL || mQuizBlockData[j - w + word.size()][k] != NULL) {
							break;
						}

						bool success = true;
						// 중복되는 단어가 이미 배치되어 있는 경우, 그 단어를 가로 세로로 해서 낱말을 배치할 수 있는지 검사하고 가능하면 넣는다.
						for (unsigned int z = 0; z < word.size(); ++z) 
						{
							int index = j - w + z;
							if (index > -1 && mQuizBlockData[index][k] != NULL && index != j) 
							{
								success = false;
								break;
							}
						
							// 들어가야 할 장소 주변에 단어가 있는지 검색한다. 단어가 겹치면 뜻이 되기 때문에 보기 안좋아지므로
							if (((k > 0 && mQuizBlockData[index][k-1] != NULL) || mQuizBlockData[index][k+1] != NULL) && index != j)
							{
								success = false;
								break;
							}
						}

						// 단어를 추가할 수 있는 곳을 찾았다면 추가해준다.
						if (success == true)
						{
							insertWordToQuizBlock(wordDb, j - w, k, true, quizIndex);
							return;
						}
					}
				}
			}
		}
	}

	// 단어를 배치할수 없는 상황이면 새로운 곳에 단어를 배치한다.
	// TODO. 배열판 크기 최적화,
	int wordSize = word.size();
	for (int j = 0; j < 10; ++j) 
	{
		for(int k = 0; k < 10; ++k) 
		{
			bool success = true;
			for (unsigned int w = 0; w < word.size(); ++w) {
				if (checkCrossWordExistToQizeBlock(j, k + w) == true) 
				{
					success = false;
					break;
				}
			}

			if (success == true)
			{
				insertWordToQuizBlock(wordDb, j, k, false, quizIndex);
				return;
			}
		}
	}
}

// 단어를 특정 위치에 넣는다.
bool GameLogic::insertWordToQuizBlock(WordDb* wordDb, int vPos, int hPos, bool addVec, int quizIndex)
{
	string word = wordDb->mWord;
	unsigned int size = word.size();
	for (unsigned int i = 0; i < size; ++i) 
	{
		if (addVec == true) 
		{
			if (mQuizBlockData[vPos+i][hPos] == NULL)
			{
				mQuizBlockData[vPos+i][hPos] = new QuizBlockData(word.at(i));
			}
		} 
		else 
		{
			if (mQuizBlockData[vPos][hPos+i] == NULL)
			{
				mQuizBlockData[vPos][hPos+i] = new QuizBlockData(word.at(i));
			}
		}
	}
	wordDb->mStartVecIndex = vPos;
	wordDb->mStartHozIndex = hPos;
	wordDb->mStartVec = addVec;

	mQuizBlockNumberData[vPos][hPos] = wordDb;
	return true;
}

// 상하좌우에 단어가 있는 블럭이 있는지를 리턴해준다.
bool GameLogic::checkCrossWordExistToQizeBlock(int vPos, int hPos)
{
	if (vPos != 0)
	{
		if (mQuizBlockData[vPos-1][hPos] != NULL)
		{
			return true;
		}
	}

	if (hPos != 0) 
	{
		if (mQuizBlockData[vPos][hPos-1] != NULL)
		{
			return true;
		}
	}

	if (mQuizBlockData[vPos+1][hPos] != NULL
		|| mQuizBlockData[vPos+1][hPos] != NULL)
	{
		return true;
	}

	return false;
}

map<int, map<int, QuizBlockData*>>* GameLogic::getQuizBlockData()
{
	return &mQuizBlockData;
}

map<int, map<int, WordDb*>>* GameLogic::getQuizBlockNumberData()
{
	return &mQuizBlockNumberData;
}

vector<WordDb*>* GameLogic::getWordList()
{
	return &mWordList;
}

vector<WordDb*>* GameLogic::getSelectWordList()
{
	return &mSelectWordList;
}
