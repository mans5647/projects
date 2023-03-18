using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics.SymbolStore;
using System.Linq;
using System.Linq.Expressions;
using System.Runtime.Remoting.Channels;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;

namespace tictak
{
    public partial class MainWindow : Window
    {

        int current_role = 1, current_player = (int)TURN.HUMAN; // by default it is equal to crosses // by default player starting first
        private enum roles
        {
            CROSSES = 1,
            NULLS = 0,
        }
        
        private enum TURN
        {
            COMP = 0,
            HUMAN = 1,
        }
        

        public MainWindow()
        {
            InitializeComponent();
        }


        private void DeclareWinner(int current_player)
        {
            if (current_player == 1) // if player then...
            {
                if (   b1.Content == "X" && b2.Content == "X" && b3.Content == "X"
                    || b4.Content == "X" && b5.Content == "X" && b6.Content == "X"
                    || b7.Content == "X" && b7.Content == "X" && b9.Content == "X"
                    || b1.Content == "X" && b4.Content == "X" && b7.Content == "X"
                    || b2.Content == "X" && b5.Content == "X" && b8.Content == "X"
                    || b3.Content == "X" && b6.Content == "X" && b9.Content == "X")
                {
                    MessageBox.Show("Player wins!");
                }
            }
        }

        private void BStart_Click(object snd,RoutedEventArgs AS)
        {
            
            List<Button> buttons = new List<Button> { b1, b2, b3, b4, b5, b6, b7, b8, b9 };
            foreach (Button but in buttons)
            {
                but.IsEnabled = true;
                but.Content = "";
            }
            switchrole.IsEnabled = true;
            return;
        }

        private void toggleRole(object sender, RoutedEventArgs ars)
        {
            if (current_role == 1)
            {
                current_role = 0; // switching to NULLS
                string tmp = "nulls";
                label1.Content = "Your role: " + tmp;
                switchrole.IsEnabled = false;
            }
            else
            {
                current_role = 1;
                string tmp = "crosses";
                label1.Content = "Your role: " + tmp;
                switchrole.IsEnabled = false;
            }
        }
        


        private void Button_Click(object sender, RoutedEventArgs args)
        {
            
            List<Button> buttons = new List<Button> { b1, b2, b3, b4, b5, b6, b7, b8, b9 };
           
                if (current_player == (int)TURN.HUMAN)
                {
                    (sender as Button).Content = "X";
                    (sender as Button).IsEnabled = false;
                    buttons.Remove((sender as Button));
                    current_role = 0; // assign 'O' to computer 
                    current_player = (int)TURN.COMP;
                }
            else
            {
                (sender as Button).Content = "O";
                (sender as Button).IsEnabled = false;
                buttons.Remove((sender as Button));
                current_role = 1; // assign 'X' to computer 
            }
                 
                Comp_Walk(buttons, current_role, current_player);
                DeclareWinner(current_player);
        }

        private void Comp_Walk(List<Button>buttons, int role, int player)
        {
            if (current_player == (int)TURN.COMP)
            {
                if (buttons.Count > 0)
                {
                    Random number = new Random();
                    int pos = number.Next(buttons.Count);
                    buttons[pos].IsEnabled = false;
                    if (role == 1)
                    {
                        buttons[pos].Content = "O";
                        current_player = 1;
                    }
                    else
                    {
                        buttons[pos].Content = "X";
                        current_player = 1;
                    }
                    buttons.RemoveAt(pos);
                    current_player = (int)TURN.HUMAN;
                }
            }
        }

    }
}
