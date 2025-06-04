#include "LoggedUser.h"

LoggedUser::LoggedUser(const std::string& username) : m_username(username)	// set username
{
}

std::string LoggedUser::getUsername() const
{
	return this->m_username;
}

bool operator<(const LoggedUser& firstUser, const LoggedUser& secondUser)
{
	return firstUser.getUsername() < secondUser.getUsername();  // compare the users by the username (capitalization) for the map sorting
}