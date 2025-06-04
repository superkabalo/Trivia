#pragma once
#include "Room.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "RequestInfo.h"
#include "RequestResult.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	/// <summary>
	/// Default C'TOR - initiate empty fields
	/// </summary>
	RoomMemberRequestHandler() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="handleFactory"> - the request handler factory</param>
	/// <param name="user"> - the room member user</param>
	/// <param name="room"> - the room of the user</param>
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room);

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
	const Room& m_room;
	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;

	/// <summary>
	/// method leaves room
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult leaveRoom(const RequestInfo& request) const;
	/// <summary>
	/// method gets the room's state
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getRoomState(const RequestInfo& request);
};