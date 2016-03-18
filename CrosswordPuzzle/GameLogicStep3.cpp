
#include "ScreenOutput.h"

#include "GameLogicStep3.h"
#include <iostream>

GameLogicStep3::GameLogicStep3(GameDataInterface *gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

bool GameLogicStep3::startQuizGame()
{
	map<int, map<int, QuizBlockData*>>* mQuizBlockData = mGameDataInterface->getQuizBlockData();
	map<int, map<int, WordDb*>>* mQuizBlockNumberData = mGameDataInterface->getQuizBlockNumberData();
	vector<WordDb*>* mSelectWordList = mGameDataInterface->getSelectWordList();

	int hozSize = 0;
	int vecSize = 0;
	mGameDataInterface->getBlockTotalSize(&hozSize, &vecSize);

	for (int j = 0; j < vecSize; ++j) 
	{
		for(int k = 0; k < hozSize; ++k) 
		{
			if ((*mQuizBlockData)[j][k] != NULL) 
			{
				(*mQuizBlockData)[j][k]->mVisible = false;
			}
		}
	}

	int quizSize = mQuizBlockData->size();
	while (true) 
	{
		system("cls");

		ScreenOutput::printQuizBlockQuiz(mQuizBlockNumberData, hozSize, vecSize);

		// 퀴즈 번호를 입력받는다.
		int quizNumber = 0;
		cout << "▶Number : ";
		cin >> quizNumber;

		WordDb *wordDb;
		if (quizNumber > 0 && quizNumber <= quizSize)
		{
			wordDb = mSelectWordList->at(quizNumber - 1);
			cout << "▶Explanation : " << wordDb->mContent << endl;
		} 
		else
		{
			continue;
		}

		string quizAnswer;
		cout << "▶Answer : ";
		cin >> quizAnswer;

		// 정답 맞았을 때 처리
		if (wordDb->mWord == quizAnswer)
		{
			wordDb->mAnswerSuccess = true;
			for (unsigned int i = 0; i < wordDb->mWord.size(); ++i)
			{
				if (wordDb->mStartVec == true)
				{
					(*mQuizBlockData)[wordDb->mStartVecIndex + i][wordDb->mStartHozIndex]->mVisible = true;
				}
				else 
				{
					(*mQuizBlockData)[wordDb->mStartVecIndex][wordDb->mStartHozIndex + i]->mVisible = true;
				}
			}

			if (checkQuizAllAnswerSuccess() == true)
			{
				break;
			}
		}
	}

	return true;
}


// 모든 칸의 정답을 맞추었는지 여부 리턴
bool GameLogicStep3::checkQuizAllAnswerSuccess()
{
	vector<WordDb*>* mSelectWordList = mGameDataInterface->getSelectWordList();

	for (unsigned int i = 0; i < mSelectWordList->size(); ++i)
	{
		if (mSelectWordList->at(i)->mAnswerSuccess == false)
		{
			return false;
		}
	}

	return true;
}