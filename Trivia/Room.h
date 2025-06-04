#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include <vector>

class Room
{
public:
	/// <summary>
	/// default C'TOR - initiate empty fields
	/// </summary>
	Room() = default;
	/// <summary>
	/// C'TOR - initiate room with given room data and user
	/// </summary>
	/// <param name="roomData"> - the room data</param>
	/// <param name="user"> - the user creating the room</param>
	Room(const LoggedUser& user, const RoomData& roomData);
	/// <summary>
	/// method adds user to the room
	/// </summary>
	/// <param name="user"> - the user</param>
	void addUser(const LoggedUser& user);
	/// <summary>
	/// method removes user from the room
	/// </summary>
	/// <param name="user"> - the user</param>
	void removeUser(const LoggedUser& user);
	/// <summary>
	/// method gets list of all users in the room
	/// </summary>
	/// <returns>all the users in the room</returns>
	std::vector<std::string> getAllUsers() const;
	/// <summary>
	/// method gets room data
	/// </summary>
	/// <returns>the room data</returns>
	RoomData getRoomData() const;
	/// <summary>
	/// method starts game (sets room as active)
	/// </summary>
	void startGame();
private:
	RoomData m_metadata;	// room data
	std::vector<LoggedUser> m_users;	// users in the room
};