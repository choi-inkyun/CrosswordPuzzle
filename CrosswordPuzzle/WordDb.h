
#pragma once;

#include <string>

using namespace std;

// 데이터가 들어갈 객체
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

	// 연산자 오버로딩
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
	bool mAnswerSuccess; // 정답을 맞추었는지.
	int mStartVecIndex; // 어느 위치에서 시작되는지 세로
	int mStartHozIndex; // 어느 위치에서 시작 되는지 가로
	bool mStartVec; // 세로로 나열 되는지 여부
};