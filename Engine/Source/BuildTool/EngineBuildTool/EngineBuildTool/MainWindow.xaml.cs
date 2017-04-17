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

// Dispatcher
using System.Windows.Threading;
using System.Runtime.InteropServices;
using System.Security.Permissions;

// C/C++ Wrapping
using System.Windows.Interop;

// Lua
using NLua;

namespace EngineBuildTool
{
    public partial class MainWindow : Window
    {
        // D3D Render functions
        [DllImport( "WindowsApplication.dll", EntryPoint = "InitScene" )]
        private static extern IntPtr InitScene();

        [DllImport( "WindowsApplication.dll", EntryPoint = "Render" )]
        private static extern void Render();

        [DllImport( "WindowsApplication.dll", EntryPoint = "ReleaseScene" )]
        private static extern void ReleaseScene();

        //[DllImport( "WindowsApplication.dll", EntryPoint = "test" )]
        //private static extern void test();

        private IntPtr _scene;

        // Window scales
        private ScaleTransform _scale = new ScaleTransform();
        private double _width;
        private double _height;

        public MainWindow()
        {

            //test();
            //Lua lua = new Lua();
            //lua.DoFile( "../../NinetailEngine/test.lua" );
            //LuaFunction myFunction = lua["pp"] as LuaFunction;
            //myFunction.Call();

            d3dimg = new D3DImage();
            d3dimg.IsFrontBufferAvailableChanged
               += new DependencyPropertyChangedEventHandler( OnIsFrontBufferAvailableChanged );

            // begin rendering the custom D3D scene into the D3DImage
            BeginRenderingScene();

            InitializeComponent();

            //// test wpf
            //Button button = new Button();
            //button.Content = "0";
            //button.Name = "Button0";
            ////button.Height = 30;
            ////button.Width = 211;
            //button.RenderSize = new Size( 211, 30 );

            DataPanel.Children.Add( new Button() );

            // 화면 크기 조절
            this.Loaded += new RoutedEventHandler( WindowLoaded );
        }

        private void OnIsFrontBufferAvailableChanged( object sender, DependencyPropertyChangedEventArgs e )
        {
            // if the front buffer is available, then WPF has just created a new
            // D3D device, so we need to start rendering our custom scene
            if ( d3dimg.IsFrontBufferAvailable )
            {
                BeginRenderingScene();
            }

            else
            {
                // If the front buffer is no longer available, then WPF has lost its
                // D3D device so there is no reason to waste cycles rendering our
                // custom scene until a new device is created.
                StopRenderingScene();
            }
        }

        private void BeginRenderingScene()
        {
            if ( d3dimg.IsFrontBufferAvailable )
            {
                // create a custom D3D scene and get a pointer to its surface
                _scene = InitScene();

                // set the back buffer using the new scene pointer
                //d3dimg.Lock();
                //d3dimg.SetBackBuffer( D3DResourceType.IDirect3DSurface9, _scene );
                //d3dimg.Unlock();

                // leverage the Rendering event of WPF's composition target to
                // update the custom D3D scene
                CompositionTarget.Rendering += OnRendering;
            }
        }

        private void StopRenderingScene()
        {
            // This method is called when WPF loses its D3D device.
            // In such a circumstance, it is very likely that we have lost 
            // our custom D3D device also, so we should just release the scene.
            // We will create a new scene when a D3D device becomes 
            // available again.
            CompositionTarget.Rendering -= OnRendering;
            ReleaseScene();
            _scene = IntPtr.Zero;
        }

        private void OnRendering( object sender, EventArgs e )
        {
            // when WPF's composition target is about to render, we update our 
            // custom render target so that it can be blended with the WPF target
            UpdateScene();
        }

        private void UpdateScene()
        {
            if ( d3dimg.IsFrontBufferAvailable && _scene == IntPtr.Zero )
                return;
            
            
            // lock the D3DImage
            d3dimg.Lock();

            // set the back buffer using the new scene pointer
            d3dimg.SetBackBuffer( D3DResourceType.IDirect3DSurface9, _scene );

            // update the scene (via a call into our custom library)
            //SIZE size = new SIZE();
            Render();

            // invalidate the updated region of the D3DImage (in this case, the whole image)
            d3dimg.AddDirtyRect( new Int32Rect( 0, 0, 1280, 720 ) );

            // unlock the D3DImage
            d3dimg.Unlock();
        }


        // Functions to control window Size
        private void WindowSizeChanged( object sender, SizeChangedEventArgs e )
        {
            ChangeSize( e.NewSize.Width, e.NewSize.Height );
        }

        private void WindowLoaded( object sender, RoutedEventArgs e )
        {
            _width = this.Width;
            _height = this.Height; 

            if ( this.WindowState == System.Windows.WindowState.Maximized )
            {
                ChangeSize( this.ActualWidth, this.ActualHeight );
            }

            this.SizeChanged += new SizeChangedEventHandler( WindowSizeChanged );
        }

        private void ChangeSize( double width, double height )
        {
            _scale.ScaleX = width / _width;
            _scale.ScaleY = height / _height;

            FrameworkElement rootElement = this.Content as FrameworkElement;

            rootElement.LayoutTransform = _scale;
        }

    }
}
