#pragma once
#include <ctime>
#include "Constants.h"

struct RequestInfo
{
	RequestId id;
	std::time_t receivalTime;	// request receival time
	Buffer buffer;	// request buffer
} typedef RequestInfo;