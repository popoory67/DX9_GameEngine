#pragma once

#include <d3dx9.h>
#include "DevicePlatform.h"

using namespace std;

#define	D3D9_INSTANCE		D3D9::Get()
#define D3D9_DEVICE			D3D9::Get()->GetDevice()


class D3D9;

using D3D9Ptr		= shared_ptr<D3D9>;

class D3D9 : public DevicePlatform
{
public:

	virtual ~D3D9();

	/**
	 * Gets the singleton instance of the D3D class.
	 * @return the create device d3dx instance.
	 */
	static D3D9Ptr Get();

	LPDIRECT3DDEVICE9 GetDevice();

	LPDIRECT3DSURFACE9 UseBuildRenderView( bool isUsedRenderView );

	virtual void Init( HWND hWnd, bool screenMode, float screenWidth, float screenHeight );

	virtual void Release();

private:

	D3D9();

private:

	static D3D9Ptr			_instance;

	LPDIRECT3D9				_d3d			= nullptr;	// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9		_d3dDevice		= nullptr;	// the pointer to the device class
	LPDIRECT3DSURFACE9		_d3dSurface;

	D3DPRESENT_PARAMETERS	_d3dPP;

	float					_screenWidth	= 0;
	float					_screenHeight	= 0;

};