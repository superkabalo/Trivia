#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "IDatabase.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameManager.h"

class LoginRequestHandler;	// prevent doubly linking
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="RequestHandlerFactory"> - RequestHandlerFactory to copy</param>
	RequestHandlerFactory(const RequestHandlerFactory& handlerFactory) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the RequestHandlerFactory object
	/// </summary>
	/// <returns>the instance of the RequestHandlerFactory object</returns>
	static RequestHandlerFactory& getInstance(IDatabase& database);

	/// <summary>
	/// method creates new LoginRequestHandler
	/// </summary>
	/// <returns>pointer to the LoginRequestHandler</returns>
	LoginRequestHandler* createLoginRequestHandler();
	/// <summary>
	/// method creates new menu request handler
	/// </summary>
	/// <param name="loggedUser"> - the user connected</param>
	/// <returns>the menu request handler</returns>
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);
	/// <summary>
	/// method creates new room admin request handler
	/// </summary>
	/// <param name="user"> - the room admin user</param>
	/// <param name="room"> - the room of the user</param>
	/// <returns>the room admin request handler</returns>
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser& user, const Room& room);
	/// <summary>
	/// method creates new room member request handler
	/// </summary>
	/// <param name="user"> - the room member user</param>
	/// <param name="room"> - the room of the user</param>
	/// <returns>the room member request handler</returns>
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const LoggedUser& user, const Room& room);
	/// <summary>
	/// method creates new game request handler
	/// </summary>
	/// <param name="user"> - the user</param>
	/// <param name="room"> - the room of the game</param>
	/// <returns>the game request handler</returns>
	GameRequestHandler* createGameRequestHandler(const LoggedUser& user, const Room& room);
	/// <summary>
	/// method gets the login manager
	/// </summary>
	/// <returns>the login manager</returns>
	LoginManager& getLoginManager();
	/// <summary>
	/// method gets the room manager
	/// </summary>
	/// <returns>the room manager</returns>
	RoomManager& getRoomManager();
	/// <summary>
	/// method gets the statistics manager
	/// </summary>
	/// <returns>the room manager</returns>
	StatisticsManager& getStatisticsManager();
	GameManager& getGameManager();
private:
	IDatabase& m_database;
	LoginManager& m_loginManager;	// the managers
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	GameManager& m_gameManager;

	/// <summary>
	/// Default C'TOR - initiate empty fields
	/// </summary>
	RequestHandlerFactory() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="database"> - the database</param>
	RequestHandlerFactory(IDatabase& database);
};