#include <iostream>
#include <thread>
#include "Server.h"
#include "WSAInitializer.h"
#include "SqliteDatabase.h"

Server::Server() : m_communicator(Communicator::getInstance(m_handlerFactory)), m_handlerFactory(RequestHandlerFactory::getInstance(m_database)), m_database(SqliteDatabase::getInstance())	// initiate fields
{
	m_database.open();  // open the database
}

Server::~Server()
{
	m_database.close();    // close the database
}

Server& Server::getInstance()
{
	static Server instance;	 // create Server instance which will be the only instance becuase it is static
	return instance;
}

void Server::run()
{
	// initiate WSA
	WSAInitializer wsaInit;
	std::string userInput;
	std::thread t_connector(&Communicator::startHandleRequests, &m_communicator);	// create communicator handle-requests thread
	t_connector.detach();	// do not wait for communicator thread to finish running

	while (userInput != EXIT)
	{
		std::cin >> userInput;	// get user input until he chooses to exit the server
	}
}