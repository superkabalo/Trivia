#pragma once
#include <iostream>
struct PlayerResults
{
	std::string username;  // the player's username and the game results info
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};