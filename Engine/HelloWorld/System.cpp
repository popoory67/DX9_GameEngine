#include "System.h"
#include "Application.h"

//#include "MessageHeader.h"
//#include "Controller.h"

System* System::_instance = NULL;

System::System()
{
	_graphics	= new Graphics();
	_view		= new Camera();

	//_d3d11Render = new D3D11Renderer();
}


System::~System()
{
	if (_instance)
	{
		delete (_instance);
	}
}

System& System::Get()
{
	if (!_instance)
	{
		_instance = new System();
	}

	return *_instance;
}

bool System::Init()
{
	// ������ ������
	int screenWidth, screenHeight;

	screenWidth		= 0;
	screenHeight	= 0;

	// ������ �ʱ�ȭ
	InitWindows(screenWidth, screenHeight);

	// d3dx �ʱ�ȭ
	_graphics->Init(_hWnd);
	// ī�޶� �ʱ�ȭ
	_view->Init();

	//_d3d11Render->Init(_hWnd);

	// ��� ������Ʈ �ʱ�ȭ
	GameManager game;
	game.Start();
	//Controller* con = new Controller();
	//con->Init();
	//con->Update();

	return true;
}

void System::Release()
{
	_graphics->Release();

	//_d3d11Render->Release();

	ReleaseWindows();
}


void System::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
		}

		else
		{
			// render
			_graphics->RenderScene();
			//_d3d11Render->RenderScene();

			// ��� update �Լ� ȣ��
		}
	}
}


LRESULT CALLBACK System::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Ű���尡 Ű�� ���ȴ��� Ȯ���մϴ�.
		case WM_KEYDOWN:
		{
			// Ű�� ���ȴٸ� input��ü�� �� ����� �����Ͽ� ����ϵ��� �մϴ�.
			//m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Ű������ ���� Ű�� ���������� Ȯ���մϴ�.
		case WM_KEYUP:
		{
			// Ű�� �������ٸ� input��ü�� �� ����� �����Ͽ� �� Ű�� ��������մϴ�.
			//m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// �ٸ� �޼������� ������� �����Ƿ� �⺻ �޼��� ó���⿡ �����մϴ�.
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}

void System::InitWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX		wc;
	DEVMODE			dmScreenSettings;
	int				posX, posY;

	// �� ���ø����̼��� �ν��Ͻ��� �����ɴϴ�.
	_hInstance = GetModuleHandle(NULL);

	// ���ø����̼��� �̸��� �����մϴ�.
	_applicationName	= L"Ninetail Engine";

	// ������ Ŭ������ �⺻ �������� ����ϴ�.
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WindowProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= _hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm			= wc.hIcon;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= _applicationName;
	wc.cbSize			= sizeof(WNDCLASSEX);

	// ������ Ŭ������ ����մϴ�.
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� �˾ƿɴϴ�.
	screenWidth		= GetSystemMetrics(SM_CXSCREEN);
	screenHeight	= GetSystemMetrics(SM_CYSCREEN);

	// Ǯ��ũ�� ��� ������ ���� ���� ȭ�� ������ �մϴ�.
	if (FULL_SCREEN)
	{
		// ���� Ǯ��ũ�� ����� ȭ�� ũ�⸦ ����ũ�� ũ�⿡ ���߰� ������ 32bit�� �մϴ�.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize			= sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight	= (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel	= 32;
		dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Ǯ��ũ���� �´� ���÷��� ������ �մϴ�.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// �������� ��ġ�� ȭ���� ���� ���� ����ϴ�.
		posX = posY = 0;
	}

	else
	{
		// ������ ����� 800x600�� ũ�⸦ ������ �մϴ�.
		screenWidth		= 800;
		screenHeight	= 600;

		// â�� ������� �߾ӿ� ������ �մϴ�.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// ������ ���� ������ â�� ����� �� �ڵ��� �����ɴϴ�.
	_hWnd = CreateWindowEx(WS_EX_APPWINDOW, _applicationName, _applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, _hInstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �ݴϴ�.
	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);

	// ���콺 Ŀ���� ǥ������ �ʽ��ϴ�.
	ShowCursor(false);

	return;
}

void System::ReleaseWindows()
{
	// ���콺 Ŀ���� ǥ���մϴ�.
	ShowCursor(true);

	// Ǯ��ũ�� ��带 �������� �� ���÷��� ������ �ٲߴϴ�.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� �����մϴ�.
	DestroyWindow(_hWnd);
	_hWnd = NULL;

	// ���ø����̼� �ν��Ͻ��� �����մϴ�.
	UnregisterClass(_applicationName, _hInstance);
	_hInstance = NULL;

	return;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// �����찡 ���ŵǾ����� Ȯ���մϴ�.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// �����찡 �������� Ȯ���մϴ�.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// �ٸ� ��� �޼������� system Ŭ������ �޼��� ó���⿡ �����մϴ�.
		default:
		{
			return System::Get().MessageHandler(hWnd, message, wParam, lParam);
		}
	}
}