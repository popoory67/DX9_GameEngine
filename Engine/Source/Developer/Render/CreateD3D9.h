#pragma once

#include <memory>
#include <d3dx9.h>
#include "Util.h"

using namespace std;

#define	D3D9_INSTANCE	CreateD3D9::Get()
#define D3D9_DEVICE		CreateD3D9::Get()->GetDevice()


class CreateD3D9;

using D3D9Ptr = shared_ptr<CreateD3D9>; // CreateD3D9*;

class CreateD3D9
{
public:

	~CreateD3D9();

	/**
	 * Gets the singleton instance of the create device d3dx class.
	 * @return the create device d3dx instance.
	 */
	static D3D9Ptr Get();

	LPDIRECT3DDEVICE9 GetDevice();

	LPDIRECT3DSURFACE9 UseBuildRenderView( bool isUsedRenderView );

	void Init( HWND hWnd );

	void Clear();

private:

	CreateD3D9();

private:

	static D3D9Ptr _instance;

	LPDIRECT3D9 _d3d;					// the pointer to our Direct3D interface

	LPDIRECT3DDEVICE9 _d3dDevice;		// the pointer to the device class

	LPDIRECT3DSURFACE9 _d3dSurface;

	D3DPRESENT_PARAMETERS _d3dPP;
};