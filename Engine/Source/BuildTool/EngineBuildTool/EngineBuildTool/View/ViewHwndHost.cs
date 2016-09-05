using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Windows;
using System.Windows.Interop;
using System.Windows.Input;
using System.Windows.Media;
using System.Runtime.InteropServices;


namespace EngineBuildTool.View
{
    public class ViewHwndHost : HwndHost
    {
        // Create Win32 window
        [DllImport( "WindowsApplication.dll", EntryPoint = "Init", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl )]
        private static extern IntPtr Init( IntPtr applicationInstance, IntPtr hWndParent );

        // Destroy winodw  
        [DllImport( "WindowsApplication.dll", EntryPoint = "Clear", CallingConvention = CallingConvention.Cdecl )]
        private static extern void Clear();

        protected override HandleRef BuildWindowCore( HandleRef hwndParent )
        {
            // marshaling
            IntPtr instanceHandle = Marshal.GetHINSTANCE( System.Reflection.Assembly.GetExecutingAssembly().GetModules()[0] );
            IntPtr hwndHost = Init( instanceHandle, hwndParent.Handle );

            return new HandleRef( this, hwndHost );
        }

        protected override void DestroyWindowCore( HandleRef hwnd )
        {
            Clear();
        }
    }
}
