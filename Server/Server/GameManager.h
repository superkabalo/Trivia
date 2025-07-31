#pragma once
#include "IDatabase.h"
#include "Game.h"
#include "Room.h"
#include <vector>
class GameManager
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="GameManager"> - GameManager to copy</param>
	GameManager(const GameManager& gameManager) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the GameManager object
	/// </summary>
	/// <param name="database"> - the database</param>
	/// <returns>the instance of the GameManger object</returns>
	static GameManager& getInstance(IDatabase& database);

	/// <summary>
	/// method creates a new game
	/// </summary>
	/// <param name="room">the room to create a game of</param>
	/// <returns>the created game</returns>
	Game& createGame(const Room& room);
	/// <summary>
	/// method deletes game
	/// </summary>
	/// <param name="gameId">the game id of the game to delete</param>
	void deleteGame(const int gameId);
private:
	IDatabase& m_database;  // the database and the active games
	std::vector<Game> m_games;

	/// <summary>
	/// Default C'TOR - initiate fields
	/// </summary>
	GameManager() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="database"> - the database</param>
	GameManager(IDatabase& database);
};