#include <iostream>
#include "Server.h"

int main()
{
	Server& server = Server::getInstance();	 // get server instance

	try
	{
		server.run();	// run server
	}
	catch (const std::exception& e)	// handle exceptions
	{
		std::cout << e.what();
	}

	return 0;
}