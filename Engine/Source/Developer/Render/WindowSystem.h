#pragma once

#include "CoreMacros.h"
#include "D3DXHeader.h"
#include "SceneManager.h"

#define FULL_SCREEN		SCREEN_MODE


class WindowSystem
{
public:

	~WindowSystem();

	static WindowSystem& Get();

public:

	bool Init();

	void Clear();

	void Run();

	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

private:

	WindowSystem();

	HWND InitWindows();

	void DestroyWindows();

private:

	static WindowSystem* _instance;

	HWND _hWnd;
	HINSTANCE _hInstance;

	LPCSTR _applicationName;
};

static LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );