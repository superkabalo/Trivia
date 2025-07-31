#include "Game.h"
#include <algorithm>
#include "SqliteDatabase.h"
#include "Constants.h"
Question Game::getQuestionForUser(const LoggedUser& user)
{
	for (auto playerIt = m_players.begin(); playerIt != m_players.end(); ++playerIt)
	{
		if (!playerIt->first.getUsername().compare(user.getUsername()))  // find the user
		{
			// create the current question
			Question question(playerIt->second.currentQuestion.getQuestion(), playerIt->second.currentQuestion.getPossibleAnswers());
			for (auto questionIt = m_questions.begin(); questionIt != m_questions.end(); ++questionIt)  // find the question in the questions vector
			{
				if (questionIt->getQuestion() == question.getQuestion())  // find the question
				{
					if (questionIt + INC == m_questions.end())  // if it is the last question
					{
						break;
					}
					playerIt->second.currentQuestion = *(++questionIt);  // switch current question to the next question
					break;
				}
			}
			return question;
		}
	}
	std::string emptyStr;  // return empty question (in case anything went wrong)
	std::vector<std::string> emptyVec;
	Question question(emptyStr, emptyVec);
	return question;
}

Game::Game(std::vector<Question>& questions, std::map<LoggedUser, GameData>& players, int gameId)
{
	this->m_gameId = gameId;  // initiate the fields
	this->m_players = players;
	this->m_questions = questions;
	for (auto playerIt = m_players.begin(); playerIt != m_players.end(); ++playerIt)  // initiate the hashmap as fully false
	{
		m_usersFinishedGame[playerIt->first] = false;
	}
}

void Game::removePlayer(const LoggedUser& user)
{
	if (m_players.find(user) != m_players.end())  // find the user and remove him from the players map
	{
		auto playerIt = m_players.find(user);
		submitGameStatsToDB(playerIt->second, user);  // submit the user's stats
		m_players.erase(user);  // remove the user from the players vector
	}
	if (m_usersFinishedGame.find(user) != m_usersFinishedGame.end())  // check if the user is in the hashmapS
	{
		auto usersFinishedGameIt = m_usersFinishedGame.find(user);  // remove the user from the hashmap
		m_usersFinishedGame.erase(usersFinishedGameIt);
	}
}
void Game::submitGameStatsToDB(const GameData& gameData, const LoggedUser& user) const
{
	SqliteDatabase::getInstance().submitGameStatistics(gameData, user);  // submit the user stats to the db
}

std::pair<bool, int> Game::submitAnswer(const int answerId, const int answerTime, const LoggedUser& user)
{
	std::pair<bool, int> submitAnswerPair;
	for (auto playerIt = m_players.begin(); playerIt != m_players.end(); ++playerIt)
	{
		if (!playerIt->first.getUsername().compare(user.getUsername()))  // find the user
		{
			submitAnswerPair.second = CORRECT_ANSWER_INDEX;  // set the correct answer index (always 3)
			playerIt->second.averageAnswerTime += answerTime;

			if (!playerIt->second.isFirstQuestion)  // calculate the user average answer time
			{
				playerIt->second.averageAnswerTime /= TWO_ITEM_AVG_DIVIDE;
			}
			playerIt->second.isFirstQuestion = false;

			if (answerId == CORRECT_ANSWER_INDEX)  // update the user's game data
			{
				playerIt->second.correctAnswerCount++;
				submitAnswerPair.first = true;  // user was correct
			}
			else
			{
				playerIt->second.wrongAnswerCount++;
				submitAnswerPair.first = false;  // user was incorrect
			}
		}
	}
	return submitAnswerPair;
}

std::map<LoggedUser, GameData> Game::getPlayers() const
{
	return this->m_players;
}

int Game::getGameId() const
{
	return this->m_gameId;
}

void Game::userFinished(const LoggedUser& user)
{
	m_usersFinishedGame[user] = true;  // set the user as finished the game
}

bool Game::allUsersFinishedGame() const
{
	for (auto playerFinishedIt = m_usersFinishedGame.begin(); playerFinishedIt != m_usersFinishedGame.end(); ++playerFinishedIt)  // find the user
	{
		if (!playerFinishedIt->second)
		{
			return false;  // if even one of the players did not finish the game
		}
	}
	return true;  // all players finished the gme
}