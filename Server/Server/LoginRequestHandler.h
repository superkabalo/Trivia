#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	/// <summary>
	/// Default C'TOR - initiate empty fields
	/// </summary>
	LoginRequestHandler() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="handleFactory"> - the request handler factory</param>
	LoginRequestHandler(RequestHandlerFactory& handlerFactory);
	/// <summary>
	/// method checks if request is relevant
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>request is relevant or not</returns>
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	/// <summary>
	/// method handles request
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	virtual RequestResult handleRequest(const RequestInfo& request) override;
private:
	RequestHandlerFactory& m_handlerFactory;	// the handler factory
	LoginManager& m_loginManager;

	/// <summary>
	/// method logs in a user
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult login(const RequestInfo& request);
	/// <summary>
	/// method signs up a user
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult signup(const RequestInfo& request);
};