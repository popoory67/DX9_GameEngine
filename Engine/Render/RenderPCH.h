#pragma once

// Window screen : false, Full screen : true
#define SCREEN_MODE			false

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720

#include <Windows.h>
#include <WindowsX.h>

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <assert.h>
#include <iostream>

#include <memory>

#include <vector>
#include <map>
#include <string>
#include <functional>

using namespace std;

#include "RenderMacros.h" 


//#if (_D3DX_VERSION <= 9)
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")
//#else
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
//#endif


// GL
//#include <gl\glew.h>
//#include <GLFW\glfw3.h>
//#include <glm\glm.hpp>
//
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "glfw3dll.lib")
//
//using namespace glm;
