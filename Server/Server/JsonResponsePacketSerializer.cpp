#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
using json = nlohmann::json;

JsonResponsePacketSerializer& JsonResponsePacketSerializer::getInstance()
{
	static JsonResponsePacketSerializer instance;	// create JsonResponsePacketSerializer instance which will be the only instance becuase it is static
	return instance;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)ERROR_RES);	 // insert error code to buffer

	Buffer errorBson = json::to_bson({ {"message", errorResponse.message} });	// create binary json
	int dataLen = errorBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), errorBson.begin(), errorBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)LOGIN_RES);	 // insert login response code to buffer

	Buffer loginBson = json::to_bson({ {"status", loginResponse.status} });		// create binary json
	int dataLen = loginBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), loginBson.begin(), loginBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)SIGNUP_RES);	 // insert signup response code to buffer

	Buffer signupBson = json::to_bson({ {"status", signupResponse.status} });	// create binary json
	int dataLen = signupBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), signupBson.begin(), signupBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)LOGOUT_RES);	 // insert logout response code to buffer

	Buffer logoutBson = json::to_bson({ {"status", logoutResponse.status} });	// create binary json
	int dataLen = logoutBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), logoutBson.begin(), logoutBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& getRoomsResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)GET_ROOMS_RES);	 // insert get room response code to buffer
	json getRoomsJson; // create a new json
	getRoomsJson["status"] = getRoomsResponse.status;
	// loop through all rooms and add them to the json
	for (int i = 0; i < getRoomsResponse.rooms.size(); i++)
	{
		// add the current room details into their according array in the json
		getRoomsJson["id"].push_back(std::to_string(getRoomsResponse.rooms[i].id));
		getRoomsJson["name"].push_back(getRoomsResponse.rooms[i].name);
		getRoomsJson["isActive"].push_back(std::to_string(getRoomsResponse.rooms[i].isActive));
		getRoomsJson["maxPlayers"].push_back(std::to_string(getRoomsResponse.rooms[i].maxPlayers));
		getRoomsJson["numOfQuestionsInGame"].push_back(std::to_string(getRoomsResponse.rooms[i].numOfQuestionsInGame));
		getRoomsJson["timePerQuestion"].push_back(std::to_string(getRoomsResponse.rooms[i].timePerQuestion));
	}
	Buffer getRoomsBson = json::to_bson(getRoomsJson);	 // convert json to bson
	int dataLen = getRoomsBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), getRoomsBson.begin(), getRoomsBson.end());  // insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)GET_PLAYERS_IN_ROOM_RES);  // insert get players in room response code to buffer

	json getPlayersJson; // create a new json
	// loop through all players and add them to the json
	for (int i = 0; i < getPlayersInRoomResponse.players.size(); i++)
	{
		getPlayersJson["players"].push_back(getPlayersInRoomResponse.players[i]); // add currnet player's name as string to its array in the json
	}
	Buffer getPlayersBson = json::to_bson(getPlayersJson);  // convert json to bson
	int dataLen = getPlayersBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), getPlayersBson.begin(), getPlayersBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& joinRoomResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)JOIN_ROOM_RES);	 // insert join room response code to buffer
	Buffer joinRoomBson = json::to_bson({ {"status", joinRoomResponse.status} });	// create binary json
	int dataLen = joinRoomBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), joinRoomBson.begin(), joinRoomBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& createRoomResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)CREATE_ROOM_RES);	// insert create room response code to buffer
	Buffer createRoomBson = json::to_bson({ {"status", createRoomResponse.status}, {"roomId", createRoomResponse.roomId } });  // create binary json
	int dataLen = createRoomBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), createRoomBson.begin(), createRoomBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& getHighScoreResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)HIGH_SCORE_RES);	 // insert get high score response code to buffer
	json getHighScoreJson;	// create a new json
	getHighScoreJson["status"] = getHighScoreResponse.status;
	// Loop through all statistics and add them to the json
	for (int i = 0; i < getHighScoreResponse.statistics.size(); i++)
	{
		getHighScoreJson["statistics"].push_back(getHighScoreResponse.statistics[i]); // add statistic to the statistics array in the json
	}
	Buffer getHighScoreBson = json::to_bson(getHighScoreJson);  // convert json to bson
	int dataLen = getHighScoreBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), getHighScoreBson.begin(), getHighScoreBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)PERSONAL_STATS_RES);	 // insert get personal stats response code to buffer

	json getPersonalStatsJson;  // create a new json
	getPersonalStatsJson["status"] = getPersonalStatsResponse.status;
	// loop through all statistics and add them to the json
	for (int i = 0; i < getPersonalStatsResponse.statistics.size(); i++)
	{
		getPersonalStatsJson["statistics"].push_back(getPersonalStatsResponse.statistics[i]); // Add statistics as string to "Statistics" array
	}
	Buffer getPersonalStatsBson = json::to_bson(getPersonalStatsJson);  // convert json to bson
	int dataLen = getPersonalStatsBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), getPersonalStatsBson.begin(), getPersonalStatsBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& leaveRoomResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)LEAVE_ROOM_RES);	 // insert leave room response code to buffer

	Buffer leaveRoomBson = json::to_bson({ {"status", leaveRoomResponse.status} });	 // create binary json
	int dataLen = leaveRoomBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), leaveRoomBson.begin(), leaveRoomBson.end());	// insert binary json to buffer
	return serializedMsg;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& startGameResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)START_GAME_RES);	 // insert start game response code to buffer

	Buffer startGameBson = json::to_bson({ {"status", startGameResponse.status} });		// create binary json
	int dataLen = startGameBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), startGameBson.begin(), startGameBson.end());	// insert binary json to buffer
	return serializedMsg;
}
Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& getRoomStateResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)GET_ROOM_STATE_RES);	 // insert get room state response code to buffer

	Buffer getRoomStateBson = json::to_bson({ {"status", getRoomStateResponse.status}, {"hasGameBegun", getRoomStateResponse.hasGameBegun}, {"players", getRoomStateResponse.players},{"questionCount", getRoomStateResponse.questionCount},{"answerTimeout", getRoomStateResponse.answerTimeout} });		// create binary json
	int dataLen = getRoomStateBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), getRoomStateBson.begin(), getRoomStateBson.end());	// insert binary json to buffer
	return serializedMsg;
}
Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse& leaveGameResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)LEAVE_GAME_RES);	 // insert leave game response code to buffer

	Buffer leaveGameBson = json::to_bson({ {"status", leaveGameResponse.status} });		// create binary json
	int dataLen = leaveGameBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), leaveGameBson.begin(), leaveGameBson.end());	// insert binary json to buffer
	return serializedMsg;
}
Buffer JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& getQuestionResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)GET_QUESTION_RES);	 // insert get question response code to buffer
	json getQuestionJson;	// construct json
	getQuestionJson["status"] = getQuestionResponse.status;
	getQuestionJson["question"] = getQuestionResponse.question;
	for (auto i = getQuestionResponse.answers.begin(); i != getQuestionResponse.answers.end(); ++i)
	{
		// push the possible answers and their ids to the json
		getQuestionJson["answers"].push_back(i->second);
		getQuestionJson["answerId"].push_back(std::to_string(i->first));
	}
	Buffer GetQuestionBson = json::to_bson(getQuestionJson);  // create binary json
	int dataLen = GetQuestionBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), GetQuestionBson.begin(), GetQuestionBson.end());	// insert binary json to buffer
	return serializedMsg;
}
Buffer JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse& getGameResultsResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)GET_GAME_RESULTS_RES);	 // insert get game results response code to buffer
	json getGameResults = { {"status", getGameResultsResponse.status} };  // Create a new JSON document to store rooms
	// Loop through all results and add them to the gameResults document
	for (int i = 0; i < getGameResultsResponse.results.size(); i++)
	{
		// push the game results into their according array in the json
		getGameResults["username"].push_back(getGameResultsResponse.results[i].username);
		getGameResults["correctAnswerCount"].push_back(std::to_string(getGameResultsResponse.results[i].correctAnswerCount));
		getGameResults["wrongAnswerCount"].push_back(std::to_string(getGameResultsResponse.results[i].wrongAnswerCount));
		getGameResults["averageAnswerTime"].push_back(std::to_string(getGameResultsResponse.results[i].averageAnswerTime));
	}
	Buffer getGameResultsBson = json::to_bson(getGameResults);  // convert json to bson
	int dataLen = getGameResultsBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), getGameResultsBson.begin(), getGameResultsBson.end());	// insert binary json to buffer
	return serializedMsg;
}
Buffer JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& submitAnswerResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)SUBMIT_ANSWERS_RES);	 // insert submit answers response code to buffer

	Buffer submitAnswerBson = json::to_bson({ {"status", submitAnswerResponse.status}, {"correctAnswerId", submitAnswerResponse.correctAnswerId } });	// create binary json
	int dataLen = submitAnswerBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), submitAnswerBson.begin(), submitAnswerBson.end());	// insert binary json to buffer
	return serializedMsg;
}
Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& closeRoomResponse)
{
	Buffer serializedMsg;
	serializedMsg.push_back((unsigned char)CLOSE_ROOM_RES);	 // insert close room response code to buffer

	Buffer closeRoomBson = json::to_bson({ {"status", closeRoomResponse.status} });		// create binary json
	int dataLen = closeRoomBson.size();
	for (int i = EMPTY; i < sizeof(dataLen); i++)	// convert dataLen int to bytes and add it to the buffer
	{
		serializedMsg.insert(serializedMsg.begin() + INC, (unsigned char)(dataLen & MAX_BYTE_VALUE));	// push current leftest byte to the beginning of the data length field
		dataLen >>= BYTE_SIZE;	// shift dataLen right to move to the next byte
	}
	serializedMsg.insert(serializedMsg.end(), closeRoomBson.begin(), closeRoomBson.end());	// insert binary json to buffer
	return serializedMsg;
}