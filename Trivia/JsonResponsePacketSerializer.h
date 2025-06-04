#pragma once
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"
#include "SubmitAnswerResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetGameResultsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "GetHighScoreResponse.h"
#include "GetPersonalStatsResponse.h"
#include "Constants.h"
#include "GetQuestionResponse.h"
#include "LeaveRoomResponse.h"
#include "LeaveGameResponse.h"
#include "GetRoomStateResponse.h"
#include "StartGameResponse.h"
#include "CloseRoomResponse.h"
class JsonResponsePacketSerializer
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="JsonResponsePacketSerializer"> - JsonResponsePacketSerializer to copy</param>
	JsonResponsePacketSerializer(const JsonResponsePacketSerializer& requestSerializer) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the JsonResponsePacketSerializer object
	/// </summary>
	/// <returns>the instance of the JsonResponsePacketSerializer object</returns>
	static JsonResponsePacketSerializer& getInstance();

	/// <summary>
	/// method serializes error response
	/// </summary>
	/// <param name="errorResponse"> - the error response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const ErrorResponse& errorResponse);
	/// <summary>
	/// method serializes login response
	/// </summary>
	/// <param name="loginResponse"> - the login response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const LoginResponse& loginResponse);
	/// <summary>
	/// method serializes signup response
	/// </summary>
	/// <param name="signupResponse"> - the signup response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const SignupResponse& signupResponse);
	/// <summary>
	/// method serializes logout response
	/// </summary>
	/// <param name="logoutResponse"> - the logout response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const LogoutResponse& logoutResponse);
	/// <summary>
	/// method serializes get rooms response
	/// </summary>
	/// <param name="getRoomsResponse"> - the get rooms response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetRoomsResponse& getRoomsResponse);
	/// <summary>
	/// method serializes get players in room response
	/// </summary>
	/// <param name="getPlayersInRoomResponse"> - the get players in room response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	/// <summary>
	/// method serializes join room response
	/// </summary>
	/// <param name="joinRoomResponse"> - the join room response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const JoinRoomResponse& joinRoomResponse);
	/// <summary>
	/// method serializes create room response
	/// </summary>
	/// <param name="createRoomResponse"> - the create room response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const CreateRoomResponse& createRoomResponse);
	/// <summary>
	/// method serializes get high score response
	/// </summary>
	/// <param name="getHighScoreResponse"> - the get high score response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetHighScoreResponse& getHighScoreResponse);
	/// <summary>
	/// method serializes get personal stats response
	/// </summary>
	/// <param name="getPersonalStatsResponse"> - the get personal stats response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse);
	/// <summary>
	/// method serializes leave room response
	/// </summary>
	/// <param name="leaveRoomResponse"> - the leave room response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const LeaveRoomResponse& leaveRoomResponse);
	/// <summary>
	/// method serializes start game response
	/// </summary>
	/// <param name="startGameResponse"> - the start game response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const StartGameResponse& startGameResponse);
	/// <summary>
	/// method serializes close room response
	/// </summary>
	/// <param name="closeRoomResponse"> - the close room response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const CloseRoomResponse& closeRoomResponse);
	/// <summary>
	/// method serializes get room state response
	/// </summary>
	/// <param name="getRoomState"> - the get room state response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetRoomStateResponse& getRoomStateResponse);
	/// <summary>
	/// method serializes leave game response
	/// </summary>
	/// <param name="getRoomState"> - the leave game response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const LeaveGameResponse& leaveGameResponse);
	/// <summary>
	/// method serializes get question response
	/// </summary>
	/// <param name="getRoomState"> - the get question response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetQuestionResponse& getQuestionResponse);
	/// <summary>
	/// method serializes get game results response
	/// </summary>
	/// <param name="getRoomState"> - the get game results response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const GetGameResultsResponse& getGameResultsResponse);
	/// <summary>
	/// method serializes submit answer response
	/// </summary>
	/// <param name="getRoomState"> - the submit answer response</param>
	/// <returns>Buffer with the serialized response</returns>
	static Buffer serializeResponse(const SubmitAnswerResponse& submitAnswerResponse);
private:
	/// <summary>
	/// default C'TOR - initiate empty fields
	/// </summary>
	JsonResponsePacketSerializer() = default;
};