using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
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
using System.Runtime;
using ConnectDLL;

namespace Test_union_c__
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    

    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
            //MessageBox.Show(DLL.GetSectorSize().ToString());
        }

        private void Start_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("System started");
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            
        }

        private void Stop_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("System stopped");
        }

        private void Create_Process_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Created process");
        }

        private void Delete_Process_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Deleted process");
        }

        private void Empty_Command_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sended empty command");
        }

        private void Read_Linear_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Linear reading");
        }

        private void Write_Linear_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Linear recording");
        }

        private void Read_Segment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Segmental reading");
        }

        private void Write_Segment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Segmental recording");
        }

        private void Read_Memory_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Memory reading");
        }

        private void Write_Memory_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Memory recording");
        }

        private void ADD_LOG(string message)
        {
            DLL.AddLog(message.ToCharArray(), message.Length);
            Log_ListBox.Items.Add(message);
            Log_ListBox.ScrollIntoView(Log_ListBox.Items[Log_ListBox.Items.Count - 1]);
        }
    }
}
