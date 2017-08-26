#pragma once

#include <memory>

class DevicePlatform
{
public:

	DevicePlatform();
	~DevicePlatform();

	virtual void	Init( HWND hWnd, bool screenMode, float screenWidth, float screenHeight ) = 0;
	virtual void	Release() = 0;
};

