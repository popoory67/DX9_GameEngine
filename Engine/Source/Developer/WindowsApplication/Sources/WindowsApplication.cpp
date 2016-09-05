#include "WindowsApplication.h"


namespace WindowsApplication
{
	WinApp::WinApp()
	{

	}

	WinApp::~WinApp()
	{

	}

	/*IntPtr WinApp::Init( IntPtr applicationInstance, IntPtr hWndParent )
	{
		HINSTANCE appInstance = static_cast<HINSTANCE>(applicationInstance.ToPointer());
		HWND hWnd = static_cast<HWND>(hWndParent.ToPointer());

		HWND ret = WindowSystem::Get().Init( appInstance, hWnd );
		
		return static_cast<IntPtr>(ret);
	}

	void WinApp::Clear()
	{
		WindowSystem::Get().Clear();
	}*/
}