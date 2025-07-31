#pragma once
#include "RoomData.h"
#include <vector>

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;	// rooms to show
};