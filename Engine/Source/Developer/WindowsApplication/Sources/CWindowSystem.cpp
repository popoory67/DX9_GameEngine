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


		// �ν��Ͻ��� ������
		_hInstance = GetModuleHandle( NULL );

		// ���ø����̼��� �̸��� ����
		_applicationName = "Ninetail Engine";

		// ������ Ŭ������ �⺻ �������� ����
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

		// ������ Ŭ������ ���
		RegisterClassEx( &wc );

		// window size
		int screenWidth = 0;
		int screenHeight = 0;

		// ����� ȭ���� �ػ󵵸� �˾ƿ�
		screenWidth = GetSystemMetrics( SM_CXSCREEN );
		screenHeight = GetSystemMetrics( SM_CYSCREEN );

		// Ǯ��ũ�� ��� ������ ���� ���� ȭ�� ����
		if (FULL_SCREEN)
		{
			// ���� Ǯ��ũ�� ����� ȭ�� ũ�⸦ ����ũ�� ũ�⿡ ���߰� ������ 32bit�� ����
			memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );

			dmScreenSettings.dmSize = sizeof( dmScreenSettings );
			dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Ǯ��ũ���� �´� ���÷��� ����
			ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN );

			// �������� ��ġ�� ȭ���� ���� ���� ����
			posX = posY = 0;
		}

		else
		{
			// ������ ����� 800x600�� ũ�⸦ ������ �մϴ�
			screenWidth = 800;
			screenHeight = 600;

			// â�� ������� �߾ӿ� ������ �մϴ�
			posX = (GetSystemMetrics( SM_CXSCREEN ) - screenWidth) / 2;
			posY = (GetSystemMetrics( SM_CYSCREEN ) - screenHeight) / 2;
		}

		// ������ ���� ������ â�� ����� �� �ڵ��� �����ɴϴ�
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
		// ���콺 Ŀ���� ǥ���մϴ�
		ShowCursor( true );

		// Ǯ��ũ�� ��带 �������� �� ���÷��� ������ �ٲߴϴ�
		if (FULL_SCREEN)
		{
			ChangeDisplaySettings( NULL, 0 );
		}

		// â�� �����մϴ�
		DestroyWindow( _hWnd );
		_hWnd = NULL;

		// ���ø����̼� �ν��Ͻ��� �����մϴ�
		UnregisterClass( _applicationName, _hInstance );
		_hInstance = NULL;

		return;
	}

	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
}