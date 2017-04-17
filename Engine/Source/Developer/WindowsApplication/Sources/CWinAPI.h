/**
 * This is header make to use WinAPI is made into C on C++/CLI.
 */
#pragma once

#include <Windows.h>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace System::Runtime::InteropServices;


[DllImport( "user32.dll" )]
WINUSERAPI BOOL WINAPI ShowWindow( _In_ HWND hWnd, _In_ int nCmdShow );

[DllImport( "user32.dll" )]
WINUSERAPI BOOL WINAPI DestroyWindow( _In_ HWND hWnd );

[DllImport( "user32.dll" )]
WINUSERAPI int WINAPI GetSystemMetrics( _In_ int nIndex );

//[DllImport( "user32.dll" )]
//#ifdef UNICODE
//WINUSERAPI uint WINAPI MessageBoxW( _In_opt_ HWND hWnd, _In_opt_ LPCWSTR lpText, _In_opt_ LPCWSTR lpCaption, _In_ UINT uType );
//#define MessageBox  MessageBoxW
//#else
//WINUSERAPI int WINAPI MessageBoxA( _In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType );
//#define MessageBox  MessageBoxA
//#endif // !UNICODE

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI BOOL WINAPI PeekMessageW( _Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax, _In_ UINT wRemoveMsg );
#else
WINUSERAPI BOOL WINAPI PeekMessageA( _Out_ LPMSG lpMsg, _In_opt_ HWND hWnd, _In_ UINT wMsgFilterMin, _In_ UINT wMsgFilterMax, _In_ UINT wRemoveMsg );
#endif // !UNICODE

[DllImport( "user32.dll" )]
#ifdef UNICODE WINUSERAPI BOOL WINAPI PostMessageW( _In_opt_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam );
#else
WINUSERAPI BOOL WINAPI PostMessageA( _In_opt_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam );
#endif // !UNICODE

[DllImport( "user32.dll" )]
WINUSERAPI BOOL WINAPI TranslateMessage( _In_ CONST MSG *lpMsg );

[DllImport( "user32.dll" )]
WINUSERAPI HWND WINAPI SetFocus( _In_opt_ HWND hWnd );

[DllImport( "user32.dll" )]
WINUSERAPI BOOL WINAPI SetForegroundWindow( _In_ HWND hWnd );

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI HWND WINAPI CreateWindowExW( _In_ DWORD dwExStyle,
										_In_opt_ LPCWSTR lpClassName,
										_In_opt_ LPCWSTR lpWindowName,
										_In_ DWORD dwStyle,
										_In_ int X,
										_In_ int Y,
										_In_ int nWidth,
										_In_ int nHeight,
										_In_opt_ HWND hWndParent,
										_In_opt_ HMENU hMenu,
										_In_opt_ HINSTANCE hInstance,
										_In_opt_ LPVOID lpParam );
#else
WINUSERAPI HWND WINAPI CreateWindowExA( _In_ DWORD dwExStyle,
										_In_opt_ LPCSTR lpClassName,
										_In_opt_ LPCSTR lpWindowName,
										_In_ DWORD dwStyle,
										_In_ int X,
										_In_ int Y,
										_In_ int nWidth,
										_In_ int nHeight,
										_In_opt_ HWND hWndParent,
										_In_opt_ HMENU hMenu,
										_In_opt_ HINSTANCE hInstance,
										_In_opt_ LPVOID lpParam );
#endif // !UNICODE

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI ATOM WINAPI RegisterClassExW( _In_ CONST WNDCLASSEXW * );
#else
WINUSERAPI ATOM WINAPI RegisterClassExA( _In_ CONST WNDCLASSEXA * );
#endif // !UNICODE

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI HCURSOR WINAPI LoadCursorW( _In_opt_ HINSTANCE hInstance, _In_ LPCWSTR lpCursorName );
#else
WINUSERAPI HCURSOR WINAPI LoadCursorA( _In_opt_ HINSTANCE hInstance, _In_ LPCSTR lpCursorName );
#endif // !UNICODE

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI HICON WINAPI LoadIconW( _In_opt_ HINSTANCE hInstance, _In_ LPCWSTR lpIconName );
#else
WINUSERAPI HICON WINAPI LoadIconA( _In_opt_ HINSTANCE hInstance, _In_ LPCSTR lpIconName );
#endif // !UNICODE

[DllImport( "user32.dll" )]
WINUSERAPI VOID WINAPI PostQuitMessage( _In_ int nExitCode );

[DllImport( "user32.dll" )]
WINUSERAPI BOOL WINAPI UnregisterClassA( _In_ LPCSTR lpClassName, _In_opt_ HINSTANCE hInstance );

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI LONG WINAPI ChangeDisplaySettingsW( _In_opt_ DEVMODEW* lpDevMode, _In_ DWORD dwFlags );
#else
WINUSERAPI LONG WINAPI ChangeDisplaySettingsA( _In_opt_ DEVMODEA* lpDevMode, _In_ DWORD dwFlags );
#endif // !UNICODE

[DllImport( "user32.dll" )]
WINUSERAPI int WINAPI ShowCursor( _In_ BOOL bShow );

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI
#ifndef _MAC
LRESULT WINAPI
#else
LRESULT CALLBACK
#endif
DefWindowProcW( _In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam );
#else
WINUSERAPI
#ifndef _MAC
LRESULT WINAPI
#else
LRESULT CALLBACK
#endif
DefWindowProcA( _In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam );
#endif // !UNICODE

[DllImport( "user32.dll" )]
#ifdef UNICODE
WINUSERAPI LRESULT WINAPI DispatchMessageW( _In_ CONST MSG *lpMsg );
#else
WINUSERAPI LRESULT WINAPI DispatchMessageA( _In_ CONST MSG *lpMsg );
#endif // !UNICODE

[DllImport( "Gdi32.dll" )]
WINGDIAPI HGDIOBJ WINAPI GetStockObject( _In_ int i );