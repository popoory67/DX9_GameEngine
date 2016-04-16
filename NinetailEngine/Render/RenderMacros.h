
// DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define WINDOW_MODE					1
#define PLATFORM_DESKTOP			1

#define SCREEN_WIDTH				1024
#define SCREEN_HEIGHT				768

//#define DEBUG
//#define RELEASE

#define		SAFE_RELEASE(p) if (p != NULL) { p->Release(); p = NULL; }

#define		KEY_DOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define		KEY_UP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
