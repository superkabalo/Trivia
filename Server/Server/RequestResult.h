#pragma once
#include "Constants.h"
#include "IRequestHandler.h"

class IRequestHandler;
struct RequestResult
{
public:
	Buffer response;	// response Buffer
	IRequestHandler* newHandler;	// next handler to be used
};