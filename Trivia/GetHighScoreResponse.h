#pragma once
#include <vector>
#include <string>

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;	// the highest scoring players and their scores
};