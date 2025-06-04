#include "GameManager.h"
#include "Constants.h"
#include <vector>
#include <map>
#include <iostream>
#include <list>
#include <algorithm>

GameManager::GameManager(IDatabase& database) : m_database(database)
{
}

GameManager& GameManager::getInstance(IDatabase& database)
{
	static GameManager gameManager(database);   // create GameManager instance which will be the only instance becuase it is static
	return gameManager;
}

Game& GameManager::createGame(const Room& room)
{
	for (auto gameIt = m_games.begin(); gameIt != m_games.end(); ++gameIt)
	{
		if (gameIt->getGameId() == room.getRoomData().id)  // check if the room already exists
		{
			return *gameIt;
		}
	}
	std::vector<std::string> users = room.getAllUsers();  // get the room's users
	std::vector<GameData> gameDataVector;
	std::list<Question> questionList = m_database.getQuestions(room.getRoomData().numOfQuestionsInGame);  // get the game's questions from the database
	std::vector<Question> questions{ std::begin(questionList), std::end(questionList) };  // initiate the questions vector
	std::map<LoggedUser, GameData> players;
	for (int i = 0; i < users.size(); i++)
	{
		// initiate the em[ty game data
		GameData gameData{ questions[i], EMPTY, EMPTY, EMPTY, true };
		std::pair<LoggedUser, GameData> userGamePair(LoggedUser(users[i]), gameData);  // push the game data
		players.insert(userGamePair);
	}
	this->m_games.push_back(Game(questions, players, room.getRoomData().id));  // insert the new game to the active games list
	return m_games.back();
}

void GameManager::deleteGame(const int gameId)
{
	std::map<LoggedUser, GameData> usersGameData;
	for (auto gameIt = m_games.begin(); gameIt != m_games.end(); ++gameIt)  // find the game to delete
	{
		if (gameIt->getGameId() == gameId)
		{
			m_games.erase(gameIt);  // remove the game from the games vector
			break;
		}
	}
}