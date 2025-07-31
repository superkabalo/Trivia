#include "Question.h"
#include "Constants.h"

std::string Question::getQuestion() const
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}

Question::Question(const std::string& question, const  std::vector<std::string>& possibleAnswers) : m_question(question), m_possibleAnswers(possibleAnswers)  // initiate fields
{
}

int Question::getCorrectAnswerId() const
{
	return m_possibleAnswers.size() - INC;  // return the index of the last element -> the size of the vector - 1
}