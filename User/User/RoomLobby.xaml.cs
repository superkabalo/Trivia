using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using User.Response;

namespace User
{
    /// <summary>
    /// Interaction logic for RoomLobby.xaml
    /// </summary>
    public partial class RoomLobby : Page
    {
        private RoomData m_roomData { get; set; }
        private bool m_admin { get; set; }
        private bool m_keepRefreshing { get; set; }

        public RoomLobby(RoomData roomData, List<string> players)
        {
            m_roomData = roomData;
            InitializeComponent();
            m_admin = false;
            updatePlayersInRoom(players);  // update room players
            GetRoomStateResponse roomState = ((MainWindow)Application.Current.MainWindow).m_communicator.GetRoomState();  // update the room details
            txtQuestionCount.Text = roomState.questionCount.ToString();
            txtAnswerTimeout.Text = roomState.answerTimeout.ToString();
            Thread refreshThread = new Thread(autoRefresh);  // create the auto refresh thread
            refreshThread.Start();
            m_keepRefreshing = true;

            this.Unloaded += RoomLobby_Unloaded;  // method in case the refresh thread is still running after the user exited the page
        }

        private void RoomLobby_Unloaded(object sender, RoutedEventArgs e)
        {
        }

        private void LeaveCloseRoom_Click(object sender, RoutedEventArgs e)
        {
            if (m_admin)
            {
                ((MainWindow)Application.Current.MainWindow).m_communicator.CloseRoom();  // close the room if the user is an admin and chose so
            }
            else
            {
                ((MainWindow)Application.Current.MainWindow).m_communicator.LeaveRoom();  // leave the room in case of a regular user
            }
            NavigationService.Content = null;   // set frame content as null
            m_keepRefreshing = false;  // stop the refresh thread
        }

        private void StartGame_Click(object sender, RoutedEventArgs e)
        {
            ((MainWindow)Application.Current.MainWindow).m_communicator.StartGame();  // start the game
            m_keepRefreshing = false;  // stop the refresh thread
            NavigationService.Content = new Game(m_roomData);   // link the user to the game
        }

        private void updatePlayersInRoom(List<string> players)
        {
            PlayersInRoomListBox.Items.Clear();  // clear the room players list
            for (int i = 0; i < players.Count; i++)
            {
                if (i == Constants.FRONT)  // the first user is an admin
                {
                    PlayersInRoomListBox.Items.Add("(ADMIN) " + players[i]);
                    if (players[i] == ((MainWindow)Application.Current.MainWindow).m_username)  // check if the connected user is the admin
                    {
                        m_admin = true;
                        LeaveCloseRoom.Content = "Close Room";  // set Close Room button accordingly
                        StartGameButton.Visibility = Visibility.Visible;  // make Start Game button visible
                    }
                }
                else
                {
                    PlayersInRoomListBox.Items.Add(players[i]);  // add a regular player without the admin tag
                }
            }
        }

        private void autoRefresh()
        {
            while (m_keepRefreshing)  // run while m_keepRefreshing is true
            {
                Thread.Sleep(Constants.THREE_SECONDS_MS);  // wait for three seconds until the next refresh
                if (m_keepRefreshing)
                {
                    Application.Current.Dispatcher.Invoke(() =>  // invoke the main thread in order to change the ui elements
                    {
                        GetRoomStateResponse roomState = ((MainWindow)Application.Current.MainWindow).m_communicator.GetRoomState();  // get the current room state
                        if (roomState.hasGameBegun)
                        {
                            m_keepRefreshing = false;  // stop refreshing
                            NavigationService.Content = new Game(m_roomData);  // link user to game page
                            return;
                        }
                        else if (roomState.status == (int)Constants.Status.ROOM_CLOSED_STATUS)  // if the room was closed
                        {
                            m_keepRefreshing = false;
                            NavigationService.Content = null;
                            return;
                        }
                        updatePlayersInRoom(roomState.players);  // update room players
                    });
                }
            }
        }
    }
}