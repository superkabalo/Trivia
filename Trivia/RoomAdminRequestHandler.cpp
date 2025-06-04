#include "RoomAdminRequestHandler.h"
#include "CloseRoomResponse.h"
#include "StartGameResponse.h"
#include "GetRoomStateResponse.h"
#include "JsonResponsePacketSerializer.h"
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <thread>

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room) : m_handlerFactory(handlerFactory), m_user(user), m_room(room), m_roomManager(m_handlerFactory.getRoomManager())	// initiate fields
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	if (CLOSE_ROOM_REQ == request.id || START_GAME_REQ == request.id || GET_ROOM_STATE_REQ == request.id)  // check if the request is one of the following
	{
		return true;
	}
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& request)
{
	if (request.id == CLOSE_ROOM_REQ)  // check the request id and call the according method
	{
		return closeRoom(request);
	}
	else if (request.id == START_GAME_REQ)
	{
		return startGame(request);
	}
	else if (request.id == GET_ROOM_STATE_REQ)
	{
		return getRoomState(request);
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& request) const
{
	RequestResult result;	// request result
	std::cout << "New Close Room Request (ADMIN)" << std::endl;
	m_roomManager.deleteRoom(m_room.getRoomData().id);  // delete the room
	CloseRoomResponse closeRoomResponse = { SUCCESS_STATUS };
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);	// return the user to the menu handler
	result.response = JsonResponsePacketSerializer::serializeResponse(closeRoomResponse);
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& request) const
{
	RequestResult result;	// request result
	std::cout << "New Start Game Request (ADMIN)" << std::endl;
	m_roomManager.startGame(m_room.getRoomData().id);   // start the game
	StartGameResponse startGameResponse = { SUCCESS_STATUS };   // construct succesful response and serialize it
	result.response = JsonResponsePacketSerializer::serializeResponse(startGameResponse);
	result.newHandler = m_handlerFactory.createGameRequestHandler(m_user, m_room);  // navigate the user to the game request handler
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& request)
{
	RequestResult result;	// request result
	std::cout << "New Get Room State Request (ADMIN)" << std::endl;
	GetRoomStateResponse getRoomStateResponse;
	getRoomStateResponse.status = m_room.getRoomData().status;  // set getRoomStateResponse fields
	getRoomStateResponse.hasGameBegun = m_room.getRoomData().isActive;
	getRoomStateResponse.players = m_room.getAllUsers();
	getRoomStateResponse.answerTimeout = m_room.getRoomData().timePerQuestion;
	getRoomStateResponse.questionCount = m_room.getRoomData().numOfQuestionsInGame;
	result.response = JsonResponsePacketSerializer::serializeResponse(getRoomStateResponse);  // serialize response
	result.newHandler = this;   // keep the handler as the RoomAdminRequestHandler
	return result;
}