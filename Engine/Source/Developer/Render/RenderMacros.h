#pragma once

// utilize key input
#define KEY_DOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// for pointers allocated with new
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p) = nullptr; } }

// for arrays allocated with new []
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p) = nullptr; } }

// for use with COM pointers
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = nullptr; } }

#define MIN(x,y)				( (x)<(y)? (x) : (y) )
#define MAX(x,y)				( (x)>(y)? (x) : (y) )