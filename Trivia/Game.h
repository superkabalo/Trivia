#pragma once
#include "Question.h"
#include "GameData.h"
#include "LoggedUser.h"
#include "IDatabase.h"
#include <vector>
#include <iostream>
#include <map>
class  Game
{
public:
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="m_questions"> - the game questions</param>
	/// <param name="m_players"> - the game players</param>
	/// <param name="m_gameId"> - the game's id</param>
	Game(std::vector<Question>& m_questions, std::map<LoggedUser, GameData>& players, int gameId);
	/// <summary>
	/// method gets the current question for a user
	/// </summary>
	/// <param name="user"> - the user to get the question for</param>
	/// <returns>the current Question of the user</returns>
	Question getQuestionForUser(const LoggedUser& user);
	/// <summary>
	/// function removes a player from the game
	/// </summary>
	/// <param name="user"> - the user to remove from the game</param>
	void removePlayer(const LoggedUser& user);
	/// <summary>
	/// function submits the answer (checks its correctness and updates the user's game data)
	/// </summary>
	/// <param name="answerId"> - the answer's id</param>
	/// <param name="answerTime"> - the time it took the user to answer</param>
	/// <param name="user"> - the submitting user</param>
	/// <returns>pair of wether the answer was correct, and the correct answer id</returns>
	std::pair<bool, int> submitAnswer(const int answerId, const int answerTime, const LoggedUser& user);
	/// <summary>
	/// method gets all the players in a game
	/// </summary>
	/// <returns>a map with all the players and their according game data</returns>
	std::map<LoggedUser, GameData> getPlayers() const;
	/// <summary>
	/// method submits a game's stats to the database
	/// </summary>
	/// <param name="gameData"> - the game's data</param>
	/// <param name="user"> - the user to submit his data</param>
	void submitGameStatsToDB(const GameData& gameData, const LoggedUser& user) const;
	/// <summary>
	/// method gets the game's id
	/// </summary>
	/// <returns>the game's id</returns>
	int getGameId() const;
	/// <summary>
	/// method sets the user as - user finished the game
	/// </summary>
	/// <param name="user"> - the user to set as finished the game</param>
	void userFinished(const LoggedUser& user);
	/// <summary>
	/// method checks if all the users finished their game
	/// </summary>
	/// <returns>wether all users finished the game or not</returns>
	bool allUsersFinishedGame() const;
private:
	std::vector <Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	std::map<LoggedUser, bool> m_usersFinishedGame;  // hashmap of which users finished the game
	int m_gameId;
};
