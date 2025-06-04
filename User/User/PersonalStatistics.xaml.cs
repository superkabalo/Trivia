using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for PersonalStatistics.xaml
    /// </summary>
    public partial class PersonalStatistics : Page
    {
        public PersonalStatistics()
        {
            InitializeComponent();
            List<string> stats = ((MainWindow)Application.Current.MainWindow).m_communicator.GetPersonalStats();    // get personal user statistics
            txtUsername.Text = ((MainWindow)Application.Current.MainWindow).m_username;
            // set the user's personal stats according to the statistics List
            txtCorrectAnswers.Text = stats.First();
            stats.Remove(stats.First());
            txtTotalAnswers.Text = stats.First();
            stats.Remove(stats.First());
            txtTotalGames.Text = stats.First();
            stats.Remove(stats.First());
            txtAvgAnsTime.Text = stats.First();
            stats.Remove(stats.First());
            txtScore.Text = stats.First();
            stats.Remove(stats.First());
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = new Statistics();   // return to a statistics page
        }
    }
}