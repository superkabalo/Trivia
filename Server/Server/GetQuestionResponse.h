#pragma once
#include <iostream>
#include <map>
struct GetQuestionResponse
{
	unsigned int status;
	std::string question;	// the question
	std::map<unsigned int, std::string> answers;  // a map of map[questionIndex] = questionAnswer
};