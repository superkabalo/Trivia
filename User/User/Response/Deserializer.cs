using MongoDB.Bson;
using MongoDB.Bson.Serialization;
using Newtonsoft.Json.Linq;
using static User.Constants;

namespace User.Response
{
    using Buffer = List<byte>;

    internal class Deserializer
    {
        /// <summary>
        /// method deserializes login response
        /// </summary>
        /// <param name="request"> - the login response buffer</param>
        /// <returns>the login response</returns>
        public static LoginResponse deserializeLoginResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert buffer data to json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to LoginResponse struct
            LoginResponse loginResponse = jsonObject.ToObject<LoginResponse>();
            return loginResponse;
        }

        /// <summary>
        /// method deserializes error response
        /// </summary>
        /// <param name="request"> - the error response buffer</param>
        /// <returns>the error response</returns>
        public static ErrorResponse deserializeErrorResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to ErrorResponse
            ErrorResponse errorResponse = jsonObject.ToObject<ErrorResponse>();
            return errorResponse;
        }

        /// <summary>
        /// method deserializes signup response
        /// </summary>
        /// <param name="response"> - the signup response buffer</param>
        /// <returns>the signup response</returns>
        public static SignupResponse deserializeSignupResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to SignupResponse
            SignupResponse signupResponse = jsonObject.ToObject<SignupResponse>();
            return signupResponse;
        }

        /// <summary>
        /// method deserializes get players in room response
        /// </summary>
        /// <param name="response"> - the get players in room respons buffer</param>
        /// <returns>the get players in room response</returns>
        public static GetPlayersInRoomResponse deserializeGetPlayersInRoomResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from response buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // save data in json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to GetPlayersInRoomResponse
            GetPlayersInRoomResponse getPlayersInRoomResponse = jsonObject.ToObject<GetPlayersInRoomResponse>();
            return getPlayersInRoomResponse;
        }

        /// <summary>
        /// method deserializes join room response
        /// </summary>
        /// <param name="response"> - the join room response buffer</param>
        /// <returns>the join room response</returns>
        public static JoinRoomResponse deserializeJoinRoomResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // save data in json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to JoinRoomResponse
            JoinRoomResponse joinRoomResponse = jsonObject.ToObject<JoinRoomResponse>();
            return joinRoomResponse;
        }

        /// <summary>
        /// method deserializes create room response
        /// </summary>
        /// <param name="response"> - the create room response buffer</param>
        /// <returns>the create room response</returns>
        public static CreateRoomResponse deserializeCreateRoomResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // save data in json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to CreateRoomResponse
            CreateRoomResponse createRoomResponse = jsonObject.ToObject<CreateRoomResponse>();
            return createRoomResponse;
        }

        /// <summary>
        /// method deserializes get high scores response
        /// </summary>
        /// <param name="response"> - the get high scores response buffer</param>
        /// <returns>the get high sscores response</returns>
        public static GetHighScoreResponse deserializeGetHighScoresResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // save data in json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to GetHighScoreResponse
            GetHighScoreResponse getHighScoreResponse = jsonObject.ToObject<GetHighScoreResponse>();
            return getHighScoreResponse;
        }

        /// <summary>
        /// method deserializes personal stats response
        /// </summary>
        /// <param name="response"> - the personal stats response buffer</param>
        /// <returns>the personal stats response</returns>
        public static GetPersonalStatsResponse deserializeGetPersonalStatsResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // save data in json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to GetPersonalStatsResponse
            GetPersonalStatsResponse getPersonalStatsResponse = jsonObject.ToObject<GetPersonalStatsResponse>();
            return getPersonalStatsResponse;
        }

        /// <summary>
        /// method deserializes logout response
        /// </summary>
        /// <param name="request"> - the logout response buffer</param>
        /// <returns>the logout response</returns>
        public static LogoutResponse deserializeLogoutResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to LogoutResponse
            LogoutResponse logoutResponse = jsonObject.ToObject<LogoutResponse>();
            return logoutResponse;
        }

        /// <summary>
        /// method deserializes get game results response
        /// </summary>
        /// <param name="request"> - the get game results response buffer</param>
        /// <returns>the get game results response</returns>
        public static GetGameResultsResponse deserializeGetGameResultsResponse(Buffer response)
        {
            GetGameResultsResponse getGameResultsRes = new GetGameResultsResponse();  // create new GetGameResultsResponse
            getGameResultsRes.results = new List<PlayerResults>();
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to GetGameResultsResponse - extract json arrays to separate arrays
            getGameResultsRes.status = int.Parse(jsonObject["status"].ToString());
            if (getGameResultsRes.status == (int)Constants.Status.WAIT_FOR_ALL_PLAYERS_STATUS)  // check if the request is full or not all the players have finished the game
            {
                return getGameResultsRes;
            }
            JArray usernames = JArray.Parse(jsonObject["username"].ToString());  // convert the following fields into json arrays
            JArray correctAnswerCount = JArray.Parse(jsonObject["correctAnswerCount"].ToString());
            JArray wrongAnswerCount = JArray.Parse(jsonObject["wrongAnswerCount"].ToString());
            JArray averageAnswerTime = JArray.Parse(jsonObject["averageAnswerTime"].ToString());
            for (int i = 0; i < usernames.Count(); i++)
            {
                // convert the current player results into PlayerResults
                PlayerResults playerResults = new PlayerResults();
                playerResults.username = usernames[i].ToString();
                playerResults.correctAnswerCount = int.Parse(correctAnswerCount[i].ToString());
                playerResults.wrongAnswerCount = int.Parse(wrongAnswerCount[i].ToString());
                playerResults.averageAnswerTime = int.Parse(averageAnswerTime[i].ToString());
                getGameResultsRes.results.Add(playerResults);  // add the current PlayerResults to the response
            }
            return getGameResultsRes;
        }

        /// <summary>
        /// method deserializes submit answer response
        /// </summary>
        /// <param name="request"> - the submit answer response buffer</param>
        /// <returns>the submit answer response</returns>
        public static SubmitAnswerResponse deserializeSubmitAnswerResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to SubmitAnswerResponse
            SubmitAnswerResponse submitAnswerRes = jsonObject.ToObject<SubmitAnswerResponse>();
            return submitAnswerRes;
        }

        /// <summary>
        /// method deserializes leave game response
        /// </summary>
        /// <param name="request"> - the leave game response buffer</param>
        /// <returns>the leave game response</returns>
        public static LeaveGameResponse deserializeLeaveGameResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to LeaveGameResponse
            LeaveGameResponse leaveGameResponse = jsonObject.ToObject<LeaveGameResponse>();
            return leaveGameResponse;
        }

        /// <summary>
        /// method deserializes get rooms response
        /// </summary>
        /// <param name="request"> - the get rooms response buffer</param>
        /// <returns>the get rooms response</returns>
        public static GetRoomsResponse deserializeGetRoomsResponse(Buffer response)
        {
            GetRoomsResponse getRoomsResponse = new GetRoomsResponse();
            getRoomsResponse.rooms = new List<RoomData>();
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            getRoomsResponse.status = (int)jsonObject["status"];  // set the status
            // check if the keys exist and are not null before parsing
            if (jsonObject["id"] == null ||
                jsonObject["isActive"] == null ||
                jsonObject["maxPlayers"] == null ||
                jsonObject["numOfQuestionsInGame"] == null ||
                jsonObject["timePerQuestion"] == null ||
                jsonObject["name"] == null)
            {
                return getRoomsResponse;
            }
            // get the json arrays
            JArray ids = JArray.Parse(jsonObject["id"].ToString());
            JArray isActive = JArray.Parse(jsonObject["isActive"].ToString());
            JArray maxPlayers = JArray.Parse(jsonObject["maxPlayers"].ToString());
            JArray numOfQuestionsInGame = JArray.Parse(jsonObject["numOfQuestionsInGame"].ToString());
            JArray timePerQuestion = JArray.Parse(jsonObject["timePerQuestion"].ToString());
            JArray name = JArray.Parse(jsonObject["name"].ToString());

            // convert the json arrays into rooms
            for (int i = 0; i < ids.Count(); i++)
            {
                RoomData roomData = new RoomData(); // construct current room's RoomData
                roomData.id = int.Parse(ids[i].ToString());
                roomData.name = name[i].ToString();
                roomData.isActive = int.Parse(isActive[i].ToString());
                roomData.maxPlayers = int.Parse(maxPlayers[i].ToString());
                roomData.numOfQuestionsInGame = int.Parse(numOfQuestionsInGame[i].ToString());
                roomData.timePerQuestion = int.Parse(timePerQuestion[i].ToString());
                getRoomsResponse.rooms.Add(roomData);   // add current room to getRoomsResponse rooms list
            }
            return getRoomsResponse;
        }

        /// <summary>
        /// method deserializes start game response
        /// </summary>
        /// <param name="request"> - the start game response buffer</param>
        /// <returns>the start game response</returns>
        public static StartGameResponse deserializeStartGameResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to StartGameResponse
            StartGameResponse startGameResponse = jsonObject.ToObject<StartGameResponse>();
            return startGameResponse;
        }

        /// <summary>
        /// method deserializes close room response
        /// </summary>
        /// <param name="request"> - the close room response buffer</param>
        /// <returns>the close room response</returns>
        public static CloseRoomResponse deserializeCloseRoomResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to CloseRoomResponse
            CloseRoomResponse closeRoomResponse = jsonObject.ToObject<CloseRoomResponse>();
            return closeRoomResponse;
        }

        /// <summary>
        /// method deserializes get room state response
        /// </summary>
        /// <param name="request"> - the get room state response buffer</param>
        /// <returns>the get room state response</returns>
        public static GetRoomStateResponse deserializeGetRoomStateResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to GetRoomStateResponse
            GetRoomStateResponse getRoomStateResponse = jsonObject.ToObject<GetRoomStateResponse>();
            return getRoomStateResponse;
        }

        /// <summary>
        /// method deserializes leave room response
        /// </summary>
        /// <param name="request"> - the leave room response buffer</param>
        /// <returns>the leave room response</returns>
        public static LeaveRoomResponse deserializeLeaveRoomResponse(Buffer response)
        {
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to LeaveRoomResponse
            LeaveRoomResponse leaveRoomResponse = jsonObject.ToObject<LeaveRoomResponse>();
            return leaveRoomResponse;
        }

        /// <summary>
        /// method deserializes get question response
        /// </summary>
        /// <param name="request"> - the get question response buffer</param>
        /// <returns>the get question response</returns>
        public static GetQuestionResponse deserializeGetQuestionResponse(Buffer response)
        {
            GetQuestionResponse getQuestionResponse = new GetQuestionResponse();  // create new GetQuestionResponse
            getQuestionResponse.answers = new Dictionary<int, string>();
            int dataLen = EMPTY;
            for (int i = DATA_LEN_BEGIN; i < DATA_LEN_BEGIN + sizeof(int); i++)  // read data length from buffer
            {
                dataLen = (dataLen << BYTE_SIZE) + response[i];  // move dataLen one byte to the left and add the current byte from the buffer
            }
            Buffer data = new Buffer();
            // read data from request buffer into the data buffer
            for (int i = DATA_BEGIN; i < DATA_BEGIN + dataLen; i++)
            {
                data.Add(response[i]);
            }
            // convert data into json
            BsonDocument deserializedDocument = BsonSerializer.Deserialize<BsonDocument>(data.ToArray());
            string json = deserializedDocument.ToJson();
            JObject jsonObject = JObject.Parse(json);
            // deserialize json object to GetQuestionResponse
            getQuestionResponse.status = int.Parse(jsonObject["status"].ToString());
            getQuestionResponse.question = jsonObject["question"].ToString();
            JArray answers = JArray.Parse(jsonObject["answers"].ToString());  // convert answers and answerId fields to array
            JArray answerIds = JArray.Parse(jsonObject["answerId"].ToString());
            for (int i = 0; i < answers.Count(); i++)
            {
                getQuestionResponse.answers.Add(int.Parse(answerIds[i].ToString()), answers[i].ToString());  // add current answer to the answers
            }
            return getQuestionResponse;
        }
    }
}