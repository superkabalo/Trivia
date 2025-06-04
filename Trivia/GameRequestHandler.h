#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "GameManager.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	/// <summary>
	/// Default C'TOR - initiate empty fields
	/// </summary>
	GameRequestHandler() = default;
	/// <summary>
	/// C'TOR - initiate fields
	/// </summary>
	/// <param name="handleFactory"> - the request handler factory</param>
	/// <param name="user"> - the logged user</param>
	/// /// <param name="room"> - the room of the game</param>
	GameRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room);

	/// <summary>
	/// method checks if request is relevant
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>is request is relevant</returns>
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	/// <summary>
	/// method handles request
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	virtual RequestResult handleRequest(const RequestInfo& request) override;

private:
	RequestHandlerFactory& m_handlerFactory;	// the handler factory
	LoggedUser m_user;
	GameManager& m_gameManager;
	Game& m_game;

	/// <summary>
	/// method gets a question
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getQuestion(const RequestInfo& request);
	/// <summary>
	/// method submits answer
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult submitAnswer(const RequestInfo& request);
	/// <summary>
	/// method gets the game results
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult getGameResults(const RequestInfo& request);
	/// <summary>
	/// method leaves the game
	/// </summary>
	/// <param name="request"> - the request</param>
	/// <returns>the result of the request</returns>
	RequestResult leaveGame(const RequestInfo& request) const;
};