namespace User.Response
{
    public struct GetQuestionResponse
    {
        public int status;
        public string question;
        public Dictionary<int, string> answers;  // possible answer questions
    }
}