#pragma once

#include <vcclr.h>
#include "WindowSystem.h"

using namespace System;
using namespace System::Windows;
using namespace System::Runtime::InteropServices;


namespace WindowsApplication 
{
	public ref class WinApp
	{
	public:		
		WinApp();
		virtual ~WinApp();

		//IntPtr Init( IntPtr applicationInstance, IntPtr hWndParent );

		//void Clear();

		//virtual HandleRef BuildWindowCore( HandleRef hwndParent ) override
		//{
		//	//Create our own window that is child of the WPF window and a parent to the video window
		//	//It allows us to more closly control the behaviour of the video window
		//	HWND handle = CreateWindowEx( 0, "Static",
		//								  NULL,
		//								  WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
		//								  0, 0, // x, y
		//								  20, 20, // height, width
		//								  (HWND)hwndParent.Handle.ToPointer(), // parent hwnd
		//								  0, // hmenu
		//								  0, // hinstance
		//								  0 ); // lparam

		//	//Return our created window
		//	return HandleRef( this, IntPtr( handle ) );
		//}

		IntPtr BuildWindowCore( IntPtr parentHandle ) override
		{
			//Create our own window that is child of the WPF window and a parent to the video window
			//It allows us to more closly control the behaviour of the video window
			HWND handle = CreateWindowEx( 0, "Static",
										  NULL,
										  WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
										  0, 0, // x, y
										  20, 20, // height, width
										  (HWND)parentHandle.ToPointer(), // parent hwnd
										  0, // hmenu
										  0, // hinstance
										  0 ); // lparam

			//Return our created window
			return static_cast<IntPtr>(handle);
		}

		virtual void DestroyWindowCore( HandleRef hwnd ) override
		{

		}

	};

}
