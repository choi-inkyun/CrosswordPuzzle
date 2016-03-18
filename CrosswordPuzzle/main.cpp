
#include "GameLogic.h"

#include <iostream>

// 단어 선택시 몇개를 할 것인가 여부
static const int SELECT_WORD_MIN_COUNT = 9;
static const int SELECT_WORD_MAX_COUNT = 15;

void main() {
	
	while(true) {
		GameLogic mGameLogic;
		mGameLogic.init();

		// Step1. 파일에서 데이터를 읽어들인다.
		if (mGameLogic.readFileWord("db.txt") == false) 
		{
			cerr << "파일에서 데이터를 읽는데 실패하였습니다." << endl;
			return;
		}

		// Step2. 랜덤한 갯수의 단어를 선택한다.
		if (mGameLogic.selectRandomWords(SELECT_WORD_MIN_COUNT, SELECT_WORD_MAX_COUNT) == false)
		{
			cerr << "단어를 선택하는데 실패하였습니다.." << endl;
			return;
		}

		// Step3. 선택된 단어를 가지고 퀴즈 블럭을 생성한다.
		if (mGameLogic.fillQuizBlock() == false)
		{
			cerr << "퀴즈 블럭을 생성하는데 실패하였습니다.." << endl;
			return;
		}

		getchar();

		if (mGameLogic.startQuizGame() == false)
		{
			cerr << "퀴즈를 진행하는데 실패하였습니다.." << endl;
			return;
		}

		if (mGameLogic.checkContinue() == false)
		{
			break;
		}
	}

	cout << "게임이 종료 되었습니다." << endl;
}