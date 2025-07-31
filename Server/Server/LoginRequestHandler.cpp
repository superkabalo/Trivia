#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginRequest.h"
#include "SignupRequest.h"
#include "LoggedUser.h"
#include <iostream>

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory), m_loginManager(m_handlerFactory.getLoginManager())	// initiate fields
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	if (request.id != LOGIN_REQ && request.id != SIGNUP_REQ)	// check if request is signup or login request
	{
		return false;
	}
	return true;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request)
{
	if (request.id == LOGIN_REQ)	// login request
	{
		return login(request);
	}
	else if (request.id == SIGNUP_REQ)	// signup request
	{
		return signup(request);
	}
}

RequestResult LoginRequestHandler::login(const RequestInfo& request)
{
	RequestResult result;	// request result
	LoginRequest loginRequest;	// login request
	loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);	// deserialize and save the login request
	std::cout << "New Login Request -" << std::endl
		<< "Username: " << loginRequest.username << std::endl
		<< "Password: " << loginRequest.password << std::endl;

	LoginResponse loginResponse;		// login response
	if (m_loginManager.login(loginRequest.username, loginRequest.password))
	{
		loginResponse.status = SUCCESS_STATUS;
		LoggedUser loggedUser(loginRequest.username);	// set the new handler as a menu request handler for the user
		result.newHandler = m_handlerFactory.createMenuRequestHandler(loggedUser);
	}
	else
	{
		loginResponse.status = ERROR_STATUS;
		result.newHandler = this;	// keep new handler as login request handler
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);	 // serialize the response
	return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& request)
{
	RequestResult result;
	SignupRequest signupRequest;
	signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);	// deserialize and save the signup request
	std::cout << "New signup request -" << std::endl
		<< "Username: " << signupRequest.username << std::endl
		<< "Password: " << signupRequest.password << std::endl
		<< "Email: " << signupRequest.email << std::endl
		<< "Address: " << signupRequest.address << std::endl
		<< "Phone number: " << signupRequest.phoneNumber << std::endl
		<< "Birth date: " << signupRequest.birthDate << std::endl;

	SignupResponse signupResponse;	// signup response
	if (m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email, signupRequest.address, signupRequest.phoneNumber, signupRequest.birthDate))
	{
		signupResponse.status = SUCCESS_STATUS;
		LoggedUser loggedUser(signupRequest.username);	// set the new handler as a menu request handler for the user
		result.newHandler = m_handlerFactory.createMenuRequestHandler(loggedUser);
	}
	else
	{
		signupResponse.status = ERROR_STATUS;
		result.newHandler = this;	// keep new handler as login request handler
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);	// serialize the response
	return result;
}