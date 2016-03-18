
#include "ScreenOutput.h"

#include <iostream>

GameDataInterface* ScreenOutput::mGameDataInterface = NULL;

void ScreenOutput::setGameDataInterface(GameDataInterface* gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

void ScreenOutput::printSelectWoards(vector<WordDb*> *selectWordList) 
{
	cout << "┏━━━━━━━━━━━━━━━━┓" << endl;
	cout << "┃Select Words                    ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;

	for (unsigned int i = 0; i < selectWordList->size(); ++i) 
	{
		cout << " " << i + 1 << ". " << selectWordList->at(i)->mWord << endl;
	}
}

void ScreenOutput::printQuizBlockAnswer(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize)
{
	cout << "┏━━━━━━━━━━━━━━━━┓" << endl;
	cout << "┃Answer                          ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;

//	cout << "hozSize : " << hozSize << " vecSize : " << vecSize << endl;
	printQuizBlock(hozSize, vecSize);
}

void ScreenOutput::printQuizBlockQuiz(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize)
{
	cout << "┏━━━━━━━━━━━━━━━━┓" << endl;
	cout << "┃Quiz                            ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;

//	cout << "hozSize : " << hozSize << " vecSize : " << vecSize << endl;
	printQuizBlock(hozSize, vecSize);
}

void ScreenOutput::printQuizBlock(int hozSize, int vecSize)
{
	map<int, map<int, QuizBlockData*>> *quizBlockData = mGameDataInterface->getQuizBlockData();
	map<int, map<int, WordDb*>> *quizBlockNumberData = mGameDataInterface->getQuizBlockNumberData();

	// 첫번째 라인을 그린다.
	for (int j = 0; j < hozSize; ++j) 
	{
		if (j == 0) {
			cout << "┏━━┳";
		} else if (j == hozSize - 1) {
			cout << "━━┓";
		} else {
			cout << "━━┳";
		}
	}

	cout << endl; // 한줄 띈다.


	for (int i = 0; i < vecSize; ++i) 
	{
		for (int z = 0; z < 2; ++z) { // 한 칸에 세로 2줄씩
			for (int j = 0; j < hozSize; ++j) 
			{
				cout << "┃";

				bool valueExistCheck = (*quizBlockData)[i][j] != NULL && (*quizBlockData).find(i) != (*quizBlockData).end() 
					&& (*quizBlockData)[i].find(j) != (*quizBlockData)[i].end(); // 문자열 값이 있는지 체크

				// 세로로 2줄 출력
				for (int k = 0; k < 2; ++k) {
					if (valueExistCheck == true) {
						if (z == 0 && k == 0) {
							if ((*quizBlockNumberData)[i][j] != NULL)
							{
								int quizIndex = (*quizBlockNumberData)[i][j]->mQuizIndex + 1;
								printQuizIndex(quizIndex);
							}
							else
							{
								cout << "  ";
							}
						}
						else if (z == 1 && k == 1) 
						{
							// 영어 단어 출력
							if ((*quizBlockData)[i][j]->mVisible == true) {
								cout << (*quizBlockData)[i][j]->mText << " ";
							} 
							else
							{
								cout << "  ";
							}
						} 
						else 
						{
							cout << "  ";
						}
					} else {
						cout << "■";
					}
				}
			}
			cout << "┃";

			cout << endl; // 한줄 띈다.
		}

		if (i != vecSize - 1) { // 마지막 줄이 아닐때만
			for (int j = 0; j < hozSize; ++j) {
				if (j == 0) {
					cout << "┣━━╋";
				} else if (j == hozSize - 1) {
					cout << "━━┫";
				} else {
					cout << "━━╋";
				}
			}
			cout << endl; // 한줄 띈다.
		}
	}

	// 마지막 줄 처리
	for (int j = 0; j < hozSize; ++j) 
	{
		if (j == 0) {
			cout << "┗━━┻";
		} else if (j == hozSize - 1) {
			cout << "━━┛";
		} else {
			cout << "━━┻";
		}
	}

	cout << endl; // 한줄 띈다.
}

void ScreenOutput::printQuizIndex(int index)
{
	switch (index)
	{
	case 1:
		cout << "①";
		break;
	case 2:
		cout << "②";
		break;
	case 3:
		cout << "③";
		break;
	case 4:
		cout << "④";
		break;
	case 5:
		cout << "⑤";
		break;
	case 6:
		cout << "⑥";
		break;
	case 7:
		cout << "⑦";
		break;
	case 8:
		cout << "⑧";
		break;
	case 9:
		cout << "⑨";
		break;
	case 10:
		cout << "⑩";
		break;
	case 11:
		cout << "⑪";
		break;
	case 12:
		cout << "⑫";
		break;
	case 13:
		cout << "⑬";
		break;
	case 14:
		cout << "⑭";
		break;
	case 15:
		cout << "⑮";
		break;
	}
}

bool ScreenOutput::printContinue()
{
	cout << "┏━━━━━━━━━━━━━━━━┓" << endl;
	cout << "┃System                          ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━┛" << endl;

	string input;

	cout << "▶Continue(Y/N) : ";
	cin >> input;

	if (input == "Y")
	{
		return true;
	}

	return false;
}
