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
	HWND _hWnd = nullptr;

	HINSTANCE _hInstance = nullptr;

	LPCSTR _applicationName;

	// D3D Render
	DLL_EXPORT void* WINAPI InitScene();

	DLL_EXPORT void Render();

	DLL_EXPORT void ReleaseScene();

	HWND InitWindows();

	void DestroyWindows();

	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
}

