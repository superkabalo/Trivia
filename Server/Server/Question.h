#pragma once
#include <iostream>
#include<vector>
class Question
{
public:
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="question"> - the question</param>
	/// <param name="possibleAnswers"> - the possible question answers</param>
	Question(const std::string& question, const std::vector<std::string>& possibleAnswers);
	/// <summary>
	/// method gets the question
	/// </summary>
	/// <returns>the question</returns>
	std::string getQuestion() const;
	/// <summary>
	/// method gets the possible answers to the question
	/// </summary>
	/// <returns>the possible answers to the question</returns>
	std::vector<std::string> getPossibleAnswers() const;
	/// <summary>
	/// method gets the id (index) of the correct answer
	/// </summary>
	/// <returns>the corrent answer id</returns>
	int getCorrectAnswerId() const;
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;	// possible answers to the question
};