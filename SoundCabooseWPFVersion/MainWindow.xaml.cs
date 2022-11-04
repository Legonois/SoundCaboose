using System;
using System.Collections.Generic;
using System.Linq;
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
//using System.Windows.Shapes;
using System.Diagnostics;
using Syncfusion;
using Syncfusion.Windows.Tools.Controls;
using Syncfusion.SfSkinManager;
using Syncfusion.Windows.PropertyGrid;
using SoundCabooseWPFVersion.code;
using SoundCabooseWPFVersion.CustomControls;
using NAudio;
using NAudio.Wave;
using NAudio.Utils;
using NAudio.Wave.SampleProviders;
using System.Threading;
using System.DirectoryServices;
using System.IO;
using Syncfusion.Windows.Shared;
using Syncfusion.Themes.MaterialDark.WPF;

namespace SoundCabooseWPFVersion
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            MaterialDarkThemeSettings materialDarkThemeSettings = new MaterialDarkThemeSettings();
            materialDarkThemeSettings.PrimaryBackground = new SolidColorBrush(Colors.Red);
            materialDarkThemeSettings.PrimaryForeground = new SolidColorBrush(Colors.Yellow);
            materialDarkThemeSettings.FontFamily = new FontFamily("Arial");
            materialDarkThemeSettings.BodyFontSize = 12;
            materialDarkThemeSettings.SubTitleFontSize = 14;
            string style = "MaterialDark";
            SfSkinManager.RegisterThemeSettings("MaterialDark", materialDarkThemeSettings);

            SfSkinManager.SetTheme(Main_view, new Theme() { ThemeName = "MaterialDark" });

            //string style = "MaterialDark";
            //SkinHelper? styleInstance = null;
            //string skinHelpterStr = "Syncfusion.Themes." + style + ".WPF." + style + "SkinHelper, Syncfusion.Themes." + style + ".WPF";
            //Type? skinHelpterType = Type.GetType(skinHelpterStr);
            //if (skinHelpterType != null)
            //    styleInstance = Activator.CreateInstance(skinHelpterType) as SkinHelper;
            //if (styleInstance != null)
            //{
            //    SfSkinManager.RegisterTheme(style, styleInstance);
            //}
            //SfSkinManager.SetTheme(this, new Theme(style));

            // old style MaterialDark
            // new style MaterialDarkRoyalBlue

            //DockingManager dockingManager = new DockingManager();

            //ContentControl SolutionExplorer = new ContentControl();
            //ContentControl ToolBox = new ContentControl();
            //ContentControl Properties = new ContentControl();
            //ContentControl Output = new ContentControl();
            //ContentControl StartPage = new ContentControl();

            ////Add content controls as child of DockingManager

            //dockingManager.Children.Add(SolutionExplorer);
            //dockingManager.Children.Add(ToolBox);
            //dockingManager.Children.Add(Properties);
            //dockingManager.Children.Add(Output);
            //dockingManager.Children.Add(StartPage);

            //this.Content = dockingManager;
            Control soundEditor = new CustomControls.SoundEditor();

            soundEditor.BeginInit();
            soundEditor.EndInit();
        }

        private void Grid_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();

            Debug.WriteLine("something");
        }

        private void CloseBtn_Click(object sender, RoutedEventArgs e)
        {
            Button? b = sender as Button;
            Close();


        }

        private void MaximizeBtn_Click(object sender, RoutedEventArgs e)
        {

            Button? maximizeBtn = sender as Button;

            

            if (WindowState == WindowState.Normal && maximizeBtn != null)
            {
                maximizeBtn.Content = "";
                WindowState = WindowState.Maximized;
            }
            else if(maximizeBtn != null)
            {
                maximizeBtn.Content = "";
                WindowState = WindowState.Normal;
            }

        }

        private void MinimizeBtn_Click(object sender, RoutedEventArgs e)
        {
            WindowState = WindowState.Minimized;
        }

        //private void LoadBtn_Click(object sender, RoutedEventArgs e)
        //{
        //    string dockSavePath = Path.Combine(Appdata.FolderPath, "me.xaml");

        //    MainDockingManager.LoadDockState(dockSavePath);
        //}

        //private void Button_Click(object sender, RoutedEventArgs e)
        //{
        //    string dockSavePath = Path.Combine(Appdata.FolderPath, "me.xaml");

        //    MainDockingManager.SaveDockState(dockSavePath);
        //}

        private async void Button_Click_1(object sender, RoutedEventArgs e)
        {

            ////DSPlayWavetype.
            //int Frequency = int.Parse(FrequencyTxtBox.Text);

            //string WaveType = DSPlayWavetype.Text;

            //string FullType = "SignalGeneratorType." + WaveType;

            //ISampleProvider? sine20Seconds = new SignalGenerator()
            //{
            //    Gain = 0.05,
            //    Frequency = Frequency,
            //    Type = SignalGeneratorType.Sin
            //}
            //.Take(TimeSpan.FromSeconds(1.5));
            //using (WaveOutEvent? wo = new WaveOutEvent())
            //{
            //    wo.Init(sine20Seconds);
            //    wo.Play();
            //    while (wo.PlaybackState == PlaybackState.Playing)
            //    {
            //        await Task.Delay(500);
            //    }
            //}

            //float volume = (float)(VolumeSlider.Value / 100);

            //float frequency = float.Parse(FrequencyTxtBox.Text);

            //SoundBackend.StartStopSineWave(frequency, volume, 44100, 1, (SoundBackend.WaveType)DSPlayWavetype.SelectedIndex);
        }

        private void CreateUserDataFolder_Click(object sender, RoutedEventArgs e)
        {
            Appdata.CreateUserDataFolder();
        }
    }



    public class Appdata
    {
        public static string FolderPath = string.Empty;

        public static void CreateUserDataFolder()
        {
            // The folder for the roaming current user 
            string folder = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);

            // Combine the base folder with your specific folder....
            string specificFolder = System.IO.Path.Combine(folder, "SoundCaboose");

            // CreateDirectory will check if every folder in path exists and, if not, create them.
            // If all folders exist then CreateDirectory will do nothing.
            Directory.CreateDirectory(specificFolder);

            // Set FolderPath
            FolderPath = specificFolder;

        }
    }







        //    dockingManager2.PersistState = true;
        //    }

        //private void CoolDockingLoad(object sender, RoutedEventArgs e)
        //{
        //    dockingManager2.LoadDockState("C:/Users/wesle/Downloads/me.xaml");

        //    dockingManager2.SaveDockState("C:/Users/wesle/Downloads/me.xaml");
        //}






    public class Employee
    {
        public string WaveType { get; set; }
        public int Frequency { get; set; }
        public double Amlplitude { get; set; }
    }

    public class ViewModel
    {
        public object SelectedEmployee { get; set; }
        public ViewModel()
        {
            SelectedEmployee = new Employee()
            {
                WaveType = "Sine",
                Frequency = 25,
                Amlplitude = .2342,
            };
        }
    }
    
}
