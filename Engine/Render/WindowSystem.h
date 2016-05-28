#pragma once

#include "InputHeader.h"
#include "D3D9Header.h"
#include "D3D11Header.h"
#include "GameObjectHeader.h"

#define FULL_SCREEN				0

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