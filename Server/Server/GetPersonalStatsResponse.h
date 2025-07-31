#pragma once
#include <vector>
#include <string>

struct GetPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;	// the players stats
};
