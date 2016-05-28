#include "RenderPCH.h"
#include "WindowSystem.h"

WindowSystem* WindowSystem::_instance = NULL;

WindowSystem::WindowSystem()
{

}


WindowSystem::~WindowSystem()
{
	if (_instance)
	{
		SAFE_DELETE (_instance);
	}
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
	int screenWidth = 0, screenHeight = 0;

	// window initialization
	InitWindows(screenWidth, screenHeight);

	// d3d9 initialization
	Graphics::Get().Init(_hWnd);

	return true;
}

void WindowSystem::Clear()
{
	Graphics::Get().Clear();

	ReleaseWindows();
}


void WindowSystem::Run()
{
	// all game initialization
	GameObjectManager::Get().InitGame();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true) //msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			if (KEY_INPUT.IsKeyDown(VK_ESCAPE))
			{
				PostMessage(_hWnd, WM_DESTROY, 0, 0);
				return;
			}

			// render
			Graphics::Get().RenderScene();
			//_d3d11Render->RenderScene();

			// call all update function.
			GameObjectManager::Get().RunUpdate();
		}
	}
}


LRESULT CALLBACK WindowSystem::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Ű���尡 Ű�� ���ȴ��� Ȯ��
		case WM_KEYDOWN:
		{
			KEY_INPUT.KeyDown((unsigned int)wParam);
			return 0;
		}

		// Ű������ ���� Ű�� ���������� Ȯ��
		case WM_KEYUP:
		{
			KEY_INPUT.KeyUp((unsigned int)wParam);
			return 0;
		}

		// �ٸ� �޼������� ������� �����Ƿ� �⺻ �޼��� ó���⿡ ����
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}

void WindowSystem::InitWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX		wc;
	DEVMODE			dmScreenSettings;
	int				posX, posY;

	// �� ���ø����̼��� �ν��Ͻ��� ������
	_hInstance = GetModuleHandle(NULL);

	// ���ø����̼��� �̸��� ����
	_applicationName	= "Ninetail Engine";

	// ������ Ŭ������ �⺻ �������� ����
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

	// ������ Ŭ������ ���
	RegisterClassEx(&wc);

	// ����� ȭ���� �ػ󵵸� �˾ƿ�
	screenWidth		= GetSystemMetrics(SM_CXSCREEN);
	screenHeight	= GetSystemMetrics(SM_CYSCREEN);

	// Ǯ��ũ�� ��� ������ ���� ���� ȭ�� ����
	if (FULL_SCREEN)
	{
		// ���� Ǯ��ũ�� ����� ȭ�� ũ�⸦ ����ũ�� ũ�⿡ ���߰� ������ 32bit�� ����
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize			= sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight	= (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel	= 32;
		dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Ǯ��ũ���� �´� ���÷��� ����
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// �������� ��ġ�� ȭ���� ���� ���� ����
		posX = posY = 0;
	}

	else
	{
		// ������ ����� 800x600�� ũ�⸦ ������ �մϴ�
		screenWidth		= 800;
		screenHeight	= 600;

		// â�� ������� �߾ӿ� ������ �մϴ�
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// ������ ���� ������ â�� ����� �� �ڵ��� �����ɴϴ�
	_hWnd = CreateWindowEx(WS_EX_APPWINDOW, _applicationName, _applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, _hInstance, NULL);

	// �����츦 ȭ�鿡 ǥ���ϰ� ��Ŀ���� �ݴϴ�
	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);

	// ���콺 Ŀ���� ǥ������ �ʽ��ϴ�
	ShowCursor(false);

	return;
}

void WindowSystem::ReleaseWindows()
{
	// ���콺 Ŀ���� ǥ���մϴ�
	ShowCursor(true);

	// Ǯ��ũ�� ��带 �������� �� ���÷��� ������ �ٲߴϴ�
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� �����մϴ�
	DestroyWindow(_hWnd);
	_hWnd = NULL;

	// ���ø����̼� �ν��Ͻ��� �����մϴ�
	UnregisterClass(_applicationName, _hInstance);
	_hInstance = NULL;

	return;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// �����찡 ���ŵǾ����� Ȯ���մϴ�
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// �����찡 �������� Ȯ���մϴ�
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// �ٸ� ��� �޼������� system Ŭ������ �޼��� ó���⿡ �����մϴ�
		default:
		{
			return WindowSystem::Get().MessageHandler(hWnd, message, wParam, lParam);
		}
	}
}