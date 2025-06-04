#pragma once
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class Communicator
{
public:
	/// <summary>
	/// delete copy C'TOR
	/// </summary>
	/// <param name="Communicator"> - Communicator to copy</param>
	Communicator(const Communicator& communicator) = delete;
	/// <summary>
	/// static method to ensure that there is only one instance of the Communicator object
	/// </summary>
	/// <returns>the instance of the Communicator object</returns>
	static Communicator& getInstance(RequestHandlerFactory& handlerFactory);

	/// <summary>
	/// method starts handling incoming requests
	/// </summary>
	void startHandleRequests();
private:
	std::map<SOCKET, IRequestHandler*> m_clients;	// clients map of the client's socket and the according request handler
	SOCKET m_serverSocket;
	RequestHandlerFactory& m_handlerFactory;

	/// <summary>
	/// default C'TOR - initiate empty fields
	/// </summary>
	Communicator() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="handlerFactory"> - the request handler factory</param>
	Communicator(RequestHandlerFactory& handlerFactory);

	/// <summary>
	/// method binds socket to its port and starts listening on it
	/// </summary>
	void bindAndListen();
	/// <summary>
	/// method handles new clients logging into the server
	/// </summary>
	/// <param name="clientSocket"> - SOCKET of the logging client's socket</param>
	void handleNewClient(const SOCKET clientSocket);
};
