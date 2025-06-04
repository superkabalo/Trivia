#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase& database) : m_statisticsManager(StatisticsManager::getInstance(m_database)), m_roomManager(RoomManager::getInstance()), m_loginManager(LoginManager::getInstance(m_database)), m_gameManager(GameManager::getInstance(m_database)), m_database(database)  // initiate database
{
}

RequestHandlerFactory& RequestHandlerFactory::getInstance(IDatabase& database)
{
	static RequestHandlerFactory instance(database);   // create RequestHandlerFactory instance which will be the only instance becuase it is static
	return instance;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);	// return new LoginRequestHandler with the current ReqeustHandlerFactory
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user)
{
	return new MenuRequestHandler(*this, user);	// return new MenuRequestHandler with the current ReqeustHandlerFactory
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& user, const Room& room)
{
	return new RoomAdminRequestHandler(*this, user, room);  // return new RoomAdminRequestHandler with the current ReqeustHandlerFactory
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const LoggedUser& user, const Room& room)
{
	return new RoomMemberRequestHandler(*this, user, room);  // return new RoomMemberRequestHandler with the current ReqeustHandlerFactory
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const LoggedUser& user, const Room& room)
{
	return new GameRequestHandler(*this, user, room);  // return new GameRequestHandler with the current ReqeustHandlerFactory
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return m_gameManager;
}