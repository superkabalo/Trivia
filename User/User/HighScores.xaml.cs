using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Page
    {
        public HighScores()
        {
            InitializeComponent();
            List<string> scores = ((MainWindow)Application.Current.MainWindow).m_communicator.GetHighScores();  // get the high scores
            try   // in case there aren't 3 high scores
            {
                // set the scores according to their index in the scores List
                txtFirstName.Text = scores.First();
                scores.Remove(scores.First());
                txtFirstScore.Text = scores.First();
                scores.Remove(scores.First());
                txtSecondName.Text = scores.First();
                scores.Remove(scores.First());
                txtSecondScore.Text = scores.First();
                scores.Remove(scores.First());
                txtThirdName.Text = scores.First();
                scores.Remove(scores.First());
                txtThirdScore.Text = scores.First();
            }
            catch (Exception)
            {
            }
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = new Statistics();   // return to a statistics page
        }
    }
}