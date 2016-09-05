#pragma once

#include "CoreMacros.h"
#include "D3DXHeader.h"
#include "InputHeader.h"
#include "GameObjectHeader.h"

#include "CWinAPI.h"	// Header for changing "C" Windows API to "C++/CLI".
						// This declare should be located under the bottom.

#define FULL_SCREEN		SCREEN_MODE


class WindowSystem
{
public:

	~WindowSystem();

	static WindowSystem& Get();

public:

	bool Init();

	HWND Init( HINSTANCE applicationInstance, HWND hWndParent );

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

//
//HWND _hWnd;
//HINSTANCE _hInstance;
//
//LPCSTR _applicationName;
//
//extern "C"
//{
//	//bool Init();
//
//	void Run();
//
//	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
//
//	HWND InitWindows();
//
//	void DestroyWindows();
//
//	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
//
//	DLL_EXPORT HWND Init( HINSTANCE applicationInstance, HWND hWndParent );
//
//	DLL_EXPORT void Clear();
//}
//
