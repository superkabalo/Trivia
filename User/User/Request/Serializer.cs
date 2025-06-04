using MongoDB.Bson;
using Newtonsoft.Json;
using static User.Constants;

namespace User.Request
{
    using Buffer = List<byte>;

    public class Serializer
    {
        /// <summary>
        /// method serializes login request
        /// </summary>
        /// <param name="loginRequest"> - the login request</param>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeRequest(LoginRequest loginRequest)
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.LOGIN_REQ);   // insert login code to buffer
            // create LoginRequest Json
            string loginJson = JsonConvert.SerializeObject(new { username = loginRequest.username, password = loginRequest.password });
            // parse the Json to a BsonDocument
            BsonDocument loginBsonDocument = BsonDocument.Parse(loginJson);
            // convert the BsonDocument to a byte array
            byte[] loginBson = loginBsonDocument.ToBson();

            int dataLen = loginBson.Length; // get length of Bson data
            byte[] dataLenBytes = BitConverter.GetBytes(dataLen); // convert dataLen int to byte array
            Array.Reverse(dataLenBytes);    // convert datalength to big endian notation
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            serializedMsg.AddRange(loginBson); // add Bson data to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes signup request
        /// </summary>
        /// <param name="signupRequest"> - the signup request</param>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeRequest(SignupRequest signupRequest)
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.SIGNUP_REQ);   // insert signup code to buffer
            // create SignUpRequest Json
            string signupJson = JsonConvert.SerializeObject(new { username = signupRequest.username, password = signupRequest.password, email = signupRequest.email, address = signupRequest.address, birthDate = signupRequest.birthDate, phoneNumber = signupRequest.phoneNumber });
            // parse the Json to a BsonDocument
            BsonDocument signupBsonDocument = BsonDocument.Parse(signupJson);
            // convert the BsonDocument to a byte array
            byte[] signupBson = signupBsonDocument.ToBson();

            int dataLen = signupBson.Length; // get length of Bson data
            byte[] dataLenBytes = BitConverter.GetBytes(dataLen); // convert dataLen int to byte array
            Array.Reverse(dataLenBytes);    // convert datalength to big endian notation
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            serializedMsg.AddRange(signupBson); // add Bson data to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes create room request
        /// </summary>
        /// <param name="createRoomRequest"> - the create room request</param>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeRequest(CreateRoomRequest createRoomRequest)
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.CREATE_ROOM_REQ);   // insert create room code to buffer
            // create CreateRoomRequest json
            string createRoomJson = JsonConvert.SerializeObject(new { questionCount = createRoomRequest.questionCount, maxUsers = createRoomRequest.maxUsers, answerTimeout = createRoomRequest.answerTimeout, roomName = createRoomRequest.roomName });
            // parse the Json to a BsonDocument
            BsonDocument createRoomBsonDocument = BsonDocument.Parse(createRoomJson);
            // convert the BsonDocument to a byte array
            byte[] createRoomBson = createRoomBsonDocument.ToBson();

            int dataLen = createRoomBson.Length; // get length of Bson data
            byte[] dataLenBytes = BitConverter.GetBytes(dataLen); // convert dataLen int to byte array
            Array.Reverse(dataLenBytes);    // convert datalength to big endian notation
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            serializedMsg.AddRange(createRoomBson); // add Bson data to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes join room request
        /// </summary>
        /// <param name="joinRoomRequest"> - the join room request</param>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeRequest(JoinRoomRequest joinRoomRequest)
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.JOIN_ROOM_REQ);   // insert join room code to buffer
            // create JoinRoomRequest json
            string joinRoomJson = JsonConvert.SerializeObject(new { roomId = joinRoomRequest.roomId });
            // parse the Json to a BsonDocument
            BsonDocument joinRoomBsonDocument = BsonDocument.Parse(joinRoomJson);
            // convert the BsonDocument to a byte array
            byte[] joinRoomBson = joinRoomBsonDocument.ToBson();

            int dataLen = joinRoomBson.Length; // get length of Bson data
            byte[] dataLenBytes = BitConverter.GetBytes(dataLen); // convert dataLen int to byte array
            Array.Reverse(dataLenBytes);    // convert datalength to big endian notation
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            serializedMsg.AddRange(joinRoomBson); // add Bson data to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get players in room request
        /// </summary>
        /// <param name="getPlayersInRoomRequest"> - the get players in room request</param>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeRequest(GetPlayersInRoomRequest getPlayersInRoomRequest)
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.GET_PLAYERS_IN_ROOM_REQ);   // insert get players in room code to buffer
            // create GetPlayersInRoomRequest json
            string getPlayersInRooomJson = JsonConvert.SerializeObject(new { roomId = getPlayersInRoomRequest.roomId });
            // parse the Json to a BsonDocument
            BsonDocument getPlayersInRooomBsonDocument = BsonDocument.Parse(getPlayersInRooomJson);
            // convert the BsonDocument to a byte array
            byte[] getPlayersInRooomBson = getPlayersInRooomBsonDocument.ToBson();
            int dataLen = getPlayersInRooomBson.Length; // get length of Bson data
            byte[] dataLenBytes = BitConverter.GetBytes(dataLen); // convert dataLen int to byte array
            Array.Reverse(dataLenBytes);    // convert datalength to big endian notation
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            serializedMsg.AddRange(getPlayersInRooomBson); // add Bson data to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get high scores request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeGetHighScoresRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.HIGH_SCORE_REQ);   // insert get high score code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get personal stats request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeGetPersonalStatsRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.PERSONAL_STATS_REQ);   // insert get personal stats code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes logoutrequest
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeLogoutRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.LOGOUT_REQ);   // insert get logout code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get rooms request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeGetRoomsRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.GET_ROOMS_REQ);   // insert get rooms in room code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes close room request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeCloseRoomRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.CLOSE_ROOM_REQ);   // insert close room code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes start game request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeStartGameRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.START_GAME_REQ);   // insert start game code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get room state request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeGetRoomStateRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.GET_ROOM_STATE_REQ);   // insert get room state code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes leave room request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeLeaveRoomRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.LEAVE_ROOM_REQ);   // insert leave room code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes leave game request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeLeaveGameRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.LEAVE_GAME_REQ);   // insert leave game code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes submit answer request
        /// </summary>
        /// <param name="answerId"> - the the submitted answer id</param>
        /// /// <param name="answerTime"> - the time it took the user to answer</param>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeSubmitAnswerRequest(int answerId, int answerTime)
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.SUBMIT_ANSWER_REQ);   // insert submit answers code to buffer
            string joinRoomJson = JsonConvert.SerializeObject(new { answerId = answerId, answerTime = answerTime });
            // parse the Json to a BsonDocument
            BsonDocument submitAnswerBsonDocument = BsonDocument.Parse(joinRoomJson);
            // convert the BsonDocument to a byte array
            byte[] submitAnswerBson = submitAnswerBsonDocument.ToBson();
            int dataLen = submitAnswerBson.Length; // get length of Bson data
            byte[] dataLenBytes = BitConverter.GetBytes(dataLen); // convert dataLen int to byte array
            Array.Reverse(dataLenBytes);    // convert datalength to big endian notation
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            serializedMsg.AddRange(submitAnswerBson); // add Bson data to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get game results request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeGetGameResultsRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.GET_GAME_RESULTS_REQ);   // insert get game results code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }

        /// <summary>
        /// method serializes get question request
        /// </summary>
        /// <returns>Buffer with the serialized message</returns>
        public static Buffer serializeGetQuestionRequest()
        {
            Buffer serializedMsg = new Buffer();
            serializedMsg.Add((byte)RequestId.GET_QUESTION_REQ);   // insert get question code to buffer
            byte[] dataLenBytes = BitConverter.GetBytes(Constants.EMPTY); // convert dataLen int to byte array
            serializedMsg.AddRange(dataLenBytes); // add dataLen bytes to buffer
            return serializedMsg;
        }
    }
}