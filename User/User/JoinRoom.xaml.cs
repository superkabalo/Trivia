using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        private bool m_keepRefreshing { get; set; }

        public JoinRoom()
        {
            InitializeComponent();
            List<RoomData> rooms = ((MainWindow)Application.Current.MainWindow).m_communicator.GetRooms(); // set rooms source as the response of GetRooms
            updateRooms(rooms);
            Thread refreshThread = new Thread(autoRefresh);  // create auto refresh thread
            refreshThread.Start();
            m_keepRefreshing = true;
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            m_keepRefreshing = false;
            NavigationService.Content = null;   // set frame content as null
        }

        private void RoomsListView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            RoomData roomData = (RoomData)RoomsListView.SelectedItem;  // get the user choice
            if (roomData == null)
            {
                return;
            }
            List<string> players = ((MainWindow)Application.Current.MainWindow).m_communicator.GetPlayersInRoom(roomData.id);  // get the room players and
            players.Add(((MainWindow)Application.Current.MainWindow).m_username);  // add the user to the players list
            if (((MainWindow)Application.Current.MainWindow).m_communicator.JoinRoom(roomData.id))  // try to insert the user to the chosen room
            {
                m_keepRefreshing = false;
                NavigationService.Content = new RoomLobby(roomData, players);  // link user to the room lobby
            }
            else
            {
                txtError.Text = "Room is full!";
            }
        }

        private void updateRooms(List<RoomData> rooms)
        {
            RoomsListView.Items.Clear();   // clear the rooms
            for (int i = 0; i < rooms.Count; i++)
            {
                if (!Convert.ToBoolean(rooms[i].isActive))  // display room if it isn't active
                {
                    RoomsListView.Items.Add(rooms[i]);
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
                        List<RoomData> rooms = ((MainWindow)Application.Current.MainWindow).m_communicator.GetRooms(); // get updated rooms list
                        updateRooms(rooms);    // update rooms
                    });
                }
            }
        }
    }
}