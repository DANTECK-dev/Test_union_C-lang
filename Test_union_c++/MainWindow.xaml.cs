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
using System.Data;
using System.Reflection;

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

        DataTable employeeDataTable = new DataTable();

        internal class Process
        {
            public string? ProcessData { get; set; }
            public string? AddressSpace { get; set; }
        }
        public static class DataGridHelper
        {
            public static DataGridCell FindCell(int iRow, int iColumn, DataGrid dg)
            {
                return GetCell(new DataGridCellInfo(dg.Items[iRow], dg.Columns[iColumn]));
            }

            public static DataGridCell GetCell(DataGridCellInfo dataGridCellInfo)
            {
                if (!dataGridCellInfo.IsValid)
                {
                    return null;
                }

                var cellContent = dataGridCellInfo.Column.GetCellContent(dataGridCellInfo.Item);
                if (cellContent != null)
                {
                    return (DataGridCell)cellContent.Parent;
                }
                else
                {
                    return null;
                }
            }
            public static int GetRowIndex(DataGridCell dataGridCell)
            {
                // Use reflection to get DataGridCell.RowDataItem property value.
                PropertyInfo rowDataItemProperty = dataGridCell.GetType().GetProperty("RowDataItem", BindingFlags.Instance | BindingFlags.NonPublic);

                DataGrid dataGrid = GetDataGridFromChild(dataGridCell);

                return dataGrid.Items.IndexOf(rowDataItemProperty.GetValue(dataGridCell, null));
            }
            public static DataGrid GetDataGridFromChild(DependencyObject dataGridPart)
            {
                if (VisualTreeHelper.GetParent(dataGridPart) == null)
                {
                    throw new NullReferenceException("Control is null.");
                }
                if (VisualTreeHelper.GetParent(dataGridPart) is DataGrid)
                {
                    return (DataGrid)VisualTreeHelper.GetParent(dataGridPart);
                }
                else
                {
                    return GetDataGridFromChild(VisualTreeHelper.GetParent(dataGridPart));
                }
            }
        }

        public MainWindow()
        {
            InitializeComponent();
            Process_control_algorithm_comboBox.Items.Add("5. Многоуровневая очередь (2 уровня: высокий приоритет – Round robin, низкий приоритет – FCFS)");
            Memory_control_algorithm_comboBox.Items.Add("3. Страничное распределение памяти (страница – 1024 байт)");
            VSU_control_algorithm_comboBox.Items.Add("2. Непрерывное размещение файлов (Кластер – 512 байт)");

            int p = new int();
            Byte value = 12;

            DLL.WriteMemoryByte(ref p, value);

            //MessageBox.Show(DLL.ReadMemoryByte(ref p).ToString());
            
            Initialize_DataGrid();

            //Process_StatusBar.Items.Add(new Separator());
            //Process_StatusBar.Items.Add("hui");
            //MessageBox.Show(DLL.GetSectorSize().ToString());
        }

        private void Initialize_DataGrid()
        {

            //var _ds = new DataSet("Test");

            //employeeDataTable = _ds.Tables.Add("DT");
            //for (int i = 0; i < 10; i++)//create columns
            //{
            //    employeeDataTable.Columns.Add(i.ToString());
            //}

            //for (int i = 0; i < 50; i++)//fill data to rows
            //{
            //    var theRow = employeeDataTable.NewRow();
            //    for (int j = 0; j < 10; j++)
            //    {
            //        if (j % 2 == 0)
            //            theRow[j] = "a";
            //        else
            //            theRow[j] = "b";
            //    }
            //    employeeDataTable.Rows.Add(theRow);
            //}
            //Process_DataGrid.ItemsSource = employeeDataTable.AsDataView();

            DataGridTextColumn ProcessData = new DataGridTextColumn();
            ProcessData.Header = "Данные\nпроцесса";
            ProcessData.Binding = new Binding("ProcessData");
            ProcessData.MinWidth = 65;
            Process_DataGrid.Columns.Add(ProcessData);

            DataGridTextColumn AddressSpace = new DataGridTextColumn();
            AddressSpace.Header = "Адрс.\nпро-во";
            AddressSpace.Binding = new Binding("AddressSpace");
            AddressSpace.MinWidth = 50;
            Process_DataGrid.Columns.Add(AddressSpace);

            for(int i = 0; i < 50; i++)
            {
                DataGridTextColumn num = new DataGridTextColumn();
                num.Header = i+1;
                num.Binding = new Binding((i+1).ToString());
                Process_DataGrid.Columns.Add(num);
            }

            List<Process> processes = new List<Process>();
            for (int i = 0; i < 10; i++)
            {
                processes.Add(new Process() { ProcessData = "12345", AddressSpace = "78564" });
            }
            Process_DataGrid.Items.Add(processes[0]);



            //Process_DataGrid.ItemsSource = processes;
            //Memory_Process_DataGrid.Items.Clear();
            //Disk_Sector_DataGrid.Items.Clear();
            //Disk_Map_DataGrid.Items.Clear();
            //Disk_Catalog_DataGrid.Items.Clear();
            //Memory_Address_DataGrid.Items.Clear();
            //Memory_Map_DataGrid.Items.Clear();
            //Memory_Process_DataGrid.Items.Clear();
            //Process_DataGrid.Items.Clear();
        }
        void Process_DataGrid_LoadingRow(object sender, DataGridRowEventArgs e)
        {
            e.Row.Header = (e.Row.GetIndex() + 1).ToString();
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
        private void Sector_TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            ADD_LOG("Sector changed");
            Sector_TextBox.Text = string.Join("", Sector_TextBox.Text.Where(c => char.IsDigit(c)));
        }

        private void Sector_Increment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sector increment button click");
            string str = string.Join("", Sector_TextBox.Text.Where(c => char.IsDigit(c)));
            if (int.TryParse(str, out _))
            {
                Sector_TextBox.Text = (int.Parse(str) + 1).ToString();
            }
            else
            {
                MessageBox.Show("В поле сектор должно быть число", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Sector_Decrement_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Sector decrement button click");
            string str = string.Join("", Sector_TextBox.Text.Where(c => char.IsDigit(c)));
            if (int.TryParse(str, out _))
            {
                Sector_TextBox.Text = (int.Parse(str) - 1).ToString();
            }
            else
            {
                MessageBox.Show("В поле сектор должно быть число", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
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

        private void Address_TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            ADD_LOG("Address changed");
            Address_TextBox.Text = string.Join("", Address_TextBox.Text.Where(c => char.IsDigit(c)));
        }

        private void Address_Increment_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Address increment button click");
            string str = string.Join("", Address_TextBox.Text.Where(c => char.IsDigit(c)));
            if (int.TryParse(str, out _))
            {
                Address_TextBox.Text = (int.Parse(str) + 1).ToString();
            }
            else
            {
                MessageBox.Show("В поле адресс должно быть число", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Address_Decrement_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Address decrement button click");
            string str = string.Join("", Address_TextBox.Text.Where(c => char.IsDigit(c)));
            if (int.TryParse(str, out _))
            {
                Address_TextBox.Text = (int.Parse(str) - 1).ToString();
            }
            else
            {
                MessageBox.Show("В поле адресс должно быть число", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Address_Content_Button_Click(object sender, RoutedEventArgs e)
        {
            ADD_LOG("Address content button click");
        }

        private void ADD_LOG(string message)
        {
            if(Log_ListBox != null)
            {
                DLL.AddLog(message.ToCharArray(), message.Length);
                Log_ListBox.Items.Add(message);
                Log_ListBox.ScrollIntoView(Log_ListBox.Items[Log_ListBox.Items.Count - 1]);
            }
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
