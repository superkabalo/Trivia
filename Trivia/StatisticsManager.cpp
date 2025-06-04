#include "StatisticsManager.h"

StatisticsManager& StatisticsManager::getInstance(IDatabase& database)
{
	static StatisticsManager statisticsManager(database);   // create StatisticsManager instance which will be the only instance becuase it is static
	return statisticsManager;
}

StatisticsManager::StatisticsManager(IDatabase& database) : m_database(database)
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
	return m_database.getHighScores();  // return the high scores
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username)
{
	std::vector<std::string> statistics;    // insert the user statistics to the statistics vector
	statistics.push_back(std::to_string(m_database.getNumOfCorrectAnswers(username)));
	statistics.push_back(std::to_string(m_database.getNumOfTotalAnswers(username)));
	statistics.push_back(std::to_string(m_database.getNumOfPlayerGames(username)));
	statistics.push_back(std::to_string(m_database.getPlayerAverageAnswerTime(username)));
	statistics.push_back(std::to_string(m_database.getPlayerScore(username)));
	return statistics;
}