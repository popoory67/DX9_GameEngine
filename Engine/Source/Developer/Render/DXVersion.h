#pragma once

#define DX_9					9
#define DX_11					11

#ifndef CHECK_DX_VERSION
#define CHECK_DX_VERSION		DX_9
#endif

#if (CHECK_DX_VERSION == DX_9)
#include "D3D9Header.h"
#elif (CHECK_DX_VERSION == DX_11)
#include "D3D11Header.h"
#endif
