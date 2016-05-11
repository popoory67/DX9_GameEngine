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
	// 윈도우 사이즈
	int screenWidth, screenHeight;

	screenWidth		= 0;
	screenHeight	= 0;

	// 윈도우 초기화
	InitWindows(screenWidth, screenHeight);

	// d3dx 초기화
	_graphics->Init(_hWnd);
	// 카메라 초기화
	_view->Init();

	//_d3d11Render->Init(_hWnd);

	// 모든 오브젝트 초기화
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

			// 모든 update 함수 호출
		}
	}
}


LRESULT CALLBACK System::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// 키보드가 키가 눌렸는지 확인합니다.
		case WM_KEYDOWN:
		{
			// 키가 눌렸다면 input객체에 이 사실을 전달하여 기록하도록 합니다.
			//m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}

		// 키보드의 눌린 키가 떼어졌는지 확인합니다.
		case WM_KEYUP:
		{
			// 키가 떼어졌다면 input객체에 이 사실을 전달하여 이 키를 해제토록합니다.
			//m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}

		// 다른 메세지들은 사용하지 않으므로 기본 메세지 처리기에 전달합니다.
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

	// 이 어플리케이션의 인스턴스를 가져옵니다.
	_hInstance = GetModuleHandle(NULL);

	// 어플리케이션의 이름을 설정합니다.
	_applicationName	= L"Ninetail Engine";

	// 윈도우 클래스를 기본 설정으로 맞춥니다.
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

	// 윈도우 클래스를 등록합니다.
	RegisterClassEx(&wc);

	// 모니터 화면의 해상도를 알아옵니다.
	screenWidth		= GetSystemMetrics(SM_CXSCREEN);
	screenHeight	= GetSystemMetrics(SM_CYSCREEN);

	// 풀스크린 모드 변수의 값에 따라 화면 설정을 합니다.
	if (FULL_SCREEN)
	{
		// 만약 풀스크린 모드라면 화면 크기를 데스크톱 크기에 맞추고 색상을 32bit로 합니다.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

		dmScreenSettings.dmSize			= sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight	= (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel	= 32;
		dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 풀스크린에 맞는 디스플레이 설정을 합니다.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// 윈도우의 위치를 화면의 왼쪽 위로 맞춥니다.
		posX = posY = 0;
	}

	else
	{
		// 윈도우 모드라면 800x600의 크기를 가지게 합니다.
		screenWidth		= 800;
		screenHeight	= 600;

		// 창을 모니터의 중앙에 오도록 합니다.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// 설정한 것을 가지고 창을 만들고 그 핸들을 가져옵니다.
	_hWnd = CreateWindowEx(WS_EX_APPWINDOW, _applicationName, _applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, _hInstance, NULL);

	// 윈도우를 화면에 표시하고 포커스를 줍니다.
	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);

	// 마우스 커서를 표시하지 않습니다.
	ShowCursor(false);

	return;
}

void System::ReleaseWindows()
{
	// 마우스 커서를 표시합니다.
	ShowCursor(true);

	// 풀스크린 모드를 빠져나올 때 디스플레이 설정을 바꿉니다.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// 창을 제거합니다.
	DestroyWindow(_hWnd);
	_hWnd = NULL;

	// 어플리케이션 인스턴스를 제거합니다.
	UnregisterClass(_applicationName, _hInstance);
	_hInstance = NULL;

	return;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// 윈도우가 제거되었는지 확인합니다.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// 윈도우가 닫히는지 확인합니다.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// 다른 모든 메세지들은 system 클래스의 메세지 처리기에 전달합니다.
		default:
		{
			return System::Get().MessageHandler(hWnd, message, wParam, lParam);
		}
	}
}