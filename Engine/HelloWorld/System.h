#pragma once

#include "RenderHeader.h"

#define FULL_SCREEN				0

class System
{
public:

	~System();

	static System& Get();

	bool Init();

	void Release();

	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:

	System();

	void InitWindows(int&, int&);

	void ReleaseWindows();

private:

	static System*			_instance;

	HWND					_hWnd;
	HINSTANCE				_hInstance;
	WNDCLASSEX				_wc;

	LPCWSTR					_applicationName;

	Graphics*				_graphics;
	Camera*					_view;
};

static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);