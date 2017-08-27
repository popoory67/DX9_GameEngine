#pragma once

#include <memory>

class D3DXDevice
{
public:

	D3DXDevice();
	virtual ~D3DXDevice();

	virtual void	Init( HWND hWnd, bool screenMode, float screenWidth, float screenHeight ) = 0;
	virtual void	Release() = 0;
};

