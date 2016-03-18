
#pragma once;

#include "GameLogicStep1.h"
#include "GameLogicStep2.h"
#include "GameLogicStep3.h"
#include "GameLogicStep4.h"

#include "WordDb.h"
#include "QuizBlockData.h"
#include "ScreenOutput.h"
#include "GameDataInterface.h"
#include <vector>
#include <map>

using namespace std;

// 게임을 하는데 있어서 로직들을 처리하는 Class이다.
class GameLogic : public GameDataInterface, public GameLogicStep1, public GameLogicStep2, public GameLogicStep3, public GameLogicStep4
{
public:
	GameLogic();
	void init();

private:
	void getBlockTotalSize(int *hozSize, int *vecSize);
	void insertWordToQuizBlock(WordDb* wordDb, int quizIndex); // 단어를 넣는다.
	bool insertWordToQuizBlock(WordDb* wordDb, int vPos, int hPos, bool addVec, int quizIndex); // 단어를 특정 위치에 넣는다.
	bool checkCrossWordExistToQizeBlock(int vPos, int hPos); // 상하좌우에 단어가 들어가 있는지 여부를 리턴한다.
private:
	vector<WordDb*> mWordList; // 데이터 리스트 정의
	vector<WordDb*> mSelectWordList; // 데이터 리스트 정의

	map<int, map<int, QuizBlockData*>> mQuizBlockData; // 퀴즈 블럭 데이터. mSelectWordList 를 가지고 알고리즘에 의해 채워진다.
	map<int, map<int, WordDb*>> mQuizBlockNumberData; // 각 퀴즈 블럭에 어떤 넘버의 퀴즈가 들어가 있는지 여부.. 시작만 표시

public:
	map<int, map<int, QuizBlockData*>>* getQuizBlockData();
	map<int, map<int, WordDb*>>* getQuizBlockNumberData();

	vector<WordDb*>* getWordList();
	vector<WordDb*>* getSelectWordList();
};