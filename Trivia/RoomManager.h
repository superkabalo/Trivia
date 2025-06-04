#pragma once
#include "Constants.h"
#include "Room.h"
#include <map>

class RoomManager
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="RoomManager"> - RoomManager to copy</param>
	RoomManager(const RoomManager& roomManager) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the RoomManager object
	/// </summary>
	/// <returns>the instance of the RoomManager object</returns>
	static RoomManager& getInstance();

	/// <summary>
	/// method creates room
	/// </summary>
	/// <param name="user"> - the user</param>
	/// <param name="roomData"> - the room data</param>
	void createRoom(const LoggedUser& user, const RoomData& roomData);
	/// <summary>
	/// method deletes room
	/// </summary>
	/// <param name="id"> - the room id</param>
	void deleteRoom(const unsigned int id);
	/// <summary>
	/// method gets the state of a room
	/// </summary>
	/// <param name="id"> - the room id</param>
	/// <returns>the room state</returns>
	unsigned int getRoomState(const unsigned int id) const;
	/// <summary>
	/// method gets a list of all the rooms
	/// </summary>
	/// <returns>all the rooms</returns>
	std::vector<RoomData> getRooms() const;
	/// <summary>
	/// method gets a specific room
	/// </summary>
	/// <param name="id"> - the room id</param>
	/// <returns>the room</returns>
	Room& getRoom(const unsigned int id);
	/// <summary>
	/// method starts game (activates room)
	/// </summary>
	void startGame(const unsigned int id);
private:
	std::map<roomID, Room> m_rooms;	 // room map

	/// <summary>
	/// Default C'TOR - initiate fields
	/// </summary>
	RoomManager() = default;
};