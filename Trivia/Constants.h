#pragma once
#include <vector>

typedef std::vector<unsigned char> Buffer;	// define Buffer type

enum RequestId // request codes
{
	LOGIN_REQ = 10,
	SIGNUP_REQ = 12,
	LOGOUT_REQ = 14,
	GET_ROOMS_REQ = 16,
	GET_PLAYERS_IN_ROOM_REQ = 18,
	PERSONAL_STATS_REQ = 20,
	HIGH_SCORE_REQ = 22,
	JOIN_ROOM_REQ = 24,
	CREATE_ROOM_REQ = 26,
	LEAVE_ROOM_REQ = 28,
	GET_ROOM_STATE_REQ = 30,
	CLOSE_ROOM_REQ = 32,
	START_GAME_REQ = 34,
	LEAVE_GAME_REQ = 36,
	GET_QUESTION_REQ = 38,
	GET_GAME_RESULTS_REQ = 40,
	SUBMIT_ANSWERS_REQ = 42
};
enum ResponseId	// resposnse codes
{
	LOGIN_RES = 11,
	SIGNUP_RES = 13,
	LOGOUT_RES = 15,
	GET_ROOMS_RES = 17,
	GET_PLAYERS_IN_ROOM_RES = 19,
	PERSONAL_STATS_RES = 21,
	HIGH_SCORE_RES = 23,
	JOIN_ROOM_RES = 25,
	CREATE_ROOM_RES = 27,
	ERROR_RES = 99,
	LEAVE_ROOM_RES = 29,
	GET_ROOM_STATE_RES = 31,
	CLOSE_ROOM_RES = 33,
	START_GAME_RES = 35,
	LEAVE_GAME_RES = 37,
	GET_QUESTION_RES = 39,
	GET_GAME_RESULTS_RES = 41,
	SUBMIT_ANSWERS_RES = 43
};
enum Status
{
	SUCCESS_STATUS = 1,
	ROOM_OPEN_STATUS = 50, // room open status
	ROOM_CLOSED_STATUS = 52,	// room closed status
	ANSWER_CORRECT_STATUS = 54,  // answers status
	ANSWER_WRONG_STATUS = 56,
	WAIT_FOR_ALL_PLAYERS_STATUS = 58,  // wait for all players to finish the game
	ERROR_STATUS = 99
};
#define ERROR_MSG "ERROR"
// protocol related
#define DATA_BEGIN 5	// index of data beginning in request
#define DATA_LEN_BEGIN 1	// index of data length beginnning in request
// deserialization/serialization
#define BYTE_SIZE 8	 // byte size in bits
#define MAX_BYTE_VALUE 0xFF	// maximum value of a byte
// general
#define BUFFER_SIZE 1024
#define EMPTY 0
#define INC 1
#define FALSE 0
#define EXIT "EXIT"
#define EQUAL 0
#define FRONT 0
#define ACTIVE 1
#define TWO_ITEM_AVG_DIVIDE 2
// exceptions
#define CLIENT_DISCONNECT_EXCEPTION "Error while reading from client socket"
#define SERVER_DISCONNECT_CLIENT_EXCEPTION "Disconnected client from server because the communication is over"
// database related (mostly)
#define PASSWORD "PASSWORD"
#define PASSWORD_LENGTH 8
#define MIN_PASSWORD_LENGTH 8
#define ANSWER_1_INDEX 1
#define ANSWER_2_INDEX 2
#define ANSWER_3_INDEX 3
#define ANSWER_4_INDEX 4
#define QUESTION_INDEX 0
#define NUM_OF_QUESTIONS 10
#define START_OF_RANGE 1
// room related
typedef int roomID;
// questions related
#define NUM_QUESTIONS 4
#define CORRECT_ANSWER_INDEX 3