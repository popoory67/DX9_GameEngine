#pragma once

#include "InputHeader.h"

#include "D3D9Header.h"
#include "D3D11Header.h"

#define FULL_SCREEN				0

class System
{
public:

	~System();

	static System& Get();

	bool Init();

	void Clear();

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

	LPCSTR					_applicationName;

	// key input
	KeyInput*				_input;

	// d3d9
	Graphics*				_graphics;
	//Camera*					_camera;

	// d3d11
	//D3D11Renderer*			_d3d11Render;
};

static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);