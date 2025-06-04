#include "RoomMemberRequestHandler.h"
#include "Constants.h"
#include "LeaveRoomResponse.h"
#include "JsonResponsePacketSerializer.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room) : m_handlerFactory(handlerFactory), m_user(user), m_room(room), m_roomManager(m_handlerFactory.getRoomManager())	// initiate fields
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	if (request.id == LEAVE_ROOM_REQ || request.id == GET_ROOM_STATE_REQ)  // check if the request is one of the following
	{
		return true;
	}
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& request)
{
	if (request.id == LEAVE_ROOM_REQ)	// check the request id and call the according method
	{
		return leaveRoom(request);
	}
	else if (request.id == GET_ROOM_STATE_REQ)
	{
		return getRoomState(request);
	}
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& request) const
{
	RequestResult result;	// request result
	std::cout << "New Leave Room Request" << std::endl;
	m_roomManager.getRoom(m_room.getRoomData().id).removeUser(m_user);	// remove the user from the room
	LeaveRoomResponse leaveRoomResponse = { SUCCESS_STATUS };
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveRoomResponse);	// serialize the response
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);	// return the user to the menu handler
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& request)
{
	RequestResult result;	// request result
	std::cout << "New Get Room State Request" << std::endl;
	GetRoomStateResponse getRoomStateResponse;
	getRoomStateResponse.status = m_room.getRoomData().status;  // set getRoomStateResponse fields according to the room data
	getRoomStateResponse.hasGameBegun = false;
	if (m_room.getRoomData().isActive == ACTIVE)  // check if the room is active
	{
		getRoomStateResponse.hasGameBegun = true;
	}
	getRoomStateResponse.players = m_room.getAllUsers();  // get the room details
	getRoomStateResponse.answerTimeout = m_room.getRoomData().timePerQuestion;
	getRoomStateResponse.questionCount = m_room.getRoomData().numOfQuestionsInGame;
	if (m_room.getRoomData().status == ROOM_OPEN_STATUS)	// check if the room is still open
	{
		result.newHandler = this;	// keep handler as RoomMemberRequestHandler
	}
	if (getRoomStateResponse.hasGameBegun)  // room is closed
	{
		result.newHandler = m_handlerFactory.createGameRequestHandler(m_user, m_room);	// set handler as GameRequestHandler
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResponse);  // serialize response
	return result;
}