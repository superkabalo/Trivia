#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "StatisticsManager.h"

int MenuRequestHandler::m_curRoomId = EMPTY;

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user) : m_handlerFactory(handlerFactory), m_user(user)	// initiate request handler factory
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	// check if request is not relavant (is not any of the avilable menu requests)
	if (request.id != LOGIN_REQ && request.id != SIGNUP_REQ && request.id != LOGOUT_REQ && request.id != GET_ROOMS_REQ && request.id != GET_PLAYERS_IN_ROOM_REQ && request.id != PERSONAL_STATS_REQ && request.id != HIGH_SCORE_REQ && request.id != JOIN_ROOM_REQ && request.id != CREATE_ROOM_REQ)
	{
		return false;
	}
	return true;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& request)
{
	if (request.id == LOGOUT_REQ)	// check the request type and call the according handler method
	{
		return logout(request);
	}
	else if (request.id == GET_ROOMS_REQ)
	{
		return getRooms(request);
	}
	else if (request.id == GET_PLAYERS_IN_ROOM_REQ)
	{
		return getPlayersInRoom(request);
	}
	else if (request.id == PERSONAL_STATS_REQ)
	{
		return getPersonalStats(request);
	}
	else if (request.id == HIGH_SCORE_REQ)
	{
		return getHighScore(request);
	}
	else if (request.id == JOIN_ROOM_REQ)
	{
		return joinRoom(request);
	}
	else if (request.id == CREATE_ROOM_REQ)
	{
		return createRoom(request);
	}
}

RequestResult MenuRequestHandler::logout(const RequestInfo& request) const
{
	RequestResult result;	// request result
	std::cout << "New Logout Request" << std::endl;
	result.newHandler = m_handlerFactory.createLoginRequestHandler();	// set next handler as login request handler since the user logged out
	LogoutResponse logoutResponse = { SUCCESS_STATUS };	// construct successful logout response and serialize it
	result.response = JsonResponsePacketSerializer::serializeResponse(logoutResponse);
	return result;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo& request)
{
	RequestResult result;	// request result
	std::cout << "New Get Rooms Request" << std::endl;
	// construct successful get rooms response with the rooms and serialize it
	GetRoomsResponse getRoomsResponse = { SUCCESS_STATUS, m_handlerFactory.getRoomManager().getRooms() };
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomsResponse);
	result.newHandler = this;	// keep handler as MenuRequestHandler
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& request)
{
	RequestResult result;	// request result
	GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(request.buffer);  // deserialize request
	std::cout << "New Get Players in Room Request" << std::endl;
	// construct get players in room response with the room's users and serialize it
	GetPlayersInRoomResponse getPlayersInRoomResponse = { m_handlerFactory.getRoomManager().getRoom(getPlayersInRoomRequest.roomId).getAllUsers() };
	result.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);
	result.newHandler = this;  // keep handler as MenuRequestHandler
	return result;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& request)
{
	RequestResult result;	// request result
	std::cout << "New Get Personal Stats Request" << std::endl;
	// construct successful get personal stats response and serialize it
	GetPersonalStatsResponse getPersonalStatsResponse = { SUCCESS_STATUS, m_handlerFactory.getStatisticsManager().getUserStatistics(m_user.getUsername()) };
	result.response = JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse);
	result.newHandler = this; // keep handler as MenuRequestHandler
	return result;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo& request)
{
	RequestResult result;	// request result
	std::cout << "New Get High Score Request" << std::endl;
	// construct successful get high score response and serialize it
	GetHighScoreResponse getHighScoreResponse = { SUCCESS_STATUS, m_handlerFactory.getStatisticsManager().getHighScore() };
	result.response = JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse);
	result.newHandler = this;  // keep handler as MenuRequestHandler
	return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& request)
{
	RequestResult result;	// request result
	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);  // deserialize request
	std::cout << "New Join Room Request" << std::endl;
	Room& room = m_handlerFactory.getRoomManager().getRoom(joinRoomRequest.roomId);	// get room to join to
	JoinRoomResponse joinRoomResponse;
	if (room.getAllUsers().size() == room.getRoomData().maxPlayers)	// check if the room is full
	{
		joinRoomResponse.status = ERROR_STATUS;
		result.newHandler = this;  // keep handler as MenuRequestHandler
	}
	else
	{
		room.addUser(m_user);	// add user to the room
		joinRoomResponse.status = SUCCESS_STATUS;
		result.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, m_handlerFactory.getRoomManager().getRoom(joinRoomRequest.roomId));  // set the handler as a RoomMemberRequestHandler
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(joinRoomResponse); // serialize join room response
	return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& request) const
{
	RequestResult result;	// request result
	std::cout << "New Create Room Request" << std::endl;
	CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);  // deserialize request
	// creste the room through the room manager
	RoomData roomData = { ++m_curRoomId, createRoomRequest.roomName, createRoomRequest.maxUsers, createRoomRequest.questionCount, createRoomRequest.answerTimeout, false, ROOM_OPEN_STATUS };
	m_handlerFactory.getRoomManager().createRoom(m_user, roomData);
	// create create room response and serialize it
	CreateRoomResponse createRoomResponse = { SUCCESS_STATUS, m_curRoomId };
	result.response = JsonResponsePacketSerializer::serializeResponse(createRoomResponse); // serialize successful join room response
	result.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_handlerFactory.getRoomManager().getRoom(m_curRoomId));  // set handler as RoomAdminRequestHandler
	return result;
}