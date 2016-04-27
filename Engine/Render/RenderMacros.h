
#define		WINDOW_MODE					1
#define		PLATFORM_DESKTOP			1

#define		SCREEN_WIDTH				1024
#define		SCREEN_HEIGHT				768

//#define	DEBUG
//#define	RELEASE

#define		KEY_DOWN(vk_code)	((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define		KEY_UP(vk_code)		((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


/**
 *	
 */
#define		SAFE_RELEASE(p) if (p != NULL) { p->Release(); p = NULL; }

/**
 *	utilize std::tr1::shared_ptr<class>
 */
#define		SHARED_PTR(name) ::tr1::shared_ptr<name>

/**
 *  simplify Get/Set function
 */
#define		SIMPLE_GET(return_type, func_name, get_value) return_type Get##func_name() { return get_value; }
#define		SIMPLE_SET(return_type, func_name, set_value) void Set##func_name(return_type tmp) { set_value = tmp; }

/**
 *  simplify DLL export and import definitions
 */
#define		DLLEXPORT __declspec(dllexport)
#define		DLLIMPORT __declspec(dllimport)