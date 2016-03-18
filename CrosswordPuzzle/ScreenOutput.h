
#pragma once;

#include "WordDb.h"
#include "QuizBlockData.h"
#include "GameDataInterface.h"

#include <vector>
#include <map>

// ȭ�鿡 ����� ����ϴ� Class
class ScreenOutput {

public:
	static void setGameDataInterface(GameDataInterface* gameDataInterface);
	static GameDataInterface* ScreenOutput::mGameDataInterface;

public:
	static void printSelectWoards(vector<WordDb*> *selectWordList); // ���õ� �ܾ� ����Ʈ�� ����Ѵ�.
	static void printQuizBlockAnswer(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize);
	static void printQuizBlockQuiz(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize);
	static bool printContinue();
private:
	static void printQuizBlock(int hozSize, int vecSize);
	static void printQuizIndex(int index);
};