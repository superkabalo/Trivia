using System.Net;
using System.Net.Sockets;
using System.Text;
using User.Request;
using User.Response;
using static User.Constants;

namespace User
{
    using Buffer = List<byte>;

    public class Communicator
    {
        private Socket? socket;
        private IPEndPoint? remoteEP;

        /// <summary>
        /// C'TOR - initiate connection with the server
        /// </summary>
        public Communicator()
        {
            try
            {
                IPAddress ipAddress = IPAddress.Parse(SERVER_IP);  // create an ip endpoint with the server
                remoteEP = new IPEndPoint(ipAddress, PORT);

                // create a tcp socket
                socket = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                socket.Connect(remoteEP); // connect to the server
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        /// <summary>
        /// D'TOR - close socket
        /// </summary>
        ~Communicator()
        {
            socket.Close(); // close the socket
        }

        /// <summary>
        /// method signs up user
        /// </summary>
        /// <param name="username"> - the username</param>
        /// <param name="password"> - the user password</param>
        /// <param name="email"> - the user email</param>
        /// <param name="address"> - the user address</param>
        /// <param name="phoneNumber"> - the user phone number</param>
        /// <param name="birthDate"> - the user birth date</param>
        /// <returns>was the signup successful or not</returns>
        public bool Signup(string username, string password, string email, string address, string phoneNumber, string birthDate)
        {
            byte[] bytes = new byte[BUFFER_SIZE];   // initiate buffer
            SignupRequest request = new SignupRequest();    // create signup request
            request.address = address;
            request.username = username;
            request.password = password;
            request.email = email;
            request.phoneNumber = phoneNumber;
            request.birthDate = birthDate;
            Buffer serializedMsg = Serializer.serializeRequest(request);    // serialize request
            try
            {
                // send the request
                int bytesSent = socket.Send(Serializer.serializeRequest(request).ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            SignupResponse response = Deserializer.deserializeSignupResponse(bytes.ToList());   // deserialize the response
            if (response.status == ((int)Status.SUCCESS_STATUS))    // check if the request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method creates room
        /// </summary>
        /// <param name="roomData"> - the room's data</param>
        /// <returns>pair of wether the room creating was successful, and the updated RoomData</returns>
        public KeyValuePair<bool, RoomData> CreateRoom(RoomData roomData)
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            CreateRoomRequest request = new CreateRoomRequest();   // create new CreateRoomRequest
            request.roomName = roomData.name;
            request.maxUsers = roomData.maxPlayers;
            request.questionCount = roomData.numOfQuestionsInGame;
            request.answerTimeout = roomData.timePerQuestion;
            Buffer serializedMsg = Serializer.serializeRequest(request);    // serialize request
            try
            {
                // send the request
                int bytesSent = socket.Send(Serializer.serializeRequest(request).ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            CreateRoomResponse response = Deserializer.deserializeCreateRoomResponse(bytes.ToList());   // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))    // check if response was successful
            {
                roomData.id = response.roomId;
                roomData.isActive = FALSE;
                return new KeyValuePair<bool, RoomData>(true, roomData);  // return true with the room id
            }
            return new KeyValuePair<bool, RoomData>(false, new RoomData());
        }

        /// <summary>
        /// method gets players in a room
        /// </summary>
        /// <param name="roomId"> - the room id</param>
        /// <returns>List of the room players' names</returns>
        public List<string> GetPlayersInRoom(int roomId)
        {
            byte[] bytes = new byte[BUFFER_SIZE];   // initiate buffer
            GetPlayersInRoomRequest request = new GetPlayersInRoomRequest();    // create new GetPlayersInRoomRequest
            request.roomId = roomId;
            Buffer serializedMsg = Serializer.serializeRequest(request);   // serialize request
            try
            {
                // send the request
                int bytesSent = socket.Send(Serializer.serializeRequest(request).ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetPlayersInRoomResponse response = Deserializer.deserializeGetPlayersInRoomResponse(bytes.ToList());   // deserialize response
            return response.players;
        }

        /// <summary>
        /// method joins room
        /// </summary>
        /// <param name="roomId"> - the room id</param>
        /// <returns>room joining was succcessful or not</returns>
        public bool JoinRoom(int roomId)
        {
            byte[] bytes = new byte[BUFFER_SIZE];   // initiate buffer
            JoinRoomRequest request = new JoinRoomRequest();  // create new JoinRoomRequest
            request.roomId = roomId;
            Buffer serializedMsg = Serializer.serializeRequest(request);  // serialize request
            try
            {
                // send the request
                int bytesSent = socket.Send(Serializer.serializeRequest(request).ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            JoinRoomResponse response = Deserializer.deserializeJoinRoomResponse(bytes.ToList());   // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))    // check if request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method logins user
        /// </summary>
        /// <param name="username"> - the username</param>
        /// <param name="password"> - the user password</param>
        /// <returns>was login successful or not</returns>
        public bool Login(string username, string password)
        {
            byte[] bytes = new byte[BUFFER_SIZE];   // initiate buffer
            LoginRequest request = new LoginRequest();  // create new LoginRequest
            request.username = username;
            request.password = password;
            Buffer serializedMsg = Serializer.serializeRequest(request);   // serialize request
            try
            {
                // send the request
                int bytesSent = socket.Send(Serializer.serializeRequest(request).ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            LoginResponse response = Deserializer.deserializeLoginResponse(bytes.ToList());  // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))    // check if request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method gets the 3 highest scoring players' names and their scores
        /// </summary>
        /// <returns>List of the 3 highest scoring players' names and their scores</returns>
        public List<string> GetHighScores()
        {
            byte[] bytes = new byte[BUFFER_SIZE];   // initiate buffer
            Buffer serializedMsg = Serializer.serializeGetHighScoresRequest();  // create new GetHighScoresRequest
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetHighScoreResponse response = Deserializer.deserializeGetHighScoresResponse(bytes.ToList());  // deserialize response
            if (response.status != ((int)Status.SUCCESS_STATUS))    // check if response was unsuccessful
            {
                return new List<string>();
            }
            return response.statistics;
        }

        /// <summary>
        /// method gets user's personal stats
        /// </summary>
        /// <returns>List of the user's personal stats</returns>
        public List<string> GetPersonalStats()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeGetPersonalStatsRequest();   // serialize GetPersonalStats request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetPersonalStatsResponse response = Deserializer.deserializeGetPersonalStatsResponse(bytes.ToList());  // deserialize response
            if (response.status != ((int)Status.SUCCESS_STATUS))   // check if request was unsuccessful
            {
                return new List<string>();
            }
            return response.statistics;
        }

        /// <summary>
        /// method gets all the avilable rooms
        /// </summary>
        /// <returns>List of the rooms' data</returns>
        public List<RoomData> GetRooms()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeGetRoomsRequest();   // serialize GetRoomsRequest
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetRoomsResponse response = Deserializer.deserializeGetRoomsResponse(bytes.ToList());   // deserialize response
            if (response.status != ((int)Status.SUCCESS_STATUS))    // check if request was unsuccessful
            {
                return new List<RoomData>();
            }
            return response.rooms;
        }

        /// <summary>
        /// method leaves game
        /// </summary>
        /// <returns>was game leaving successful or not</returns>
        public bool LeaveGame()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate the buffer

            Buffer serializedMsg = Serializer.serializeLeaveGameRequest();  // serialize the request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            LeaveGameResponse response = Deserializer.deserializeLeaveGameResponse(bytes.ToList());  // deserialize the response
            if (response.status == ((int)Status.SUCCESS_STATUS))  // check if the request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method submits answer to a question
        /// </summary>
        /// <param name="answerId"> - the question id</param>
        /// <returns>the submit answer response</returns>
        public SubmitAnswerResponse SubmitAnswer(int answerId, int answerTime)
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate the buffer
            Buffer serializedMsg = Serializer.serializeSubmitAnswerRequest(answerId, answerTime);  // serialize the request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            SubmitAnswerResponse response = Deserializer.deserializeSubmitAnswerResponse(bytes.ToList());  // deserialize the response
            return response;
        }

        /// <summary>
        /// method gets question
        /// </summary>
        /// <returns>the GetQuestion response</returns>
        public GetQuestionResponse GetQuestion()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeGetQuestionRequest();  // serialize the request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetQuestionResponse response = Deserializer.deserializeGetQuestionResponse(bytes.ToList());  // deserialize the answer
            if (response.status != (int)Status.SUCCESS_STATUS)  // check if request was unsuccessful
            {
                return new GetQuestionResponse();
            }
            return response;
        }

        /// <summary>
        /// method logs out user
        /// </summary>
        /// <returns>was logout successful or not</returns>
        public bool Logout()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeLogoutRequest();  // serialize Logout requset
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            LogoutResponse response = Deserializer.deserializeLogoutResponse(bytes.ToList());  // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))  // check if request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method closes room
        /// </summary>
        /// <returns>was room closing successful or not</returns>
        public bool CloseRoom()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeCloseRoomRequest();  // serializer CloseRoom request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            CloseRoomResponse response = Deserializer.deserializeCloseRoomResponse(bytes.ToList());  // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))  // check if request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method gets the game results
        /// </summary>
        /// <returns>pair of wether the request was successful or not (all the players finished their games or not) and the players' results</returns>
        public KeyValuePair<bool, List<PlayerResults>> GetGameResults()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate the buffer
            Buffer serializedMsg = Serializer.serializeGetGameResultsRequest();  // serialize the request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the serverS
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetGameResultsResponse response = Deserializer.deserializeGetGameResultsResponse(bytes.ToList());  // deserialize the response
            if (response.status != ((int)Status.SUCCESS_STATUS))  // check if request was unsuccessful
            {
                return new KeyValuePair<bool, List<PlayerResults>>(false, new List<PlayerResults>());  // return a false key of the pair
            }
            return new KeyValuePair<bool, List<PlayerResults>>(true, response.results);  // return the response with a true key
        }

        /// <summary>
        /// method starts game
        /// </summary>
        /// <returns>was game starting successful or not</returns>
        public bool StartGame()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeStartGameRequest();  // serialize StartGameRequest
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            StartGameResponse response = Deserializer.deserializeStartGameResponse(bytes.ToList());  // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))  // check if request was successful
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// method gets a room's state
        /// </summary>
        /// <returns>the room state</returns>
        public GetRoomStateResponse GetRoomState()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeGetRoomStateRequest();  // serialize GetRoomState request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            GetRoomStateResponse response = Deserializer.deserializeGetRoomStateResponse(bytes.ToList());  // deserialize response
            return response;
        }

        /// <summary>
        /// method leaves room
        /// </summary>
        /// <returns>was room leaving successful or not</returns>
        public bool LeaveRoom()
        {
            byte[] bytes = new byte[BUFFER_SIZE];  // initiate buffer
            Buffer serializedMsg = Serializer.serializeLeaveRoomRequest();  // serializer LeaveRoom request
            try
            {
                // send the request
                int bytesSent = socket.Send(serializedMsg.ToArray());

                // receive the response from the server
                int bytesRec = socket.Receive(bytes);
                Console.WriteLine("Echoed test = {0}",
                    Encoding.ASCII.GetString(bytes, 0, bytesRec));
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
            }
            LeaveRoomResponse response = Deserializer.deserializeLeaveRoomResponse(bytes.ToList());  // deserialize response
            if (response.status == ((int)Status.SUCCESS_STATUS))    // check if request was successful
            {
                return true;
            }
            return false;
        }
    }
}