
#pragma once;

#include <string>

// 퀴즈 창의 하나하나 블럭 데이터
class QuizBlockData
{
public:
	char mText;
	bool mVisible;

	QuizBlockData()
	{
		mVisible = true;
		mText = 0;
	}

	QuizBlockData(char text)
	{
		mVisible = true;
		mText = text;
	}

};