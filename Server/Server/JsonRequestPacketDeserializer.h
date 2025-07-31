#pragma once
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "GetPlayersInRoomRequest.h"
#include "JoinRoomRequest.h"
#include "CreateRoomRequest.h"
#include "Constants.h"
#include "SubmitAnswerRequest.h"
class JsonRequestPacketDeserializer
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="JsonRequestPacketDeserializer"> - JsonRequestPacketDeserializer to copy</param>
	JsonRequestPacketDeserializer(const JsonRequestPacketDeserializer& requestDeserializer) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the JsonRequestPacketDeserializer object
	/// </summary>
	/// <returns>the instance of the JsonRequestPacketDeserializer object</returns>
	static JsonRequestPacketDeserializer& getInstance();

	/// <summary>
	/// method deserializes login request
	/// </summary>
	/// <param name="request"> - the login request buffer</param>
	/// <returns>the login request</returns>
	static LoginRequest deserializeLoginRequest(const Buffer& request);
	/// <summary>
	/// method deserializes signup request
	/// </summary>
	/// <param name="request"> - the signup request buffer</param>
	/// <returns>the signup request</returns>
	static SignupRequest deserializeSignupRequest(const Buffer& request);
	/// <summary>
	/// method deserializes get players in room request
	/// </summary>
	/// <param name="request"> - the get players in room request buffer</param>
	/// <returns>the get players in room request</returns>
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const Buffer& request);
	/// <summary>
	/// method deserializes join room request
	/// </summary>
	/// <param name="request"> - the join room request buffer</param>
	/// <returns>the join room request</returns>
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer& request);
	/// <summary>
	/// method deserializes create room request
	/// </summary>
	/// <param name="request"> - the create room request buffer</param>
	/// <returns>the create room request</returns>
	static CreateRoomRequest deserializeCreateRoomRequest(const Buffer& request);
	/// <summary>
	/// method deserializes create submit answer request
	/// </summary>
	/// <param name="request"> - the submit answer request buffer</param>
	/// <returns>the submit answer request</returns>
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const Buffer& request);
private:
	/// <summary>
	/// default C'TOR - initiate empty fields
	/// </summary>
	JsonRequestPacketDeserializer() = default;
};