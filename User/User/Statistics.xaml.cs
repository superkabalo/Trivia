using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        public Statistics()
        {
            InitializeComponent();
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = null;   // set frame content as null
        }

        private void PersonalStatisticsBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = new PersonalStatistics();  // set frame content as the requested page content
        }

        private void HighScoresBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = new HighScores();  // set frame content as the requted page content
        }
    }
}