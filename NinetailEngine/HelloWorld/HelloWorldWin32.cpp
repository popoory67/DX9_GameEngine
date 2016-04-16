#include "Application.h"

LPSTR game_name = "hello world win32";

#define	SCREEN_XPOS		10
#define SCREEN_YPOS		10

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

struct ApplicationWin32
{
	HWND			hWnd;
	HINSTANCE		hInstance;
	WNDCLASSEX		wc;

	virtual LRESULT		WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void		Dispatch();
	int					SetupWindow(LPCSTR gamename);

	ApplicationWin32() : hInstance(0) {}

};

LRESULT ApplicationWin32::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int ApplicationWin32::SetupWindow(LPCSTR gamename)
{
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = gamename;

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx (
		NULL,
		gamename,
		gamename,
		WS_EX_TOPMOST | WS_POPUP,
		SCREEN_XPOS, SCREEN_YPOS,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	GameManager game;
	game.Init(hWnd);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
			game.Render();

		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);

	}

	game.Release();

	return msg.wParam;
}

void ApplicationWin32::Dispatch()
{

}

ApplicationWin32 window;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return window.WindowProcedure(hWnd, message, wParam, lParam);

}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	window.hInstance = hInstance;
	return window.SetupWindow(game_name);
}

