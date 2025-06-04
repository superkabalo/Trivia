namespace User.Response
{
    public struct GetRoomStateResponse
    {
        // details regarding the room
        public int status;
        public bool hasGameBegun;
        public List<string> players;
        public int questionCount;
        public int answerTimeout;
    }
}