namespace User
{
    public class RoomData
    {
        // room details
        public int id { get; set; }

        public string name { get; set; }
        public int maxPlayers { get; set; }
        public int numOfQuestionsInGame { get; set; }
        public int timePerQuestion { get; set; }
        public int isActive { get; set; }
    }
}