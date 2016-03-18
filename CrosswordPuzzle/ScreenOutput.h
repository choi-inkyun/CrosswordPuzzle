
#pragma once;

#include "WordDb.h"
#include "QuizBlockData.h"
#include "GameDataInterface.h"

#include <vector>
#include <map>

// 화면에 출력을 담당하는 Class
class ScreenOutput {

public:
	static void setGameDataInterface(GameDataInterface* gameDataInterface);
	static GameDataInterface* ScreenOutput::mGameDataInterface;

public:
	static void printSelectWoards(vector<WordDb*> *selectWordList); // 선택된 단어 리스트를 출력한다.
	static void printQuizBlockAnswer(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize);
	static void printQuizBlockQuiz(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize);
	static bool printContinue();
private:
	static void printQuizBlock(int hozSize, int vecSize);
	static void printQuizIndex(int index);
};