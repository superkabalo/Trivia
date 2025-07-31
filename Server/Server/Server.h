#pragma once
#pragma comment (lib, "ws2_32.lib")
#include "Communicator.h"
#include "IDatabase.h"

class Server
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="server"> - Server to copy</param>
	Server(const Server& server) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the Server object
	/// </summary>
	/// <returns>the instance of the Server object</returns>
	static Server& getInstance();

	/// <summary>
	/// method initiates WSA as needed and starts handling requests
	/// </summary>
	void run();
private:
	IDatabase& m_database;
	RequestHandlerFactory& m_handlerFactory;  // the handler factory
	Communicator& m_communicator;

	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	Server();
	/// <summary>
	/// D'TOR - free allocated memory
	/// </summary>
	~Server();
};