using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using User.Response;

namespace User
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Page
    {
        private RoomData m_roomData;
        private int m_correctAnswers = Constants.EMPTY;  // the user's total correct answers
        private bool m_hasUserAnswered;  // did the user answer the current question
        private bool m_userQuit = false;  // did the user quit
        private int firstAnswerId;  // the id of each answer (according to the ui answers that is)
        private int secondAnswerId;
        private int thirdAnswerId;
        private int fourthAnswerId;
        private int userAnswerId;  // the user's answer id

        public Game(RoomData roomData)
        {
            InitializeComponent();
            m_roomData = roomData;
            txtNumQuestionLeft.Text = roomData.numOfQuestionsInGame.ToString();  // set the number of remaining questions
            Thread gameThread = new Thread(RunGame);  // start the RunGame thread
            gameThread.Start();

            this.Unloaded += RoomLobby_Unloaded;  // method in case the any thread is still running after the user exited the page
        }

        private void RoomLobby_Unloaded(object sender, RoutedEventArgs e)
        {
        }

        private void firstAns_Click(object sender, RoutedEventArgs e)
        {
            userAnswerId = firstAnswerId;  // mark the user's answer
            m_hasUserAnswered = true;  // mark that the user answered
        }

        private void secondAns_Click(object sender, RoutedEventArgs e)
        {
            userAnswerId = secondAnswerId;
            m_hasUserAnswered = true;
        }

        private void thirdAns_Click(object sender, RoutedEventArgs e)
        {
            userAnswerId = thirdAnswerId;
            m_hasUserAnswered = true;
        }

        private void fourthAns_Click(object sender, RoutedEventArgs e)
        {
            userAnswerId = fourthAnswerId;
            m_hasUserAnswered = true;
        }

        private void leaveGame_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).m_communicator.LeaveGame(); // leave the game
            m_userQuit = true;  // mark that the user quit
            NavigationService.Content = null;   // set frame content as null
        }

        private void RunGame()
        {
            for (int curQuestion = Constants.FIRST_QUESTION_NUM; curQuestion <= m_roomData.numOfQuestionsInGame; curQuestion++)  // go over all the question (ideally)
            {
                GetQuestionResponse getQuestionResponse = new GetQuestionResponse();
                Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
                {
                    getQuestionResponse = ((MainWindow)Application.Current.MainWindow).m_communicator.GetQuestion();  // get the current question
                    txtQuestion.Text = getQuestionResponse.question;
                    txtCorrectAnswers.Text = m_correctAnswers.ToString();
                });
                HashSet<int> randomAnswerIndexes = new HashSet<int>();  // define a set for randomizing the answers
                Random rnd = new Random();
                int randNum = Constants.EMPTY;
                while (randomAnswerIndexes.Count < Constants.NUM_OF_ANSWERS)  // generate the 4 different question index
                {
                    randNum = rnd.Next(Constants.NUM_OF_ANSWERS);  // generate the current index
                    if (!randomAnswerIndexes.Contains(randNum))  // add the current index if it is not already in the set
                    {
                        randomAnswerIndexes.Add(randNum);
                    }
                }

                Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
                {
                    // set the ui's answer ids which are randomized so that the answers are shuffled
                    firstAnswerId = randomAnswerIndexes.First();
                    firstAns.Content = getQuestionResponse.answers[firstAnswerId];
                    randomAnswerIndexes.Remove(firstAnswerId);
                    // although this does not seem randomized, the randomAnswerIndex set contains the possible answer ids in a randomized order, as done in the previous while loop
                    secondAnswerId = randomAnswerIndexes.First();
                    secondAns.Content = getQuestionResponse.answers[secondAnswerId];
                    randomAnswerIndexes.Remove(secondAnswerId);

                    thirdAnswerId = randomAnswerIndexes.First();
                    thirdAns.Content = getQuestionResponse.answers[thirdAnswerId];
                    randomAnswerIndexes.Remove(thirdAnswerId);

                    fourthAnswerId = randomAnswerIndexes.First();
                    fourthAns.Content = getQuestionResponse.answers[fourthAnswerId];
                    randomAnswerIndexes.Remove(fourthAnswerId);
                });

                m_hasUserAnswered = false;
                Thread timerThread = new Thread(updateTimer);  // start the timer thread
                Stopwatch sw = new Stopwatch();  // stopwatch for checking the user's answer time
                sw.Start();
                timerThread.Start();
                timerThread.Join();  // wait for the timer to finish / stop running
                sw.Stop();  // stop the user's stopwatch

                if (m_hasUserAnswered)  // in case the user answered
                {
                    Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
                    {
                        SubmitAnswerResponse submitAnswerResponse = ((MainWindow)Application.Current.MainWindow).m_communicator.SubmitAnswer(userAnswerId, (sw.Elapsed).Seconds);  // submit the user's answer
                        if (submitAnswerResponse.status == (int)Constants.Status.ANSWER_CORRECT_STATUS)  // check if the user answered correctly
                        {
                            m_correctAnswers++;
                            txtCorrectAnswers.Text = m_correctAnswers.ToString();  // update the correct answers element
                        }
                    });
                }
                else if (m_userQuit)  // check if the user quit
                {
                    return;
                }
                else  // user did not answer
                {
                    Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to use the MainWindow class
                    {
                        ((MainWindow)Application.Current.MainWindow).m_communicator.SubmitAnswer(Constants.NO_ANSWER, m_roomData.timePerQuestion); // submit the answer as an impossible answer id, and set the time as the maximum question time
                    });
                }
                Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
                {
                    txtNumQuestionLeft.Text = (m_roomData.numOfQuestionsInGame - curQuestion).ToString();  // set the number of questions left
                });
            }
            // we'll get here ONLY after the user ran through all the questions
            Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
            {
                KeyValuePair<bool, List<PlayerResults>> playerResults;  // the game results
                do
                {
                    playerResults = ((MainWindow)Application.Current.MainWindow).m_communicator.GetGameResults();  // get the game results
                } while (!playerResults.Key);
                ((MainWindow)Application.Current.MainWindow).m_communicator.LeaveGame(); // leave the game
                // sort the game results from high to low and link the user to a GameResults page
                NavigationService.Content = new GameResults(Enumerable.Reverse(playerResults.Value.OrderBy(obj => obj.correctAnswerCount).ToList()).ToList());
            });
        }

        private void updateTimer()
        {
            int secondsLeft = m_roomData.timePerQuestion;
            while (secondsLeft > Constants.EMPTY)
            {
                Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
                {
                    txtTimeLeft.Text = secondsLeft.ToString();  // set the seconds left
                });
                Thread.Sleep(Constants.ONE_SECOND_MS);  // wait a second and remove it from the time left
                if (m_hasUserAnswered || m_userQuit)  // check if the user answered or quit
                {
                    return;
                }
                secondsLeft--;
            }
            Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
            {
                txtTimeLeft.Text = Constants.EMPTY.ToString();  // set the time left as 0 seconds
            });
        }
    }
}