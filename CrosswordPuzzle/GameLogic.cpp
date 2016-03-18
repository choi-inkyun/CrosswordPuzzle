
#include "GameLogic.h"

#include <fstream>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>

#include "ScreenOutput.h"

GameLogic::GameLogic()
: GameLogicStep1(this), GameLogicStep2(this), GameLogicStep3(this), GameLogicStep4(this) // ���ڸ� �־ �ʱ�ȭ
{
}

void GameLogic::init() 
{
	ScreenOutput::setGameDataInterface((GameDataInterface*)this);
}

// Block �� ���� ���� ����� ���´�.
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

	// ���� ���� �� ��
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
		// �Ѱ� �ܾ ���ؼ� ��ü ���� �ǿ��� ������ �ܾ �ִ����� �˻��Ѵ�.
		for (int j = 0; j < vecSize; ++j) 
		{
			for(int k = 0; k < hozSize; ++k) 
			{
				if (mQuizBlockData[j][k] != NULL && mQuizBlockData[j][k]->mText == word.at(w) != 0) 
				{
					if ((j != 0 && mQuizBlockData[j-1][k] != NULL) || mQuizBlockData[j+1][k] != NULL)
					{
						// ���η� üũ
						// ���η� ��ġ�� ������ �ִ��� ���� üũ
						int checkIndex = k - w;
						if (checkIndex < 0) {
							break;
						}

						// �ܾ ��ġ�� ���� �� ���� ������ �ܾ �ִ� ��� ���� �ʴ´�. �ܾ �̾����鼭 ��� �� �ֱ� �����̴�.
						int index = k - w - 1;
						if (index > -1 && mQuizBlockData[j][index] != NULL || mQuizBlockData[j][k - w + word.size()] != NULL) {
							break;
						}

						bool success = true;
						// �ߺ��Ǵ� �ܾ �̹� ��ġ�Ǿ� �ִ� ���, �� �ܾ ���� ���η� �ؼ� ������ ��ġ�� �� �ִ��� �˻��ϰ� �����ϸ� �ִ´�.
						for (unsigned int z = 0; z < word.size(); ++z) 
						{
							// ���� �� ��ҿ� �ܾ �ִ��� �˻��Ѵ�.
							index = k - w + z;
							if (mQuizBlockData[j][index] != NULL && index != k) 
							{
								success = false;
								break;
							}
	
							// ���� �� ��� �ֺ��� �ܾ �ִ��� �˻��Ѵ�. �ܾ ��ġ�� ���� �Ǳ� ������ ���� ���������Ƿ�
							if (((j > 0 && mQuizBlockData[j-1][index] != NULL) || mQuizBlockData[j+1][index] != NULL) && index != k)
							{
								success = false;
								break;
							}

						}

						// �ܾ �߰��� �� �ִ� ���� ã�Ҵٸ� �߰����ش�.
						if (success == true)
						{
							insertWordToQuizBlock(wordDb, j, k - w, false, quizIndex);
							return;
						}
					} 
					else if ((k != 0 && mQuizBlockData[j][k-1] != NULL) || mQuizBlockData[j][k+1] != NULL)
					{
						// ���η� üũ
						// ���η� ��ġ�� ������ �ִ��� ���� üũ
						int checkIndex = j - w;
						if (checkIndex < 0) {
							break;
						}

						// �ܾ ��ġ�� ���� �� ���� ������ �ܾ �ִ� ��� ���� �ʴ´�. �ܾ �̾����鼭 ��� �� �ֱ� �����̴�.
						int index = j - w - 1;
						if (index > -1 && mQuizBlockData[index][k] != NULL || mQuizBlockData[j - w + word.size()][k] != NULL) {
							break;
						}

						bool success = true;
						// �ߺ��Ǵ� �ܾ �̹� ��ġ�Ǿ� �ִ� ���, �� �ܾ ���� ���η� �ؼ� ������ ��ġ�� �� �ִ��� �˻��ϰ� �����ϸ� �ִ´�.
						for (unsigned int z = 0; z < word.size(); ++z) 
						{
							int index = j - w + z;
							if (index > -1 && mQuizBlockData[index][k] != NULL && index != j) 
							{
								success = false;
								break;
							}
						
							// ���� �� ��� �ֺ��� �ܾ �ִ��� �˻��Ѵ�. �ܾ ��ġ�� ���� �Ǳ� ������ ���� ���������Ƿ�
							if (((k > 0 && mQuizBlockData[index][k-1] != NULL) || mQuizBlockData[index][k+1] != NULL) && index != j)
							{
								success = false;
								break;
							}
						}

						// �ܾ �߰��� �� �ִ� ���� ã�Ҵٸ� �߰����ش�.
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

	// �ܾ ��ġ�Ҽ� ���� ��Ȳ�̸� ���ο� ���� �ܾ ��ġ�Ѵ�.
	// TODO. �迭�� ũ�� ����ȭ,
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

// �ܾ Ư�� ��ġ�� �ִ´�.
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

// �����¿쿡 �ܾ �ִ� ���� �ִ����� �������ش�.
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
