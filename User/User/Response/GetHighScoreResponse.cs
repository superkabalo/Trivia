namespace User.Response
{
    public struct GetHighScoreResponse
    {
        public int status;
        public List<string> statistics;    // the highest scoring players
    };
}