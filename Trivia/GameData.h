#pragma once
#include "Question.h"
struct GameData
{
	Question currentQuestion;  // the game's data
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	bool isFirstQuestion;
};