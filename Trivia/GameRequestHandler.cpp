#include "GameRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "GetQuestionResponse.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, const LoggedUser& user, const Room& room) : m_handlerFactory(handlerFactory), m_user(user), m_game(m_gameManager.createGame(room)), m_gameManager(m_handlerFactory.getGameManager())	// initiate fields
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	if (request.id != GET_QUESTION_REQ && request.id != LEAVE_GAME_REQ && request.id != SUBMIT_ANSWERS_REQ && request.id != GET_GAME_RESULTS_REQ && request.id != LEAVE_GAME_REQ)	// check if request is of the relevant requests
	{
		return false;
	}
	return true;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& request)
{
	if (request.id == LEAVE_GAME_REQ)	// leave game request
	{
		return leaveGame(request);
	}
	else if (request.id == SUBMIT_ANSWERS_REQ)	// submit answer request
	{
		return submitAnswer(request);
	}
	else if (request.id == GET_GAME_RESULTS_REQ)	// get game results request
	{
		return getGameResults(request);
	}
	else if (request.id == GET_QUESTION_REQ)	// get question request
	{
		return getQuestion(request);
	}
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& request)
{
	RequestResult result;	// request result
	Question question = m_game.getQuestionForUser(m_user);  // get the question

	std::map<unsigned int, std::string> possibleAnswers;
	for (int i = 0; i < NUM_QUESTIONS; i++)  // insert the possible answers to their according id in the map
	{
		possibleAnswers[i] = question.getPossibleAnswers()[i];
	}
	// the answers will be randomized on the client side
	GetQuestionResponse getQuestionRes = { SUCCESS_STATUS, question.getQuestion(), possibleAnswers };  // construct the response
	result.response = JsonResponsePacketSerializer::serializeResponse(getQuestionRes);	// serialize the response
	result.newHandler = this;  // keep the handler as a GameRequestHandler
	return result;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& request)
{
	RequestResult result;	// request result
	SubmitAnswerRequest submitAnswerReq = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);  // deserialize the request
	std::pair<bool, int> submitAnswerPair = m_game.submitAnswer(submitAnswerReq.answerId, submitAnswerReq.answerTime, m_user);
	SubmitAnswerResponse submitAnswerRes;  // construct the response

	if (submitAnswerPair.first)  // check if the user was correct
	{
		submitAnswerRes.status = ANSWER_CORRECT_STATUS;
	}
	else
	{
		submitAnswerRes.status = ANSWER_WRONG_STATUS;
	}
	submitAnswerRes.correctAnswerId = submitAnswerPair.second;  // set the correct answer id
	result.response = JsonResponsePacketSerializer::serializeResponse(submitAnswerRes);	// serialize the response
	result.newHandler = this;  // keep the handler as a GameRequestHandler
	return result;
}

RequestResult GameRequestHandler::getGameResults(const RequestInfo& request)
{
	RequestResult result;	// request result
	m_game.userFinished(m_user);
	GetGameResultsResponse getGameResultsRes;  // construct the response
	if (!m_game.allUsersFinishedGame())
	{
		getGameResultsRes.status = WAIT_FOR_ALL_PLAYERS_STATUS;
		getGameResultsRes.results = std::vector<PlayerResults>();
		result.response = JsonResponsePacketSerializer::serializeResponse(getGameResultsRes);
		result.newHandler = this;
		return result;
	}
	getGameResultsRes.status = SUCCESS_STATUS;
	std::vector<PlayerResults> playerResultsVec;
	std::map<LoggedUser, GameData> usersGameData = m_game.getPlayers();  // get the game players
	for (auto playerIt = usersGameData.begin(); playerIt != usersGameData.end(); ++playerIt)
	{
		// create the current player's PlayerResults
		PlayerResults playerResults = { playerIt->first.getUsername(), playerIt->second.correctAnswerCount, playerIt->second.wrongAnswerCount, playerIt->second.averageAnswerTime };
		playerResultsVec.push_back(playerResults);  // insert the player's results to the players vector
	}
	getGameResultsRes.results = playerResultsVec;
	result.response = JsonResponsePacketSerializer::serializeResponse(getGameResultsRes);	// serialize the response
	result.newHandler = this;  // keep the handler as a GameRequestHandler
	return result;
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& request) const
{
	RequestResult result;	// request result
	LeaveGameResponse leaveGameRes = { SUCCESS_STATUS };  // construct the response
	m_game.removePlayer(m_user);  // remove the player from the game
	if (m_game.getPlayers().size() == EMPTY)  // check if the game is empty
	{
		m_gameManager.deleteGame(m_game.getGameId());  // delete the game
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(leaveGameRes);	// serialize the response
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);  // set the new handler as a MenuRequestHandler
	return result;
}