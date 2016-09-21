#include "CWindowSystem.h"
#include "Application.h"

extern "C"
{

	void* WINAPI InitScene()
	{
		_hWnd = InitWindows();

#if (CHECK_DX_VERSION == 9) //D3DX_VERSION_9)
		D3D9Renderer::Get()->Init( _hWnd );
#else
		D3D11Renderer::Get()->RenderScene();
#endif

		// Get d3d surface
		auto d3dSurface = D3D9_INSTANCE->UseBuildRenderView( true );

		// test
		GameObjectPtr game( new GameManager() );
		GameObjectManager::Get().AddGame( game );

		// All game initialization
		GameObjectManager::Get().InitGame();

		return d3dSurface;
	}

	void Render()
	{

#if (CHECK_DX_VERSION == 9) //D3DX_VERSION_9)
		D3D9Renderer::Get()->RenderScene();
#else
		D3D11Renderer::Get()->RenderScene();
#endif

		// call all update function.
		GameObjectManager::Get().RunUpdate();
	}

	void ReleaseScene()
	{
		DestroyWindows();
	}


//	void Run()
//	{
//		// all game initialization
//		GameObjectManager::Get().InitGame();
//
//		MSG msg;
//		ZeroMemory( &msg, sizeof( msg ) );
//
//		while (true) //msg.message != WM_QUIT)
//		{
//			if (PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
//			{
//				TranslateMessage( &msg );
//				DispatchMessage( &msg );
//			}
//
//			else
//			{
//				if (KEY_INPUT.IsKeyDown( VK_ESCAPE ))
//				{
//					PostMessage( _hWnd, WM_DESTROY, 0, 0 );
//					return;
//				}
//
//				// render
//#if (CHECK_D3DX_VERSION == 0)//D3DX_VERSION_9)
//				D3D9Renderer::Get()->RenderScene();
//#else
//				D3D11Renderer::Get()->RenderScene();
//#endif
//
//				// call all update function.
//				GameObjectManager::Get().RunUpdate();
//			}
//		}
//	}

	HWND InitWindows()
	{
		WNDCLASSEX		wc;
		DEVMODE			dmScreenSettings;
		int				posX, posY;


		// 인스턴스를 가져옴
		_hInstance = GetModuleHandle( NULL );

		// 어플리케이션의 이름을 설정
		_applicationName = "Ninetail Engine";

		// 윈도우 클래스를 기본 설정으로 맞춤
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = MessageHandler;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hInstance;
		wc.hIcon = LoadIcon( NULL, IDI_WINLOGO );
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
		wc.lpszMenuName = NULL;
		wc.lpszClassName = _applicationName;
		wc.cbSize = sizeof( WNDCLASSEX );

		// 윈도우 클래스를 등록
		RegisterClassEx( &wc );

		// window size
		int screenWidth = 0;
		int screenHeight = 0;

		// 모니터 화면의 해상도를 알아옴
		screenWidth = GetSystemMetrics( SM_CXSCREEN );
		screenHeight = GetSystemMetrics( SM_CYSCREEN );

		// 풀스크린 모드 변수의 값에 따라 화면 설정
		if (FULL_SCREEN)
		{
			// 만약 풀스크린 모드라면 화면 크기를 데스크톱 크기에 맞추고 색상을 32bit로 설정
			memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );

			dmScreenSettings.dmSize = sizeof( dmScreenSettings );
			dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// 풀스크린에 맞는 디스플레이 설정
			ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN );

			// 윈도우의 위치를 화면의 왼쪽 위로 맞춤
			posX = posY = 0;
		}

		else
		{
			// 윈도우 모드라면 800x600의 크기를 가지게 합니다
			screenWidth = 800;
			screenHeight = 600;

			// 창을 모니터의 중앙에 오도록 합니다
			posX = (GetSystemMetrics( SM_CXSCREEN ) - screenWidth) / 2;
			posY = (GetSystemMetrics( SM_CYSCREEN ) - screenHeight) / 2;
		}

		// 설정한 것을 가지고 창을 만들고 그 핸들을 가져옵니다
		_hWnd = CreateWindowEx( WS_EX_APPWINDOW, 
								_applicationName, _applicationName,
								WS_OVERLAPPEDWINDOW,
								posX, posY,
								screenWidth, screenHeight,
								NULL,
								NULL,
								_hInstance,
								NULL );

		return _hWnd;
	}

	void DestroyWindows()
	{
		// 마우스 커서를 표시합니다
		ShowCursor( true );

		// 풀스크린 모드를 빠져나올 때 디스플레이 설정을 바꿉니다
		if (FULL_SCREEN)
		{
			ChangeDisplaySettings( NULL, 0 );
		}

		// 창을 제거합니다
		DestroyWindow( _hWnd );
		_hWnd = NULL;

		// 어플리케이션 인스턴스를 제거합니다
		UnregisterClass( _applicationName, _hInstance );
		_hInstance = NULL;

		return;
	}

	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
}