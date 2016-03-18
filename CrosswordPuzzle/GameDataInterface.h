
#pragma once;

#include <map>
#include <vector>
#include "WordDb.h"
#include "QuizBlockData.h"

class GameDataInterface {

public:
	virtual vector<WordDb*>* getWordList()
	{
		return NULL;
	}

	virtual vector<WordDb*>* getSelectWordList()
	{
		return NULL;
	}

	virtual map<int, map<int, QuizBlockData*>>* getQuizBlockData()
	{
		return NULL;
	}

	virtual map<int, map<int, WordDb*>>* getQuizBlockNumberData()
	{
		return NULL;
	}

	virtual void getBlockTotalSize(int *hozSize, int *vecSize)
	{
	}

	virtual void insertWordToQuizBlock(WordDb* wordDb, int quizIndex)
	{
	}
};