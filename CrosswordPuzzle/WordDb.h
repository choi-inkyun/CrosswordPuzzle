
#pragma once;

#include <string>

using namespace std;

// �����Ͱ� �� ��ü
class WordDb {
	
public:
	WordDb(string word, string content, int quizIndex) 
	{
		mWord = word;
		mContent = content;
		mQuizIndex = quizIndex;
		mAnswerSuccess = false;
		mStartVecIndex = 0;
		mStartHozIndex = 0;
		mStartVec = false;
	}

	// ������ �����ε�
	void operator = (const WordDb& data)
	{
		mWord = data.mWord;
		mContent = data.mContent;
		mQuizIndex = data.mQuizIndex;
		mAnswerSuccess = data.mAnswerSuccess;
		mStartVecIndex = data.mStartVecIndex;
		mStartHozIndex = data.mStartHozIndex;
		mStartVec = data.mStartVec;
	}
public:
	string mWord;
	string mContent;
	int mQuizIndex;
	bool mAnswerSuccess; // ������ ���߾�����.
	int mStartVecIndex; // ��� ��ġ���� ���۵Ǵ��� ����
	int mStartHozIndex; // ��� ��ġ���� ���� �Ǵ��� ����
	bool mStartVec; // ���η� ���� �Ǵ��� ����
};