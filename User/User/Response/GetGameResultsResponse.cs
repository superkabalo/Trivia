namespace User.Response
{
    public struct GetGameResultsResponse
    {
        public int status;
        public List<PlayerResults> results;  // all the game participants results
    }
}