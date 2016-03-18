
#include "ScreenOutput.h"

#include <iostream>

GameDataInterface* ScreenOutput::mGameDataInterface = NULL;

void ScreenOutput::setGameDataInterface(GameDataInterface* gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

void ScreenOutput::printSelectWoards(vector<WordDb*> *selectWordList) 
{
	cout << "������������������������������������" << endl;
	cout << "��Select Words                    ��" << endl;
	cout << "������������������������������������" << endl;

	for (unsigned int i = 0; i < selectWordList->size(); ++i) 
	{
		cout << " " << i + 1 << ". " << selectWordList->at(i)->mWord << endl;
	}
}

void ScreenOutput::printQuizBlockAnswer(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize)
{
	cout << "������������������������������������" << endl;
	cout << "��Answer                          ��" << endl;
	cout << "������������������������������������" << endl;

//	cout << "hozSize : " << hozSize << " vecSize : " << vecSize << endl;
	printQuizBlock(hozSize, vecSize);
}

void ScreenOutput::printQuizBlockQuiz(map<int, map<int, WordDb*>> *quizBlockNumberData, int hozSize, int vecSize)
{
	cout << "������������������������������������" << endl;
	cout << "��Quiz                            ��" << endl;
	cout << "������������������������������������" << endl;

//	cout << "hozSize : " << hozSize << " vecSize : " << vecSize << endl;
	printQuizBlock(hozSize, vecSize);
}

void ScreenOutput::printQuizBlock(int hozSize, int vecSize)
{
	map<int, map<int, QuizBlockData*>> *quizBlockData = mGameDataInterface->getQuizBlockData();
	map<int, map<int, WordDb*>> *quizBlockNumberData = mGameDataInterface->getQuizBlockNumberData();

	// ù��° ������ �׸���.
	for (int j = 0; j < hozSize; ++j) 
	{
		if (j == 0) {
			cout << "��������";
		} else if (j == hozSize - 1) {
			cout << "������";
		} else {
			cout << "������";
		}
	}

	cout << endl; // ���� ���.


	for (int i = 0; i < vecSize; ++i) 
	{
		for (int z = 0; z < 2; ++z) { // �� ĭ�� ���� 2�پ�
			for (int j = 0; j < hozSize; ++j) 
			{
				cout << "��";

				bool valueExistCheck = (*quizBlockData)[i][j] != NULL && (*quizBlockData).find(i) != (*quizBlockData).end() 
					&& (*quizBlockData)[i].find(j) != (*quizBlockData)[i].end(); // ���ڿ� ���� �ִ��� üũ

				// ���η� 2�� ���
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
							// ���� �ܾ� ���
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
						cout << "��";
					}
				}
			}
			cout << "��";

			cout << endl; // ���� ���.
		}

		if (i != vecSize - 1) { // ������ ���� �ƴҶ���
			for (int j = 0; j < hozSize; ++j) {
				if (j == 0) {
					cout << "��������";
				} else if (j == hozSize - 1) {
					cout << "������";
				} else {
					cout << "������";
				}
			}
			cout << endl; // ���� ���.
		}
	}

	// ������ �� ó��
	for (int j = 0; j < hozSize; ++j) 
	{
		if (j == 0) {
			cout << "��������";
		} else if (j == hozSize - 1) {
			cout << "������";
		} else {
			cout << "������";
		}
	}

	cout << endl; // ���� ���.
}

void ScreenOutput::printQuizIndex(int index)
{
	switch (index)
	{
	case 1:
		cout << "��";
		break;
	case 2:
		cout << "��";
		break;
	case 3:
		cout << "��";
		break;
	case 4:
		cout << "��";
		break;
	case 5:
		cout << "��";
		break;
	case 6:
		cout << "��";
		break;
	case 7:
		cout << "��";
		break;
	case 8:
		cout << "��";
		break;
	case 9:
		cout << "��";
		break;
	case 10:
		cout << "��";
		break;
	case 11:
		cout << "��";
		break;
	case 12:
		cout << "��";
		break;
	case 13:
		cout << "��";
		break;
	case 14:
		cout << "��";
		break;
	case 15:
		cout << "��";
		break;
	}
}

bool ScreenOutput::printContinue()
{
	cout << "������������������������������������" << endl;
	cout << "��System                          ��" << endl;
	cout << "������������������������������������" << endl;

	string input;

	cout << "��Continue(Y/N) : ";
	cin >> input;

	if (input == "Y")
	{
		return true;
	}

	return false;
}
