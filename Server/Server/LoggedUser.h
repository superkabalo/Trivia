#pragma once
#include <string>
class LoggedUser
{
public:
	/// <summary>
	/// Defualt C'TOR - initiate empty fields
	/// </summary>
	LoggedUser() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="username"> - the username</param>
	LoggedUser(const std::string& username);
	/// <summary>
	/// method gets username
	/// </summary>
	/// <returns>the username</returns>
	std::string getUsername() const;
	/// <summary>
	/// method implementes the opeartor <
	/// </summary>
	/// <param name="firstUser"> - the first user in the comparison</param>
	/// <param name="secondUser"> - the second user in the comparison</param>
	/// <returns>wether the firstUser < secondUser</returns>
	friend bool operator<(const LoggedUser& firstUser, const LoggedUser& secondUser);

private:
	std::string m_username;
};