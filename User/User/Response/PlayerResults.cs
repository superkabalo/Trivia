namespace User.Response
{
    public class PlayerResults
    {
        public string username { get; set; }  // the user's name and his results
        public int correctAnswerCount { get; set; }
        public int wrongAnswerCount { get; set; }
        public int averageAnswerTime { get; set; }
    }
}