#pragma once
#include "IDatabase.h"
#include <vector>
#include <iostream>
class StatisticsManager
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="StatisticsManager"> - StatisticsManager to copy</param>
	StatisticsManager(const StatisticsManager& statisticsManager) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the StatisticsManager object
	/// </summary>
	/// <param name="database"> - the database</param>
	/// <returns>the instance of the StatisticsManager object</returns>
	static StatisticsManager& getInstance(IDatabase& database);

	/// <summary>
	/// method gets the 3 highest scoring players
	/// </summary>
	/// <returns>the 3 highest scoring players' names</returns>
	std::vector<std::string> getHighScore();
	/// <summary>
	/// method gets the user statistics
	/// </summary>
	/// <param name="username"> - the username</param>
	/// <returns>the user statistics</returns>
	std::vector<std::string> getUserStatistics(const std::string& username);
private:
	IDatabase& m_database;

	/// <summary>
	/// Default C'TOR - initiate empty fields
	/// </summary>
	StatisticsManager() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="database"> - the database</param>
	StatisticsManager(IDatabase& database);
};