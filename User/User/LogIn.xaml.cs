using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for LogIn.xaml
    /// </summary>
    public partial class LogIn : Page
    {
        public LogIn()
        {
            InitializeComponent();
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = null;   // set frame content as null
        }

        private void LogInBtn_Click(object sender, RoutedEventArgs e)
        {
            Communicator communicator = ((MainWindow)Application.Current.MainWindow).m_communicator;  // get communicator
            if (!communicator.Login(txtUsername.Text, txtPassword.Text))  // if login was unsuccessful
            {
                txtLoginError.Text = "Error while signing up, please recheck the credentials and retry.";
            }
            else
            {
                ((MainWindow)Application.Current.MainWindow).LoginUser();   // login user in the client-side
                ((MainWindow)Application.Current.MainWindow).m_username = txtUsername.Text;
            }
        }
    }
}