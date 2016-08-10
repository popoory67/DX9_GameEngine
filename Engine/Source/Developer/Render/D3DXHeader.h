#pragma once

// Version check
#define _D3DX_VERSION_9			9
#define _D3DX_VERSION_11		11

#ifndef _D3DX_VERSION
#define _D3DX_VERSION _D3DX_VERSION_9
#endif

#if (_D3DX_VERSION <= 9)
#include "D3D9Header.h"
#else
#include "D3D11Header.h"
#endif