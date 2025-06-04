#include <exception>
#include <thread>
#include <iostream>
#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "Communicator.h"
#include "Constants.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include <ctime>
#include <mutex>
// using static const instead of macros
static const unsigned short PORT = 9584;
static const unsigned int IFACE = 0;

std::mutex clientMapMtx;

Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_clients(), m_serverSocket(), m_handlerFactory(handlerFactory)  // initiate fields
{
}

Communicator& Communicator::getInstance(RequestHandlerFactory& handlerFactory)
{
	static Communicator instance(handlerFactory);	// create communicator instance which will be the only instance becuase it is static
	return instance;
}

void Communicator::startHandleRequests()
{
	// step out to the global namespace for the resolution of the function socket
	m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	bindAndListen();

	while (true)
	{
		// accept client
		SOCKET clientSocket = accept(m_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		{
			std::lock_guard<std::mutex> lock(clientMapMtx);	// lock client map access mutex
			m_clients[clientSocket] = m_handlerFactory.createLoginRequestHandler();	// create login request handler for client
		}

		// create new thread for client	and detach it
		std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
		clientThread.detach();
	}

	try
	{
		// close the server socket
		::closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	// bind socket
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	// listen on the port
	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void Communicator::handleNewClient(const SOCKET clientSocket)
{
	try
	{
		RequestResult result;	 // initiate empty result
		do
		{
			RequestInfo request;	// initiate empty request
			const char* ansData = NULL;
			char* msgData = new char[BUFFER_SIZE];	// allocate memory for the request buffer
			if (recv(clientSocket, msgData, BUFFER_SIZE, 0) == INVALID_SOCKET)
			{
				throw std::exception("Error while reading from client socket");
			}

			request.receivalTime = time(EMPTY);	 // set current time as message receival time
			for (int i = 0; i < BUFFER_SIZE; i++)	// copy BUFFER into request
			{
				request.buffer.push_back(msgData[i]);
			}
			request.id = RequestId(request.buffer.front());	// read id from the front of the buffer

			if (!m_clients[clientSocket]->isRequestRelevant(request))	// check if request is relevant
			{
				const ErrorResponse error = { ERROR_MSG };
				request.buffer = JsonResponsePacketSerializer::serializeResponse(error);	// serialize error response
				ansData = (const char*)(request.buffer.data());	 // convert buffer to const char*
			}
			else
			{
				{
					std::lock_guard<std::mutex> lock(clientMapMtx);	// lock client map access mutex
					result = m_clients[clientSocket]->handleRequest(request);	// handle request
				}
				ansData = (const char*)(result.response.data());	// convert buffer to const char*
			}
			send(clientSocket, ansData, BUFFER_SIZE, 0);	// send answer
			delete[] msgData;  // free allocated memory

			{
				std::lock_guard<std::mutex> lock(clientMapMtx);	// lock client map access mutex
				m_clients[clientSocket] = result.newHandler;	// set handler as new handler
			}
		} while (result.newHandler != nullptr);	// run until there is no next handler

		throw std::exception(SERVER_DISCONNECT_CLIENT_EXCEPTION);	// throw client disconnect exception
	}
	catch (const std::exception& e)
	{
		{
			std::lock_guard<std::mutex> lock(clientMapMtx);	// lock client map access mutex
			m_clients.erase(clientSocket);	// remove client handler from client socket
		}
		closesocket(clientSocket);		// close client socket
		if (std::string(e.what()).find(CLIENT_DISCONNECT_EXCEPTION) != std::string::npos ||
			std::string(e.what()).find(SERVER_DISCONNECT_CLIENT_EXCEPTION) != std::string::npos)	// check if the exception is because the client disconnected or because the communication is over
		{
			std::cout << e.what() << std::endl;
		}
	}
}