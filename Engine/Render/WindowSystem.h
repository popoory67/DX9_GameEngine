#pragma once

#include "D3DXHeader.h"

#include "InputHeader.h"
#include "GameObjectHeader.h"

#define FULL_SCREEN SCREEN_MODE

class WindowSystem
{
public:

	~WindowSystem();

	static WindowSystem& Get();

public:

	bool Init();

	void Clear();

	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:

	WindowSystem();

	void InitWindows(int& screenWidth, int& screenHeight);

	void ReleaseWindows();

private:

	static WindowSystem* _instance;

	HWND _hWnd;
	HINSTANCE _hInstance;

	LPCSTR _applicationName;
};

static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);