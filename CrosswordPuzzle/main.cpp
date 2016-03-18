
#include "GameLogic.h"

#include <iostream>

// �ܾ� ���ý� ��� �� ���ΰ� ����
static const int SELECT_WORD_MIN_COUNT = 9;
static const int SELECT_WORD_MAX_COUNT = 15;

void main() {
	
	while(true) {
		GameLogic mGameLogic;
		mGameLogic.init();

		// Step1. ���Ͽ��� �����͸� �о���δ�.
		if (mGameLogic.readFileWord("db.txt") == false) 
		{
			cerr << "���Ͽ��� �����͸� �дµ� �����Ͽ����ϴ�." << endl;
			return;
		}

		// Step2. ������ ������ �ܾ �����Ѵ�.
		if (mGameLogic.selectRandomWords(SELECT_WORD_MIN_COUNT, SELECT_WORD_MAX_COUNT) == false)
		{
			cerr << "�ܾ �����ϴµ� �����Ͽ����ϴ�.." << endl;
			return;
		}

		// Step3. ���õ� �ܾ ������ ���� ���� �����Ѵ�.
		if (mGameLogic.fillQuizBlock() == false)
		{
			cerr << "���� ���� �����ϴµ� �����Ͽ����ϴ�.." << endl;
			return;
		}

		getchar();

		if (mGameLogic.startQuizGame() == false)
		{
			cerr << "��� �����ϴµ� �����Ͽ����ϴ�.." << endl;
			return;
		}

		if (mGameLogic.checkContinue() == false)
		{
			break;
		}
	}

	cout << "������ ���� �Ǿ����ϴ�." << endl;
}