using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;

namespace User
{
    /// <summary>
    /// Interaction logic for SignUp.xaml
    /// </summary>
    public partial class SignUp : Page
    {
        public SignUp()
        {
            InitializeComponent();
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Content = null;   // set frame content as null
        }

        private void SignUpButton_Click(object sender, RoutedEventArgs e)
        {
            Communicator communicator = ((MainWindow)Application.Current.MainWindow).m_communicator;  // get communicator
            if (!communicator.Signup(txtUsername.Text, txtPassword.Text, txtEmail.Text, txtAddress.Text, txtPhoneNumber.Text, txtBirthDate.Text))  // if signup was unsuccessful
            {
                txtSignupError.Text = "Error while signing up, please recheck the credentials format and retry.";
            }
            else
            {
                ((MainWindow)Application.Current.MainWindow).LoginUser();   // login user
                ((MainWindow)Application.Current.MainWindow).m_username = txtUsername.Text;
            }
        }
    }
}