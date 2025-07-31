#pragma once
#include <string>

struct CreateRoomRequest
{
	std::string roomName;	// details regarding the room
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};