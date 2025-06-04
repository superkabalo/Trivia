namespace User.Request
{
    public struct CreateRoomRequest
    {
        public string roomName;   // details regarding the room
        public int maxUsers;
        public int questionCount;
        public int answerTimeout;
    }
}