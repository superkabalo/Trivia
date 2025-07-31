#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
using json = nlohmann::json;

JsonRequestPacketDeserializer& JsonRequestPacketDeserializer::getInstance()
{
	static JsonRequestPacketDeserializer instance;	// create JsonRequestPacketDeserializer instance which will be the only instance becuase it is static
	return instance;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& request)
{
	LoginRequest loginReq;
	int dataLen = EMPTY;
	for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
	{
		dataLen = (dataLen << BYTE_SIZE) + request[i];  // move dataLen one byte to the left and add the current byte from the buffer
	}
	Buffer data;
	// read data from request buffer into the data buffer
	for (auto i = request.begin() + DATA_BEGIN; i != request.begin() + DATA_BEGIN + dataLen; i++)
	{
		data.push_back(*i);
	}
	// convert data into json
	json jsonData = json::from_bson(data);
	// save data in LoginRequest struct
	loginReq.password = jsonData["password"];
	loginReq.username = jsonData["username"];
	return loginReq;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& request)
{
	SignupRequest signupReq;
	int dataLen = EMPTY;
	for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
	{
		dataLen = (dataLen << BYTE_SIZE) + request[i];  // move dataLen one byte to the left and add the current byte from the buffer
	}
	Buffer data;
	// read data from request buffer into the data buffer
	for (auto i = request.begin() + DATA_BEGIN; i != request.begin() + DATA_BEGIN + dataLen; i++)
	{
		data.push_back(*i);
	}
	// convert data into json
	json jsonData = json::from_bson(data);
	// save data in SignupRequest struct
	signupReq.password = jsonData["password"];
	signupReq.username = jsonData["username"];
	signupReq.email = jsonData["email"];
	signupReq.address = jsonData["address"];
	signupReq.phoneNumber = jsonData["phoneNumber"];
	signupReq.birthDate = jsonData["birthDate"];
	return signupReq;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const Buffer& request)
{
	GetPlayersInRoomRequest getPlayersInRoomReq;
	int dataLen = EMPTY;
	for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
	{
		dataLen = (dataLen << BYTE_SIZE) + request[i];  // move dataLen one byte to the left and add the current byte from the buffer
	}
	Buffer data;
	// read data from request buffer into the data buffer
	for (auto i = request.begin() + DATA_BEGIN; i != request.begin() + DATA_BEGIN + dataLen; i++)
	{
		data.push_back(*i);
	}
	// convert data into json
	json jsonData = json::from_bson(data);
	// save data in GetPlayersInRoomRequest struct
	getPlayersInRoomReq.roomId = jsonData["roomId"];
	return getPlayersInRoomReq;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const Buffer& request)
{
	JoinRoomRequest joinRoomReq;
	int dataLen = EMPTY;
	for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
	{
		dataLen = (dataLen << BYTE_SIZE) + request[i];  // move dataLen one byte to the left and add the current byte from the buffer
	}
	Buffer data;
	// read data from request buffer into the data buffer
	for (auto i = request.begin() + DATA_BEGIN; i != request.begin() + DATA_BEGIN + dataLen; i++)
	{
		data.push_back(*i);
	}
	// convert data into json
	json jsonData = json::from_bson(data);
	// save data in JoinRoomRequest struct
	joinRoomReq.roomId = jsonData["roomId"];
	return joinRoomReq;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const Buffer& request)
{
	CreateRoomRequest createRoomReq;
	int dataLen = EMPTY;
	for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
	{
		dataLen = (dataLen << BYTE_SIZE) + request[i];  // move dataLen one byte to the left and add the current byte from the buffer
	}
	Buffer data;
	// read data from request buffer into the data buffer
	for (auto i = request.begin() + DATA_BEGIN; i != request.begin() + DATA_BEGIN + dataLen; i++)
	{
		data.push_back(*i);
	}
	// convert data into json
	json jsonData = json::from_bson(data);
	// save data in CreateRoomRequest struct
	createRoomReq.answerTimeout = jsonData["answerTimeout"];
	createRoomReq.maxUsers = jsonData["maxUsers"];
	createRoomReq.questionCount = jsonData["questionCount"];
	createRoomReq.roomName = jsonData["roomName"];
	return createRoomReq;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const Buffer& request)
{
	SubmitAnswerRequest submitAnswerReq;
	int dataLen = EMPTY;
	for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
	{
		dataLen = (dataLen << BYTE_SIZE) + request[i];  // move dataLen one byte to the left and add the current byte from the buffer
	}
	Buffer data;
	// read data from request buffer into the data buffer
	for (auto i = request.begin() + DATA_BEGIN; i != request.begin() + DATA_BEGIN + dataLen; i++)
	{
		data.push_back(*i);
	}
	// convert data into json
	json jsonData = json::from_bson(data);
	// save data in SubmitAnswerRequest struct
	submitAnswerReq.answerId = jsonData["answerId"];
	submitAnswerReq.answerTime = jsonData["answerTime"];
	return submitAnswerReq;
}