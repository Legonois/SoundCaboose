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
using System.Windows.Shapes;
using System.Diagnostics;
using Syncfusion;
using Syncfusion.Windows.Tools.Controls;
using Syncfusion.SfSkinManager;

namespace SoundCabooseWPFVersion
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private int iClicked;

        public MainWindow()
        {
            InitializeComponent();
            string style = "MaterialDarkRoyalBlue";
            SkinHelper styleInstance = null;
            var skinHelpterStr = "Syncfusion.Themes." + style + ".WPF." + style + "SkinHelper, Syncfusion.Themes." + style + ".WPF";
            Type skinHelpterType = Type.GetType(skinHelpterStr);
            if (skinHelpterType != null)
                styleInstance = Activator.CreateInstance(skinHelpterType) as SkinHelper;
            if (styleInstance != null)
            {
                SfSkinManager.RegisterTheme(style, styleInstance);
            }
            SfSkinManager.SetTheme(this, new Theme(style));

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
            if (WindowState == WindowState.Normal)
            {
                WindowState = WindowState.Maximized;
            }
            else
            {
                WindowState = WindowState.Normal;
            }

        }

        private void MinimizeBtn_Click(object sender, RoutedEventArgs e)
        {
            WindowState = WindowState.Minimized;
        }
    }
}
