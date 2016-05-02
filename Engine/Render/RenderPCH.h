#pragma once

#include <Windows.h>
#include <WindowsX.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <memory>

#include <vector>
#include <map>
#include <string>
#include <functional>

using namespace std;

#include "RenderMacros.h" 

// D3D9
#include <d3d9.h>
#include <d3dx9.h>
 
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib")

// D3D11
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
 
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
