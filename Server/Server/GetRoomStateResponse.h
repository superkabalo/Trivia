#pragma once
#include <iostream>
#include <vector>
struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players; // the players who are currently in the room
	unsigned int questionCount;  // the number of questions in the room
	unsigned int answerTimeout;  //the time to answer
};