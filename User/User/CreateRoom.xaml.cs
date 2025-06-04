using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        public CreateRoom()
        {
            InitializeComponent();
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = null;   // set frame content as null
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            RoomData roomData = new RoomData();  // construct RoomData struct
            roomData.name = txtRoomName.Text;
            roomData.maxPlayers = int.Parse(txtMaxPlayers.Text);
            roomData.numOfQuestionsInGame = int.Parse(txtNumQuestions.Text);
            roomData.timePerQuestion = int.Parse(txtQuestionTime.Text);
            // try to create the room
            KeyValuePair<bool, RoomData> roomResponse = ((MainWindow)Application.Current.MainWindow).m_communicator.CreateRoom(roomData);
            if (roomResponse.Key)   // check if the room was created successfully
            {
                List<string> players = new List<string>();
                players.Add(((MainWindow)Application.Current.MainWindow).m_username);  // add the user to the room players
                NavigationService.Content = new RoomLobby(roomResponse.Value, players);  // redirect the user to a room lobby
            }
        }
    }
}