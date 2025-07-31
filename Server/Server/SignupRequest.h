#pragma once
#include <string>
struct SignupRequest
{
	std::string username;	// user details
	std::string password;
	std::string email;
	std::string address;
	std::string phoneNumber;
	std::string birthDate;
} typedef SignupRequest;