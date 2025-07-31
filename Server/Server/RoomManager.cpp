#include "RoomManager.h"
#
RoomManager& RoomManager::getInstance()
{
	static RoomManager instance;	// create RoomManager instance which will be the only instance becuase it is static
	return instance;
}

void RoomManager::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	m_rooms[roomData.id] = Room(user, roomData);	// create new room and insert it to the rooms map
}

void RoomManager::deleteRoom(const unsigned int id)
{
	m_rooms.erase(id);	// remove room from rooms map
}

unsigned int RoomManager::getRoomState(const unsigned int id) const
{
	return m_rooms.find(id)->second.getRoomData().isActive;	// get room and then get its state
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> roomsData;
	for (auto i = m_rooms.begin(); i != m_rooms.end(); ++i)
	{
		roomsData.push_back(i->second.getRoomData());	// insert the data of all the rooms to roomsData vector
	}
	return roomsData;
}

Room& RoomManager::getRoom(const unsigned int id)
{
	return m_rooms.find(id)->second;  // return room with the given id
}

void RoomManager::startGame(const unsigned int id)
{
	m_rooms.find(id)->second.startGame();	// start the game in the room
}