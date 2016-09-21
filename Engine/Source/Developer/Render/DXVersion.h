#pragma once

#ifndef CHECK_DX_VERSION
#define CHECK_DX_VERSION		9
#endif

#if (CHECK_DX_VERSION == 9)
#include "D3D9Header.h"
#else
#include "D3D11Header.h"
#endif
