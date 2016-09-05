#pragma once

#include "RenderPCH.h"

#include "CoreMacros.h"
#include "D3DXHeader.h"
#include "InputHeader.h"
#include "GameObjectHeader.h"

#include "CWinAPI.h"	// Header for changing Windows API to usable one on "C++/CLI".
						// This declare should be located under the bottom.

#define FULL_SCREEN		SCREEN_MODE

extern "C"
{
	HWND _hWnd;
	HINSTANCE _hInstance;
	LPCSTR _applicationName;

	DLL_EXPORT HWND Init( HINSTANCE applicationInstance, HWND hWndParent );

	DLL_EXPORT void Clear();

	void Run();

	HWND InitWindows( HINSTANCE applicationInstance, HWND hWndParent );

	void DestroyWindows();

	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
}

