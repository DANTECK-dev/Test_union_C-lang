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

    public class DataGridItem
    {
        public int Column { get; set; }
        public int Row { get; set; }
        public string Data { get; set; }
    }

    public partial class MainWindow : Window
    {
        bool Selected_Process_control_algorithm = false;
        bool Selected_Memory_control_algorithm = false;
        bool Selected_VSU_control_algorithm = false;
        bool Started = false;

        public MainWindow()
        {
            InitializeComponent();
            Process_control_algorithm_comboBox.Items.Add("5. Многоуровневая очередь (2 уровня: высокий приоритет – Round robin, низкий приоритет – FCFS)");
            Memory_control_algorithm_comboBox.Items.Add("3. Страничное распределение памяти (страница – 1024 байт) ");
            VSU_control_algorithm_comboBox.Items.Add("2. Непрерывное размещение файлов (Кластер – 512 байт)");

            int p = new int();
            Byte value = 12;

            DLL.WriteMemoryByte(ref p, value);

            MessageBox.Show(DLL.ReadMemoryByte(ref p).ToString());
            
            Initialize_DataGrid();

            //Process_StatusBar.Items.Add(new Separator());
            //Process_StatusBar.Items.Add("hui");
            //MessageBox.Show(DLL.GetSectorSize().ToString());
        }

        private void Initialize_DataGrid()
        {
            Memory_Process_DataGrid.Items.Clear();
            Disk_Sector_DataGrid.Items.Clear();
            Disk_Map_DataGrid.Items.Clear();
            Disk_Catalog_DataGrid.Items.Clear();
            Memory_Address_DataGrid.Items.Clear();
            Memory_Map_DataGrid.Items.Clear();
            Memory_Process_DataGrid.Items.Clear();
            Process_DataGrid.Items.Clear();

            //for (int i = 0; i < 50; i++)
            //{
            //    for(int j = 0; j < 50; j++)
            //    {
                    Process_DataGrid.Items.Add(new DataGridItem() { Column = 2, Row = 2, Data = "test" });
                    //Memory_Process_DataGrid.Items.Add(i);
                    //Disk_Sector_DataGrid.Items.Add(i);
                    //Disk_Map_DataGrid.Items.Add(i);
                    //Disk_Catalog_DataGrid.Items.Add(i);
                    //Memory_Address_DataGrid.Items.Add(i);
                    //Memory_Map_DataGrid.Items.Add(i);
                    //Memory_Process_DataGrid.Items.Add(i);
                    //Process_DataGrid.Items.Add(i);
            //    }
            //}
        }

        private void Reverse_IsEnabled()
        {
            Start_Button.IsEnabled                          = !Start_Button.IsEnabled;
            Process_control_algorithm_comboBox.IsEnabled    = !Process_control_algorithm_comboBox.IsEnabled;
            Memory_control_algorithm_comboBox.IsEnabled     = !Memory_control_algorithm_comboBox.IsEnabled;
            VSU_control_algorithm_comboBox.IsEnabled        = !VSU_control_algorithm_comboBox.IsEnabled;
            Stop_Button.IsEnabled                           = !Stop_Button.IsEnabled;
            Create_Process_Button.IsEnabled                 = !Create_Process_Button.IsEnabled;
            Delete_Process_Button.IsEnabled                 = !Delete_Process_Button.IsEnabled;
            Empty_Comand_Button.IsEnabled                   = !Empty_Comand_Button.IsEnabled;
            Write_Linear_Button.IsEnabled                   = !Write_Linear_Button.IsEnabled;
            Read_Linear_Button.IsEnabled                    = !Read_Linear_Button.IsEnabled;
            Write_Segment_Button.IsEnabled                  = !Write_Segment_Button.IsEnabled;
            Read_Segment_Button.IsEnabled                   = !Read_Segment_Button.IsEnabled;
            Write_Memory_Button.IsEnabled                   = !Write_Memory_Button.IsEnabled;
            Read_Memory_Button.IsEnabled                    = !Read_Memory_Button.IsEnabled;
            Linear_TextBox.IsEnabled                        = !Linear_TextBox.IsEnabled;
            Segment_1_TextBox.IsEnabled                     = !Segment_1_TextBox.IsEnabled;
            Segment_2_TextBox.IsEnabled                     = !Segment_2_TextBox.IsEnabled;
            Value_TextBox.IsEnabled                         = !Value_TextBox.IsEnabled;
            Physical_Address_TextBox.IsEnabled              = !Physical_Address_TextBox.IsEnabled;
            File_Name_TextBox.IsEnabled                     = !File_Name_TextBox.IsEnabled;
            File_Offset_TextBox.IsEnabled                   = !File_Offset_TextBox.IsEnabled;
            Number_Bytes_TextBox.IsEnabled                  = !Number_Bytes_TextBox.IsEnabled;
            Address_Content_Button.IsEnabled                = !Address_Content_Button.IsEnabled;
            Address_Decrement_Button.IsEnabled              = !Address_Decrement_Button.IsEnabled;
            Address_Increment_Button.IsEnabled              = !Address_Increment_Button.IsEnabled;
            Address_TextBox.IsEnabled                       = !Address_TextBox.IsEnabled;
            Sector_Content_Button.IsEnabled                 = !Sector_Content_Button.IsEnabled;
            Sector_Decrement_Button.IsEnabled               = !Sector_Decrement_Button.IsEnabled;
            Sector_Increment_Button.IsEnabled               = !Sector_Increment_Button.IsEnabled;
            Sector_TextBox.IsEnabled                        = !Sector_TextBox.IsEnabled;
            Edit_File_Button.IsEnabled                      = !Edit_File_Button.IsEnabled;
            Read_File_Button.IsEnabled                      = !Read_File_Button.IsEnabled;
            Delete_File_Button.IsEnabled                    = !Delete_File_Button.IsEnabled;
            Create_File_Button.IsEnabled                    = !Create_File_Button.IsEnabled;
            Started                                         = !Started;
        }

        private void Start_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("System started button click");

            if(!Started && Start_Button.IsEnabled && !Stop_Button.IsEnabled)
            {
                //включаем
                Reverse_IsEnabled();
            }
        }

        private void Stop_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("System stopped button click");

            if (Started && !Start_Button.IsEnabled && Stop_Button.IsEnabled)
            {
                //выключаем
                Reverse_IsEnabled();
            }
        }

        private void Create_Process_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Created process button click");
        }

        private void Delete_Process_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Deleted process button click");
        }

        private void Empty_Command_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sended empty command button click");
        }

        private void Read_Linear_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Linear reading button click");
        }

        private void Write_Linear_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Linear recording button click");
        }

        private void Read_Segment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Segmental reading button click");
        }

        private void Write_Segment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Segmental recording button click");
        }

        private void Read_Memory_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Memory reading button click");
        }

        private void Write_Memory_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Memory recording button click");
        }

        private void Sector_Increment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sector increment button click");
        }

        private void Sector_Decrement_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sector decrement button click");
        }

        private void Sector_Content_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sector content button click");
        }

        private void Create_File_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Create file button click");
        }

        private void Delete_File_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Delete file button click");
        }

        private void Read_File_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Read file button click");
        }

        private void Edit_File_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Edit file button click");
        }

        private void Address_Increment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Address increment button click");
        }

        private void Address_Decrement_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Address decrement button click");
        }

        private void Address_Content_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Address content button click");
        }

        private void ADD_LOG(string message)
        {
            DLL.AddLog(message.ToCharArray(), message.Length);
            Log_ListBox.Items.Add(message);
            Log_ListBox.ScrollIntoView(Log_ListBox.Items[Log_ListBox.Items.Count - 1]);
        }

        private void VSU_control_algorithm_comboBox_DropDownClosed(object sender, EventArgs e)
        {
            if (VSU_control_algorithm_comboBox.SelectedIndex == -1) Selected_VSU_control_algorithm = false;
            else Selected_VSU_control_algorithm = true;
            if (Selected_Process_control_algorithm && Selected_Memory_control_algorithm && Selected_VSU_control_algorithm)
                Start_Button.IsEnabled = true;
            else Start_Button.IsEnabled = false;
        }

        private void Memory_control_algorithm_comboBox_DropDownClosed(object sender, EventArgs e)
        {
            if (Memory_control_algorithm_comboBox.SelectedIndex == -1) Selected_Memory_control_algorithm = false;
            else Selected_Memory_control_algorithm = true;
            if (Selected_Process_control_algorithm && Selected_Memory_control_algorithm && Selected_VSU_control_algorithm)
                Start_Button.IsEnabled = true;
            else Start_Button.IsEnabled = false;
        }

        private void Process_control_algorithm_comboBox_DropDownClosed(object sender, EventArgs e)
        {
            if (Process_control_algorithm_comboBox.SelectedIndex == -1) Selected_Process_control_algorithm = false;
            else Selected_Process_control_algorithm = true;
            if (Selected_Process_control_algorithm && Selected_Memory_control_algorithm && Selected_VSU_control_algorithm)
                Start_Button.IsEnabled = true;
            else Start_Button.IsEnabled = false;
        }
    }
}
