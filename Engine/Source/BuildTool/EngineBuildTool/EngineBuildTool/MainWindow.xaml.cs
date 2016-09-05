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

using System.Windows.Interop;
using EngineBuildTool.View;

namespace EngineBuildTool
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            CreateRenderView();
        }

        private void CreateRenderView()
        {
            ViewHwndHost render = new ViewHwndHost();
            RenderView.Child = render;
        }
    }
}
