using System.Windows;
using System.Windows.Input;

namespace User
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool m_userConnected { get; set; }
        public Communicator m_communicator { get; set; }
        public string m_username { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            m_userConnected = false;    // user is not connected
            m_communicator = new Communicator();  // initiate a new communicator
        }

        public void LoginUser()
        {
            m_userConnected = true;
            LogInButton.Visibility = Visibility.Hidden;  // hide login button
            SignUpLogOutButton.Content = "Log Out!";   // set signup/logout button content as log out
            // set main buttons as fully visible with a hand cursor
            CreateRoomButton.Opacity = Constants.VISIBLE;
            CreateRoomButton.Cursor = Cursors.Hand;
            JoinRoomButton.Opacity = Constants.VISIBLE; ;
            JoinRoomButton.Cursor = Cursors.Hand;
            StatisticsButton.Opacity = Constants.VISIBLE; ;
            StatisticsButton.Cursor = Cursors.Hand;
            MainFrame.Content = null;   // set frame content as null
        }

        public void LogoutUser()
        {
            m_userConnected = false;
            LogInButton.Visibility = Visibility.Visible;
            SignUpLogOutButton.Content = "Sign Up!";   // set signup/logout button content as sign up
            // set main buttons as half visible with no hand cursor
            CreateRoomButton.Opacity = Constants.HALF_VISIBLE;
            CreateRoomButton.Cursor = Cursors.Hand;
            JoinRoomButton.Opacity = Constants.HALF_VISIBLE;
            JoinRoomButton.Cursor = Cursors.Hand;
            StatisticsButton.Opacity = Constants.HALF_VISIBLE;
            StatisticsButton.Cursor = Cursors.Hand;
            MainFrame.Content = null;   // set frame content as null
            m_username = null;
        }

        private void LogInBtn_Click(object sender, RoutedEventArgs e)
        {
            MainFrame.Content = new LogIn();    // set frame content as the requested page's content
        }

        private void SignUpLogOutBtn_Click(object sender, RoutedEventArgs e)
        {
            if (!m_userConnected)   // check if user is not connected
            {
                MainFrame.Content = new SignUp();
            }
            else
            {
                // log out user
                if (m_communicator.Logout())
                {
                    LogoutUser();
                }
            }
        }

        private void ExitBtn_Click(object sender, RoutedEventArgs e)
        {
            if (m_userConnected)    // logout user if he is connected
            {
                m_communicator.Logout();
            }
            Close();    // close the program
        }

        private void CreateRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            if (m_userConnected)
            {
                MainFrame.Content = new CreateRoom();  // set frame content as the request page
            }
        }

        private void JoinRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            if (m_userConnected)
            {
                MainFrame.Content = new JoinRoom();  // set frame content as the requested page
            }
        }

        private void StatisticsBtn_Click(object sender, RoutedEventArgs e)
        {
            if (m_userConnected)
            {
                MainFrame.Content = new Statistics();  // set frame content as the request page
            }
        }
    }
}