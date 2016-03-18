
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

// ������ �ϴµ� �־ �������� ó���ϴ� Class�̴�.
class GameLogic : public GameDataInterface, public GameLogicStep1, public GameLogicStep2, public GameLogicStep3, public GameLogicStep4
{
public:
	GameLogic();
	void init();

private:
	void getBlockTotalSize(int *hozSize, int *vecSize);
	void insertWordToQuizBlock(WordDb* wordDb, int quizIndex); // �ܾ �ִ´�.
	bool insertWordToQuizBlock(WordDb* wordDb, int vPos, int hPos, bool addVec, int quizIndex); // �ܾ Ư�� ��ġ�� �ִ´�.
	bool checkCrossWordExistToQizeBlock(int vPos, int hPos); // �����¿쿡 �ܾ �� �ִ��� ���θ� �����Ѵ�.
private:
	vector<WordDb*> mWordList; // ������ ����Ʈ ����
	vector<WordDb*> mSelectWordList; // ������ ����Ʈ ����

	map<int, map<int, QuizBlockData*>> mQuizBlockData; // ���� �� ������. mSelectWordList �� ������ �˰��� ���� ä������.
	map<int, map<int, WordDb*>> mQuizBlockNumberData; // �� ���� ���� � �ѹ��� ��� �� �ִ��� ����.. ���۸� ǥ��

public:
	map<int, map<int, QuizBlockData*>>* getQuizBlockData();
	map<int, map<int, WordDb*>>* getQuizBlockNumberData();

	vector<WordDb*>* getWordList();
	vector<WordDb*>* getSelectWordList();
};