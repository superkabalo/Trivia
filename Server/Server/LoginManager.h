#pragma once
#include <string>
#include "IDatabase.h"
#include <vector>
#include "LoggedUser.h"
class LoginManager
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="LoginManager"> - LoginManager to copy</param>
	LoginManager(const LoginManager& loginManager) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the LoginManager object
	/// </summary>
	/// <param name="database"> - the database</param>
	/// <returns>the instance of the LoginManager object</returns>
	static LoginManager& getInstance(IDatabase& database);

	/// <summary>
	/// method tries to login user
	/// </summary>
	/// <param name="username"> - the username</param>
	/// <param name="password"> - the user password</param>
	/// <returns>was the login successful or not</returns>
	bool login(const std::string& username, const std::string& password);
	/// <summary>
	/// method logs out user
	/// </summary>
	/// <param name="username"> - the username</param>
	void logout(const std::string& username);
	/// <summary>
	/// method tries to signup user
	/// </summary>
	/// <param name="username"> - the username</param>
	/// <param name="password"> - the password</param>
	/// <param name="email"> - the user email</param>
	/// <param name="address"> - the user address</param>
	/// <param name="phoneNumber"> - the user phone number</param>
	/// <param name="birthDate"> - the user birth date</param>
	/// <returns>the signup was successful or not</returns>
	bool signup(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate);
private:
	IDatabase& m_database;
	std::vector<LoggedUser> m_loggedUsers;

	/// <summary>
	/// Default C'TOR - initiate fields
	/// </summary>
	LoginManager() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="database"> - the database</param>
	LoginManager(IDatabase& database);

	/// <summary>
	/// method checks if signup fields input is valid using regex
	/// </summary>
	/// <param name="password"> - the password</param>
	/// <param name="email"> - the email</param>
	/// <param name="address"> - the address</param>
	/// <param name="phoneNumber"> - the phone number</param>
	/// <param name="birthDate"> - the birth date</param>
	/// <returns>is the input is valid or not</returns>
	bool isSignupInputValid(const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate);
};