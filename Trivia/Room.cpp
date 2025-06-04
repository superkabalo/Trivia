#include "Room.h"
#include "Constants.h"

Room::Room(const LoggedUser& user, const RoomData& roomData) : m_metadata(roomData)	 // set room data
{
	m_users.push_back(user);  // add user to the room
}

void Room::addUser(const LoggedUser& user)
{
	m_users.push_back(user);	// add user to the users list
}

void Room::removeUser(const LoggedUser& user)
{
	for (auto i = m_users.begin(); i != m_users.end(); ++i)
	{
		if (i->getUsername() == user.getUsername())	 // search for user to remove in the users list
		{
			m_users.erase(i);	// remove the user
			break;
		}
	}
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> usernameList;
	for (auto i = m_users.begin(); i != m_users.end(); ++i)
	{
		usernameList.push_back(i->getUsername());	// add all usernames to the usernames list
	}
	return usernameList;
}

RoomData Room::getRoomData() const
{
	return m_metadata;
}

void Room::startGame()
{
	m_metadata.isActive = ACTIVE;	 // set room as active
}