namespace User
{
    public class Constants
    {
        // general constants
        public const int ANSWER_IS_CORRECT = 10;
        public const string ERROR_MSG = "ERROR";
        public const int DATA_BEGIN = 5;
        public const int DATA_LEN_BEGIN = 1;
        public const int BYTE_SIZE = 8;
        public const byte MAX_BYTE_VALUE = 0xFF;
        public const int BUFFER_SIZE = 1024;
        public const int EMPTY = 0;
        public const int INC = 1;
        public const int FALSE = 0;
        public const string EXIT = "EXIT";
        public const int EQUAL = 0;
        public const int FRONT = 0;
        public const int VISIBLE = 1;
        public const double HALF_VISIBLE = 0.5;
        // time related
        public const int FIVE_SECONDS_MS = 5000;  // seconds in ms
        public const int THREE_SECONDS_MS = 3000;
        public const int TEN_SECONDS_MS = 10000;
        public const int ONE_SECOND_MS = 1000;
        public const int FOURTH_SECOND_MS = 250;

        // answer/question related
        public const int FIRST_QUESTION_NUM = 1;
        public const int NO_ANSWER = 100;
        public const int NUM_OF_ANSWERS = 4;
        public const int FIRST_ANSWER_INDEX = 0;
        public const int SECOND_ANSWER_INDEX = 1;
        public const int THIRD_ANSWER_INDEX = 2;
        public const int FOURTH_ANSWER_INDEX = 3;

        // communication related
        public const int PORT = 9584;
        public const string SERVER_IP = "127.0.0.1";

        // Status codes
        public enum Status
        {
            SUCCESS_STATUS = 1,
            ROOM_OPEN_STATUS = 50, // room open status
            ROOM_CLOSED_STATUS = 52,    // room closed status
            ANSWER_CORRECT_STATUS = 54,  // answers status
            ANSWER_WRONG_STATUS = 56,
            WAIT_FOR_ALL_PLAYERS_STATUS = 58,  // wait for all players to finish the game
            ERROR_STATUS = 99
        }

        public enum ResponseId
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
            SUBMIT_ANSWER_RES = 43
        }

        // Request codes
        public enum RequestId
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
            SUBMIT_ANSWER_REQ = 42
        }
    }
}