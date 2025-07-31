#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"
#include "Constants.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	/// <summary>
	/// Default C'TOR - initiate empty fields
	/// </summary>
	MenuRequestHandler() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="handleFactory"> - the request handler factory</param>
	/// <param name="user"> - the logged user</param>
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user);

	/// <summary>
	/// method checks if request is relevant
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>is request is relevant</returns>
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	/// <summary>
	/// method handles request
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	virtual RequestResult handleRequest(const RequestInfo& request) override;
private:
	RequestHandlerFactory& m_handlerFactory;	// the handler factory
	LoggedUser m_user;
	static roomID m_curRoomId;	// id of the current room to be created

	/// <summary>
	/// method logs out user
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult logout(const RequestInfo& request) const;
	/// <summary>
	/// method gets rooms
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getRooms(const RequestInfo& request);
	/// <summary>
	/// method gets the players in a room
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getPlayersInRoom(const RequestInfo& request);
	/// <summary>
	/// method gets a player's personal stats
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getPersonalStats(const RequestInfo& request);
	/// <summary>
	/// method gets the 3 highest scoring players
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getHighScore(const RequestInfo& request);
	/// <summary>
	/// method joins room
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult joinRoom(const RequestInfo& request);
	/// <summary>
	/// method creates room
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult createRoom(const RequestInfo& request)  const;
};
