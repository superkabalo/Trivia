#include "LoginManager.h"
#include "Constants.h"
#include <regex>

LoginManager::LoginManager(IDatabase& database) : m_database(database), m_loggedUsers() // initiate fields
{
}

LoginManager& LoginManager::getInstance(IDatabase& database)
{
	static LoginManager loginManager(database);   // create LoginManager instance which will be the only instance becuase it is static
	return loginManager;
}

bool LoginManager::login(const std::string& username, const std::string& password)
{
	if (this->m_database.doesUserExist(username) && this->m_database.doesPasswordMatch(username, password))    // check if the user exists and the password is correct
	{
		this->m_loggedUsers.push_back(LoggedUser(username));    // save the logged user
		return true;
	}
	return false;
}

void LoginManager::logout(const std::string& username)
{
	for (auto i = this->m_loggedUsers.begin(); i != this->m_loggedUsers.end(); i++)     // find user to remove
	{
		if (i->getUsername().compare(username) == EQUAL)
		{
			this->m_loggedUsers.erase(i);   // remove the user
		}
	}
}

bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate)
{
	if (!isSignupInputValid(password, email, address, phoneNumber, birthDate))  // check input (regex)
	{
		return false;
	}
	else if (this->m_database.doesUserExist(username))  // check if user exists
	{
		return false;
	}
	this->m_database.addNewUser(username, password, email, address, phoneNumber, birthDate);    // add the new user
	return true;
}

bool LoginManager::isSignupInputValid(const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate)
{
	if (!(std::regex_match(password, std::regex("^.{8,}$")) &&  // check that password length is at least 8 chars
		std::regex_search(password, std::regex("[A-Z]")) &&  // at least one capital letter
		std::regex_search(password, std::regex("[a-z]")) &&  // at least one regular letter
		std::regex_search(password, std::regex("[1-9]")) &&  // at least one digit
		std::regex_search(password, std::regex("[!@#$%^&*]"))))  // at least one special character
	{
		return false;
	}
	else if (!std::regex_match(email, std::regex("^[a-zA-Z0-9]+@[a-zA-Z0-9]+[.][a-zA-Z0-9]+$")))   // check that the email address is built in this format: {text}@{text}.{text}
	{
		return false;
	}
	else if (!std::regex_match(address, std::regex("^[(][A-Z]+[,][ ][0-9]+[,][ ][a-zA-Z]+[)]$")))    // check that the address is built according to the format: ({letters}, {numbers}, {letters})
	{
		return false;
	}
	else if (!std::regex_match(phoneNumber, std::regex("^[0][0-9]{1,2}[-][0-9]+$")))    // check that the phone number is built in this format: 0{1-2 numbers}-{numbers}
	{
		return false;
	}
	else if (!(std::regex_match(birthDate, std::regex("^[0-9]{2}[/][0-9]{2}[/][0-9]{4}$")) ||  // check that the birth date is built in this format: {2 numbers}/{2 numbers}/{4 number}
		std::regex_match(birthDate, std::regex("^[0-9]{2}[.][0-9]{2}[.][0-9]{4}$"))))  // or this format: {2 numbers}.{2 numbers}.{4 numbers}
	{
		return false;
	}
	return true;
}