#pragma once

#include "RenderPCH.h"


class CreateDeviceD3DX //DLLEXPORT CreateDeviceD3DX
{
public:

	CreateDeviceD3DX();
	~CreateDeviceD3DX();

	/**
	 * Gets the singleton instance of the create device d3dx class.
	 * @return the create device d3dx instance.
	 */
	static CreateDeviceD3DX& Get();

	LPDIRECT3DDEVICE9 GetDevice()
	{
		return _d3dDevice;
	}

public:

	void Init(HWND hWnd);

	void Release();

private:

	void Create(HWND hWnd);

private:

	LPDIRECT3D9						_d3d;				// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9				_d3dDevice;			// the pointer to the device class
	D3DPRESENT_PARAMETERS			_d3dPP;
};


#define	D3DX_INSTANCE	CreateDeviceD3DX::Get()
#define D3DX_DEVICE		CreateDeviceD3DX::Get().GetDevice()