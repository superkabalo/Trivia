using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using User.Response;

namespace User
{
    /// <summary>
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Page
    {
        public GameResults(List<PlayerResults> gameResults)
        {
            InitializeComponent();
            ScoreListView.ItemsSource = gameResults;  // set the score view source as the game results
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = null;   // set frame content as null
        }
    }
}