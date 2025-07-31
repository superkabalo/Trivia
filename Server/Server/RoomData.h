#pragma once
#include <string>

struct RoomData
{
	unsigned int id;	// the room details
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
	unsigned int status;  // room closed or open
};