#include "RenderPCH.h"
#include "WindowSystem.h"

WindowSystem* WindowSystem::_instance = NULL;

WindowSystem::WindowSystem()
{

}


WindowSystem::~WindowSystem()
{
	SAFE_DELETE( _instance );
}

WindowSystem& WindowSystem::Get()
{
	if (!_instance)
	{
		_instance = new WindowSystem();
	}

	return *_instance;
}

bool WindowSystem::Init()
{
	// window size
	int screenWidth = 0;
	int screenHeight = 0;

	// window initialization
	InitWindows( screenWidth, screenHeight );

	// d3d9 initialization
#if (_D3DX_VERSION <= 9)
	D3D9Renderer::Get()->Init( _hWnd );
#else
	D3D11Renderer::Get()->Init( _hWnd );
#endif

	return true;
}

void WindowSystem::Clear()
{
	ReleaseWindows();
}


void WindowSystem::Run()
{
	// all game initialization
	GameObjectManager::Get().InitGame();

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while (true) //msg.message != WM_QUIT)
	{
		if (PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		else
		{
			if (KEY_INPUT.IsKeyDown( VK_ESCAPE ))
			{
				PostMessage( _hWnd, WM_DESTROY, 0, 0 );
				return;
			}

			// render
#if (_D3DX_VERSION <= 9)
			D3D9Renderer::Get()->RenderScene();
#else
			D3D11Renderer::Get()->RenderScene();
#endif

			// call all update function.
			GameObjectManager::Get().RunUpdate();
		}
	}
}


LRESULT CALLBACK WindowSystem::MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
		// 키보드가 키가 눌렸는지 확인
		case WM_KEYDOWN:
		{
			KEY_INPUT.KeyDown( (unsigned int)wParam );
			return 0;
		}

		// 키보드의 눌린 키가 떼어졌는지 확인
		case WM_KEYUP:
		{
			KEY_INPUT.KeyUp( (unsigned int)wParam );
			return 0;
		}

		// 다른 메세지들은 사용하지 않으므로 기본 메세지 처리기에 전달
		default:
		{
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
	}
}

void WindowSystem::InitWindows( int& screenWidth, int& screenHeight )
{
	WNDCLASSEX		wc;
	DEVMODE			dmScreenSettings;
	int				posX, posY;

	// 이 어플리케이션의 인스턴스를 가져옴
	_hInstance = GetModuleHandle( NULL );

	// 어플리케이션의 이름을 설정
	_applicationName = "Ninetail Engine";

	// 윈도우 클래스를 기본 설정으로 맞춤
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
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

	// WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP
	// 설정한 것을 가지고 창을 만들고 그 핸들을 가져옵니다
	_hWnd = CreateWindowEx( WS_EX_APPWINDOW, _applicationName, _applicationName,
							WS_OVERLAPPEDWINDOW,
							posX, posY, screenWidth, screenHeight, NULL, NULL, _hInstance, NULL );

	// 윈도우를 화면에 표시하고 포커스를 줍니다
	ShowWindow( _hWnd, SW_SHOW );
	SetForegroundWindow( _hWnd );
	SetFocus( _hWnd );

	// 마우스 커서 (표시 : true)
	ShowCursor( true );

	return;
}

void WindowSystem::ReleaseWindows()
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

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
		// 윈도우가 제거되었는지 확인합니다
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
		}

		// 윈도우가 닫히는지 확인합니다
		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			return 0;
		}

		// 다른 모든 메세지들은 system 클래스의 메세지 처리기에 전달합니다
		default:
		{
			return WindowSystem::Get().MessageHandler( hWnd, message, wParam, lParam );
		}
	}
}