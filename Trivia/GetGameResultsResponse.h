#pragma once
#include "PlayerResults.h"
#include <iostream>
#include <vector>
struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;  // the results of all the players
};