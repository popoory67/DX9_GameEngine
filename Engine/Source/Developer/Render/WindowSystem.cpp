#include "RenderPCH.h"
#include "WindowSystem.h"
#include "DXVersion.h"
#include "KeyInput.h"
#include "Thread.h"


WindowSystem* WindowSystem::_instance = nullptr;

WindowSystem::WindowSystem() : _hWnd(nullptr)
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
	// window initialization
	_hWnd = InitWindows();

	if (!_hWnd)
	{
		return false;
	}

	// d3d9 initialization
#if (CHECK_DX_VERSION == DX_9)
	D3D9Renderer::Get()->Init( _hWnd );
#elif (CHECK_DX_VERSION == DX_11)
	D3D11Renderer::Get()->Init( _hWnd );
#endif

	// all game initialization
	SceneManager::Get().InitScene();

	return true;

}

void WindowSystem::Clear()
{
	DestroyWindows();
}

void WindowSystem::Run()
{
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	Thread* renderThread = Thread::Create([]()
	{
		while (true)
		{
#if (CHECK_DX_VERSION == DX_9)
			D3D9Renderer::Get()->RenderScene();
#elif (CHECK_DX_VERSION == DX_11)
			D3D11Renderer::Get()->RenderScene();
#endif
		}
	});

	Thread* updateThread = Thread::Create([]()
	{
		while (true)
		{
			SceneManager::Get().UpdateScene();
		}
	});

	while (true)
	{
		if (KEY_INPUT.IsKeyDown(VK_ESCAPE))
		{
			updateThread->Detach();
			SAFE_DELETE(updateThread);

			renderThread->Detach();
			SAFE_DELETE(renderThread);

			PostMessage(_hWnd, WM_DESTROY, 0, 0);
			return;
		}

		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//renderThread->Update();
	//updateThread->Update();
}


LRESULT CALLBACK WindowSystem::MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
		// Ű���尡 Ű�� ���ȴ��� Ȯ��
		case WM_KEYDOWN:
		{
			KEY_INPUT.KeyDown( (unsigned int)wParam );
			return 0;
		}

		// Ű������ ���� Ű�� ���������� Ȯ��
		case WM_KEYUP:
		{
			KEY_INPUT.KeyUp( (unsigned int)wParam );
			return 0;
		}

		// �ٸ� �޼������� ������� �����Ƿ� �⺻ �޼��� ó���⿡ ����
		default:
		{
			return DefWindowProc( hWnd, message, wParam, lParam );
		}
	}
}

HWND WindowSystem::InitWindows()
{
	WNDCLASSEX		wc;
	DEVMODE			dmScreenSettings;
	int				posX, posY;

	// �� ���ø����̼��� �ν��Ͻ��� ������
	_hInstance = GetModuleHandle( NULL );

	// ���ø����̼��� �̸��� ����
	_applicationName = "Ninetail Engine";

	// ������ Ŭ������ �⺻ �������� ����
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

	// ������ Ŭ������ ���
	RegisterClassEx( &wc );

	// window size
	int screenWidth = 0;
	int screenHeight = 0;

	// ����� ȭ���� �ػ󵵸� �˾ƿ�
	screenWidth = GetSystemMetrics( SM_CXSCREEN );
	screenHeight = GetSystemMetrics( SM_CYSCREEN );

	// Ǯ��ũ�� ��� ������ ���� ���� ȭ�� ����
	if (SCREEN_MODE)
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

	// WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP
	// ������ ���� ������ â�� ����� �� �ڵ��� �����ɴϴ�
	HWND hWnd = CreateWindowEx( WS_EX_APPWINDOW, _applicationName, _applicationName,
								WS_OVERLAPPEDWINDOW,
								posX, posY, screenWidth, screenHeight, NULL, NULL, _hInstance, NULL );

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �ݴϴ�
	ShowWindow( hWnd, SW_SHOW );
	SetForegroundWindow( hWnd );
	SetFocus( hWnd );

	// ���콺 Ŀ�� (ǥ�� : true)
	ShowCursor( true );


	return hWnd;
}

void WindowSystem::DestroyWindows()
{
	// ���콺 Ŀ���� ǥ���մϴ�
	ShowCursor( true );

	// Ǯ��ũ�� ��带 �������� �� ���÷��� ������ �ٲߴϴ�
	if (SCREEN_MODE)
	{
		ChangeDisplaySettings( NULL, 0 );
	}

	// â�� �����մϴ�
	DestroyWindow( _hWnd );
	_hWnd = NULL;

	// ���ø����̼� �ν��Ͻ��� �����մϴ�
	UnregisterClass( _applicationName, _hInstance );
	_hInstance = NULL;
}

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
		// �����찡 ���ŵǾ����� Ȯ���մϴ�
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			return 0;
		}

		// �����찡 �������� Ȯ���մϴ�
		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			return 0;
		}

		// �ٸ� ��� �޼������� system Ŭ������ �޼��� ó���⿡ �����մϴ�
		default:
		{
			return WindowSystem::Get().MessageHandler( hWnd, message, wParam, lParam );
		}
	}
}