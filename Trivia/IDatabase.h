#pragma once
#include <string>
#include "LoggedUser.h"
#include "Question.h"
#include "GameData.h"
#include<vector>
#include <list>
class IDatabase
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="IDatabase"> - IDatabase to copy</param>
	IDatabase(const IDatabase& database) = delete;

	/// <summary>
	/// method opens the database
	/// </summary>
	/// <returns>was the database opening was successful or not</returns>
	virtual bool open() = 0;
	/// <summary>
	/// method closes the database
	/// </summary>
	/// <returns>was the database closing was successful or not</returns>
	virtual bool close() = 0;
	/// <summary>
	/// method checks if user exists in the database
	/// </summary>
	/// <param name="username"> - the username</param>
	/// <returns>does the user exist or not</returns>
	virtual int doesUserExist(const std::string& username) = 0;
	/// <summary>
	/// method checks if the given passwrod matches the user password in the database
	/// </summary>
	/// <param name="username"> - the username</param>
	/// <param name="password"> - the password to verify</param>
	/// <returns>do the passwords match or not</returns>
	virtual int doesPasswordMatch(const std::string& username, const std::string& password) = 0;
	/// <summary>
	/// method adds new user to the database
	/// </summary>
	/// <param name="username"> - the username</param>
	/// <param name="password"> - the password</param>
	/// <param name="email"> - the email</param>
	/// <param name="address"> - the address</param>
	/// <param name="phoneNumber"> - the phone number</param>
	/// <param name="birthDate"> - of the birth date</param>
	/// <returns>was the user adding was successful or not</returns>
	virtual int addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate) = 0;
	/// <summary>
	/// method gets questions from the database
	/// </summary>
	/// <param name="numOfQuestions"> - how many questions to get</param>
	/// <returns>the requested questions</returns>
	virtual std::list<Question> getQuestions(const int numOfQuestions) = 0;
	/// <summary>
	/// method gets the average answer time of a player
	/// </summary>
	/// <param name="username"> - the player's username</param>
	/// <returns>the average answer time of the player</returns>
	virtual int getPlayerAverageAnswerTime(const std::string& username) = 0;
	/// <summary>
	/// method gets the number of correct answers which the player has
	/// </summary>
	/// <param name="username"> - the player's username</param>
	/// <returns>the number of correct answers which the user has</returns>
	virtual int getNumOfCorrectAnswers(const std::string& username) = 0;
	/// <summary>
	/// method gets the number of total answers which the player has
	/// </summary>
	/// <param name="username"> - the player's username</param>
	/// <returns>the number of total answers which the player has</returns>
	virtual int getNumOfTotalAnswers(const std::string& username) = 0;
	/// <summary>
	/// method gets the number of games which the player played
	/// </summary>
	/// <param name="username"> - the player's username</param>
	/// <returns>the number of games which the player played</returns>
	virtual int getNumOfPlayerGames(const std::string& username) = 0;
	/// <summary>
	/// method gets the player's score
	/// </summary>
	/// <param name="username"> - the player's username</param>
	/// <returns>the player score</returns>
	virtual int getPlayerScore(const std::string& username) = 0;
	/// <summary>
	/// method gets the 3 highest scoring players
	/// </summary>
	/// <returns>the 3 highest scoring players'usernames</returns>
	virtual std::vector<std::string> getHighScores() = 0;
	/// <summary>
	/// method submits game statistics into the database
	/// </summary>
	/// <param name="gameData"> - the game's data</param>
	/// <returns>was statistics submitting successful or not</returns>
	virtual int submitGameStatistics(const GameData& gameData, const LoggedUser& user) = 0;
	/// <summary>
	/// method inserts question into the database
	/// </summary>
	/// <param name="question"> - the question</param>
	/// <param name="firstAns"> - the first answer</param>
	/// <param name="secondAns"> - the second answer</param>
	/// <param name="thirdAns"> - the third answer</param>
	/// <param name="correctAns"> - the correct answer</param>
	virtual void insertQuestion(const std::string& question, const std::string& firstAns, const std::string& secondAns, const std::string& thirdAns, const std::string& correctAns) = 0;
protected:
	/// <summary>
	/// default C'TOR - initiate empty fields
	/// </summary>
	IDatabase() = default;
};