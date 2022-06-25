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
    }
}
