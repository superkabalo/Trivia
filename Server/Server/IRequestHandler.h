#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"

class IRequestHandler
{
public:
	/// <summary>
	/// method checks if request is relevant
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>request is relevant or not</returns>
	virtual bool isRequestRelevant(const RequestInfo& request) const = 0;
	/// <summary>
	/// method handles request
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	virtual RequestResult handleRequest(const RequestInfo& request) = 0;
};