
#pragma once;

#include <string>

// ���� â�� �ϳ��ϳ� �� ������
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